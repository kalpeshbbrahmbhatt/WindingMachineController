#ifndef HAL_H
#define HAL_H


#include "GSM.h"

//#define USART_FLAG_TXE                       ((uint16_t)0x0080)
//u8 buf[512];

extern GPIO_TypeDef* PORT[];
extern const uint16_t PIN[];
//extern struct Date_s s_DateStructVar;
extern GPIO_TypeDef* Port[];
extern const uint16_t Pin[];

//Hardware initialization
extern void  ChipHalInit(void);
extern void  ChipOutHalInit(void);

//System clock delay
extern volatile u16 Timer1;
extern void SysTickDelay(u16);

extern void io_Init(void);
extern void Pin_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,GPIOMode_TypeDef Mode,GPIOSpeed_TypeDef Speed);
extern void lcd_initialize(void);
extern void send_command(unsigned char );
extern void send_data(unsigned char );
extern void lcd_gotoxy(unsigned char,unsigned char);

extern void delay(unsigned int);
extern void lcd_write_string(unsigned  char*);
extern void lcd_write_string_year(unsigned char*);
extern void send_four_bits(unsigned char);
extern void lcd_clr(void);

extern void USART1_SendByte(unsigned char );
extern void USART1_Putc(unsigned char date[],unsigned char);

//extern void USART3_SendByte(unsigned char );
//extern void USART3_Putc(unsigned char date[],unsigned char);

#define step_port					GPIOB
#define	dire_port					GPIOB
#define enab1_port					GPIOB
#define enab2_port					GPIOB
#define enab3_port					GPIOB
#define enab4_port					GPIOB
#define enab5_port					GPIOB
#define enab6_port					GPIOB
#define	step_pin					GPIO_Pin_0
#define	dire_pin					GPIO_Pin_1
#define enab1_pin					GPIO_Pin_3
#define enab2_pin					GPIO_Pin_4
#define enab3_pin					GPIO_Pin_5
#define enab4_pin					GPIO_Pin_6
#define enab5_pin					GPIO_Pin_7
#define enab6_pin					GPIO_Pin_8
#define	beep_port					GPIOB
#define	beep_pin					GPIO_Pin_9
#define ref_port					GPIOB
#define ref_pin						GPIO_Pin_12

//
//extern u16 TestAdc(void);


//extern unsigned char Rx;
//extern unsigned char  SystemBuf[];



//Output macro definitions
//#define LED1_ON		GPIO_ResetBits(GPIOA, GPIO_Pin_8)
//#define LED1_OFF	GPIO_SetBits(GPIOA, GPIO_Pin_8)

//#define LED2_ON		GPIO_ResetBits(GPIOD, GPIO_Pin_7)
//#define LED2_OFF	GPIO_SetBits(GPIOD, GPIO_Pin_7)
//
//#define LED6_ON		GPIO_ResetBits(GPIOF, GPIO_Pin_6)
//#define LED6_OFF	GPIO_SetBits(GPIOF, GPIO_Pin_6)
//
//#define LED7_ON		GPIO_ResetBits(GPIOF, GPIO_Pin_7)
//#define LED7_OFF	GPIO_SetBits(GPIOF, GPIO_Pin_7)
//
//#define LED8_ON		GPIO_ResetBits(GPIOF, GPIO_Pin_8)
//#define LED8_OFF	GPIO_SetBits(GPIOF, GPIO_Pin_8)
//
//#define LED9_ON		GPIO_ResetBits(GPIOF, GPIO_Pin_9)
//#define LED9_OFF	GPIO_SetBits(GPIOF, GPIO_Pin_9)

//#define LED7_ON		GPIO_ResetBits(GPIOB, GPIO_Pin_5)
//#define LED7_OFF	GPIO_SetBits(GPIOB, GPIO_Pin_5)

//#define LED8_ON		GPIO_ResetBits(GPIOB, GPIO_Pin_0)
//#define LED8_OFF	GPIO_SetBits(GPIOB, GPIO_Pin_0)
#endif
