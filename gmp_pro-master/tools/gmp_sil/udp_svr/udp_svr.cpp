/**
 * @file udp_svr.cpp
 * @author Javnson (javnson@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2024-09-30
 * 
 * @copyright Copyright GMP(c) 2024
 * 
 */
 
// GMP support
#include <core/gmp_core.hpp>

// UDP server struct definition 
#include <core/util/udp_svr/udp_svr.hpp>

// necessary language support
#include <iostream>
#include <stdio.h>

using std::cout;


#define ENABLE_DEBUG_INFORMATION

// WinSock support
// This header will be included by CSP.
//#include <winsock2.h>

// WinSock lib
#pragma comment(lib,"ws2_32.lib") // Winsock Library
#pragma warning(disable:4996) 

//////////////////////////////////////////////////////////////////////////
// global variables

// WinSock objects
WSADATA ws;

// RECV timeout, unit ms
DWORD timeout = MAX_RECV_TIMEOUT; 

// Simulation max iteration
constexpr size_t max_iteration = MAX_ITERATION_LOOPS;


//////////////////////////////////////////////////////////////////////////
// Here are the 3 necessary sockets 
// send: periodically transmit upstream data
// recv: periodically receive downstream data
// cmd : rx/tx commands
SOCKET send_socket = SOCKET_ERROR;
sockaddr_in send_hints;

SOCKET recv_socket = SOCKET_ERROR;
sockaddr_in recv_hints;

SOCKET cmd_socket = SOCKET_ERROR;
sockaddr_in cmd_hints;


