#include "GSM.h"



extern unsigned char keyno;
extern uint32_t timer;
unsigned char mesgage_check_after_dailing_flag;
unsigned char  RxIn=120;	//Define the length of the array received 90
unsigned char  AT[]="AT";	//Handshake signals
unsigned char  ATE[]="ATE0";	 //Off echo
unsigned char  ATW[]="AT&W";	 //SAVE PARAMETERS
unsigned char  AT_IPR[]="AT+IPR=9600";	 //baud rate 
unsigned char  gsm_data_flag=0;
unsigned char  phone_number_array[45][14];
unsigned char  MYNUM[] 		= "9783831755";
unsigned char  ATD[18] 		= "ATD9783831755;";
unsigned char  AT_CPIN[]	="AT+CPIN=?";  //check pin status
unsigned char  AT_CREG[]	="AT+CREG?";
unsigned char  AT_CGREG[]	="AT+CGREG?";
unsigned char  AT_CLIP[] = "AT+CLIP=1";//CALLER DETAIL
unsigned char  AT_COLP[] = "AT+COLP=1";//ATENDEE WHILE CALL IS INTIMATED 
unsigned char  AT_QMDA[] = "AT+CMGD=1,4";	//delete all SMS command//"AT+QMGDA= DEL ALL ";
unsigned char  ATH[]      = "ATH";
unsigned char  AT_CCLK[] 	=	"AT+CCLK?";
unsigned char  AT_CSQ[] 	=	"AT+CSQ";
unsigned char  AT_CSQA[]	=	"AT+CSQ=?";
unsigned char  AT_QEXTUNSOL[]= "AT+QEXTUNSOL=" ;
unsigned char  AT_QNITZ[] =	"AT+QNITZ=1";
unsigned char  AT_CNMI[]	=	"AT+CNMI=2,1,0,1,0";//Set this set of parameters to the new information directly to the serial port, and no storage
unsigned char  AT_CSCA[]	=	"AT+CSCA=+8613800100500";//Set the service center number
unsigned char  AT_CMGF[]	=	"AT+CMGF=1";//Set the format of the SMS text format
unsigned char  AT_CMGR[]	=	"AT+CMGR=";//Read SMS commands
unsigned char  AT_CMGS[]	=	"AT+CMGS=";//Send SMS command
unsigned char  AT_CMGD[]	=	"AT+CMGD=";//delete SMS command
unsigned char  successfully1[]="INPUT 1 FAULTY!";//Send operation is successful to the target number
unsigned char  successfully2[]="INPUT 2 FAULTY!";
unsigned char  successfully3[]="INPUT 3 FAULTY!";
unsigned char  system_on_status[]= "SYSTEM POWER ON";
unsigned char  pass[]="Operate sucess!";
unsigned char  fail[]="Operate failed,try again!";	//Send operation failed to the target number
unsigned char AT_delete[12];
unsigned char AT_Read[12];	//Send read SMS command used to store 
unsigned char AT_SendNumber[50];  //Used to store the SMS number instruction
unsigned char numberbuf[14];		 //Used to save the number of short messages 
unsigned char  SystemBuf[120];  //Save export receive data 
unsigned char  CommandBuf[15];	//Used to store instructions 
unsigned char  state[17];	  		//Used to store IO port state 
unsigned char  state1[17];	 	//Used to store IO port state 
unsigned char Rx=0;
unsigned int temp;						//Record status 	 
unsigned char temp1;					// P0 port status is used to record
unsigned char temp2;   				//  P2 port status is used to record 
unsigned int check=0;					//Query flag 
unsigned int receiveready=0;		  //Receive SMS flag
unsigned int sendready=0;		      //Send SMS ready flag
unsigned int send=0;				   //Send SMS flag
unsigned int flag=0;				   //Command flag
unsigned char operate=0;			   //Command to select
extern u8 USART1GetBufDat( void );
void Delay_ms(unsigned int i);
void Start_GSM(void);
void UART_init (void);
void dial_number(unsigned char,unsigned char );
void sendstring(unsigned char *p);
void GSM_INIT(void);
void receive_ready(void);
unsigned char message_read(void);
void read_message(void);
u8 sendmessage(unsigned char);
u8 sendmessage_multiple(unsigned char, unsigned char);
void delete_all_message(void);
u8 check_signal_strength(unsigned char lcd_flag);
extern unsigned char key_check(void);
extern void key_action(void);
extern void superloop(void);
extern void delay_key(unsigned int);
/******************************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////The function void Delay_ms (uint i); functions: millisecond delay//////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************/
//void Delay_ms(unsigned int i)
//{
//    unsigned int j;
//    for(;i>0;i--){
//    for(j=0;j<125;j++)
//    {;}
// }
//}
/******************************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////The function void Start_GSM (void); functions://///////////////////////////
//The detailed function: the the P3_7 pin on the microcontroller is connected with the TC35 IGT pin; need to start 
// plus the length of at least 100ms low-level signals,
///And fall time of the signal is less than 1ms. Starts, the 15 feet of the signal should remain high.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************/
void Start_GSM(void)
{
  GPIO_SetBits(GPIOB, GPIO_Pin_1 );
  SysTickDelay(100);
 	GPIO_ResetBits(GPIOB, GPIO_Pin_1 );
 	SysTickDelay(1000);
 	GPIO_SetBits(GPIOB, GPIO_Pin_1 );
 	SysTickDelay(1000);
}
/******************************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////The function void sendstring (uchar * p); functionality: send the string through the serial port///////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************/
void sendstring(unsigned char *p)
{  
  while(*p)
  {
  USART1_SendByte(*p);
  p++;
	}
  USART1_SendByte(0x0D);
  USART1_SendByte(0x0A);
}

