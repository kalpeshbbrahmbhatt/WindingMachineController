#include "STM32Lib\\stm32f10x.h"

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Set PD3, PD4, PD5, PD6 keyboard input
* Set PB0, 5, 8, 9; PC5, 7; PD7; PA8 output LED lights
*******************************************************************************/
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|
							RCC_APB2Periph_GPIOB| 
							RCC_APB2Periph_GPIOC|
						/*	RCC_APB2Periph_GPIOD|	*/
							RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

//****************initialise power on/off key of gsm module
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//Push-pull output
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	
	/* A9 USART1_Tx */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//Push-pull output-TX
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* A10 USART1_Rx  */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//Floating input-RX
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* PF6,7,8,9Êä³ö */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	     //Push-pull output
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M clock speed
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
}


