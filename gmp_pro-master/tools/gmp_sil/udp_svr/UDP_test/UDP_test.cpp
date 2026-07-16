/**
 * @file UDP_test.cpp
 * @author Javnson (javnson@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2024-09-30
 * 
 * @copyright Copyright GMP(c) 2024
 * 
 */

// UDP_test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//#include <windows.h>
#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <iphlpapi.h>

#include <stdio.h>

using std::cout;

#pragma comment(lib,"ws2_32.lib") // Winsock Library
#pragma warning(disable:4996) 

//////////////////////////////////////////////////////////////////////////
// 下面这段代码实现了UDP通信但是没有做数据校验。也没有实现跨平台。


//////////////////////////////////////////////////////////////////////////
// 相关配置信息用XML文件或者json文件保存起来，可以在编译之后修改端口和目标地址。

#define TARGET_ADDR "127.0.0.1"
#define BUFLEN 512

#define CMD_PORT 10033
#define SEND_PORT 10034
#define RECV_PORT 10035


#define RECV_BUFFER_LENGTH 8
#define SEND_BUFFER_LENGTH 8



int main()
{
    int main_ret = 0;
    int wsa_ret = 0;

    double a = 1.0;

    uint32_t total_bytes = 0;
    uint64_t recv_counter = 0;
    uint32_t recv_bytes = 0;
    uint64_t send_counter = 0;
    uint32_t send_bytes = 0;

    size_t MAX_ITERATION = 100000;

    BOOL debug_param = 1;
    DWORD timeout = 20 * 1000; // 20 s

    WSADATA ws;

    SOCKET send_socket = SOCKET_ERROR;
    sockaddr_in send_hints;

    SOCKET recv_socket = SOCKET_ERROR;
    sockaddr_in recv_hints;

    SOCKET cmd_socket = SOCKET_ERROR;
    sockaddr_in cmd_hints;

    //	struct addrinfo send_hints;

    std::string message = "Hello World\r\n";

    double t = 0.0;
    double data = 0.0;

    std::cout << "Hello World!\n" << std::endl;
    std::cout << "[INFO] data pack length: " << sizeof(double) << std::endl;


    // init WinSock
    if (WSAStartup(MAKEWORD(2, 2), &ws) != 0) {
        cout << "Meet ERROR when WSAStartup() invoke, Error code: " << WSAGetLastError() << std::endl;
        main_ret = 1;
        goto cleanup_label;
    }

    cout << "[INFO] WSA API init done." << std::endl;

    //////////////////////////////////////////////////////////////////////////
    // create socket for command
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
    // create socket for send
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

    cout << "[INFO] Socket has created & connected to target, " << TARGET_ADDR << ":" << SEND_PORT << " for control data transmitting." << std::endl;


    //////////////////////////////////////////////////////////////////////////
    // create socket for recv
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

    // Enable Debug information
    if (setsockopt(recv_socket, SOL_SOCKET, SO_DEBUG, (char*)&debug_param, sizeof(BOOL)) == SOCKET_ERROR)
    {
        cout << "Meet ERROR when setsockopt() invoke, Error code: " << WSAGetLastError() << std::endl;
        goto cleanup_label;
    }


    //// listen for incoming connection request
    //if (listen(recv_socket, 2) == SOCKET_ERROR)
    //{
    //    cout << "Meet ERROR when listen() invoke, Error code: " << WSAGetLastError() << std::endl;
    //    main_ret = 1;
    //    goto cleanup_label;
    //}

    //// Create a SOCKET for accepting incoming requests.
    //SOCKET access_socket;
    //wprintf(L"Waiting for client to connect...\n");

    //// Accept the connection.
    //access_socket = accept(recv_socket, NULL, NULL);
    //if (access_socket == INVALID_SOCKET)
    //{
    //    cout << "Meet ERROR when accept() invoke, Error code: " << WSAGetLastError() << std::endl;
    //    main_ret = 1;
    //    goto cleanup_label;
    //}

    cout << "[INFO] Socket has created & connected to target, " << TARGET_ADDR << ":" << RECV_PORT << " for control data receiving." << std::endl;


 
    char recv_buf[8];
    memcpy(recv_buf, &a, 8);
    // wait until message is coming
    //do 
    //{
    //	// check message without remove message.
    //	wsa_ret = recv(recv_socket, (char*)recv_buf, 8, MSG_PEEK);
    //	Sleep(100);
    //} while (wsa_ret!=0);

    for (size_t i = 0; i < MAX_ITERATION; ++i)
    {

        memcpy(recv_buf, &a, 8);

        // Send Routine
        //if (send(send_socket, message.c_str(), message.length(), 0) == SOCKET_ERROR)
        wsa_ret = send(send_socket, 
            (char*)recv_buf, SEND_BUFFER_LENGTH, 0);
        if (wsa_ret == SOCKET_ERROR)
        {
            cout << "Meet ERROR when send() invoke, Error code : " << WSAGetLastError() << std::endl;
            main_ret = 1;
            goto cleanup_label;
        }

        send_counter += 1;
        send_bytes += SEND_BUFFER_LENGTH;

        // Avoid continous operating        
        //Sleep(1);


        // Receive Routine
        int len = sizeof(sockaddr);
        // wsa_ret = recv(recv_socket, (char*)recv_buf, 8, NULL);
        wsa_ret = recvfrom(recv_socket, 
            (char*)recv_buf, RECV_BUFFER_LENGTH, NULL,
            (sockaddr*)&recv_hints, &len);

        if (wsa_ret == 0) // connection has not form.
        {
            cout << "Connection not created." << std::endl;
        }
        else if (wsa_ret == SOCKET_ERROR)
        {
            int error_code = WSAGetLastError();

            if (error_code == 10060)
            {
                cout << "\n\n[INFO] receive process timeout, will exit. Error code : " << error_code << std::endl;
                break;
            }

            cout << "Meet ERROR when recv() invoke, Error code : " << error_code << std::endl;
            main_ret = 1;
            goto cleanup_label;
        }

        recv_counter += 1;
        recv_bytes += RECV_BUFFER_LENGTH;
        memcpy(&a, recv_buf, 8);
        a = a + 1.0;

        cout << ".";
        
    }

    cout << "\n\n\n";

    cout << "[INFO] All process has done. " << recv_bytes << " bytes are received, " << send_bytes << " bytes are sent." << std::endl;
    cout << "[INFO] User-friendly view: receive: " << (double)recv_bytes / 1024 << " kB, transmit: " << (double)send_bytes / 1024 << " kB." << std::endl;
    cout << "[INFO] Receive Package(s): " << recv_counter << ", Send Packages(s): " << send_counter << std::endl;




    //for (int i = 0; i < 100; ++i)
    //{

    //	// Send Routine
    //	if (sendto(send_socket, message.c_str(), message.length(), 0, (sockaddr*)&send_hints, sizeof(sockaddr_in)) == SOCKET_ERROR)
    //	{
    //		cout << "Meet ERROR when socket() invoke, Error code : " << WSAGetLastError() << std::endl;
    //		main_ret = 1;
    //		goto cleanup_label;
    //	}

    //	Sleep(1);
    //}

    // shutdown the connection
    shutdown(recv_socket, SD_SEND);
    shutdown(send_socket, SD_SEND);
    shutdown(cmd_socket, SD_SEND);
    cout << "[INFO] Connection has shutdown." << std::endl;


cleanup_label:
    closesocket(send_socket);
    closesocket(recv_socket);
    closesocket(cmd_socket);
    cout << "[INFO] Socket has released." << std::endl;


    WSACleanup();
    cout << "[INFO] WSA has released." << std::endl;

    return main_ret;
}

