/*
 * File:   ADC_Sensores.c
 * Author: andres
 *
 * Created on June 8, 2017, 10:39 AM
 */


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

#include <xc.h>
#define _XTAL_FREQ 40000000

void CONF_PUERTOS(void);
void BORRAR_BASURA(void);
void CONF_ADC(void);
void CONF_USART(void);
void ESTABLECER_CANAL(unsigned char CANAL);
void TRANSMITIR(unsigned char DATO);

unsigned char SENSOR;


void main(void) 
{
    
 unsigned char CH=0,TEMP=0; 

	CONF_PUERTOS();
    BORRAR_BASURA();
	CONF_ADC();
    CONF_USART();
    
	
	while(1)
	{
	
	 ESTABLECER_CANAL(CH);
     // Establece el canal que va a convertir
     
	 __delay_ms (2);
     // Retardo para que se cargue el condensador del Sample and Hold
     
	 ADCON0bits.GO = 1;
     // Inicia la conversion
     
     
	 	// Espera a que finalice la conversión
        // del canal activo
        while(ADCON0bits.GO == 1)
	 	{			
		}
     
        if(ADRESH>127)            
        // Detectó linea negra en el sensor dado
        {
            TEMP = '1';
            SENSOR = SENSOR | (1<<CH);
        } 
     
        else
        {
            TEMP = '0';
        }    
     
        CH++;
                        
        TRANSMITIR(TEMP);
        
        
        if (CH == 8)
        //Indica que recorrió toda la regleta
        {
            SENSOR  =   0;
            CH      =   0;
            TEMP    =   13;
            TRANSMITIR(TEMP);
        }       
	 
	}

}

///////////////////////////////////////////////////////
void CONF_PUERTOS(void)
{      
            //76543210
	TRISA = 0b00101111;
    // Configura 5 pines de Entrada para los 
    // canales Analógicos

            //76543210
	TRISE = 0b00000111;
    // Configura 3 pines de Entrada
    // canales Analógicos

	        //76543210
    TRISC = 0b10000000;
    // TC<7> Entrada    --> Para el pin de recepción
    // TC<6> Salida     --> Para el pin de transmisión   
}

///////////////////////////////////////////////////////
void BORRAR_BASURA(void)
{
    LATA = 0;
    LATC = 0;    
    SENSOR = 0;
}

///////////////////////////////////////////////////////
void CONF_ADC(void)
{
             //76543210
	ADCON0 = 0b10000001;

             //76543210
	ADCON1 = 0b01000000;
}
///////////////////////////////////////////////////////
void CONF_USART(void)
{
            //76543210
    TXSTA = 0b00100010;
    
    RCSTA = 0b10010000;
    
    SPBRG = 64;
}

///////////////////////////////////////////////////////
void ESTABLECER_CANAL(unsigned char CANAL)
{
	ADCON0bits.CHS = CANAL;
}


///////////////////////////////////////////////////////
void TRANSMITIR(unsigned char DATO)
{
    
    while(PIR1bits.TXIF == 0)
    {}
        // Espera a que finalice el envio del dato
        
        TXREG  = DATO ;
     
    
    
}    

    

