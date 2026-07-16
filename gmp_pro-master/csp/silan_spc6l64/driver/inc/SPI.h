#ifndef __SPI_H__
#define __SPI_H__

#include "driver/inc/SLMCU.h"          
#include "driver/inc/public.h"

#define SPI_SEND_BUF_SIZE	100
#define SPI_REV_BUF_SIZE	100

typedef struct
{
	uint8_t SendBuf[SPI_SEND_BUF_SIZE];
	uint8_t RevBuf[SPI_REV_BUF_SIZE];  

	uint16_t SBWriteIdx;        // 发送缓存写入序号
	uint16_t SBReadIdx;			// 发送缓存读取序号
	uint16_t UnSendCnt;			// 未发送字节数

	uint8_t IntSendFlag;        // 发送忙碌标志

	uint16_t RBWriteIdx;        // 接收缓存写入序号
	uint16_t RBReadIdx;			// 接收缓存读取序号
	uint16_t UnRevCnt;			// 未读取字节数

}SPI_PARAM_s;


extern SPI_PARAM_s Spi0_S;
void SPI_Config(void);

#endif


