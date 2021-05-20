#include<p18F452.h>
#include<stdio.h>
#include<delays.h>

void CONF_PUERTOS(void);
void BORRAR_BASURA(void);
void CONF_ADC(void);
void ESTABLECER_CANAL(unsigned char CANAL);
void CONF_PWM(void);
void CONF_TIMER2(void);

void main(void)
{
 unsigned char CH=0; 

	CONF_PUERTOS();
	CONF_ADC();
	BORRAR_BASURA();
	CONF_PWM();
	CONF_TIMER2();
	
	while(1)
	{
	
	 ESTABLECER_CANAL(CH);	
	 Delay10TCYx(2);
	 ADCON0bits.GO = 1;

	 	while(ADCON0bits.GO)
	 	{			
		}
	 LATB = ADRESH;
	CCPR1L = ADRESH;
	 CH++;
	 // repitepara leer segundo nanal
	 ESTABLECER_CANAL(CH);	
	 Delay10TCYx(2);
	 ADCON0bits.GO = 1;

	 	while(ADCON0bits.GO)
	 	{			
		}
	 LATD = ADRESH;
	CCPR2L = ADRESH;
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

	TRISA = 0b00111111;

	TRISE = 0b00000111;

	TRISB = 0;
	
	TRISC = 0;
	
	TRISD = 0;
	
}
///////////////////////////////////////////////////////
void CONF_ADC(void)
{

	ADCON0 = 0b01000001;

	ADCON1 = 0b00000000;
}
///////////////////////////////////////////////////////

void ESTABLECER_CANAL(unsigned char CANAL)
{
	ADCON0bits.CHS = CANAL;
}
///////////////////////////////////////////////////////
void BORRAR_BASURA(void)
{
	LATC = 0;
}
///////////////////////////////////////////////////////
void CONF_PWM(void)
{

	CCP1CON = 0b00001100;
	CCP2CON = 0b00001100;

	CCPR1L 	= 100; // Ancho de pulso del canal 1
	CCPR2L 	= 100; // Ancho de pulso del canal 2 

	PR2 	= 249; // Establece la frecuencia de
				   // de ambas señales(aplica para ambos canales)
}
///////////////////////////////////////////////////////
void CONF_TIMER2(void)
{
	TMR2 	= 0;

	T2CON	= 0b00000101;

}