/******************************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////The function void GSM_INIT (void); functions: initialization TC35 module/////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************/
void GSM_INIT(void)
{
		lcd_clr();delay(0xFFF);
		lcd_gotoxy(1,1);delay(0xFFF);
		lcd_write_string("INIT GSM........");
		SysTickDelay(9000);
LOOP:
		lcd_gotoxy(1,1);delay(0xFFF);
		lcd_write_string("SEARCHING N/W...");
					for(Rx=0;Rx<RxIn;Rx++)
					{
									SystemBuf[Rx]=0x00;   
					}
					Rx=0; delay(0xFFF);
	sendstring(AT);//2,3
	SysTickDelay(600);
	sendstring(ATE);//8,9
	SysTickDelay(600);
	//sendstring(AT_CPIN);//30,31
	//SysTickDelay(600);
	//sendstring(AT_IPR);//36,37
 	//SysTickDelay(600);
	sendstring(AT_CLIP);//42,43
 	SysTickDelay(600);
	sendstring(AT_COLP);//48,49
 	SysTickDelay(600);
	sendstring(AT_CMGF);//54,55
	SysTickDelay(600);
	sendstring(AT_CNMI); // new mesg indication and delivery report69,70
	SysTickDelay(600);
	sendstring(ATW);//60,61
	SysTickDelay(600);
	delete_all_message();
	SysTickDelay(600);
	
/*	if((SystemBuf[2]=='O')&&(SystemBuf[3]=='K')&&(SystemBuf[8]=='O')&&(SystemBuf[9]=='K')
		&&(SystemBuf[30]=='O')&&(SystemBuf[31]=='K')&&(SystemBuf[36]=='O')&&(SystemBuf[37]=='K')
	&&(SystemBuf[42]=='O')&&(SystemBuf[43]=='K')&&(SystemBuf[48]=='O')&&(SystemBuf[49]=='K')
	&&(SystemBuf[54]=='O')&&(SystemBuf[55]=='K')&&(SystemBuf[60]=='O')&&(SystemBuf[61]=='K')
	&&(SystemBuf[66]=='O')&&(SystemBuf[67]=='K')&&(SystemBuf[72]=='O')&&(SystemBuf[73]=='K')) 	*/ //Determine whether the module initialization is successful, the success of the module will reply "OK" to the microcontroller
	if((SystemBuf[2] == 'O')&&(SystemBuf[3]=='K'))
	{											//If the microcontroller is not received the OK to continue to send the initialization command /

			for(Rx=0;Rx<RxIn;Rx++)
					{
									SystemBuf[Rx]=0x00;   
					}
					Rx=0;
			check_sim_presence(1);
			SysTickDelay(1000);		
			if((check_signal_strength(1)== 2)||(	check_signal_strength(1)== 1)) // netwok strength 87,88
			{SysTickDelay(4000);	}
			else
			{goto LOOP;   				}  
			
											
	}
	else
	{ 		 for(Rx=0;Rx<RxIn;Rx++)
					{
									SystemBuf[Rx]=0x00;   
					}
					Rx=0; 
			if(check_sim_presence(1)== 1)
			{SysTickDelay(1000);		
			check_signal_strength(1);
			SysTickDelay(3000);	}
			goto LOOP;              
	}
	
 	for(Rx=0;Rx<RxIn;Rx++)
	{
					SystemBuf[Rx]=0x00;   
	}
	Rx=0; 

}
/******************************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////The function void receive_ready (void); functions: receive SMS ready///////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************/ 
void receive_ready(void)
{
  unsigned char i;
	if((SystemBuf[1]!=0x00)&&(SystemBuf[2]!=0x00))
	{	SysTickDelay(300);
		if((SystemBuf[3]=='C')&&(SystemBuf[4]=='M')&&(SystemBuf[5]=='T')&&SystemBuf[6]=='I')		 //If you have a new text message arrives, the module will send a string through the serial port to the microcontroller,
		{							 //The function of this function is to determine whether there is a new text comes to set prepared to accept the flag 1
		receiveready=1;					 //If not a new SMS instruction, it is discarded, and the receiver array is cleared /
		}
		else
		{ 
		for(i=0;i<Rx;i++)	
				{
								SystemBuf[i]=0x00;   
				}
				Rx=0; 	
		}
	}
	
 }
