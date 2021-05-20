#include<p18F452.h>
#include<stdio.h>
#include<delays.h>
#include<xc.h>

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
	 CH++;
	 ESTABLECER_CANAL(CH);	
	 Delay10TCYx(2);
	 ADCON0bits.GO = 1;

	 	while(ADCON0bits.GO)
	 	{			
		}
	 LATD = ADRESH;
	 CH++;
	 if(CH == 1)
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
	
	TRISC	= 0b00000000;
	
	LATD = 0;
	
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
///////////////////////////////////////////////////////
void BORRAR_BASURA(void)
{
	LATC 	= 0;
}
///////////////////////////////////////////////////////
void CONF_PWM(void)
{
			  //76543210
	CCP1CON = 0b00001100;
	CCP2CON = 0b00001100;

	CCPR1L 	= 100;  // Ancho de pulso del canal 1
	CCPR2L 	= 100; // Ancho de pulso del canal 2 

	PR2 	= 249; // Establece la frecuencia de
				   // de ambas señales(aplica para
				   // ambos canales)
}
///////////////////////////////////////////////////////
void CONF_TIMER2(void)
{
	TMR2 	= 0;
			  //76543210
	T2CON	= 0b00000101;

}




