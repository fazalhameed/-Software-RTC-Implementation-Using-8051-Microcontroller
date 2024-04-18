
#ifndef __DS1302_H__
#define __DS1302_H__
 

void UART_Init();
void Ext_int_Init();
void SCLK_Pulse (void);
void Send_Bit (unsigned int value);
void WriteByte (unsigned int Value);
unsigned char ReadByte (unsigned char cmd1);
void RTC_WriteByte (unsigned char cmd,unsigned char Value);
void ReadBurst (void);
void RTC_Intialization();
void RTC_Set_DateTime(unsigned char second,unsigned char minutes,unsigned char hours);
void Display (unsigned  value);
void Displayhour (unsigned char hour);
void rtc_Intilization ();
void MAIN_RTC ();

#endif