/******************************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////The function void message_read (void); functions: to determine SMS, ready reply SMS to the target number/////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************/ 
 unsigned char message_read(void)
{		
  unsigned char ig;
  if((SystemBuf[3]=='C')&&(SystemBuf[4]=='M')&&(SystemBuf[5]=='G')&&(SystemBuf[6]=='R'))
  {
    	if((SystemBuf[14] == 'U')&&(SystemBuf[15]=='N'))
    	{
    		 ig = SystemBuf[65];
			 return ig;
    	}
    	else
    	{
			 ig = SystemBuf[63];
			 return ig;
    	}
  }
  else
  send=0;
   SysTickDelay(500);
   SysTickDelay(500);
   for(Rx=0;Rx<RxIn;Rx++)
   {
     SystemBuf[Rx]=0x00;    
   }
   Rx=0;  
   return 0x00;	  
}
/******************************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////The function void read_message (void); functions: send read SMS commands,//////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************/ 	 
void read_message(void)
{
   unsigned char i;
   SysTickDelay(1000);
		for(Rx=0;Rx<RxIn;Rx++)
		{
						SystemBuf[Rx]=0x00;    
		}
		Rx=0; 
		for(i=0;i<8;i++)
		{
		AT_Read[i]=AT_CMGR[i];
		}
		AT_Read[i]='1';
    	sendstring(AT_Read);						   //Send AT + CMGR =?,? Behalf SMS storage location
		SysTickDelay(500);
		SysTickDelay(500);
}
/******************************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////The function void readcommend (void); functions: to read the content of the message to determine the///////////// 
////corresponding instruction is correct/////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************/ 
 void readcommend(unsigned char task, unsigned char message_content_pos)
 {
  	unsigned char  sucess_fail =0;uint16_t temp_var = 0;
		flag=1;
	//	PWR_BackupAccessCmd(ENABLE);
		message_content_pos =message_content_pos+2;
		switch (task)
		{
			case 0x31: 
			{
				if(SystemBuf[message_content_pos] == 0x31)
				{
					message_content_pos = message_content_pos+2;
					if(SystemBuf[message_content_pos] == 'A')
					{
						temp_var = BKP_ReadBackupRegister(BKP_DR9);
						temp_var &= 0xFFFE; 
						BKP_WriteBackupRegister(BKP_DR9,temp_var );	
						sucess_fail =1;
					}
					else
					if(SystemBuf[message_content_pos] == 'D')
					{
						temp_var = BKP_ReadBackupRegister(BKP_DR9);
						temp_var |= 0x0001; 
						BKP_WriteBackupRegister(BKP_DR9,temp_var );
						sucess_fail = 1;
					}
					
				}
				else
				if(SystemBuf[message_content_pos] == 0x32)
				{
					message_content_pos = message_content_pos+2;
					if(SystemBuf[message_content_pos] == 'A')
					{
						temp_var = BKP_ReadBackupRegister(BKP_DR9);
						temp_var &= 0xFFFD; 
						BKP_WriteBackupRegister(BKP_DR9,temp_var );
						sucess_fail =1;
					}
					else
					if(SystemBuf[message_content_pos] == 'D')
					{
						temp_var = BKP_ReadBackupRegister(BKP_DR9);
						temp_var |= 0x0002; 
						BKP_WriteBackupRegister(BKP_DR9,temp_var );
						sucess_fail =1;
					}
				}
				else
				if(SystemBuf[message_content_pos] == 0x33)
				{
					message_content_pos = message_content_pos+2;
					if(SystemBuf[message_content_pos] == 'A')
					{
						temp_var = BKP_ReadBackupRegister(BKP_DR9);
						temp_var &= 0xFFFB; 
						BKP_WriteBackupRegister(BKP_DR9,temp_var );
						sucess_fail =1;
					}
					else
					if(SystemBuf[message_content_pos] == 'D')
					{
						temp_var = BKP_ReadBackupRegister(BKP_DR9);
						temp_var |= 0x0004; 
						BKP_WriteBackupRegister(BKP_DR9,temp_var );
						sucess_fail =1;
					}
				}
			}
				break;
			case 0x32:
			{
				if(SystemBuf[message_content_pos] == 0x31)
				{
					message_content_pos = message_content_pos+2;
					if(SystemBuf[message_content_pos] == 'E')
					{
						temp_var = BKP_ReadBackupRegister(BKP_DR9);
						temp_var &= 0xFFFE; 
						BKP_WriteBackupRegister(BKP_DR9,temp_var );	
						sucess_fail =1;
					}
					else
					if(SystemBuf[message_content_pos] == 'O')
					{
						temp_var = BKP_ReadBackupRegister(BKP_DR9);
						temp_var |= 0x0001; 
						BKP_WriteBackupRegister(BKP_DR9,temp_var );
						sucess_fail =1;
					}
					
				}
				else
				if(SystemBuf[message_content_pos] == 0x32)
				{
					message_content_pos = message_content_pos+2;
					if(SystemBuf[message_content_pos] == 'E')
					{
						temp_var = BKP_ReadBackupRegister(BKP_DR9);
						temp_var &= 0xFFFD; 
						BKP_WriteBackupRegister(BKP_DR9,temp_var );
						sucess_fail =1;
					}
					else
					if(SystemBuf[message_content_pos] == 'O')
					{
						temp_var = BKP_ReadBackupRegister(BKP_DR9);
						temp_var |= 0x0002; 
						BKP_WriteBackupRegister(BKP_DR9,temp_var );
						sucess_fail =1;
					}
				}
				else
				if(SystemBuf[message_content_pos] == 0x33)
				{
					message_content_pos = message_content_pos+2;
					if(SystemBuf[message_content_pos] == 'E')
					{
						temp_var = BKP_ReadBackupRegister(BKP_DR9);
						temp_var &= 0xFFFB; 
						BKP_WriteBackupRegister(BKP_DR9,temp_var );
						sucess_fail =1;
					}
					else
					if(SystemBuf[message_content_pos] == 'O')
					{
						temp_var = BKP_ReadBackupRegister(BKP_DR9);
						temp_var |= 0x0004; 
						BKP_WriteBackupRegister(BKP_DR9,temp_var );
						sucess_fail =1;
					}
				}
			}
				break;
			case 0x33:
			{
				if(SystemBuf[message_content_pos] == 0x31)
				{
					message_content_pos = message_content_pos+2;
					if(SystemBuf[message_content_pos] == 'C')
					{
						temp_var = BKP_ReadBackupRegister(BKP_DR9);
						temp_var &= 0xFEFF; 
						BKP_WriteBackupRegister(BKP_DR9,temp_var );
						sucess_fail =1;
					}
					else
					if(SystemBuf[message_content_pos] == 'O')
					{
							temp_var = BKP_ReadBackupRegister(BKP_DR9);
							temp_var |= 0x0100; 
							BKP_WriteBackupRegister(BKP_DR9,temp_var );	
							sucess_fail =1;
					}
					
				}
				else
				if(SystemBuf[message_content_pos] == 0x32)
				{
					message_content_pos = message_content_pos+2;
					if(SystemBuf[message_content_pos] == 'C')
					{
										temp_var = BKP_ReadBackupRegister(BKP_DR9);
										temp_var &= 0xFDFF; 
										BKP_WriteBackupRegister(BKP_DR9,temp_var );
										sucess_fail =1;
					}
					else
					if(SystemBuf[message_content_pos] == 'O')
					{
										temp_var = BKP_ReadBackupRegister(BKP_DR9);
										temp_var |= 0x0200; 
										BKP_WriteBackupRegister(BKP_DR9,temp_var );
										sucess_fail =1;
					}
				}
				else
				if(SystemBuf[message_content_pos] == 0x33)
				{
					message_content_pos = message_content_pos+2;
					if(SystemBuf[message_content_pos] == 'C')
					{
										temp_var = BKP_ReadBackupRegister(BKP_DR9);
										temp_var &= 0xFBFF; 
										BKP_WriteBackupRegister(BKP_DR9,temp_var );
										sucess_fail =1;
					}
					else
					if(SystemBuf[message_content_pos] == 'O')
					{
										temp_var = BKP_ReadBackupRegister(BKP_DR9);
										temp_var |= 0x0400; 
										BKP_WriteBackupRegister(BKP_DR9,temp_var );
										sucess_fail =1;
					}
				}
			}
				break;
			
			case 0x34:
				if((SystemBuf[message_content_pos] == 'F')&&(SystemBuf[message_content_pos+1] == 'U')&&(SystemBuf[message_content_pos+2] == 'L')&&(SystemBuf[message_content_pos+3] == 'L')&&
					(SystemBuf[message_content_pos+4] == 'D')&&(SystemBuf[message_content_pos+5] == 'I')&&(SystemBuf[message_content_pos+6] == 'S')&&
					(SystemBuf[message_content_pos+7] == 'A')&&(SystemBuf[message_content_pos+8] == 'R')&&(SystemBuf[message_content_pos+9] == 'M'))
				{
									//	PWR_BackupAccessCmd(ENABLE);
										temp_var = BKP_ReadBackupRegister(BKP_DR9);
										temp_var |= 0x0001; 
										BKP_WriteBackupRegister(BKP_DR9,temp_var );
										temp_var = BKP_ReadBackupRegister(BKP_DR9);
										temp_var |= 0x0002; 
										BKP_WriteBackupRegister(BKP_DR9,temp_var );
										temp_var = BKP_ReadBackupRegister(BKP_DR9);
										temp_var |= 0x0004; 
										BKP_WriteBackupRegister(BKP_DR9,temp_var );
										sucess_fail =1;		
					
				}
				break;
			case 0x35:
				if((SystemBuf[message_content_pos] == 'F')&&(SystemBuf[message_content_pos+1] == 'U')&&(SystemBuf[message_content_pos+2] == 'L')&&(SystemBuf[message_content_pos+3] == 'L')&&
					(SystemBuf[message_content_pos+4] == 'A')&&(SystemBuf[message_content_pos+5] == 'R')&&(SystemBuf[message_content_pos+6] == 'M'))
				{
									//	PWR_BackupAccessCmd(ENABLE);
										temp_var = BKP_ReadBackupRegister(BKP_DR9);
										temp_var |= 0x0001; 
										BKP_WriteBackupRegister(BKP_DR9,temp_var );
										temp_var = BKP_ReadBackupRegister(BKP_DR9);
										temp_var |= 0x0002; 
										BKP_WriteBackupRegister(BKP_DR9,temp_var );
										temp_var = BKP_ReadBackupRegister(BKP_DR9);
										temp_var |= 0x0004; 
										BKP_WriteBackupRegister(BKP_DR9,temp_var );
										sucess_fail =1;		
					
				}
				break;
			case 0x36:
				break;
			case 0x37:
				break;
			case 0x38:
				break;
		}
		if(sucess_fail == 0x01)
		{
					sendmessage(sucess_fail);
		}
		else
		{
					sendmessage(sucess_fail);
		}
}
/******************************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////The function void readstate;: P0, P2 port state into an array,///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************/
//void readstate(void)
//{  
//   unsigned int bitcnt,i,j;
//   for(bitcnt=0,i=0;bitcnt<16,i<16;bitcnt++,i++)
//   {
//       if((temp<<bitcnt)&0x8000){state1[i]=0x30;}
//	   else state1[i]=0x31;
//	   }
//	for(j=15,i=0;j>=0,i<16;j--,i++)
//	{
//	  state[j]=state1[i];
//	  }
//}


