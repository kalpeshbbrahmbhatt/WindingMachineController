#include "STM32Lib\\stm32f10x.h"
#include "STM32Lib\\stm32f10x_usart.h"
/**********************************************
**Serial port configuration function enable serial port 1
**
**********************************************/

void USART_Configuration(void)
{   
	GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;
	
	//Enable serial port 1, PA, AFIO bus
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE);

    // A9 do T1X
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // A10 do R1X 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
      
    USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

	USART_ClockInit(USART1, &USART_ClockInitStructure);
    
	USART_Init(USART1, &USART_InitStructure);
    /* Enable the USARTx */
    USART_Cmd(USART1, ENABLE);
	//Serial receive interrupt
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
}

void USART3_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;
				 	
	//Enable serial 2 clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	
	// B10 do T3X
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // B11 do 3X 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
    USART_ClockInit(USART3, &USART_ClockInitStructure);
    USART_Init(USART3, &USART_InitStructure);
    
    USART_Cmd(USART3, ENABLE);
	//Serial 3 Use receive interrupt
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
//	USART_ITConfig(USART3,USART_IT_TXE,ENABLE);

}

void USART3_Putc(unsigned char date[],unsigned char n)
{
    int i;
    for(i=0;i<n;i++)
    {    
	    USART_SendData(USART2, date[i]);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET );
	}
}

/****************************************************
**Function name:Combine
**Function: Combining high eight and low eight
****************************************************/
u16 Combine(u8 high, u8 low)
{
    u16 tmp;
	tmp=high;
	tmp=(tmp<<8)|low;

	return((u16)tmp);	        
}

/*******************************************************************************
* Function Name  : USART_SendByte
* Description    : Transmits single data through the USARTx peripheral.
* Input          : Hexadecimal data
* Output         : None
* Return         : None
*******************************************************************************/
void USART3_SendByte(unsigned char Data)
{
  
    USART_SendData(USART3, Data);
    /* Loop until the end of transmission */
    while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
  
}

void USART1_Putc(unsigned char date[],unsigned char n)		//void USART1_Putc(u16 c[],u16 n)
{
int i;
  for(i =0;i<n;i++)
  {
    USART_SendData(USART1, date[i]);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
	}
}

