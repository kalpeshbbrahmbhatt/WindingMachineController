/***************************************************
**HAL.c
**Internal peripherals and external peripheral initialization, two major INIT function is mainly used for chip hardware
**Called in MAIN MAIN function to make has nothing to do with the hardware library
***************************************************/
#include "hal.h"
#include "STM32Lib\\stm32f10x.h"
#include "STM32Lib\\stm32f10x_gpio.h"
#include "STM32Lib\\stm32f10x_exti.h"
#include "STM32Lib\\stm32f10x_bkp.h"
#include "STM32Lib\\stm32f10x_pwr.h"
#include "STM32Lib\\stm32f10x_rtc.h"

//#define leds 									8
#define	lcd_lines							4
//#define lcd_on_off_port				GPIOA
#define lcd_line_1_port				GPIOA
#define lcd_line_2_port				GPIOA
#define lcd_line_3_port				GPIOA
#define lcd_line_4_port				GPIOA
//#define lcd_on_off_pin				GPIO_Pin_1  
#define lcd_line_1_pin				GPIO_Pin_3	//GPIO_Pin_0  
#define lcd_line_2_pin				GPIO_Pin_2	//GPIO_Pin_1
#define lcd_line_3_pin        		GPIO_Pin_1	//GPIO_Pin_2
#define lcd_line_4_pin				GPIO_Pin_0	//GPIO_Pin_3
#define en_pin						GPIO_Pin_4
#define rw_pin						GPIO_Pin_5
#define rs_pin						GPIO_Pin_6

#define en_port						GPIOA
#define rw_port						GPIOA
#define rs_port						GPIOA

//**************************************************
 
GPIO_TypeDef* PORT[lcd_lines] = {	lcd_line_1_port, lcd_line_2_port, 
									lcd_line_3_port, lcd_line_4_port, 
								};
const uint16_t PIN[lcd_lines] = {	lcd_line_1_pin, lcd_line_2_pin, 
									lcd_line_3_pin, lcd_line_4_pin,
								};

/*GPIO_TypeDef* Port[leds] = {   GPIOB, GPIOB, 
                           GPIOB, GPIOB,
                           GPIOB, GPIOB, 
                           GPIOB, GPIOC
                        };
  

const uint16_t Pin[leds] = {   GPIO_Pin_2, GPIO_Pin_10, 
                           GPIO_Pin_11, GPIO_Pin_12, 
                           GPIO_Pin_13, GPIO_Pin_14, 
                           GPIO_Pin_15, GPIO_Pin_6
													}; 
 __IO uint32_t TimeDisplay = 0;
 uint8_t ClockSource;
 uint16_t SummerTimeCorrect; */
//Various internal hardware module configuration function
extern void GPIO_Configuration(void);			//GPIO
extern void RCC_Configuration(void);			//RCC
//extern void ADC_Configuration(void);			//ADC
extern void USART_Configuration(void);			//USART
extern void USART3_Configuration(void);
extern void NVIC_Configuration(void);			//NVIC
extern void TIM_Configuration(void);			//NVIC
void Pin_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,GPIOMode_TypeDef Mode,GPIOSpeed_TypeDef Speed);
//void SysTickDelay(u16);
extern void beep_buzzer (void);

/*******************************
**Function name::ChipHalInit()
**Function: on-chip hardware initialization
*******************************/
void  ChipHalInit(void)
{
	 //Initialization clock source
	RCC_Configuration();
	 	
	//Initialize GPIO
	GPIO_Configuration();

    //ADC initialization	
    //ADC_Configuration();
	 
	//Initialize USART	 	
	USART_Configuration();
	//USART3_Configuration();

	//Initialization NVIC
	NVIC_Configuration();

	//Initialization TIM
	//TIM_Configuration();
	
}

/*********************************
**Function name:ChipOutHalInit()
**Function: chip hardware initialization
*********************************/
void  ChipOutHalInit(void)
{
	
}
//************************************************************
void delay(unsigned int i )
{
	while(i--);
}

void send_four_bits(unsigned char d)
{
	char	a;
	for(a=0;a<4;a++)
	{	//send 4 bits
		if(d & (0x80 >> a))
			GPIO_SetBits(PORT[a],PIN[a]);

		else
			GPIO_ResetBits(PORT[a],PIN[a]);
	}
}
void send_command(unsigned char temp)
{
	unsigned char data1;
	//wait_while_busy();
	data1=temp;
	data1=data1 & 0xf0;
	send_four_bits(data1);
	delay(100);
	GPIO_ResetBits(rs_port,rs_pin);		//   rs=0;
	GPIO_SetBits(en_port,en_pin);		//   en=1;
	delay(100);
	GPIO_ResetBits(en_port,en_pin);		//   en=0;
	delay(100);

	data1=temp<<4;
	data1=data1 & 0xf0;
	send_four_bits(data1);
	delay(100);
	GPIO_ResetBits(rs_port,rs_pin);		//   rs=0;
	GPIO_SetBits(en_port,en_pin);		//   en=1;
	delay(100);
	GPIO_ResetBits(en_port,en_pin);		//   en=0;
	delay(100);

}
//*********************************************
void send_data(unsigned char temp)
{
   unsigned char data1;
	//wait_while_busy();
	data1=temp;
	data1=data1 & 0xf0;
	send_four_bits(data1);
	delay(100);
	GPIO_SetBits(rs_port,rs_pin);		//   rs=1;
	GPIO_SetBits(en_port,en_pin);		//   en=1;
	delay(100);
	GPIO_ResetBits(en_port,en_pin);		//   en=0;
	delay(100);

	data1=temp<<4;
	data1=data1 & 0xf0;
	send_four_bits(data1);
	delay(100);
	GPIO_SetBits(rs_port,rs_pin);		//   rs=1;
	GPIO_SetBits(en_port,en_pin);		//   en=1;
	delay(100);
	GPIO_ResetBits(en_port,en_pin);		//   en=0;
	delay(100);
}
void lcd_clr(void)
{
	delay(7200);
	send_command(0x01);
	delay(7200);
	delay(7200);
}

