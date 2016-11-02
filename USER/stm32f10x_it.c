/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* stm32f10x_it.c
* All interrupt response function, generally If the interrupt is relatively simple, direct written this, otherwise
* Respective processing functions callable HAL module to handle interrupts.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "STM32Lib\\stm32f10x.h"
#include "hal.h"
#include "USART.h"
#include "STM32Lib\\stm32f10x_exti.h"
#include "STM32Lib\\stm32f10x_rtc.h"
#include "STM32Lib\\stm32f10x_bkp.h"
#include "STM32Lib\\stm32f10x_pwr.h"

#define countof(a)   (sizeof(a) / sizeof(*(a)))

uint8_t DisplayDateFlag;

/* Private function prototypes -----------------------------------------------*/

extern __IO uint32_t TimeDisplay;
extern unsigned char zone_fault_flag_123 = 0x00;
extern void DateUpdate(void);
extern uint16_t WeekDay(uint16_t,uint8_t,uint8_t);
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : NMIException
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMIException(void)
{
}

/*******************************************************************************
* Function Name  : HardFaultException
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFaultException(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : MemManageException
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManageException(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : BusFaultException
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFaultException(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : UsageFaultException
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFaultException(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : DebugMonitor
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMonitor(void)
{
}

/*******************************************************************************
* Function Name  : SVCHandler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVCHandler(void)
{
}

/*******************************************************************************
* Function Name  : PendSVC
* Description    : This function handles PendSVC exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSVC(void)
{
}

/*******************************************************************************
* Function Name  : SysTickHandler
* Description    :System clock, usually tuned to 1MS interrupt
*******************************************************************************/
void SysTick_Handler(void)
{
	if(Timer1)
		Timer1--;
}

/*******************************************************************************
* Function Name  : WWDG_IRQHandler
* Description    : This function handles WWDG interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WWDG_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : PVD_IRQHandler
* Description    : This function handles PVD interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PVD_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TAMPER_IRQHandler
* Description    : This function handles Tamper interrupt request. 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TAMPER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : RTC_IRQHandler    RTC interrupt
* Description    : RTC interrupt Real_Time value of
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_IRQHandler(void)
{
 /*		uint8_t Month,Day;
		uint16_t Year;
		if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
		{									   */
    /* Clear the RTC Second interrupt */
    

    
    /* Enable time update */
  /*  TimeDisplay = 1;
		 Month = BKP_ReadBackupRegister(BKP_DR2);
		Day = BKP_ReadBackupRegister(BKP_DR3);
		Year = BKP_ReadBackupRegister(BKP_DR4);
		NVIC_ClearPendingIRQ(RTC_IRQn);
		RTC_ClearITPendingBit(RTC_IT_SEC);	  */
		/* If counter is equal to 86399: one day was elapsed */
  /* This takes care of date change and resetting of counter in case of
  power on - Run mode/ Main supply switched on condition*/
	/*	if(RTC_GetCounter() == 86399)
		{							*/
			/* Wait until last write operation on RTC registers has finished */
		//	RTC_WaitForLastTask();
			/* Reset counter value */
		//	RTC_SetCounter(0x0);
			/* Wait until last write operation on RTC registers has finished */
		//	RTC_WaitForLastTask();

			/* Increment the date */
		//	DateUpdate();
		//}

		//if((RTC_GetCounter()/3600 == 1)&&(((RTC_GetCounter()%3600)/60) == 59)&&
		//	 (((RTC_GetCounter()%3600)%60) == 59))
		//{
			/* March Correction */
		//	if((Month == 3) && (Day >24))
		//	{
		//		if(WeekDay(Year,Month,Day)==0)
		//		{
		//				if((SummerTimeCorrect & 0x8000) == 0x8000)
		//				{
		//					RTC_SetCounter(RTC_GetCounter() + 3601);
						 
							/* Reset March correction flag */
		//					SummerTimeCorrect &= 0x7FFF;
						 
							/* Set October correction flag  */
		//					SummerTimeCorrect |= 0x4000;
		//					SummerTimeCorrect |= Year;
		//					BKP_WriteBackupRegister(BKP_DR7,SummerTimeCorrect);
		//				}
		//		}
		//	}
				/* October Correction */
		//		if((Month == 10) && (Day >24))
		//		{
		//					if(WeekDay(Year,Month,Day)==0)
		//					{
		//								if((SummerTimeCorrect & 0x4000) == 0x4000)
		//								{
		//									RTC_SetCounter(RTC_GetCounter() - 3599);
		//									
		//									/* Reset October correction flag */
		//									SummerTimeCorrect &= 0xBFFF;
											
											/* Set March correction flag  */
		//									SummerTimeCorrect |= 0x8000;
		//									SummerTimeCorrect |= Year;
		//									BKP_WriteBackupRegister(BKP_DR7,SummerTimeCorrect);
		//								}
		//					}
		//		}
		//}			
