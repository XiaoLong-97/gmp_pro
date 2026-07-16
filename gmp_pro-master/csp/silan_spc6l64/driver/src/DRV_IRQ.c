#include "IRQ.h"

/***************************************************************************
			配置中断有限级
****************************************************************************/
void IRQ_Init(void)
{
	NVIC_ClearPendingIRQ(PWM0_IRQn);
	NVIC_SetPriority(PWM0_IRQn,1);
	NVIC_EnableIRQ(PWM0_IRQn);	

	NVIC_ClearPendingIRQ(BT41_IRQn);
	NVIC_SetPriority(BT41_IRQn,2);
	NVIC_EnableIRQ(BT41_IRQn);		
	
	NVIC_ClearPendingIRQ(BT40_IRQn);
	NVIC_SetPriority(BT40_IRQn,3);
	NVIC_EnableIRQ(BT40_IRQn);	
	
	NVIC_ClearPendingIRQ(WWDT_IRQn);
	NVIC_SetPriority(WWDT_IRQn,0);
	NVIC_EnableIRQ(WWDT_IRQn);	
	
	NVIC_ClearPendingIRQ(IWDT_IRQn);
	NVIC_SetPriority(IWDT_IRQn,0);
	NVIC_EnableIRQ(IWDT_IRQn);	
	
	EXINT->SCLR = 0x07;	//外部中断标志清除	
	NVIC_ClearPendingIRQ(EXINT_IRQn);
	NVIC_SetPriority(EXINT_IRQn,0);
	NVIC_EnableIRQ(EXINT_IRQn);		

//	NVIC_ClearPendingIRQ(ADC_IRQn);
//	NVIC_SetPriority(ADC_IRQn,0);
//	NVIC_EnableIRQ(ADC_IRQn);		

//	NVIC_ClearPendingIRQ(BT00_IRQn);
//	NVIC_SetPriority(BT00_IRQn,0);   
//	NVIC_EnableIRQ(BT00_IRQn);       //使能BT10_IRQn中断	
}


