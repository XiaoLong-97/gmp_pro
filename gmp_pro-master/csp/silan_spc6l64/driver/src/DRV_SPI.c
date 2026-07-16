#include "driver/inc/SPI.h"
#include "driver/inc/DMA.h"
#include "driver/inc/GPIO.h"

SPI_PARAM_s Spi0_S;

void SPI_Config(void)
{	
	Gpio_Af_Sel(DIGITAL,PA,4,5);//SPI0 NSS
	Gpio_Af_Sel(DIGITAL,PA,5,5);//SPI0 SCK
	Gpio_Af_Sel(DIGITAL,PA,6,5);//SPI0 MISO
	Gpio_Af_Sel(DIGITAL,PA,7,5);//SPI0 MOSI	
	
	SPI0->SPICTL0_b.SPC = 0;//0,选择全双工方式  1,选择半双工方式
//	SPI0->SPICTL0_b.BIDIROE = 0;//0,MOMI或SISO设置成输入  1,MOMI或SISO设置成输出
//	SPI0->SPICTL0_b.MODFEN = 0;//0,多主机方式冲突检测输入禁止，NSS做普通IO  1,多主机方式冲突检测输入使能
	
	SPI0->SPICTL0_b.DFF = 1;//0,8 位数据帧格式  1,16位
	SPI0->SPICTL0_b.LSBF = 0;//0,高位优先发送  1,低位优先发送
	SPI0->SPICTL0_b.MSTEN = 1;//0,工作在从机方式  1,工作在主机方式

	SPI0->SPICTL1_b.CPOL = 1;//Clock Polarity High
	SPI0->SPICTL1_b.CPHA = 0;//First edge to lock the data
	SPI0->SPICTL1_b.SPCR = 0x07;//4分频	

//	SPI0->SPICTL0_b.SPTIE = 1;//0,禁止SPTEF中断  1,允许SPTEF申请中断
	SPI0->SPICTL0_b.SPRIE = 1;//SPRF中断使能	
	SPI0->SPICTL0_b.SPIE = 1;//使能SPI模块
	
//	NVIC_ClearPendingIRQ(SPI0_IRQn);
//	NVIC_SetPriority(SPI0_IRQn,1);	
//	NVIC_EnableIRQ(SPI0_IRQn);	
}


void SPI0_IRQHandler(void)
{
	uint32_t temp8;

	temp8 = SPI0->SPIFLAG;
	
	if(SPI0->SPICTL0_b.SPRIE == 1)
	{
		if (temp8 & SPI0_SPIFLAG_SPRF_Msk)
		{
			Spi0_S.RevBuf[Spi0_S.RBReadIdx ++] = SPI0->SPIDAT;
		}
		
		if (temp8 & SPI0_SPIFLAG_RXOV_Msk)
		{
			SPI0->SPIFLAG_b.RXOV = 0x00;
		}
		
		if (temp8 & SPI0_SPIFLAG_WCOL_Msk)
		{
			SPI0->SPIFLAG_b.WCOL = 0x00;
		}
		
		if (temp8 & SPI0_SPIFLAG_MODF_Msk)
		{
			SPI0->SPIFLAG_b.MODF = 0x00;
		}
	}
	
//	if(SPI0->SPICTL0_b.SPTIE == 1)
//	{
//		if(Spi0_S.SBWriteIdx <= 15)
//			SPI0->SPIDAT = D_data0[Spi0_S.SBWriteIdx ++];
//		else
//			SPI0->SPICTL0_b.SPTIE = 0;
//	}
	
}




