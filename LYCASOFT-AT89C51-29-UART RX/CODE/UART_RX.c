#include<reg51.h>
#include "8051_delay.h"
#include "LCD_4_BIT_HEADER_FILE.h"

void Uart_Intialization()
{
	TMOD = 0x20;
	SCON = 0x50;
	TH1  = 0xFD;
	TL1  = 0xFD;
	TR1  = 1;
}

unsigned char RX()
{
	while(!RI);
	RI = 0;
	return SBUF;
}

void main()
{
	char Ch;
	
	Lcd_Intialization();
	Uart_Intialization();

	Lcd_Command(0x80);
	Lcd_String("LYCA SOFT");
	
	Lcd_Command(0xC0);
	while(1)
	{
		Ch = RX();
		
		Lcd_Data(Ch);
		
		if(Ch == 0x0d)
		{
			Lcd_Command(0xC0);
			Lcd_String("                ");
			Lcd_Command(0xC0);
		}
	}
}