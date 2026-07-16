/**
 * @file udp_svr.hpp
 * @author Javnson (javnson@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2024-09-30
 * 
 * @copyright Copyright GMP(c) 2024
 * 
 */

// This header is a windows UDP controller simulate server.
// All the application include this server should compiled as Windows X86 Application.


#ifndef _FILE_UDP_SERVER_HPP_
#define _FILE_UDP_SERVER_HPP_

//////////////////////////////////////////////////////////////////////////
// �����ⲿ�����ݱ��뵽XML�У������õ��������ڱ���֮���޸ġ�

// Simulation settings
#ifndef MAX_ITERATION_LOOPS
#define MAX_ITERATION_LOOPS ((100 * 1000))
#endif // MAX_ITERATION_LOOPS

// recv timeout, unit ms
// 20 s default
#ifndef MAX_RECV_TIMEOUT
#define MAX_RECV_TIMEOUT ((20 * 1000))
#endif // MAX_RECV_TIMEOUT

// define udp target IPv4 Address
#ifndef TARGET_ADDR
#define TARGET_ADDR "127.0.0.1"
#endif // TARGET_ADDR

// default command port
#ifndef CMD_PORT
#define CMD_PORT 10033
#endif // CMD_PORT

// default transmit port
#ifndef SEND_PORT
#define SEND_PORT 10034
#endif // SEND_PORT

// default receive port
#ifndef RECV_PORT
#define RECV_PORT 10035
#endif // RECV_PORT


// period communication package size
// Here're the default parameters
// one double parameters only.
#ifndef RECV_BUFFER_LENGTH
#define RECV_BUFFER_LENGTH 8
#endif // RECV_BUFFER_LENGTH

#ifndef SEND_BUFFER_LENGTH
#define SEND_BUFFER_LENGTH 8
#endif // SEND_BUFFER_LENGTH


typedef struct _tag_upd_svr_obj
{
	void* recv_buf;
	size_t recv_buf_len;

	void* send_buf;
	size_t send_buf_len;

	uint64_t recv_bytes;
	uint32_t recv_cnt;

	uint64_t send_bytes;
	uint32_t send_cnt;
}upd_svr_obj_t;


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	// public functions
	int periodic_transmit_routine(upd_svr_obj_t* svr_obj);
	int periodic_recv_routine(upd_svr_obj_t* svr_obj);
	void release_udp_server();
	int init_udp_server();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _FILE_UDP_SERVER_HPP_
