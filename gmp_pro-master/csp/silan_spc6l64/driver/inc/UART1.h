/*******************************************************************
    本文件定义了UART串口通讯的数据结构体以及各收、发函数
******************************************************************/

#ifndef __UART1_H__
#define __UART1_H__

#include "driver/inc/SLMCU.h"
#include "stdint.h"

#define UART_DEBUG         1
#define UART_SEND_BUF_SIZE 250
#define UART_REV_BUF_SIZE  100
#define UART_DATA_SIZE     50

#define UART_FUNC_RX       0
#define UART_FUNC_TX       1
#define UART_FUNC_DOUBLE   2

typedef struct
{
    uint8_t SendBuf[UART_SEND_BUF_SIZE]; // 串口发送缓存
    uint8_t RevBuf[UART_REV_BUF_SIZE];   // 串口接收缓存

    uint8_t RevData[UART_DATA_SIZE]; // 接收数据存放区

    uint16_t SBWriteIdx; // 发送缓存写入序号
    uint16_t SBReadIdx;  // 发送缓存读取序号
    uint16_t UnSendCnt;  // 未发送字节数

    uint8_t IntSendFlag; // 发送忙碌标志

    uint16_t RBWriteIdx; // 接收缓存写入序号
    uint16_t RBReadIdx;  // 接收缓存读取序号
    uint16_t UnRevCnt;   // 未读取字节数

    uint16_t RevStart; // 帧起始标志
    uint16_t RevLen;   // 接收地址计数器
    uint8_t RevOK;     // 一帧指令接收完毕标志
    uint8_t DataLen;   // 数据长度

} UART_PARAM_s;

extern UART_PARAM_s Uart0_S, Uart1_S, Uart2_S;
;

extern void UART_ISR_EN(UART0_Type *UARTx);
extern void UART_Model0_Config(UART0_Type *UARTx);
extern void UART_Model123_Config(UART0_Type *UARTx, uint8_t model, uint8_t dir);
extern void UART_Half_Duplex_Config(UART0_Type *UARTx, uint8_t dir);
extern void UartSendStart(UART_PARAM_s *v, UART0_Type *UARTx);
extern void UartSendByte(UART_PARAM_s *v, uint8_t byte);
extern void UartSendString(UART_PARAM_s *v, uint8_t *str);
extern void UartSentUint32ToASCII(UART_PARAM_s *v, uint32_t output);
extern void UartSentInt16ToASCII(UART_PARAM_s *v, uint16_t output);

#endif