//**********************************************************************
void lcd_gotoxy(unsigned char row,unsigned char col)
{
	unsigned char j;

	if(row==1)
	j=128;
	if(row==2)
	j=192;

	j=j+col-1;

	send_command(j);
	delay(1000);delay(500);
}

//***********************************************************

void lcd_write_string(unsigned char  *ptr )
{
	while(*ptr!=0)
	{
		send_data(*ptr);
		ptr++;
		delay(1500);delay(1000);
	}
}   
  

void Pin_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,GPIOMode_TypeDef Mode,GPIOSpeed_TypeDef Speed)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  /*Enable Port RCC_APB2 configurations*/
  if(GPIOx == GPIOA)
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  else if(GPIOx == GPIOB)
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  else if(GPIOx == GPIOC)
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  else if(GPIOx == GPIOD)
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  else if(GPIOx == GPIOE)
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  else if(GPIOx == GPIOF)
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
  

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
  
  GPIO_InitStructure.GPIO_Mode = Mode;
  GPIO_InitStructure.GPIO_Speed = Speed;
  GPIO_Init(GPIOx, &GPIO_InitStructure);
}

void io_Init(void)
{
	//GPIO_InitTypeDef GPIO_InitStructure;
	/* Configure ref. pin as input floating */
  //	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  //	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  //	GPIO_Init(GPIOB, &GPIO_InitStructure);
	Pin_Init(step_port,step_pin,GPIO_Mode_Out_PP,GPIO_Speed_50MHz); 
    Pin_Init(dire_port,dire_pin,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
	Pin_Init(enab1_port,enab1_pin,GPIO_Mode_Out_PP,GPIO_Speed_50MHz); 
    Pin_Init(enab2_port,enab2_pin,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
	Pin_Init(enab3_port,enab3_pin,GPIO_Mode_Out_PP,GPIO_Speed_50MHz); 
    Pin_Init(enab4_port,enab4_pin,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
	Pin_Init(enab5_port,enab5_pin,GPIO_Mode_Out_PP,GPIO_Speed_50MHz); 
    Pin_Init(enab6_port,enab6_pin,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
	GPIO_ResetBits(step_port,step_pin);
	GPIO_SetBits(dire_port,dire_pin);
	GPIO_SetBits(enab1_port,enab1_pin);
	GPIO_SetBits(enab2_port,enab2_pin);
	GPIO_SetBits(enab3_port,enab3_pin);
	GPIO_SetBits(enab4_port,enab4_pin);
	GPIO_SetBits(enab5_port,enab5_pin);
	GPIO_SetBits(enab6_port,enab6_pin);
}

//*******************************************************************
void lcd_initialize()
{
	delay(7200);

  Pin_Init(lcd_line_1_port,lcd_line_1_pin,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
  Pin_Init(lcd_line_2_port,lcd_line_2_pin,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
  Pin_Init(lcd_line_3_port,lcd_line_3_pin,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
  Pin_Init(lcd_line_4_port,lcd_line_4_pin,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
//	Pin_Init(lcd_on_off_port,lcd_on_off_pin,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
  Pin_Init(en_port,en_pin,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
  Pin_Init(rw_port,rw_pin,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
  Pin_Init(rs_port,rs_pin,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
//	GPIO_WriteBit(lcd_on_off_port,lcd_on_off_pin, Bit_SET);
	GPIO_ResetBits(rw_port,rw_pin);
//	GPIO_WriteBit(lcd_on_off_port,lcd_on_off_pin, Bit_RESET);
			
		delay(7200);
	send_command(0x03);
	delay(7200);
	send_command(0x03);
	delay(7200);
	send_command(0x03);
	delay(7200);

	send_command(0x02);
	delay(7200);
	send_command(0x02);
	delay(7200);
	send_command(0x28);
	delay(7200);
	send_command(0x01);
	delay(7200);

	send_command(0x06);
	delay(7200);
	send_command(0x0C);
	delay(7200);

	//send_command(0x10,selected_lcd);
	send_command(0x80);
	delay(7200);

	//send_command(0x06,selected_lcd);
	//send_command(0x0f,selected_lcd);
	send_command(0x0c);
	delay(7200);
	delay(7200);
}

//*************************************************************
