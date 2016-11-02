#include "STM32Lib\\stm32f10x.h"
#include "STM32Lib\\misc.h"
extern unsigned int pulse;
extern unsigned int fre;

void TIM_Configuration(void)
{
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;	 
	
	/* TIM2 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_DeInit(TIM2);
	TIM_DeInit(TIM3);

	 /* TIM2 configuration: PWM Input mode ------------------------
     The external signal is connected to TIM2 CH2 pin (PA.01), 
     The Rising edge is used as active edge,
     The TIM2 CCR2 is used to compute the frequency value 
     The TIM2 CCR1 is used to compute the duty cycle value
  ------------------------------------------------------------ */

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0;

    TIM_PWMIConfig(TIM2, &TIM_ICInitStructure);

    /* Select the TIM2 Input Trigger: TI2FP2 */
    TIM_SelectInputTrigger(TIM2, TIM_TS_TI2FP2);

    /* Select the slave Mode: Reset Mode */
    TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);

    /* Enable the Master/Slave Mode */
    TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable);

    /* Enable the CC2 Interrupt Request */
    TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE); 


	/*TIM3 Clock Configuration*/
	TIM_TimeBaseStructure.TIM_Prescaler = 720;			//Prescaler (clock divider) 72M/720 = 100K
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		//Counting up
	TIM_TimeBaseStructure.TIM_Period = fre;							//Value loaded 100k/fre =
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);

	/* Channel 1 Configuration in PWM mode */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 				//PWM mode1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 	//Forward channel
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;//Reverse channel is invalid
	TIM_OCInitStructure.TIM_Pulse =pulse; 				//Duty time
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 		//Output polarity
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;     //The complementary end the polarity 
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;  

	TIM_OC4Init(TIM3,&TIM_OCInitStructure); 			//Channel 4
	 	   		
	/* TIM1 Main Output Enable */
	TIM_CtrlPWMOutputs(TIM3,ENABLE);

    /* TIM1 counter enable */
	TIM_Cmd(TIM2,ENABLE);
	
    /* TIM1 counter enable */
	TIM_Cmd(TIM3,ENABLE);

}

//Set a capture register 1
void SetT1Pwm1(u16 pluse)
{
	TIM3->CCR1=pulse;
}
void SetT1Pwm2(u16 fre)
{
	TIM3->ARR=fre; 
}
