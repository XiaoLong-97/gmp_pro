
#include "driver/inc/BT01.h"

uint8_t HallSection_R, HallSection_L;
uint32_t Hall_SectionTime[8] = {0};

void BT0_TimingMode_test()
{
    /***************BT00  1ms***********************/
    BT0->BT0MOD_b.T0M = 0;         // 定时计数模式
    BT0->BT0MOD_b.CT0 = 0;         // 定时模式
    BT0->BT0MOD_b.CKS0 = 0;        // 0:时钟源为系统时钟fclk  1:fLCLK
    BT0->BT0PSC_b.BT0PSC0 = 5;     // 64分频
    BT0->BT0DAT0_b.DATR0 = 0XFFFF; // 0XFFFF
    BT0->BT0CTL_b.INTE0 = 1;       // T0中断使能

    /***************BT01 330us***********************/
    BT0->BT0MOD_b.T1M = 0;         // 定时计数模式
    BT0->BT0MOD_b.CT1 = 0;         // 定时模式
    BT0->BT0MOD_b.CKS1 = 0;        // 0:时钟源为系统时钟fclk  1:fLCLK
    BT0->BT0PSC_b.BT0PSC1 = 5;     // 64分频
    BT0->BT0DAT1_b.DATR1 = 0XFFFF; // 0XFFFF
    BT0->BT0CTL_b.INTE1 = 1;       // T1中断使能

    BT0->BT0CFG_b.SHADOWEN = 0;

    /***************中断***********************/
    //	BT0->BT0CTL_b.TR0 = 1;//定时器0启动
}

void BT1_TimingMode_test()
{
    /***************BT10***********************/
    BT1->BT1MOD_b.T0M = 0;     // 定时计数模式
    BT1->BT1MOD_b.CT0 = 0;     // 定时模式
    BT1->BT1MOD_b.CKS0 = 0;    // 0:时钟源为系统时钟fclk  1:fLCLK
    BT1->BT1PSC_b.BT1PSC0 = 1; // 4分频
    BT1->BT1DAT0_b.DATR0 = 18000;
    BT1->BT1CTL_b.INTE0 = 1; // T0中断使能

    /***************BT11***********************/
    BT1->BT1MOD_b.T1M = 0;     // 定时计数模式
    BT1->BT1MOD_b.CT1 = 0;     // 定时模式
    BT1->BT1MOD_b.CKS1 = 0;    // 0:时钟源为系统时钟fclk  1:fLCLK
    BT1->BT1PSC_b.BT1PSC1 = 1; // 4分频
    BT1->BT1DAT1_b.DATR1 = 18000;
    BT1->BT1CTL_b.INTE1 = 1; // T1中断使能

/***************组合成32位定时器(对应中断BT00)***********************/
#if (1)
    BT1->BT1CFG_b.BT32EN = 1;
    BT1->BT1DAT0 = 180000; // 10ms
    //	BT1->BT1DAT0_b.DATR0 = (0XFFFF & 120000);//10ms
    //	BT1->BT1DAT1_b.DATR1 = (120000>>16);

#endif
/***************分成两个8位定时器***********************/
#if (0)
    BT1->BT1PSC_b.BT1PSC0 = 7; // 256分频(48M主频，187.5KHZ)
    BT1->BT1PSC_b.BT1PSC1 = 7; // 256分频
    BT1->BT1DAT0_b.DATR0 = 144;
    BT1->BT1DAT0_b.DATR0 |= (200 << 8);
    BT1->BT1DAT1_b.DATR1 = 72;
    BT1->BT1DAT1_b.DATR1 |= (36 << 8);

    BT1->BT1MOD_b.T0M = 3;    // 分成两个8位计数器
    BT1->BT1MOD_b.T1M = 3;    // 分成两个8位计数器
    BT1->BT1CTL_b.HINTE0 = 1; // T0高八位中断使能
    BT1->BT1CTL_b.HINTE1 = 1; // T1高八位中断使能

    BT1->BT1CTL_b.TRH0 = 1; // 定时器0高八位启动
    BT1->BT1CTL_b.TRH1 = 1; // 定时器1高八位启动
#endif

    /***************中断***********************/
    BT1->BT1CTL_b.TR0 = 1;
    BT1->BT1CTL_b.TR1 = 1;

    NVIC_ClearPendingIRQ(BT10_IRQn);
    NVIC_SetPriority(BT10_IRQn, 0);
    NVIC_EnableIRQ(BT10_IRQn); // 使能BT00_IRQn中断

    NVIC_ClearPendingIRQ(BT11_IRQn);
    NVIC_SetPriority(BT11_IRQn, 0);
    NVIC_EnableIRQ(BT11_IRQn); // 使能BT01_IRQn中断
}