//	} 
}

/*******************************************************************************
* Function Name  : FLASH_IRQHandler
* Description    : This function handles Flash interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FLASH_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : RCC_IRQHandler
* Description    : This function handles RCC interrupt request. 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI0_IRQHandler
* Description    : This function handles External interrupt Line 0 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI0_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI1_IRQHandler
* Description    : This function handles External interrupt Line 1 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI2_IRQHandler
* Description    : This function handles External interrupt Line 2 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI3_IRQHandler
* Description    : This function handles External interrupt Line 3 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI4_IRQHandler
* Description    : This function handles External interrupt Line 4 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI4_IRQHandler(void)
{
}
/*******************************************************************************
* Function Name  : DMAChannel1_IRQHandler
* Description    : This function handles DMA Stream 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMAChannel2_IRQHandler
* Description    : This function handles DMA Stream 2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMAChannel3_IRQHandler
* Description    : This function handles DMA Stream 3 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMAChannel4_IRQHandler
* Description    : This function handles DMA Stream 4 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMAChannel5_IRQHandler
* Description    : This function handles DMA Stream 5 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMAChannel6_IRQHandler
* Description    : This function handles DMA Stream 6 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel6_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMAChannel7_IRQHandler
* Description    : This function handles DMA Stream 7 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel7_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : ADC_IRQHandler
* Description    : This function handles ADC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC1_2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : USB_HP_CAN_TX_IRQHandler
* Description    : This function handles USB High Priority or CAN TX interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_HP_CAN1_TX_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : USB_LP_CAN_RX0_IRQHandler
* Description    : This function handles USB Low Priority or CAN RX0 interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_LP_CAN1_RX0_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : CAN_RX1_IRQHandler
* Description    : This function handles CAN RX1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN1_RX1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : CAN_SCE_IRQHandler
* Description    : This function handles CAN SCE interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN1_SCE_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI9_5_IRQHandler
* Description    : This function handles External lines 9 to 5 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI9_5_IRQHandler(void)
{
	
	if(EXTI_GetITStatus(EXTI_Line8) != RESET)
  {
    /* Toggle LED3 */
     //STM32vldiscovery_LEDToggle(LED3);
		zone_fault_flag_123 = zone_fault_flag_123 | 0x04;
    /* Clear the User Button EXTI line pending bit */
    EXTI_ClearITPendingBit(EXTI_Line8);
  }
}

