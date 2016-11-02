/**
  ******************************************************************************
  * @file  usart.h
  * @author  X
  * @version  V3.0.0
  * @date  05/27/2011
  * @brief  This file contains all the functions prototypes for the 
  *         miscellaneous firmware library functions.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H
#define __USART_H
/* Includes ------------------------------------------------------------------*/
#include "STM32Lib\\stm32f10x.h"


void USART1_Putc(unsigned char date[],unsigned char n);

void USART1_SendByte(unsigned char Data);

void USART1_Puts(char * str);

void USART1PutDatatoBuf(unsigned char dat);

u8 USART1IsDataInBuf( void );

u32 USART1GetBufLen(void);

u8 USART1GetBufDat( void );
//void USART_SendByte(unsigned char Data);
#endif /* __USART_H */
