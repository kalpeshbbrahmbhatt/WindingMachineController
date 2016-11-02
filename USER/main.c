//**************LCD*************************************************************************
//	PC0 - DB4				PC10	-	EN
//	PC1	-	DB5				PC11	- RW
//	PC2	-	DB6				PC12	-	RS
//	PC3 - DB7
#include "STM32Lib\\stm32f10x.h"
#include "STM32Lib\\stm32f10x_flash.h"
#include "STM32Lib\\stm32f10x_rtc.h"
#include "STM32Lib\\stm32f10x_bkp.h"
#include "STM32Lib\\stm32f10x_pwr.h"
#include "hal.h"			
#include "USART.h"
#include "GSM.h"
#define	NoofStep	50

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
//**************************************************

unsigned char cmd, noofstep;
//**************************************************
//void send_one_byte(unsigned char );
//**************************************************
void display_logo(void);
void Clean_Buff(void);
void write_number_flash(unsigned char * , unsigned char, uint32_t);
void StepMot(void);
//void display_signal_strength(void);
//void beep_buzzer (void);

//extern 	RxIn;
/******************************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////Function void main (); functions: the main function,////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************/  
int main()
{
	    
		ChipHalInit();			//Chip hardware initialization
		lcd_initialize();		//initialise the lcd
		io_Init();
		
		display_logo();			//display the logo
		delay(0xFFFFFF); delay(0xFFFFF);
		GSM_INIT();
	//	RefPosMot();			// Ref. approch for all motors
		//rtc_start();				//inialise the RTC
		//flash_setup();
   	//Pin_Init( reset_port,	reset_pin,	GPIO_Mode_IPD,GPIO_Speed_50MHz);
		SysTickDelay(100);	//Delay of about 10 seconds, wait for the modules to networking  
		Clean_Buff();
		delay(0xFFFFF);
	
	while(1)
	{
			lcd_gotoxy(1,1);
			lcd_write_string("Waiting for    ");
			delay(0xFFF);
			lcd_gotoxy(2,1);
			lcd_write_string("Command Msg     ");
			CHECK:
			receive_ready();
			if(receiveready	== 1)
			{
			 	lcd_gotoxy(1,1);
				lcd_write_string("               ");
				delay(0xFFF);
				lcd_gotoxy(2,1);
				lcd_write_string("MSG. RECEIVED   ");
				read_message();
				cmd = message_read();
				switch(cmd)
				{
					case '1': 	lcd_gotoxy(1,1);
								lcd_write_string("               ");
								delay(0xFFF);
								lcd_gotoxy(2,1);
								lcd_write_string("Command Choice 1");
								GPIO_SetBits(dire_port,dire_pin);
								GPIO_ResetBits(enab5_port,enab5_pin);
								for(noofstep = 0; noofstep < NoofStep; noofstep++)
								{
									StepMot();	
								}
								GPIO_SetBits(enab5_port,enab5_pin);
								break;
					case '2': 	lcd_gotoxy(1,1);
								lcd_write_string("               ");
								delay(0xFFF);
								lcd_gotoxy(2,1);
								lcd_write_string("Command Choice 2");
								GPIO_SetBits(dire_port,dire_pin);
								GPIO_ResetBits(enab2_port,enab2_pin);
								for(noofstep = 0; noofstep < NoofStep; noofstep++)
								{
									StepMot();	
								}
								GPIO_SetBits(enab2_port,enab2_pin);
								break;
				    case '3': 	lcd_gotoxy(1,1);
								lcd_write_string("               ");
								delay(0xFFF);
								lcd_gotoxy(2,1);
								lcd_write_string("Command Choice 3");
								GPIO_SetBits(dire_port,dire_pin);
								GPIO_ResetBits(enab3_port,enab3_pin);
								for(noofstep = 0; noofstep < NoofStep; noofstep++)
								{
									StepMot();	
								}
								GPIO_SetBits(enab3_port,enab3_pin);
								break;
					case '4': 	lcd_gotoxy(1,1);
								lcd_write_string("               ");
								delay(0xFFF);
								lcd_gotoxy(2,1);
								lcd_write_string("Command Choice 4");
								GPIO_SetBits(dire_port,dire_pin);
								GPIO_ResetBits(enab4_port,enab4_pin);
								for(noofstep = 0; noofstep < NoofStep; noofstep++)
								{
									StepMot();	
								}
								GPIO_SetBits(enab4_port,enab4_pin);
								break;
					 default: 	lcd_gotoxy(1,1);
								lcd_write_string("               ");
								delay(0xFFF);
								lcd_gotoxy(2,1);
								lcd_write_string("INVALID COMMAND ");
								break;
				}
				Clean_Buff();
				//delete_all_message();
				//receiveready = 0;
			}
			else
			{	goto CHECK;	  } 
		//	}
				// delay(0xFFFF);
				//	GPIO_SetBits(buzzer_port,buzzer_pin);
				//	delay(10000);delay(10000);
				//	GPIO_ResetBits(buzzer_port,buzzer_pin)
				//	;delay(10000);delay(10000);delay(10000);delay(10000);delay(10000);
				//	GPIO_ResetBits(buzzer_port,buzzer_pin);delay(10000);delay(10000);
				//	GPIO_SetBits(buzzer_port,buzzer_pin);
				//	delay(10000);delay(10000);delay(10000);delay(10000);delay(10000);
				//	GPIO_ResetBits(buzzer_port,buzzer_pin);
	} 
}