/******************************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////The function void delete_message; Function: Remove read SMS commands,//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************/ 
 void delete_message(unsigned char x)
{
   unsigned char i;unsigned char AT_delete[12];
	 for(Rx=0;Rx<RxIn;Rx++)
		{
						SystemBuf[Rx]=0x00;    
		}
		Rx=0; 
  
	 	SysTickDelay(1000);
		for(i=0;i<8;i++)
		{
			AT_delete[i]=AT_CMGD[i];
		}
		AT_delete[i] = x + 0x30;
		while(1)
		{
			for(Rx=0;Rx<RxIn;Rx++)
			{
				SystemBuf[Rx]=0x00;    
			}
		Rx=0; 
		sendstring(AT_delete);						   //Send AT + CMGR =?,? Behalf SMS storage location
		SysTickDelay(1000);
			if((SystemBuf[2] == 'O')&&(SystemBuf[3] == 'K'))
			{
				break;
			}
		}
		
}
void delete_all_message(void)
{
	sendstring(AT_QMDA);
	SysTickDelay(1000);
	//SysTickDelay(1000);
}
//*****************sim presence*************
u8 check_sim_presence(unsigned char lcd_flag)
{	unsigned char flag =0;
	for(Rx=0;Rx<RxIn;Rx++)
	{
					SystemBuf[Rx] = 0x00;   
	}
	Rx=0; 
	sendstring(AT_CPIN);//30,31
	SysTickDelay(1000);
	SysTickDelay(1000);
	/*if(SystemBuf[3]== 'C'&& SystemBuf[4]== 'P'&& SystemBuf[5]== 'I'&&
		 SystemBuf[6]== 'N'&& SystemBuf[9]== 'R'&& SystemBuf[10]== 'E')	 */
	if((SystemBuf[2] == 'O')&&(SystemBuf[3]=='K'))
	{flag = 1;}
	if(lcd_flag ==1)
	{
		if(flag==1)
		{	lcd_clr();delay(0xFFF);
			lcd_gotoxy(1,1);delay(0xFFF);
			lcd_write_string("SIM DETECTED");
			return 1;
		}
		else
		{	lcd_clr();delay(0xFFF);
			lcd_gotoxy(1,1);delay(0xFFF);
			lcd_write_string("SIM NOT DETECTED");
			return 0;
		}	
	}
	else
		return 0;
}

