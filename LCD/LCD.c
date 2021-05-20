#include<p18f452.h>
#include<delays.h>
#include<xlcd.h>
void DelayFor18TCY(void)
{ 
Nop();
Nop();
Nop();
Nop();
Nop();
Nop();
Nop();
Nop();
Nop();
Nop();
Nop();
Nop();
return;
}
void DelayPORXLCD(void)
{
	Delay1KTCYx(15);
	return;
}
void DelayXLCD(void)
{
	Delay1KTCYx(5);
	return;
}
unsigned char uni,dec,cen;
unsigned char Display[10]={'0','1','2','3','4','5','6','7','8','9'};
void main (void)
{
	OpenXLCD(FOUR_BIT & LINES_5X7);
	WriteCmdXLCD(SHIFT_DISP_LEFT);
	WriteCmdXLCD(BLINK_OFF);
	WriteCmdXLCD(0x80);
	putrsXLCD("CONTADOR 0 a 666");
	while(1)
	{
		cen=0;
		while(cen<10)
		{
			dec=0;
			while(dec<10)
			{
				uni=0;
				while(uni<10)
				{
					WriteCmdXLCD(0xcf);
					WriteDataXLCD(Display[uni]);
					WriteCmdXLCD(0xce);
					WriteDataXLCD(Display[dec]);
					WriteCmdXLCD(0xcd);
					WriteDataXLCD(Display[cen]);
					Delay10KTCYx(100);
					uni++;
				}
			dec++;
			}
		cen++;
	    }
	}
}