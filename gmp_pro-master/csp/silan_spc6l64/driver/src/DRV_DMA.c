
#include "driver/inc/DMA.h"

uint8_t *SCR_pt1;
volatile uint8_t D_data0[100];
volatile uint8_t D_data1[100];
uint8_t Tx_num, Rx_num;
uint16_t Rx_Data[20];

extern volatile uint32_t *SCR_pt;

const uint8_t CODE_TAB1[] = {
    0x55, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12,
    0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
    0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
    0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b,
    0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e,
    0x5f, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71,
    0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x80, 0x81, 0x82, 0x83, 0x84,
    0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
    0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa,
    0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd,
    0xbe, 0xbf, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0,
    0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf, 0xe0, 0xe1, 0xe2, 0xe3,
    0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef, 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6,
    0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff};

/********************************
DMA test
DMA	register read and write test
********************************/
void Ram0_ini(void)
{
    uint16_t i;

    SCR_pt1 = (uint8_t *)D_data0;
    for (i = 0; i < 100; i++)
    {
        *SCR_pt1 = CODE_TAB1[(i & 0xff)];
        SCR_pt1++;
    }
}
// 拷贝四份code tab到Ddata中

/********************************
DMA test
DMA	register read and write test
********************************/
void Ram1_Clear(void)
{
    uint16_t i;

    SCR_pt1 = (uint8_t *)D_data1;
    for (i = 0; i < 100; i++)
    {
        *SCR_pt1 = 0x00ul;
        SCR_pt1++;
    }
}

/********************************
DMA test
DMA	register read and write test
********************************/
void DMA_Data_Struct_Clear(void)
{
    uint16_t i;

    SCR_pt1 = (uint8_t *)DMA_CH0;
    for (i = 0; i < 0x180; i++)
    {
        *SCR_pt1 = 0x00ul;
        SCR_pt1++;
    }
}

