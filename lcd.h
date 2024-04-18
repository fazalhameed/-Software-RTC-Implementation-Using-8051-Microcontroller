
#ifndef __LCD_H__
#define __LCD_H__
 

void Delay (unsigned int value);
void LCD_Command (unsigned char cmd);
void LCD_Data (unsigned char Data);
void String_data (unsigned char *p);
void LCD_Intialization(void);
void Set_cursor(int row, int coloum);

void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char);
int lcd_Pow(int X,int Y);
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String);


#endif
