// CONFIG1H
#pragma config OSC = HSPLL      // Oscillator Selection bits (HS oscillator with PLL enabled/Clock frequency = (4 x FOSC))
#pragma config OSCS = OFF       // Oscillator System Clock Switch Enable bit (Oscillator system clock switch option is disabled (main oscillator is source))

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bit (Brown-out Reset disabled)
#pragma config BORV = 20        // Brown-out Reset Voltage bits (VBOR set to 2.0V)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 128      // Watchdog Timer Postscale Select bits (1:128)

// CONFIG3H
#pragma config CCP2MUX = ON     // CCP2 Mux bit (CCP2 input/output is multiplexed with RC1)

// CONFIG4L
#pragma config STVR = ON        // Stack Full/Underflow Reset Enable bit (Stack Full/Underflow will cause RESET)
#pragma config LVP = OFF        // Low Voltage ICSP Enable bit (Low Voltage ICSP disabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000200-001FFFh) not code protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot Block (000000-0001FFh) not code protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000200-001FFFh) not write protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000200-001FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from Table Reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from Table Reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
//#include<p18F452.h>
#include<stdio.h>
#include <xc.h>
#define _XTAL_FREQ 16000000
unsigned char CH,BANDERA,ESTADO;
unsigned int CS1,CS2,CS3,CTOTAL,P1,P2,P3;
//--------------------------------------------
void CONF_PUERTOS(void);
void BORRAR_BASURA(void);
//void CONF_TIMER0(void);
//void PULSO_10u(void);
//void CONF_ADC(void);
//void ESTABLECER_CANAL(unsigned char CANAL);
//void REFLEX(void);
//void ULTRA(void);
//--------------------------------------------
void main(void)
{
	CONF_PUERTOS();
    BORRAR_BASURA();
//    CONF_TIMER0();     
//    CONF_ADC();
//    PULSO_10u();
//    REFLEX();
//    ULTRA();
    while(1)
    {
    	LATDbits.LATD6 = 1;
    	LATDbits.LATD5 = 1;
        LATBbits.LATB3 = 1;
	}
}
void CONF_PUERTOS(void)
{
    TRISB   = 0b00000111;
    TRISD   = 0b00000000;
    TRISE   = 0b00000000;
    TRISA   = 0b00000111;
            
}
//////////////////////////////////////////////////////
void BORRAR_BASURA(void)
{
    LATB = 0;
    LATD = 0;
    LATE = 0;
    LATA = 0;
}
/////////////////////////////////////////////////////
/*void CONF_ADC(void)
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
//--------------------------------------------
void CONF_TIMER0(void)
{
    T0CON = 0b01000000;
    TMR0L = 56;     
}
//--------------------------------------------
void PULSO_10u(void)
{
    LATE = 7; 
   __delay_us(20);
   LATE = 0;
}
/////////////////////////////////////////////////////////
void REFLEX(void)
{
    CH=0;
	ESTABLECER_CANAL(CH);	
	__delay_us(20);
	ADCON0bits.GO = 1;
		while(ADCON0bits.GO)
	 	{			
		}
	P1 = ADRESH;
	CH++;
	// repitepara leer segundo canal
	ESTABLECER_CANAL(CH);	
	__delay_us(20);
	ADCON0bits.GO = 1;
		while(ADCON0bits.GO)
		{			
		}
   	P2 = ADRESH;
	CH++;
	// repitepara leer TERCER canal
	ESTABLECER_CANAL(CH);	
	__delay_us(20);
	ADCON0bits.GO = 1;
		while(ADCON0bits.GO)
	 	{			
		}
   	P3 = ADRESH;
	CH++;
	if(CH == 3)
	{
	CH = 0;
	}
}
void ULTRA(void) 
{
    CS1     = 0;
    CS2     = 0;
    CS3     = 0;
    CTOTAL  = 0;
    ESTADO  = 0;
    BANDERA = 0;
    PULSO_10u();
     //Espera a que los tres sensores generen un flanco de subida
     //Cada uno
    while(BANDERA == 0)
    {
        BANDERA = PORTBbits.RB2 & PORTBbits.RB1 & PORTBbits.RB0;
    }
    
    BANDERA = 1;      
//        
    T0CONbits.TMR0ON = 1; // Inicia el timer
    while(CTOTAL <300)
    {
        if(INTCONbits.TMR0IF) // Ocurre desborde
        {
            INTCONbits.TMR0IF = 0;  // Borra bandera de desborde
            TMR0L = 60;            // Establece valor inicial 
            CTOTAL++;
// Contadores empleados para medir la distancia del objeto
// Respecto al sensor
            if(PORTBbits.RB2 == 1 ){CS3++;}
            if(PORTBbits.RB1 == 1 ){CS2++;}
            if(PORTBbits.RB0 == 1 ){CS1++;}
        }
    }
    T0CONbits.TMR0ON = 0; // Apaga el timer
    __delay_ms(30);// Retardo para generar la siguiente lectura
    __delay_ms(30);// Retardo para generar la siguiente lectura
    __delay_ms(30);// Retardo para generar la siguiente lectura   
}
 */