int init_udp_server()
{
	// return value register
	int main_ret = 0;


	cout << "[INFO] report data pack length, receive: " << RECV_BUFFER_LENGTH
		<< " byte(s), transmit: " << SEND_BUFFER_LENGTH << " bytes(s)." << std::endl;
	
	// step I: init WinSock
	if (WSAStartup(MAKEWORD(2, 2), &ws) != 0) {
		cout << "Meet ERROR when WSAStartup() invoke, Error code: " << WSAGetLastError() << std::endl;
		main_ret = 1;
		goto cleanup_label;
	}
	cout << "[INFO] WSA API init done." << std::endl;

	//////////////////////////////////////////////////////////////////////////
	// step II.1: create socket for command
	cmd_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (cmd_socket == SOCKET_ERROR)
	{
		cout << "Meet ERROR when socket() invoke, Error code: " << WSAGetLastError() << std::endl;
		main_ret = 1;
		goto cleanup_label;
	}

	// setup address structure
	memset((char*)&cmd_hints, 0, sizeof(cmd_hints));
	cmd_hints.sin_family = AF_INET;
	cmd_hints.sin_port = htons(CMD_PORT);
	cmd_hints.sin_addr.S_un.S_addr = inet_addr(TARGET_ADDR);

	// bind to target
	if (bind(cmd_socket, (sockaddr*)&cmd_hints, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		cout << "Meet ERROR when bind() invoke, Error code: " << WSAGetLastError() << std::endl;
		main_ret = 1;
		goto cleanup_label;
	}

	cout << "[INFO] Socket has created & connected to target, " << TARGET_ADDR << ":" << CMD_PORT << " for command data." << std::endl;

	//////////////////////////////////////////////////////////////////////////
	// step II.2: create socket for transmit
	send_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (send_socket == SOCKET_ERROR)
	{
		cout << "Meet ERROR when socket() invoke, Error code: " << WSAGetLastError() << std::endl;
		main_ret = 1;
		goto cleanup_label;
	}

	// setup address structure
	memset((char*)&send_hints, 0, sizeof(send_hints));
	send_hints.sin_family = AF_INET;
	send_hints.sin_port = htons(SEND_PORT);
	send_hints.sin_addr.S_un.S_addr = inet_addr(TARGET_ADDR);

	// connect to target
	if (connect(send_socket, (sockaddr*)&send_hints, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		cout << "Meet ERROR when connect() invoke, Error code: " << WSAGetLastError() << std::endl;
		main_ret = 1;
		goto cleanup_label;
	}

	cout << "[INFO] Socket has created & connected to target, " 
		 << TARGET_ADDR << ":" << SEND_PORT << " for control data transmitting." << std::endl;


	//////////////////////////////////////////////////////////////////////////
	// step II.3: create socket for receive
	recv_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (recv_socket == SOCKET_ERROR)
	{
		cout << "Meet ERROR when socket() invoke, Error code: " << WSAGetLastError() << std::endl;
		main_ret = 1;
		goto cleanup_label;
	}


	// setup address structure
	memset((char*)&recv_hints, 0, sizeof(recv_hints));
	recv_hints.sin_family = AF_INET;
	recv_hints.sin_port = htons(RECV_PORT);
	recv_hints.sin_addr.S_un.S_addr = inet_addr(TARGET_ADDR);

	// bind to target
	if (bind(recv_socket, (sockaddr*)&recv_hints, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		cout << "Meet ERROR when bind() invoke, Error code: " << WSAGetLastError() << std::endl;
		main_ret = 1;
		goto cleanup_label;
	}

	// Set Receive Block time limit
	if (setsockopt(recv_socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(DWORD)) == SOCKET_ERROR)
	{
		cout << "Meet ERROR when setsockopt() invoke, Error code: " << WSAGetLastError() << std::endl;
		goto cleanup_label;
	}

	cout << "[INFO] Socket has created & connected to target, " 
		 << TARGET_ADDR << ":" << RECV_PORT << " for control data receiving." << std::endl;

cleanup_label:
	if(main_ret != 0)
		release_udp_server();

	return main_ret;
}

void release_udp_server()
{
	// shutdown the connection
	shutdown(recv_socket, 0); // SEND
	shutdown(send_socket, 1); // RESEIVCE
	shutdown(cmd_socket, 2); // BOTH
	cout << "[INFO] Connection has shutdown." << std::endl;

	// close sockets
	closesocket(send_socket);
	closesocket(recv_socket);
	closesocket(cmd_socket);
	cout << "[INFO] Socket has released." << std::endl;

	// close WinSock API
	WSACleanup();
	cout << "[INFO] WSA has released." << std::endl;
}

int periodic_recv_routine(upd_svr_obj_t *svr_obj)
{
	// return value register
	int main_ret = 0;
	int len = sizeof(sockaddr);
	int wsa_ret;

	// Receive Routine
	wsa_ret = recvfrom(recv_socket,
		(char*)svr_obj->recv_buf, svr_obj->recv_buf_len, NULL,
		(sockaddr*)&recv_hints, &len);

	if (wsa_ret == 0) // connection has not form.
	{
		cout << "Connection not created." << std::endl;
	}
	else if (wsa_ret == SOCKET_ERROR)
	{
		int error_code = WSAGetLastError();

		// timeout
		if (error_code == 10060)
		{
			cout << "\n\n[INFO] receive process timeout, will exit. Error code : " << error_code << std::endl;
			main_ret = 1;
		}

		cout << "Meet ERROR when recvfrom() invoke, Error code : " << error_code << std::endl;
		main_ret = 1;
	}
	else
	{
		svr_obj->recv_cnt += 1;
		svr_obj->recv_bytes += wsa_ret;
	}

	//Sleep(5);

#ifdef ENABLE_DEBUG_INFORMATION
	printf("#");
#endif

	return main_ret;
}

int periodic_transmit_routine(upd_svr_obj_t* svr_obj)
{
	// return value register
	int main_ret = 0;
	int wsa_ret;

	wsa_ret = send(send_socket,
		(char*)svr_obj->send_buf, svr_obj->send_buf_len, NULL);

	if (wsa_ret == SOCKET_ERROR)
	{
		cout << "Meet ERROR when send() invoke, Error code : " << WSAGetLastError() << std::endl;
		main_ret = 1;
	}
	else
	{
		svr_obj->send_cnt += 1;
		svr_obj->send_bytes += wsa_ret;
	}

#ifdef ENABLE_DEBUG_INFORMATION
	printf(".");
#endif

	return main_ret;
}

