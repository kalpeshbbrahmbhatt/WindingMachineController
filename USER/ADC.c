/**************************************************************
 ADC PB1_ADC9 
 
***************************************************************/

#include "STM32Lib\\stm32f10x.h"

void ADC_Configuration(void)
{
	ADC_InitTypeDef   ADC_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	/* PC4*/
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* ADC1 */
	ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent;		// Independent mode
	ADC_InitStructure.ADC_ScanConvMode       = ENABLE;						//Continuous multi-channel mode
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;						//Continuous conversion
	ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;	//Conversion not decided by outsiders
	ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;			//Right-aligned
	ADC_InitStructure.ADC_NbrOfChannel       = 1;							//Scanning the number of channels
	ADC_Init(ADC1, &ADC_InitStructure);
	
	/* ADC1 Regular Channel1 Configuration                                      */
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_71Cycles5);	//Channel X, using time of 71.5 cycles, a representative of the rules channel 1
	
	ADC_Cmd   (ADC1, ENABLE);             /* Enable ADC1                        */
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);/* Start ADC1 Software Conversion     */ //Enable conversion start
}



u16 TestAdc(void)
{
	u16 adc;
	if(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==SET)
	{
  		adc=ADC_GetConversionValue(ADC1);
	}
	return adc;
}