void BT0_CountMode_test()
{
    /*******计数值为两次中断之间的脉冲个数************/
    /***************BT00***********************/
    //	EXINT_Config(0,EXINT_PINSEL_PA05,EXINT_DIR0_INTNON,EXINT_DIV(0), EXINT_PSC(15));
    //	EXINT->CFG_b[0].PINSEL = 5;//选择PA5
    //	EXINT->CFG_b[0].FILTA = 0;//关闭模拟滤波
    //	EXINT->CFG_b[0].DIV = 0;//数字滤波时钟分频
    //	EXINT->CFG_b[0].PSC = 0;//数字滤波窗口

    BT0->BT0MOD_b.T0M = 0;      // 定时计数模式
    BT0->BT0MOD_b.CT0 = 1;      // 计数模式
    BT0->BT0CFG_b.EDGESEL0 = 1; // 0:下降沿触发有效 1:上升沿触发有效

    BT0->BT0DAT0_b.DATR0 = 10;
    BT0->BT0CTL_b.INTE0 = 1; // T0中断使能

    /***************BT01***********************/
    //	EXINT_Config(1,EXINT_PINSEL_PA06,EXINT_DIR0_INTNON,EXINT_DIV(0), EXINT_PSC(15));
    //	EXINT->CFG_b[1].PINSEL = 6;//选择PA6
    //	EXINT->CFG_b[1].FILTA = 0;//关闭模拟滤波
    //	EXINT->CFG_b[1].DIV = 0;//数字滤波时钟分频
    //	EXINT->CFG_b[1].PSC = 0;//数字滤波窗口

    BT0->BT0MOD_b.T1M = 0;      // 定时计数模式
    BT0->BT0MOD_b.CT1 = 1;      // 计数模式
    BT0->BT0CFG_b.EDGESEL1 = 0; // 0:下降沿触发有效 1:上升沿触发有效

    BT0->BT0DAT1_b.DATR1 = 7;
    BT0->BT0CTL_b.INTE1 = 1; // T1中断使能

    /***************中断***********************/
    BT0->BT0CTL_b.TR0 = 1;
    BT0->BT0CTL_b.TR1 = 1;
    NVIC_ClearPendingIRQ(BT00_IRQn);
    NVIC_SetPriority(BT00_IRQn, 0);
    NVIC_EnableIRQ(BT00_IRQn); // 使能BT00_IRQn中断

    NVIC_ClearPendingIRQ(BT01_IRQn);
    NVIC_SetPriority(BT01_IRQn, 0);
    NVIC_EnableIRQ(BT01_IRQn); // 使能BT01_IRQn中断
}