//************signal strenth*******************
u8 check_signal_strength(unsigned char lcd_flag)
{ 
	unsigned int var = 0;
	receiveready =1;
	sendstring(AT_CSQA);// netwok strength 87,88
	SysTickDelay(300);
	for(Rx=0;Rx<RxIn;Rx++)
	{
					SystemBuf[Rx] = 0x00;   
	}
	Rx=0; 
	sendstring(AT_CSQ);// netwok strength 87,88
	SysTickDelay(200);	
	if(SystemBuf[9] == 0x2C)
	{
	var = SystemBuf[8];
	}
	else
	{
			var = 10 * (SystemBuf[8] - 0x30);
		var = var +(SystemBuf[9] - 0x30);
	}
	if(lcd_flag == 1)//if display on lcd
		{
		lcd_clr();delay(0xFFF);
		lcd_gotoxy(1,1);delay(0xFFF);
		lcd_write_string("SIGNAL STRENTH ");
		//lcd_gotoxy(2,1);delay(0xFFF);	
		//send_data((var/10)+0x30);
		//delay(0xFFF);	
		//send_data((var%10)+0x30);
		//delay(0x7FF);
					if(var <= 8)
					{//reurn no signal 
					lcd_gotoxy(2,4);delay(0xFFF);
					lcd_write_string("NO NETWORK");
					}
					else
						if((8 < var) && (var <= 15))
						{//low strength
						lcd_gotoxy(2,4);delay(0xFFF);
					lcd_write_string("LOW SIGNAL");
						}
						else
						if((15 <var) && (var < 32))
						{//high signal strenth
						lcd_gotoxy(2,4);delay(0xFFF);
						lcd_write_string("HIGH SIGNAL");
						}	
		}
		if(var <= 8)
		{//reurn no signal 
			send_command(0x40);	delay(7200);
				send_data(0x00);		delay(7200);
				send_data(0x00);		delay(7200);
				send_data(0x00);		delay(7200);
				send_data(0x00);		delay(7200);
				send_data(0x00);		delay(7200);
				send_data(0x00);		delay(7200);
				send_data(0x01);		delay(7200);
				send_data(0x01);		delay(7200);
				lcd_gotoxy(1,16);  // Force cursor to beginning of 1st line, if the number is 0x83 then force the cursor to 53rd position        
        delay(7200);
				send_data(0x00); // locate the first character in CGRAM
				delay(7200);
			return 0;
		}
		else
			if(8< var && var <= 15)
			{//low strength
				send_command(0x40);	delay(7200);
				send_data(0x00);		delay(7200);
				send_data(0x00);		delay(7200);
				send_data(0x00);		delay(7200);
				send_data(0x04);		delay(7200);
				send_data(0x04);		delay(7200);
				send_data(0x04);		delay(7200);
				send_data(0x14);		delay(7200);
				send_data(0x14);		delay(7200);
				lcd_gotoxy(1,16);  // Force cursor to beginning of 1st line, if the number is 0x83 then force the cursor to 53rd position        
        delay(7200);
				send_data(0x00); // locate the first character in CGRAM
				delay(7200);
				return 1;
			}
			else
				if((15 < var) && (var < 32))
				{//high signal strenth
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
					return 2;
				}				
		return 0;
		
}

