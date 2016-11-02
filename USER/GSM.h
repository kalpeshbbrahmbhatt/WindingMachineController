#ifndef __GSM_H
#define __GSM_H

#include "STM32Lib\\stm32f10x.h"
#include "STM32Lib\\stm32f10x_bkp.h"
#include "STM32Lib\\stm32f10x_flash.h"
#include "STM32Lib\\stm32f10x_rtc.h"
#include "hal.h"
#define password_START_ADDR  		((uint32_t)0x0800A000)
#define EXIT										((uint8_t)0x2B)
extern unsigned char mesgage_check_after_dailing_flag;
extern unsigned char  RxIn;
extern unsigned char  AT[];	//Handshake signals
extern unsigned char  ATE[];	 //Off echo
extern unsigned char  ATW[];	 //Off echo
extern unsigned char  AT_IPR[];
extern unsigned char  AT_CSQ[];
extern unsigned char  AT_CLIP[];//CALLER DETAIL
extern unsigned char  AT_COLP[] ;//ATENDEE WHILE CALL IS INTIMATED 
extern unsigned char  AT_QMDA[];
extern unsigned char  MYNUM[];
extern unsigned char  ATD[];
extern unsigned char  phone_number_array[45][14];
extern unsigned char  AT_CPIN[];
extern unsigned char  AT_CREG[];
extern unsigned char  AT_CGREG[];
extern unsigned char  ATH[];
extern unsigned char  AT_QEXTUNSOL[];
extern unsigned char  AT_CNMI[];//Set this set of parameters to the new information directly to the serial port, and no storage
//extern unsigned char  AT_CSCA[];//Set the service center number
extern unsigned char  AT_CMGF[];//Set the format of the SMS text format
extern unsigned char  AT_CMGR[];//Read SMS commands
extern unsigned char  AT_CMGS[];//Send SMS command
extern unsigned char  AT_CMGD[];//Send SMS command
extern unsigned char  successfully1[];//Send operation is successful to the target number
extern unsigned char  successfully2[];
extern unsigned char  successfully3[];
extern unsigned char  system_on_status[];
extern unsigned char  pass[];
extern unsigned char  fail[];	//Send operation failed to the target number
extern unsigned char  AT_delete[];
extern unsigned char  AT_Read[];	//Send read SMS command used to store 
extern unsigned char  AT_SendNumber[];  //Used to store the SMS number instruction
extern unsigned char  numberbuf[];		 //Used to save the number of short messages 
extern unsigned char  SystemBuf[];  //Save export receive data
extern unsigned char  CommandBuf[];	 //Used to store instructions
extern unsigned char  state[];	  //Used to store IO port state 
extern unsigned char  state1[];	 //Used to store IO port state 
extern unsigned char  Rx;
extern unsigned int  temp;	//Record status 	 
extern unsigned char temp1;	// P0 port status is used to record
extern unsigned char temp2;   // P2 port status is used to record 
extern unsigned int  check;	//Query flag 
extern unsigned int  receiveready;		  //Receive SMS flag
extern unsigned int  sendready;		      //Send SMS ready flag
extern unsigned int  send;				   //Send SMS flag
extern unsigned int  flag;				   //Command flag
extern unsigned char operate;

//extern void Delay_ms(unsigned int i);
extern void Start_GSM(void);
extern void UART_init (void);
extern void dial_number(unsigned char,unsigned char);
extern void sendstring(unsigned char *p);
extern void GSM_INIT(void);
extern void receive_ready(void);
extern unsigned char message_read(void);
extern void read_message(void);
extern u8 sendmessage(unsigned char);
extern u8 sendmessage_multiple(unsigned char, unsigned char);
extern void readcommend(unsigned char, unsigned char);
extern void delete_message(unsigned char);
extern void delete_all_message(void);
extern u8 check_signal_strength(unsigned char);
extern u8 check_sim_presence(unsigned char);
extern u8 check_exit_key(void);

#endif /* __GSM */