void BT1_CountMode_test()
{
    /***************BT10***********************/
    //	EXINT_Config(2,EXINT_PINSEL_PA05,EXINT_DIR0_INTNON,EXINT_DIV(0), EXINT_PSC(15));
    //	EXINT->CFG_b[2].PINSEL = 5;//选择PA5
    //	EXINT->CFG_b[2].FILTA = 0;//关闭模拟滤波
    //	EXINT->CFG_b[2].DIV = 0;//数字滤波时钟分频
    //	EXINT->CFG_b[2].PSC = 0;//数字滤波窗口

    BT1->BT1MOD_b.T0M = 0;      // 定时计数模式
    BT1->BT1MOD_b.CT0 = 1;      // 计数模式
    BT1->BT1CFG_b.EDGESEL0 = 1; // 0:下降沿触发有效 1:上升沿触发有效

    BT1->BT1DAT0_b.DATR0 = 8;
    BT1->BT1CTL_b.INTE0 = 1; // T1中断使能

    /***************BT11***********************/
    //	EXINT_Config(3,EXINT_PINSEL_PA06,EXINT_DIR0_INTNON,EXINT_DIV(0), EXINT_PSC(15));
    //	EXINT->CFG_b[3].PINSEL = 6;//选择PA6
    //	EXINT->CFG_b[3].FILTA = 0;//关闭模拟滤波
    //	EXINT->CFG_b[3].DIV = 0;//数字滤波时钟分频
    //	EXINT->CFG_b[3].PSC = 0;//数字滤波窗口

    BT1->BT1MOD_b.T1M = 0;      // 定时计数模式
    BT1->BT1MOD_b.CT1 = 1;      // 计数模式
    BT1->BT1CFG_b.EDGESEL1 = 0; // 0:下降沿触发有效 1:上升沿触发有效

    BT1->BT1DAT1_b.DATR1 = 10;
    BT1->BT1CTL_b.INTE1 = 1; // T1中断使能

    /***************中断***********************/
    BT1->BT1CTL_b.TR0 = 1;
    BT1->BT1CTL_b.TR1 = 1;
    NVIC_ClearPendingIRQ(BT10_IRQn);
    NVIC_SetPriority(BT10_IRQn, 0);
    NVIC_EnableIRQ(BT10_IRQn); // 使能BT00_IRQn中断

    NVIC_ClearPendingIRQ(BT11_IRQn);
    NVIC_SetPriority(BT11_IRQn, 0);
    NVIC_EnableIRQ(BT11_IRQn); // 使能BT01_IRQn中断
}

void BT0_capture1_test(void)
{
/***************BT00***********************/
#if (1)
    EXINT_Config(0, EXINT_PINSEL_PA05, EXINT_DIR0_INTNON, EXINT_DIV(0), EXINT_PSC(15));

    BT0->BT0MOD_b.CKS0 = 0;    // 0:时钟源为系统时钟fclk  1:fLCLK
    BT0->BT0PSC_b.BT0PSC0 = 0; // 2分频
    BT0->BT0MOD_b.T0M = 1;     // 1,周期  2,高低电平
    BT0->BT0MOD_b.CT0 = 0;     // 定时或捕获模式

    BT0->BT0MOD_b.CAPEN0 = 1; // 使能捕获0

    BT0->BT0CTL_b.INTE0 = 1;    // T0中断使能
    BT0->BT0CTL_b.OVFINTE0 = 1; // 计数溢出中断使能

    BT0->BT0CFG_b.DOUEDGE0 = 0;  // 0,捕获电平  1,捕获占空比和周期
    BT0->BT0CFG_b.LEVELSEL0 = 1; // 0,捕获低电平  1,捕获高电平
#endif
/***************BT01***********************/
#if (0)
    EXINT_Config(1, EXINT_PINSEL_PA06, EXINT_DIR0_INTNON, EXINT_DIV(0), EXINT_PSC(15));

    BT0->BT0MOD_b.CKS1 = 0;    // 0:时钟源为系统时钟fclk  1:fLCLK
    BT0->BT0PSC_b.BT0PSC1 = 0; // 2分频
    BT0->BT0MOD_b.T1M = 1;     // 1,周期  2,高低电平
    BT0->BT0MOD_b.CT1 = 0;     // 定时或捕获模式
    BT0->BT0PSC_b.BT0PSC2 = 0; // 定时器T1 FLCLK预分频
    BT0->BT0MOD_b.CAPS1 = 0;   // 0:选择为外部输入TI1 1:FLCLK

    BT0->BT0MOD_b.CAPEN1 = 1; // 使能捕获1

    BT0->BT0CTL_b.INTE1 = 1; // T0中断使能
    BT0->BT0CTL_b.OVFE1 = 1; // 计数溢出中断使能

    BT0->BT0CFG_b.DOUEDGE1 = 0;  // 0,捕获电平  1,捕获占空比和周期
    BT0->BT0CFG_b.LEVELSEL1 = 1; // 0,捕获低电平  1,捕获高电平
#endif

/***************组合成32位定时器(对应中断BT00)***********************/
#if (0)
    BT0->BT0CFG_b.BT32EN = 1;
#endif
    /***************中断***********************/
    BT0->BT0CTL_b.TR0 = 1;
    BT0->BT0CTL_b.TR1 = 1;

    NVIC_ClearPendingIRQ(BT00_IRQn);
    NVIC_SetPriority(BT00_IRQn, 0);
    NVIC_EnableIRQ(BT00_IRQn); // 使能BT00_IRQn中断

    NVIC_ClearPendingIRQ(BT01_IRQn);
    NVIC_SetPriority(BT01_IRQn, 0);
    NVIC_EnableIRQ(BT01_IRQn); // 使能BT01_IRQn中断
}