/******************************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////The function void sendmessage (void); achieve function: send a reply SMS commands,//////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************/  
u8 sendmessage(unsigned char fault_mesg)
{
  unsigned char i,ref=5;
	unsigned int timer;
  //u8 x;
	SysTickDelay(1000);
	for(i=0;i<8;i++)
		{
						AT_SendNumber[i]=AT_CMGS[i];
		}
		AT_SendNumber[8] = 0x22;
		for(i=9;(i<23) && (numberbuf[i-9] != 0x03);i++)
		{	if(numberbuf[i-9] != 0x03)
			AT_SendNumber[i]=numberbuf[i-9];		//To extract other numbers used to reply to the other party
		}
		AT_SendNumber[i] = 0x22;
	
	sendstring(AT_SendNumber);
	SysTickDelay(800);
	switch (fault_mesg)
	{
	case 0:
		sendstring(fail);
		break;
	case 1:
		sendstring(pass);
		break;

	}		    
	SysTickDelay(300);
	USART1_SendByte(0x1A);SysTickDelay(800);
	for(Rx=0;Rx<RxIn;Rx++)
		{
						SystemBuf[Rx]=0x00;    
		}
		Rx=0;
	if((SystemBuf[11]=='E')&&(SystemBuf[12]=='R')&&(SystemBuf[13]=='R')&&SystemBuf[14]=='O')
					{
					return 1;
					}
		for(Rx=0;Rx<RxIn;Rx++)
		{
						SystemBuf[Rx]=0x00;    
		}
		Rx=0; 
		timer = RTC_GetCounter();
	while(1)
	{		SysTickDelay(1000);
			if(((SystemBuf[0]!=0x00)&&(SystemBuf[0]!=0x00))|| ((RTC_GetCounter() - timer) >= ref))
			{
				if((SystemBuf[3]=='C')&&(SystemBuf[4]=='M')&&(SystemBuf[5]=='G')&&SystemBuf[6]=='S')		 //If you have a new text message arrives, the module will send a string through the serial port to the microcontroller,
				{							 //The function of this function is to determine whether there is a new text comes to set prepared to accept the flag 1
				//receiveready=1;					 //If not a new SMS instruction, it is discarded, and the receiver array is cleared /
				return 1;
				}
				else
				{ 
					return 0;
				}
			}
		for(Rx=0;Rx<RxIn;Rx++)
		{
						SystemBuf[Rx]=0x00;    
		}
		Rx=0;			
	}
}

