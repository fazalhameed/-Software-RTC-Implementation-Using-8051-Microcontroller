# include <reg52.h>
# include "lcd.h"
# include "ds1302.h"

 sbit CE = P3^5;
 sbit SCLK=P3^6;
 sbit IO =P3^4;
 

 
int ArrayReadBurst[8];

unsigned int a,b,c,d,Data,Data1,x,y;
char array[32];
char jj=0;

void Serial_ISR() interrupt 4    
{ if(RI==1){
	array[jj]=SBUF; 
	RI = 0;	
	jj++;
	}	

}

void UART_Init()
{
	TMOD = 0x20;	  	
	TH1 = 0xFD;		     
	TL1=0xFF;
	SCON = 0x50;		 
	TR1 = 1;		     
}
void Ext_int_Init()				
{
	EA  = 1;		 
	ES = 1;  				
}

 void SCLK_Pulse (void)
{
	SCLK=1;
	SCLK=0;
}

void Send_Bit (unsigned int value)
{
    if (value != 0){
        IO=1;
		}
    else {
        IO=0;
    }
}
void WriteByte (unsigned int Value)
{  
	 for(a=0;a<8;a++)
	{  	
	  x=Value & (1<<a);
		Send_Bit(x);
    SCLK_Pulse();
	}
}
unsigned char ReadByte (unsigned char cmd1)
{  
    Data=0;
  	WriteByte(cmd1);
	for(b=0;b<8;b++)
	{	 
     Data >>=1;	
	     if(IO==1)
	       { 
					 Data|=0x80;
	       }
				 else
				 {   Data &=0x7F;}
				 
	 		 SCLK_Pulse();
  	 
	}
	 return Data;
}

void RTC_WriteByte (unsigned char cmd,unsigned char Value)
{
  CE=1;
	WriteByte(cmd);
	WriteByte(Value);
	CE=0;
}


void ReadBurst (void)
{
  
	CE=1;
	WriteByte(0xBF);
	for(c=0;c<8;c++)
	{    Data1=0x00;
	    for(d=0;d<8;d++)
	   {	 
       Data1 >>=1;	
	     if(IO==1)
	       { 
					 Data1 |=0x80;
	       }
				 else
				 {   Data1 &=0x7F;}
	 		 
  	        SCLK_Pulse();
			 }
	    ArrayReadBurst[c]=Data1;
	}
	 CE=0;
}
void RTC_Intialization()
{
  CE=0;
	SCLK=0;
	RTC_WriteByte(0x8E,0x00);  
	RTC_WriteByte(0x90,0xAB); 
	y=ReadByte (0x81);
	if(y&0x80 !=0)
	RTC_WriteByte(0x80,0);

}
void RTC_Set_DateTime(unsigned char second,unsigned char minutes,unsigned char hours)
{
  RTC_WriteByte(0x80,second);
	RTC_WriteByte(0x82,minutes);  		
	RTC_WriteByte(0x84,hours);
 	 		

}

void Display (unsigned  value)
{  
	
	LCD_Data(((value>>4)&0x0F)+0x30);
	LCD_Data((value&0x0F)+0x30);

	
}

void Displayhour (unsigned char hour)
{  
	char z=0x01;
	if((hour&0x80)==0)
		z=0x03;
	LCD_Data(((hour>>4)&z)+0x30);
	LCD_Data((hour&0x0F)+0x30);
}

void rtc_Intilization ()
{	
  RTC_Intialization();
	RTC_Set_DateTime(0x50,0x59,0xB1);
	
}

void MAIN_RTC ()
{
 	 	 CE=1;
		 ReadBurst();
		 CE=0;
		 
		 Set_cursor(1,6);
		 Display(ArrayReadBurst[0]);
		 
		 Delay(10);
		 Set_cursor(1,3);
		 Display(ArrayReadBurst[1]);
		 LCD_Data(':');
		 Delay(10);
		 Set_cursor(1,0);
		 Displayhour(ArrayReadBurst[2]);
		 LCD_Data(':');
		 Delay(10);
	
		
		 
		 
}