/*******************************************************************************
* Function Name  : TIM1_BRK_IRQHandler
* Description    : This function handles TIM1 Break interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_BRK_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM1_UP_IRQHandler
* Description    : This function handles TIM1 overflow and update interrupt 
*                  request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_UP_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM1_TRG_COM_IRQHandler
* Description    : This function handles TIM1 Trigger and commutation interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_TRG_COM_IRQHandler(void)
{
 
}

/*******************************************************************************
* Function Name  : TIM1_CC_IRQHandler
* Description    : This function handles TIM1 capture compare interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_CC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM2_IRQHandler TIM2 interrupt
* Description    : This function handles TIM2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void TIM2_IRQHandler(void)
{

}

/*******************************************************************************
* Function Name  : TIM3_IRQHandler
* Description    : This function handles TIM3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM4_IRQHandler
* Description    : This function handles TIM4 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C1_EV_IRQHandler
* Description    : This function handles I2C1 Event interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C1_EV_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C1_ER_IRQHandler
* Description    : This function handles I2C1 Error interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C1_ER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C2_EV_IRQHandler
* Description    : This function handles I2C2 Event interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C2_EV_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C2_ER_IRQHandler
* Description    : This function handles I2C2 Error interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C2_ER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SPI1_IRQHandler
* Description    : This function handles SPI1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SPI2_IRQHandler
* Description    : This function handles SPI2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : USART1_IRQHandler
* Description    : This function handles USART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
extern unsigned char  RxIn;
extern unsigned char  Rx;
extern unsigned char  SystemBuf[];
void USART1_IRQHandler(void)
{
	//Receive interrupt
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);	
		if(Rx<RxIn)
		{
		    SystemBuf[Rx]=(USART1->DR);
			Rx++;
		}
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);	
		
		// USART1PutDatatoBuf(USART1->DR);
     } 

	//Overflow - overflow occurs first read the SR Read DR register can be cleared into constantly interrupt
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)==SET)
	{
		USART_ClearFlag(USART1,USART_FLAG_ORE);	//Read SR
		USART_ReceiveData(USART1);				//Read DR
	}
}


/*******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : This function handles USART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART2_IRQHandler(void)
{

}

/*******************************************************************************
* Function Name  : USART3_IRQHandler
* Description    : This function handles USART3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void USART3_IRQHandler(void)
{
	//Receive interrupt
	if(USART_GetITStatus(USART3,USART_IT_RXNE)==SET)
	{
		
//		USART_SendData(USART3,USART_ReceiveData(USART3));
//        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET );

		if(Rx<RxIn)
		{
		    SystemBuf[Rx]=(USART3->DR);
			Rx++;
		}
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
     } 

	//Overflow - overflow occurs first read the SR Read DR register can be cleared into constantly interrupt
	if(USART_GetFlagStatus(USART3,USART_FLAG_ORE)==SET)
	{
		USART_ClearFlag(USART3,USART_FLAG_ORE);	//Read SR
		USART_ReceiveData(USART3);				//Read DR
	}
}

/*******************************************************************************
* Function Name  : EXTI15_10_IRQHandler
* Description    : This function handles External lines 15 to 10 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line10) != RESET)
  {
    /* Toggle LED3 */
     //STM32vldiscovery_LEDToggle(LED3);
		zone_fault_flag_123 = zone_fault_flag_123 | 0x02;
    /* Clear the User Button EXTI line pending bit */
    EXTI_ClearITPendingBit(EXTI_Line10);
  }
	if(EXTI_GetITStatus(EXTI_Line11) != RESET)
  {
    /* Toggle LED3 */
		zone_fault_flag_123 = zone_fault_flag_123 | 0x01;
    /* Clear the User Button EXTI line pending bit */
    EXTI_ClearITPendingBit(EXTI_Line11);
  }
    
}

/*******************************************************************************
* Function Name  : RTCAlarm_IRQHandler
* Description    : This function handles RTC Alarm interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTCAlarm_IRQHandler(void)
{
	
}

/*******************************************************************************
* Function Name  : USBWakeUp_IRQHandler
* Description    : This function handles USB WakeUp interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USBWakeUp_IRQHandler(void)
{
}

/*****************************************************************
*		HD series only interrupt resources
******************************************************************/

void TIM8_BRK_IRQHandler(void)
{

}

void TIM8_UP_IRQHandler(void)
{

}

void TIM8_TRG_COM_IRQHandler(void)
{

}

void TIM8_CC_IRQHandler(void)
{

}

void ADC3_IRQHandler(void)
{

}
        
void FSMC_IRQHandler(void)
{

}

void SDIO_IRQHandler(void)
{

}

void TIM5_IRQHandler(void)
{

}

void SPI3_IRQHandler(void)
{

}

void UART4_IRQHandler(void)
{

}

void UART5_IRQHandler(void)
{

}

void TIM6_IRQHandler(void)
{

}

void TIM7_IRQHandler(void)
{

}

void DMA2_Channel1_IRQHandler(void)
{

}

void DMA2_Channel2_IRQHandler(void)
{

}

void DMA2_Channel3_IRQHandler(void)
{

}

void DMA2_Channel4_5_IRQHandler(void)
{

}










/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