u8 sendmessage_multiple(unsigned char fault_mesg, unsigned char phone_seq_no)
{
  unsigned char i,j = 0,ref=6;
	unsigned int timer;
	extern unsigned char  phone_number_array[45][14];
  //u8 x;
											//	check_exit_key();
												for(i=0;i<8;i++)
                        {
                                AT_SendNumber[i]=AT_CMGS[i];
                        }
												AT_SendNumber[8] = 0x22;
												for(i=9;i<23;i++)
                        {
														if(phone_number_array[phone_seq_no][i-9] != 0x03)
														{
															j=phone_number_array[phone_seq_no][i-9];		//To extract other numbers used to reply to the other party
															AT_SendNumber[i] = j;
														}
														else 
														{
															AT_SendNumber[i] = 0x22;
															break;
														}
                        }
												
	
	sendstring(AT_SendNumber);
	SysTickDelay(400);
	switch (fault_mesg)
	{
		case 1:
			sendstring(successfully1);
			break;
		case 2:
			sendstring(successfully2);
			break;
		case 3:
			sendstring(successfully3);
			break;
		case 4:
			sendstring(system_on_status);
			break;
	}
				 
		    
	SysTickDelay(300);
	USART1_SendByte(0x1A);	
//	check_exit_key();
	SysTickDelay(800);
		
		if((SystemBuf[11]=='E')&&(SystemBuf[12]=='R')&&(SystemBuf[13]=='R')&&SystemBuf[14]=='O')
					{
					return 1;
					}
		for(Rx=0;Rx<RxIn;Rx++)
		{
						SystemBuf[Rx]=0x00;    
		}
		Rx=0; 
		timer = RTC_GetCounter();
		
	while(1)
	{	//	check_exit_key();SysTickDelay(200);check_exit_key();SysTickDelay(200);check_exit_key();SysTickDelay(200);check_exit_key();SysTickDelay(200);check_exit_key();
			if((SystemBuf[0]!=0x00)&&(SystemBuf[0]!=0x00)|| ((RTC_GetCounter() - timer) >= ref))
			{	
				if((SystemBuf[3]=='C')&&(SystemBuf[4]=='M')&&(SystemBuf[5]=='G')&&SystemBuf[6]=='S')		 //If you have a new text message arrives, the module will send a string through the serial port to the microcontroller,
				{	//The function of this function is to determine whether there is a new text comes to set prepared to accept the flag 1
				//receiveready=1;					 //If not a new SMS instruction, it is discarded, and the receiver array is cleared /
				return 1;
				}
				else
				{ 
					return 0;
				}
			}
		
	}
}

