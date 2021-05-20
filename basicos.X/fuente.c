/*
 * File:   FUENTE.c
 * Author: JAT
 *
 * Created on 11 de octubre de 2016, 01:15 PM
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
#include <p18f452.h>
#define _XTAL_FREQ 16000000    

//--------------------------------------------
void CONF_PUERTOS(void);
void BORRAR_BASURA(void);
void CONF_TIMER0(void);
void PULSO_10u(void);

//--------------------------------------------
void main(void) 
{
    unsigned int CS1,CS2,CS3,CTOTAL;
    unsigned char BANDERA,ESTADO;
    CONF_PUERTOS();
    BORRAR_BASURA();
    CONF_TIMER0();
                 
    while(1)
    {
        CS1     = 0;
        CS2     = 0;
        CS3     = 0;
        CTOTAL  = 0;
        ESTADO  = 0;
        BANDERA = 0;
        
        PULSO_10u();
        // Espera a que los tres sensores generen un flanco de subida
        // Cada uno
        while(BANDERA == 0)
        {
            BANDERA = PORTBbits.RB2 & PORTBbits.RB1 & PORTBbits.RB0;
        }
        
        BANDERA = 1;
        
        
        T0CONbits.TMR0ON = 1; // Inicia el timer
       
        while(CTOTAL <3001)
        {
            if(INTCONbits.TMR0IF) // Ocurre desborde
            {
                INTCONbits.TMR0IF = 0;  // Borra bandera de desborde
                TMR0L = 226;            // Establece valor inicial 

                
    // Contadores empleados para medir la distancia del objeto
    // Respecto al sensor
    //            if(LATBbits.LATB7){CS1++;}
    //            if(LATBbits.LATB6){CS2++;}
    //            if(LATBbits.LATB5){CS3++;}
                
                if(BANDERA)
                {
                    if(~PORTBbits.RB2){ESTADO = 1;BANDERA = 0;}
                    if(~PORTBbits.RB1){ESTADO = 2;BANDERA = 0;}
                    if(~PORTBbits.RB0){ESTADO = 3;BANDERA = 0;}
                    CTOTAL++;
                }
            }
        }
        
        LATD = ESTADO;
        
        T0CONbits.TMR0ON = 1; // Inicia el timer
        INTCONbits.TMR0IF = 0;  // Borra bandera de desborde
        TMR0L = 226;
        
        __delay_ms(12);// Retardo para generar la siguiente lectura 
    }
}
//--------------------------------------------
void CONF_PUERTOS(void)
{
              //76543210
    TRISA   = 0b00000111;
    TRISB   = 0b00000111;
    TRISD   = 0b00000000;
    TRISE   = 0b00000000;
    ADCON1  = 0b00000110;
}
//--------------------------------------------
void BORRAR_BASURA(void)
{
    LATA = 0;
    LATB = 0;
    LATD = 0;
    LATE = 0;
}
//--------------------------------------------
void CONF_TIMER0(void)
{
       
            //76543210
    T0CON = 0b01001000;
    TMR0L = 226;     
}
//--------------------------------------------
void PULSO_10u(void)
{
   LATE = 7; 
   __delay_us(10);
   LATE = 0; 
}