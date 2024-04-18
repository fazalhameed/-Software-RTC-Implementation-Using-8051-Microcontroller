#include <reg52.h>
#include "lcd.h"
#include "ds1302.h"

int sec;
int min;
int hr;
char day;
int date;
int month;
int year;


void timer_int()            
	{
    TMOD |= 0x01;          
    TH0 = 0xFC;
    TL0 = 0x74;
    ET0 = 1;
    EA = 1;
    TR0 = 1;
}
	
void Timer0() interrupt 1       
	{
    static int i = 0;
    TH0 = 0xFC;               
    TL0 = 0x74;
    i++;

    if (i == 1000)              
			{
        sec++;
        i = 0;
      }
}



void main()
	{
    sec = 50;
    min = 59;
    hr = 11;
 
    LCD_Intialization();           
    timer_int();                   
		
    LCD_ShowString(1,11,"1302");
    LCD_ShowString(2, 2, ":  :     8051");
	
    rtc_Intilization ();           //Ds1302 Intilization
	
    while (1)                     
			{
       
			MAIN_RTC ();                 
				
        if (sec == 60)          
					{
            sec = 0;
            min++;
          }
        if (min == 60) 
					{
            min = 0;
            hr++;
          }
        if (hr == 24) 
					{
            hr = 0;
            day++;
            date++;
          }

        LCD_ShowNum(2, 0, hr, 2);
        LCD_ShowNum(2, 3, min, 2);
        LCD_ShowNum(2, 6, sec, 2);
    }
}