void BT1_capture1_test(void)
{
/***************BT10***********************/
#if (0)
    EXINT_Config(2, EXINT_PINSEL_PA05, EXINT_DIR0_INTNON, EXINT_DIV(0), EXINT_PSC(15));

    BT1->BT1MOD_b.CKS0 = 0;    // 0:时钟源为系统时钟fclk  1:fLCLK
    BT1->BT1PSC_b.BT1PSC0 = 0; // 2分频
    BT1->BT1MOD_b.T0M = 1;     // 1,周期  2,高低电平
    BT1->BT1MOD_b.CT0 = 0;     // 定时或捕获模式

    BT1->BT1MOD_b.CAPEN0 = 1; // 使能捕获0

    BT1->BT1CTL_b.INTE0 = 1; // T0中断使能
    BT1->BT1CTL_b.OVFE0 = 1; // 计数溢出中断使能

    BT1->BT1CFG_b.DOUEDGE0 = 1;  // 0,捕获电平  1,捕获占空比和周期
    BT1->BT1CFG_b.LEVELSEL0 = 1; // 0,捕获低电平  1,捕获高电平
#endif
/***************BT11***********************/
#if (0)
    EXINT_Config(3, EXINT_PINSEL_PA06, EXINT_DIR0_INTNON, EXINT_DIV(0), EXINT_PSC(15));

    BT1->BT1MOD_b.CKS1 = 0;    // 0:时钟源为系统时钟fclk  1:fLCLK
    BT1->BT1PSC_b.BT1PSC1 = 0; // 2分频
    BT1->BT1MOD_b.T1M = 1;     // 1,周期  2,高低电平
    BT1->BT1MOD_b.CT1 = 0;     // 定时或捕获模式
    BT1->BT1PSC_b.BT1PSC2 = 0; // 定时器T1 FLCLK预分频
    BT1->BT1MOD_b.CAPS1 = 0;   // 0:选择为外部输入TI1 1:FLCLK

    BT1->BT1MOD_b.CAPEN1 = 1; // 使能捕获1

    BT1->BT1CTL_b.INTE1 = 1; // T0中断使能
    BT1->BT1CTL_b.OVFE1 = 1; // 计数溢出中断使能

    BT1->BT1CFG_b.DOUEDGE1 = 1;  // 0,捕获电平  1,捕获占空比和周期
    BT1->BT1CFG_b.LEVELSEL1 = 1; // 0,捕获低电平  1,捕获高电平
#endif

/***************组合成32位定时器(对应中断BT10)***********************/
#if (0)
    BT1->BT1CFG_b.BT32EN = 1;
#endif
    /***************中断***********************/
    BT1->BT1CTL_b.TR0 = 1;
    BT1->BT1CTL_b.TR1 = 1;

    NVIC_ClearPendingIRQ(BT10_IRQn);
    NVIC_SetPriority(BT10_IRQn, 0);
    NVIC_EnableIRQ(BT10_IRQn); // 使能BT10_IRQn中断

    NVIC_ClearPendingIRQ(BT11_IRQn);
    NVIC_SetPriority(BT11_IRQn, 0);
    NVIC_EnableIRQ(BT11_IRQn); // 使能BT11_IRQn中断
}