void DMA_Config(DMA_DATA_Type *DMA_CHx, uint8_t chx, uint8_t req0_sel)
{
    uint8_t i = 0;
    switch (req0_sel)
    {
    case REQ_SEL_UART0_TX: {
        UART0->UARTCTL_b.TXDMAE = 0x01;
        DMA_CHx->DESTION = &UART0->UARTDATA;
        break;
    }
    case REQ_SEL_UART0_RX: {
        UART0->UARTCTL_b.RXDMAE = 0x01;
        DMA_CHx->SOURCE = &UART0->UARTDATA;
        break;
    }
    case REQ_SEL_UART1_TX: {
        UART1->UARTCTL_b.TXDMAE = 0x01;
        DMA_CHx->DESTION = &UART1->UARTDATA;
        break;
    }
    case REQ_SEL_UART1_RX: {
        UART1->UARTCTL_b.RXDMAE = 0x01;
        DMA_CHx->SOURCE = &UART1->UARTDATA;
        break;
    }
        //		case REQ_SEL_UART2_TX:{UART2->UARTCTL_b.TXDMAE=0x01;DMA_CHx->DESTION = &UART2->UARTDATA;break;}
        //		case REQ_SEL_UART2_RX:{UART2->UARTCTL_b.RXDMAE=0x01;DMA_CHx->SOURCE  = &UART2->UARTDATA;break;}
    case REQ_SEL_SPI0_TX: {
        SPI0->SPICTL0_b.TXDMAEN = 0x01;
        DMA_CHx->DESTION = &SPI0->SPIDAT;
        break;
    }
    case REQ_SEL_SPI0_RX: {
        SPI0->SPICTL0_b.RXDMAEN = 0x01;
        DMA_CHx->SOURCE = &SPI0->SPIDAT;
        break;
    }
    case REQ_SEL_ERU0: {
        DMA_CHx->SOURCE = (uint32_t *)&ADC->ADCRESULT[0];
        break;
    }
    case REQ_SEL_ERU1: {
        break;
    }
    case REQ_SEL_ERU2: {
        break;
    }
    case REQ_SEL_ERU3: {
        break;
    }
    default: {
        break;
    }
    }

    if (req0_sel % 2 != 0 || req0_sel >= REQ_SEL_ERU0)
    {
        DMA_CHx->DESTION = (uint32_t *)D_data1;
        DMA_CHx->CTL.SRC_INC = 0x3; // 源地址按字节自增
        DMA_CHx->CTL.DST_INC = 0x0; // 目标地址固定
    }
    else
    {
        DMA_CHx->SOURCE = (uint32_t *)D_data0;
        DMA_CHx->CTL.SRC_INC = 0x0; // 源地址按字节自增
        DMA_CHx->CTL.DST_INC = 0x3; // 目标地址固定
    }

    DMA_CHx->CTL.CYCLE_CTRL = 1;    // 基本模式
    DMA_CHx->CTL.NEXT_USEBURST = 0; //
    DMA_CHx->CTL.N_MINUS_1 = 0x0f;  // 16次传输
    DMA_CHx->CTL.R_POWER = 0x00;    // 完成1次DMA传输后仲裁
    DMA_CHx->CTL.CIRC = 0;          //
    DMA_CHx->CTL.DATA_SIZE = 0;     //

    DMA->BASEPTR = (uint32_t)DMA_CHx; // DMA通道控制基址指针
    DMA->DONE = 0x0;
    DMA->CFGERR = 0x0;
    DMA->BUSERR = 0x0;
    DMA->CFG = 0x01; // DMA使能

    for (i = 0; !(chx & 0x01); i++, chx >>= 1)
        ;

    DMA->CTRL[i] = 0x00;
    DMA->CTRL_b[i].REQ0MASK = 0;       // 通道请求信号有效
    DMA->CTRL_b[i].REQ0SEL = req0_sel; // DMA通道请求1硬件触发源选择位
    DMA->CTRL_b[i].REQ1MASK = 1;       // 通道请求信号被屏蔽

    //	DMA->CTRL_b[i].REQ1MASK = 0;
    //	DMA->CTRL_b[i].REQ1SEL = req0_sel;
    //	DMA->CTRL_b[i].REQ0MASK = 1;

    DMA->CTRL_b[i].BURST = 0;   // 0：响应req和sreq；1：响应req
    DMA->CTRL_b[i].DONEIEN = 1; // DMA通道完成中断使能
    DMA->CTRL_b[i].ENABLE = 1;  // 通道使能

    NVIC_ClearPendingIRQ(DMA_IRQn);
    NVIC_SetPriority(DMA_IRQn, 0);
    NVIC_EnableIRQ(DMA_IRQn);
}

void DMA_ERU_Config(DMA_DATA_Type *DMA_CHx, uint8_t chx, uint8_t req0_sel)
{
    uint8_t i = 0;

    DMA_CHx->SOURCE = (uint32_t *)&ADC->ADCRESULT[0];
    DMA_CHx->DESTION = (uint32_t *)Rx_Data;

    DMA_CHx->CTL.DATA_SIZE = 1; // 源数据的宽度
    DMA_CHx->CTL.SRC_INC = 0x2; // 源地址按字自增
    DMA_CHx->CTL.DST_INC = 0x1; // 目标地址按字节自增

    DMA_CHx->CTL.CYCLE_CTRL = 1;    // 基本模式
    DMA_CHx->CTL.NEXT_USEBURST = 0; //
    DMA_CHx->CTL.N_MINUS_1 = 0x0f;  // 16次传输
    DMA_CHx->CTL.R_POWER = 0x00;    // 完成1次DMA传输后仲裁
    DMA_CHx->CTL.CIRC = 0;          //

    DMA->BASEPTR = (uint32_t)DMA_CHx; // DMA通道控制基址指针
    DMA->DONE = 0x0;
    DMA->CFGERR = 0x0;
    DMA->BUSERR = 0x0;
    DMA->CFG = 0x01; // DMA使能

    for (i = 0; !(chx & 0x01); i++, chx >>= 1)
        ;

    DMA->CTRL[i] = 0x00;
    DMA->CTRL_b[i].REQ0MASK = 0;       // 通道请求信号有效
    DMA->CTRL_b[i].REQ0SEL = req0_sel; // DMA通道请求1硬件触发源选择位
    DMA->CTRL_b[i].REQ1MASK = 1;       // 通道请求信号被屏蔽

    //	DMA->CTRL_b[i].REQ1MASK = 0;
    //	DMA->CTRL_b[i].REQ1SEL = req0_sel;
    //	DMA->CTRL_b[i].REQ0MASK = 1;

    DMA->CTRL_b[i].BURST = 0;   // 0：响应req和sreq；1：响应req
    DMA->CTRL_b[i].DONEIEN = 1; // DMA通道完成中断使能
    DMA->CTRL_b[i].ENABLE = 1;  // 通道使能

    NVIC_ClearPendingIRQ(DMA_IRQn);
    NVIC_SetPriority(DMA_IRQn, 0);
    NVIC_EnableIRQ(DMA_IRQn);
}