/*******************************************************************************
* Function Name  : USART_SendByte
* Description    : Transmits single data through the USARTx peripheral.
* Input          : Hexadecimal data
* Output         : None
* Return         : None
*******************************************************************************/
void USART1_SendByte(unsigned char Data)
{
  
    USART_SendData(USART1, Data);
    /* Loop until the end of transmission */
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void USART1_Puts(char * str)
{
    while(*str)
    {
        USART_SendData(USART1, *str++);
        /* Loop until the end of transmission */
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
}

/*******************************************************************************
* Function Name  : USART_SendByte
* Description    : Transmits single data through the USARTx peripheral.
* Input          : Hexadecimal data
* Output         : None
* Return         : None
*******************************************************************************/
//void USART_SendByte(unsigned char Data)
//{
//  
//  USART_SendData(USART1, Data);
//    /* Loop until the end of transmission */
//  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
//  {
//  }
//  
//}
/**************************************************************
 	Serial port to receive queue
 
***************************************************************/

#define USART1_RX_BUF_MAX	2048	/*Must be an integer multiple of 2*/
#define USART1_RX_BUF_MARK	USART1_RX_BUF_MAX-1

static u8 USART1_RX_Buf[USART1_RX_BUF_MAX];		//Queue
volatile u32 USART1_Rx_Head=0;					//The head of the queue - received mobile
volatile u32 USART1_Rx_Tail=0;					//Queue tail - read mobile



/**************************************************************
** Function name:USART1PutDatatoBuf
** Function: the data into the queue,
** Caution: You should call this function in the serial port receive interrupt
***************************************************************/
void USART1PutDatatoBuf(unsigned char dat)
{
	u32 tmphead;
	tmphead = ( USART1_Rx_Head + 1 ) & USART1_RX_BUF_MARK;//Maximum value judgment of the head of the queue to reach the maximum, then change back to 0
	USART1_Rx_Head = tmphead; 	// Each received a data queue head increased by 1 
	USART1_RX_Buf[tmphead] = dat; 				
}

/*************************************************
**Function name:USART1IsDataInBuf
**Function: it tells you whether data in the buffer
**Note: When the head and tail of the queue are not equal when, on behalf of the data in the buffer
*************************************************/
u8 USART1IsDataInBuf( void )
{
	return ( USART1_Rx_Head != USART1_Rx_Tail ); 
}

/*************************************************
** Function name:USART1GetBufLen
** Function: Get the effective length of the data in the buffer
** Note: the value obtained is inevitable to a minimum, because the true length will be changing, 
** there is no critical problem for 32-bit data 32-bit ARM system, so you can not consider off interrupts
**************************************************/
u32 USART1GetBufLen(void)
{
	//__disalbe_irq();
	if(USART1_Rx_Head>=USART1_Rx_Tail)
	{
		//__enable_irq();	
		return(USART1_Rx_Head-USART1_Rx_Tail);
	}
	else
	{
		//__enable_irq();	
		return(USART1_RX_BUF_MAX+USART1_Rx_Head-USART1_Rx_Tail);
	}
	
	
	
}

/**************************************************
** Function name:USART1GetBufDat
** Function: to get the data from the queue
** Note: This function is called before to ensure that there is data in the queue!!
**************************************************/
u8 USART1GetBufDat( void )
{
	u32 tmptail;
	while ( USART1_Rx_Head == USART1_Rx_Tail );//Get on to prevent data confusion hard wait
	tmptail = ( USART1_Rx_Tail + 1 ) & USART1_RX_BUF_MARK;
	USART1_Rx_Tail = tmptail;
	return USART1_RX_Buf[tmptail];
}
//Unsigned data
//void DwinDisplaypoint(void)
//{	
//    u16  c[4]={0xcc,0x33,0xc3,0x3c};
//
//	unsigned char tenkilobit,kilobit,hundred,ten,one;
//	if(Frequency >= 100000)
//		return;
//	USART_SendData(USART1,0xAA);
//	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
//	USART_SendData(USART1,0x55);	
//	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
//	USART_SendData(USART1,0x00); 	
//	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
//	USART_SendData(USART1,0x7a); 	    
//	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
//	USART_SendData(USART1,0x00); 	
//	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
//	USART_SendData(USART1,0x64);	    
//	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
//	tenkilobit=Frequency/10000;
//	kilobit = (Frequency%10000)/1000;
//	hundred = (Frequency%1000)/100;
//	ten = (Frequency % 100) /10;
//	one = Frequency % 10;
//	
//	if(tenkilobit != 0)
//		{	
//			USART_SendData(USART1,tenkilobit  + 0x30);	
//			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
//		}
//	if(kilobit != 0||tenkilobit != 0)
//		{	
//			USART_SendData(USART1,kilobit+0x30);	
//			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
//		}
//	else
//		{
//			USART_SendData(USART1,0x20); 	
//			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
//		}
//	if((hundred != 0) ||(kilobit != 0))
//		{
//			USART_SendData(USART1,hundred + 0x30); 	
//			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
//		}
//	else
//		{
//			USART_SendData(USART1,0x20); 	
//			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
//		}
//	if((ten !=0) ||(hundred != 0))
//		{
//			USART_SendData(USART1,ten + 0x30); 	
//			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
//		}
//	else
//		{
//			USART_SendData(USART1,0x20);  	
//			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
//		}
//	USART_SendData(USART1,one + 0x30); 	
//	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
//	USART_SendData(USART1,0x48); 	
//	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET ); 
//	USART_SendData(USART1,0x7a); 	
//	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET ); 
//	USART1_Putc(c,4);	
//		
//}
