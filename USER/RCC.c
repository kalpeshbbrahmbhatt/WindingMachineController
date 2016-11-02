#include "STM32Lib\\stm32f10x.h"

RCC_ClocksTypeDef RCC_ClockFreq;

void RCC_Configuration(void)
{
	SystemInit();//From system_stm32f10x.c files only need to call this function, you can complete the configuration of the RCC details, please read 2_RCC

	/**************************************************
	Get information of RCC debugging
	Please refer contents of RCC_ClocksTypeDef structural body, after the configuration is completed when the clock,
	The inside variable value directly reflects the frequency of the operation of the various parts of the device
	***************************************************/
	RCC_GetClocksFreq(&RCC_ClockFreq);
	
	/* This configuration allows an external crystal stop vibration, generate an NMI interrupt, do not need to be used can be masked*/
	//RCC_ClockSecuritySystemCmd(ENABLE);

	//SYSTICK divider - 1ms system clock interrupt
	if (SysTick_Config(SystemFrequency / 1000))
  { 
		/* Capture error */ 
	while (1);
  }
}

/********************************************
**Function name:SysTickDelay
**Function: using the system clock hard delay
**Note: In general, do not interrupt the function is called, otherwise there will be reentrant. Shielding the global interrupt, do not use this function
********************************************/
volatile u16 Timer1;
void SysTickDelay(u16 dly_ms)
{
	Timer1=dly_ms;
	while(Timer1);
}

