/* lcd.c */
#include "types.h"
#include <LPC21xx.h>
#include "delay.h"
#include "defines.h"
//#include "lcd.h"
//#include "lcd_defines.h"
#include <string.h>

#define LCD_DATA  16  // LCD DATA PINS P1.16 TO P1.23
#define LCD_RS    9	  // RS PIN P0.9
#define LCD_RW    8	  // RW 
#define LCD_EN   10  // ENBLE P0.10

//definitions for primary drivers
void WriteLCD(u8 Dat)
{
	SCLRBIT(IOCLR0,LCD_RW);
  	WRITEBYTE(IOPIN1,LCD_DATA,Dat);
	SSETBIT(IOSET0,LCD_EN);
	delay_us(1);
	SCLRBIT(IOCLR0,LCD_EN);
	delay_ms(2);		 
}

void CmdLCD(u8 cmd)
{
  SSETBIT(IOCLR0,LCD_RS);
  WriteLCD(cmd);	
}

void CharLCD(u8 asciiVal)
{
  SSETBIT(IOSET0,LCD_RS);
  WriteLCD(asciiVal);	
}

void InitLCD(void)
{
	WRITEBYTE(IODIR1,LCD_DATA,0XFF);
	SETBIT(IODIR0,LCD_RS);
	SETBIT(IODIR0,LCD_RW);
	SETBIT(IODIR0,LCD_EN);
	
	delay_ms(15);
	CmdLCD(0x30);
	delay_ms(4);
	//delay_us(100);
	CmdLCD(0x30);
	delay_us(100);
	CmdLCD(0x30);
	CmdLCD(0x38);
	CmdLCD(0x0c);
	CmdLCD(0x01);
	CmdLCD(0x06);
}	

//definitions for secondar drivers
void StrLCD(s8 *s)
{
	while(*s) 
		CharLCD(*s++);
}

void U32LCD(u32 n)
{
  u8 a[10];
  s8 i=0;
	if(n==0)
		CharLCD('0');
	while(n>0)
  {
	  a[i]=(n%10)+48;
    n/=10;
    i++;		
  }		
	for(--i;i>=0;i--)
		CharLCD(a[i]);
}

void S32LCD(s32 n)
{
  if(n<0)
	{	
   CharLCD('-');
   n=-n;
  }
  U32LCD(n);	
}	

void F32LCD(f32 f,u8 nDP)
{
  u32 n; u8 i;
	if(f<0.0)
	{
		CharLCD('-');
		f=-f;
	}
	n=f;
	U32LCD(n);
	CharLCD('.');
	for(i=0;i<nDP;i++)
	{
		f=(f-n)*10;
		n=f;
		CharLCD(n+48);
	} 	
}	

void BuildCGRAM(u8 *p,u8 nBytes)
{
	u8 i;
	//take curson to start of cgram
	CmdLCD(0x40);
	for(i=0;i<nBytes;i++)
	{
		//Write to CGRAM 
		CharLCD(p[i]);
	}
	//bring back cursor to ddram start
	CmdLCD(0x80);
}	
//add more as required

u8 cgramLUT[]={0x00,0x04,0x0E,0x0E,0x0E,0x0E,0x0E,0x00, //BATTERY  
				0x00,0x04,0x0E,0x0E,0x0E,0x0E,0x0E,0x00, 
				    0x00,0x04,0x0E,0x0E,0x0E,0x0E,0x0E,0x00,
					0x00,0x04,0x0E,0x0E,0x0E,0x0E,0x0E,0x00,
					0x00,0x04,0x0E,0x0E,0x0E,0x0E,0x0E,0x00,}; 

int main()
{
	InitLCD();
	StrLCD("  VECTOR INDIA  ");
	CmdLCD(0xc0);
	StrLCD("   HYDERABAD   ");
	BuildCGRAM(cgramLUT,16);
	CmdLCD(0X80);
	CharLCD(0);	//index value
	CmdLCD(0X80+15);
	CharLCD(0);	//index value
	CmdLCD(0XC0);
	CharLCD(1);	//index value
	CmdLCD(0XC0+15);
	CharLCD(1);	//index value
	delay_ms(2000);
 /*
	InitLCD();
	StrLCD("    LOKESH  ");
	CmdLCD(0xc0);
	StrLCD("    GIRASE  ");
    BuildCGRAM(cgramLUT,16);
	CmdLCD(0X80);
//	CmdLCD(0X01);
	CmdLCD(0X80);
	CharLCD(2);	//index value
	CmdLCD(0X80+15);
	CharLCD(2);	//index value
	CmdLCD(0XC0);
	CharLCD(2);	//index value
	CmdLCD(0XC0+15);
	CharLCD(2);
	*/
	while(1);
}