/********************************
DMA Interrupt
********************************/
void DMA_IRQHandler(void)
{
    if (DMA->DONE)
    {
        if (DMA->DONE & DMA_CTL_CH0)
        {
            DMA->DONE = DMA_CTL_CH0;
            while ((DMA->DONE & DMA_CTL_CH0) != 0x00ul)
                ;
        }

        if (DMA->DONE & DMA_CTL_CH1)
        {
            DMA->DONE = DMA_CTL_CH1;
            while ((DMA->DONE & DMA_CTL_CH1) != 0x00ul)
                ;
        }

        if (DMA->DONE & DMA_CTL_CH2)
        {
            DMA->DONE = DMA_CTL_CH1;
            while ((DMA->DONE & DMA_CTL_CH1) != 0x00ul)
                ;
        }

        if (DMA->DONE & DMA_CTL_CH3)
        {
            DMA->DONE = DMA_CTL_CH1;
            while ((DMA->DONE & DMA_CTL_CH1) != 0x00ul)
                ;
        }

        if (DMA->DONE & DMA_CTL_CH4)
        {
            DMA->DONE = DMA_CTL_CH1;
            while ((DMA->DONE & DMA_CTL_CH1) != 0x00ul)
                ;
        }

        if (DMA->DONE & DMA_CTL_CH5)
        {
            DMA->DONE = DMA_CTL_CH5;
            while ((DMA->DONE & DMA_CTL_CH5) != 0x00ul)
                ;
        }
    }

    if (DMA->CFGERR)
    {
        if (DMA->CFGERR & DMA_CTL_CH0)
        {
            DMA->CFGERR = DMA_CTL_CH0;
            while ((DMA->CFGERR & DMA_CTL_CH0) != 0x00ul)
                ;
        }

        if (DMA->CFGERR & DMA_CTL_CH1)
        {
            DMA->CFGERR = DMA_CTL_CH1;
            while ((DMA->CFGERR & DMA_CTL_CH1) != 0x00ul)
                ;
        }

        if (DMA->CFGERR & DMA_CTL_CH2)
        {
            DMA->CFGERR = DMA_CTL_CH2;
            while ((DMA->CFGERR & DMA_CTL_CH2) != 0x00ul)
                ;
        }

        if (DMA->CFGERR & DMA_CTL_CH3)
        {
            DMA->CFGERR = DMA_CTL_CH3;
            while ((DMA->CFGERR & DMA_CTL_CH3) != 0x00ul)
                ;
        }

        if (DMA->CFGERR & DMA_CTL_CH4)
        {
            DMA->CFGERR = DMA_CTL_CH4;
            while ((DMA->CFGERR & DMA_CTL_CH4) != 0x00ul)
                ;
        }

        if (DMA->CFGERR & DMA_CTL_CH5)
        {
            DMA->CFGERR = DMA_CTL_CH5;
            while ((DMA->CFGERR & DMA_CTL_CH5) != 0x00ul)
                ;
        }
    }
}