void BT0_capture_test()
{
/***************BT00***********************/
#if (1)
    EXINT_Config(0, EXINT_PINSEL_PA05, EXINT_DIR0_INTNON, EXINT_DIV(0), EXINT_PSC(15));

    BT0->BT0MOD_b.CKS0 = 0;    // 0:时钟源为系统时钟fclk  1:fLCLK
    BT0->BT0PSC_b.BT0PSC0 = 0; // 2分频
    BT0->BT0MOD_b.T0M = 2;     // 捕获模式2
    BT0->BT0MOD_b.CT0 = 0;     // 定时或捕获模式

    BT0->BT0MOD_b.CAPEN0 = 1; // 使能捕获0

    BT0->BT0CTL_b.RINTE0 = 1;   // 上升沿中断使能
    BT0->BT0CTL_b.FINTE0 = 1;   // 下降沿中断使能
    BT0->BT0CTL_b.OVFINTE0 = 1; // 计数溢出中断使能

    BT0->BT0CFG_b.DOUEDGE0 = 1; // 0,捕获电平  1,捕获占空比和周期

#endif
/***************BT01***********************/
#if (0)
    EXINT_Config(1, EXINT_PINSEL_PA06, EXINT_DIR0_INTNON, EXINT_DIV(0), EXINT_PSC(15));

    BT0->BT0MOD_b.CKS1 = 0;    // 0:时钟源为系统时钟fclk  1:fLCLK
    BT0->BT0PSC_b.BT0PSC1 = 0; // 2分频
    BT0->BT0MOD_b.T1M = 2;     // 捕获模式2
    BT0->BT0MOD_b.CT1 = 0;     // 定时或捕获模式
    BT0->BT0PSC_b.BT0PSC2 = 0; // 定时器T1 FLCLK预分频
    BT0->BT0MOD_b.CAPS1 = 0;   // 0:选择为外部输入TI1 1:FLCLK

    BT0->BT0MOD_b.CAPEN1 = 1; // 使能捕获1

    BT0->BT0CTL_b.INTER1 = 1; // 上升沿中断使能
    BT0->BT0CTL_b.INTEF1 = 1; // 下降沿中断使能
    BT0->BT0CTL_b.OVFE1 = 1;  // 计数溢出中断使能

    BT0->BT0CFG_b.DOUEDGE1 = 1; // 0,捕获电平  1,捕获占空比和周期
#endif
/***************HALL捕获(对应中断BT00)*******************************/
#if (0)
    EXINT_Config(3, EXINT_PINSEL_PA08, EXINT_DIR0_TYPE0_INTNON, EXINT_DIV(0), EXINT_PSC(15));

    ACCESS_EN;
    BT0->BT0CFG_b.INSEL = 1; // T0定时器输入选择寄存器 0：选择BTI0, 1：选择BTI0、BTI1、BTI2的异或

    BT0->BT0CFG_b.BT32EN = 1;
#endif
/***************组合成32位定时器(对应中断BT00)***********************/
#if (0)
    BT0->BT0CFG_b.BT32EN = 1;
#endif
    /***************中断***********************/
    BT0->BT0CTL_b.TR0 = 1;
    //	BT0->BT0CTL_b.TR1 = 1;
}
void BT1_capture_test()
{
/***************BT10***********************/
#if (0)
    EXINT_Config(2, EXINT_PINSEL_PA05, EXINT_DIR0_INTNON, EXINT_DIV(0), EXINT_PSC(15));

    BT1->BT1MOD_b.CKS0 = 0;    // 0:时钟源为系统时钟fclk  1:fLCLK
    BT1->BT1PSC_b.BT1PSC0 = 0; // 2分频
    BT1->BT1MOD_b.T0M = 2;     // 捕获模式2
    BT1->BT1MOD_b.CT0 = 0;     // 定时或捕获模式

    BT1->BT1MOD_b.CAPEN0 = 1; // 使能捕获0

    BT1->BT1CTL_b.INTER0 = 1; // 上升沿中断使能
    BT1->BT1CTL_b.INTEF0 = 1; // 下降沿中断使能
    BT1->BT1CTL_b.OVFE0 = 1;  // 计数溢出中断使能

    BT1->BT1CFG_b.DOUEDGE0 = 1; // 0,捕获电平  1,捕获占空比和周期

#endif
/***************BT11***********************/
#if (0)
    EXINT_Config(3, EXINT_PINSEL_PA06, EXINT_DIR0_TYPE0_INTNON, EXINT_DIV(0), EXINT_PSC(15));

    BT1->BT1MOD_b.CKS1 = 0;    // 0:时钟源为系统时钟fclk  1:fLCLK
    BT1->BT1PSC_b.BT1PSC1 = 0; // 2分频
    BT1->BT1MOD_b.T1M = 2;     // 捕获模式2
    BT1->BT1MOD_b.CT1 = 0;     // 定时或捕获模式
    BT1->BT1PSC_b.BT1PSC2 = 0; // 定时器T1 FLCLK预分频
    BT1->BT1MOD_b.CAPS1 = 0;   // 0:选择为外部输入TI1 1:FLCLK

    BT1->BT1MOD_b.CAPEN1 = 1; // 使能捕获1

    BT1->BT1CTL_b.INTER1 = 1; // 上升沿中断使能
    BT1->BT1CTL_b.INTEF1 = 1; // 下降沿中断使能
    BT1->BT1CTL_b.OVFE1 = 1;  // 计数溢出中断使能

    BT1->BT1CFG_b.DOUEDGE1 = 1; // 0,捕获电平  1,捕获占空比和周期

#endif
/***************HALL捕获(对应中断BT00)*******************************/
#if (0)
    EXINT_Config(1, EXINT_PINSEL_PA08, EXINT_DIR0_TYPE0_INTNON, EXINT_DIV(0), EXINT_PSC(15));
    //	EXINT->CFG_b[1].PINSEL = 8;//选择PA8
    //	EXINT->CFG_b[1].FILTA = 0;//关闭模拟滤波
    //	EXINT->CFG_b[1].DIV = 63;//数字滤波时钟分频
    //	EXINT->CFG_b[1].PSC = 0;//数字滤波窗口
    ACCESS_EN;
    BT1->BT1CFG_b.INSEL = 1; // T0定时器输入选择寄存器 0：选择BTI0, 1：选择BTI0、BTI1、BTI2的异或

    BT1->BT1CFG_b.BT32EN = 1;
#endif
/***************组合成32位定时器(对应中断BT10)***********************/
#if (0)
    BT1->BT1CFG_b.BT32EN = 1;
#endif
    /***************中断***********************/
    BT1->BT1CTL_b.TR0 = 1;
    //	BT1->BT1CTL_b.TR1 = 1;

    NVIC_ClearPendingIRQ(BT10_IRQn);
    NVIC_SetPriority(BT10_IRQn, 0);
    NVIC_EnableIRQ(BT10_IRQn); // 使能BT10_IRQn中断

    NVIC_ClearPendingIRQ(BT11_IRQn);
    NVIC_SetPriority(BT11_IRQn, 0);
    NVIC_EnableIRQ(BT11_IRQn); // 使能BT11_IRQn中断
}
