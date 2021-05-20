#include<p18F452.h>
#include<stdio.h>
#include<delays.h>

void CONF_PUERTOS(void);
void CONF_ADC(void);
void ESTABLECER_CANAL(unsigned char CANAL);


void main(void)
{
 unsigned char CH=0; 

	CONF_PUERTOS();
	CONF_ADC();
	
	while(1)
	{
	
	 ESTABLECER_CANAL(CH);	
	 Delay10TCYx(2);
	 ADCON0bits.GO = 1;

	 	while(ADCON0bits.GO)
	 	{			
		}
	 LATB = ADRESH;
	 CH++;
	 ESTABLECER_CANAL(CH);	
	 Delay10TCYx(2);
	 ADCON0bits.GO = 1;

	 	while(ADCON0bits.GO)
	 	{			
		}
	 LATC = ADRESH;
	 CH++;
	 if(CH == 2)
	 {
	 CH = 0;
	 }
	}

}

///////////////////////////////////////////////////////
void CONF_PUERTOS(void)
{
			//76543210
	TRISA = 0b00111111;

			//76543210
	TRISE = 0b00000111;

	TRISB = 0;
	
	TRISC = 0;
	
	LATB = 0;
	
	LATC = 0;
}
///////////////////////////////////////////////////////
void CONF_ADC(void)
{
			 //76543210
	ADCON0 = 0b01000001;

			 //76543210
	ADCON1 = 0b00000000;
}
///////////////////////////////////////////////////////

void ESTABLECER_CANAL(unsigned char CANAL)
{
	ADCON0bits.CHS = CANAL;
}