void display_signal_strength(void)
{
				send_command(0x40);	delay(7200);
				send_data(0x01);		delay(7200);
				send_data(0x01);		delay(7200);
				send_data(0x01);		delay(7200);
				send_data(0x05);		delay(7200);
				send_data(0x05);		delay(7200);
				send_data(0x05);		delay(7200);
				send_data(0x15);		delay(7200);
				send_data(0x15);		delay(7200);
				lcd_gotoxy(1,16);  // Force cursor to beginning of 1st line, if the number is 0x83 then force the cursor to 53rd position        
        delay(7200);
				send_data(0x00); // locate the first character in CGRAM
				delay(7200);
}



void Clean_Buff(void)
{
	delete_all_message();
	for(Rx=0;Rx<RxIn;Rx++)
	{
		SystemBuf[Rx] = 0x00;   
	}
	Rx=0; 
	receiveready = 0;
}

void delay_key(unsigned int i )
{
	while(i--);
}



/**
  * @brief  Configures GPIO.
  * @param  GPIOx		: Specifies The Output port to be configured. 
  *			GPIO_Pin	: Specifies The	Output Pin To be Configured.
  * 		Mode		: Specifies The Mode Of Operation Of Output Pin.
  * 		Speed		: Specifies The Speed Of Operation Of Output Pin.
  * @retval None
  */

/*void send_one_byte(unsigned char d)
{
   char   a;

   for(a=0;a<8;a++)
   {   //send 8 bits 
      if(d & (0x80 >> a)) 
      {
         GPIO_ResetBits(Port[a],Pin[a]);
      }
			else
				  GPIO_SetBits(Port[a],Pin[a]);
   }
}		 */

void display_logo(void)
{
		lcd_clr();
		lcd_gotoxy(1,1);delay(0xFFF);
		lcd_write_string("   GSM BASED    ");
		lcd_gotoxy(2,1);delay(0xFFF);
		//send_command(0x0c);delay(0xFFF);
		lcd_write_string("VENDING MACHINE ");
		delay(0xFFFF);
		
}

/*void beep_buzzer (void)
{
	unsigned int i;
	for(i=0; i< 500; i++)
	{
		GPIO_SetBits(buzzer_port,buzzer_pin);
		delay(500);
		GPIO_ResetBits(buzzer_port,buzzer_pin);
	}
}  */

void RefPosMot(void)
{
	lcd_clr();
	lcd_gotoxy(1,1); delay(0xFFF);
	lcd_write_string("   Ref. Pos.    ");
	lcd_gotoxy(2,1); delay(0xFFF);
	lcd_write_string("    Approch     ");
	Z:
	GPIO_SetBits(dire_port,dire_pin);
	GPIO_SetBits(enab1_port,enab1_pin);	  					//motor 1
	StepMot();
	GPIO_ResetBits(enab1_port,enab1_pin);
	if((GPIO_ReadInputDataBit(ref_port,ref_pin))== 0)
	{
		GPIO_ResetBits(dire_port,dire_pin);
		return;
	}
	GPIO_SetBits(enab2_port,enab2_pin);						//motor 2
	StepMot();
	GPIO_ResetBits(enab2_port,enab2_pin);
	if((GPIO_ReadInputDataBit(ref_port,ref_pin))== 0)
	{
		GPIO_ResetBits(dire_port,dire_pin);
		return;
	}
	GPIO_SetBits(enab3_port,enab3_pin);		 				//motor 3
	StepMot();
	GPIO_ResetBits(enab3_port,enab3_pin);
	if((GPIO_ReadInputDataBit(ref_port,ref_pin))== 0)
	{
	    GPIO_ResetBits(dire_port,dire_pin);
		return;
	}
	GPIO_SetBits(enab4_port,enab4_pin);		  				//motor 4
	StepMot();
	GPIO_ResetBits(enab4_port,enab4_pin);
	if((GPIO_ReadInputDataBit(ref_port,ref_pin))== 0)
	{
	    GPIO_ResetBits(dire_port,dire_pin);
		return;
	}
	goto Z;
	//GPIO_ResetBits(dire_port,dire_pin);
}

void StepMot(void)
{
  GPIO_SetBits(step_port,step_pin);	
	delay(0x2FFFF);
	GPIO_ResetBits(step_port,step_pin); 
	delay(0x7FF); 
}