/*void dial_number(unsigned char message_num,unsigned char phone_seq_no)
{		
		unsigned char i = 0,j=0,flag=0, ref =15;uint32_t timer,keypad_trace_var;
		extern unsigned char  phone_number_array[45][14];
		extern unsigned char gsm_data_flag;
		check_exit_key();
if((phone_number_array[phone_seq_no][4] == 0x03)&&(phone_number_array[phone_seq_no][5] == 0x03)
	&&(phone_number_array[phone_seq_no][6] == 0x03)&&(phone_number_array[phone_seq_no][7] == 0x03))
{
	return;
}
	
		AT_SendNumber[0] = 'A';
		AT_SendNumber[1] = 'T';
		AT_SendNumber[2] = 'D';
		for(i=3;i<17;i++)
		{
				if(phone_number_array[phone_seq_no][i-3] != 0x03)
				{
					j=phone_number_array[phone_seq_no][i-3];		//To extract other numbers used to reply to the other party
					AT_SendNumber[i] = j;
				}
				else 
				{
					AT_SendNumber[i] = 0x3b;i++;
					while(i<=27)
					{AT_SendNumber[i] = 0x00;i++;}	
					break;
				}
		}
		gsm_data_flag =0;
		lcd_clr();delay(0xFFF);
		lcd_gotoxy(1,1);delay(0xFFF);
		lcd_write_string("Dailing number..");		
		lcd_gotoxy(2,1);i=0;
		while(phone_number_array[phone_seq_no][i] != 0x03)
		{
		send_data(phone_number_array[phone_seq_no][i]);
		delay(0xFFF);
		i++;
		}
		for(Rx=0;Rx<RxIn;Rx++)
		{
				SystemBuf[Rx]=0x00;    
		}
		Rx=0;
		check_exit_key();
		sendstring(AT_SendNumber);
		SysTickDelay(100);
		for(Rx=0;Rx<RxIn;Rx++)
		{
				SystemBuf[Rx]=0x00;    
		}
		Rx=0;
		timer = RTC_GetCounter();ref = 22;flag =0;
		while(1)
		{	//SysTickDelay(1000);
				check_exit_key();
				
			if((SystemBuf[0]!=0x00)&&(SystemBuf[1]!=0x00)&&(SystemBuf[2]!=0x00)&&(SystemBuf[3]!=0x00))
			{SysTickDelay(100);
				
				if((SystemBuf[2] == '+')&&(SystemBuf[3] == 'C')
					&&(SystemBuf[4] == 'O')&&(SystemBuf[5] == 'L')&&(SystemBuf[6] == 'P'))
				{		flag = 1;
						lcd_clr();
						delay(0xFFF);
						lcd_gotoxy(1,1);delay(0xFFF);
						lcd_write_string("call picked");delay(0x3FFFFF);
					//	play_message(message_num,gsm,1);
						sendstring(ATH);
						break;
				}
				
				
				if((SystemBuf[2] == 'N')&&(SystemBuf[3] == 'O')
						&&(SystemBuf[4] == ' ')&&(SystemBuf[5] == 'C')&&(SystemBuf[6] == 'A')
						&&(SystemBuf[7] == ' ')&&(SystemBuf[8] == 'C'))
				{
						lcd_clr();
						delay(0xFFF);
						lcd_gotoxy(1,1);delay(0xFFF);
						lcd_write_string("call disconnect");
						break;
				}
						if((RTC_GetCounter() - timer) >= ref && flag ==0)
						{	sendstring(ATH);lcd_clr();delay(0xFFF);
							break;
						}
			
						for(i=0;i<Rx;i++)	
						{
										SystemBuf[i]=0x00;   
						}
						Rx=0; 	
			}
			if((RTC_GetCounter() - timer) >= ref && flag ==0)
						{	sendstring(ATH);lcd_clr();delay(0xFFF);
							break;
						}
			
			
		}		
}				   */
