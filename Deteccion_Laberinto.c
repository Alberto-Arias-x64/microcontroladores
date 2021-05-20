/*
 * File:   Solucionador de Laberinto
 * 
 * Este archivo permite que el robot recorra el
 * laberinto de manera autonoma SIN aprendizaje
 * 
 * Author: Andrés Torres.
 *
 * Created on June 20, 2017, 9:56 AM
 * 
 * 
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
void CONF_PWM(void);
void CONF_TMR2(void);
void CONF_USART(void);
void ROMPER_INERCIA(void);
int  LEER_SENSORES(void);
void TRANSMITIR(unsigned char DATO);
int  ESTABLECER_VEL_INI(void);
void AVANZAR(int SENSOR);
void VALORES_INI_PWM(void);
unsigned char DETERMINAR_ESTADO(int SENSOR);
void DECIDIR_SENTIDO(void);
void G_IZQUIERDA(void);
void G_COMPLETO(void);
void DETENER(void);
void G_DERECHA(void);
 
unsigned char AA[10];
unsigned char VAL_IZQ;
unsigned char VAL_DER;
unsigned char E_ANTERIOR;
unsigned char E_ACTUAL;
 
void main(void) 
{
    int TEMP,SENSOR;
     
    CONF_PUERTOS();
    BORRAR_BASURA();
    CONF_ADC();
    CONF_PWM();
    CONF_TMR2();    
    CONF_USART();   
     
     
    do
    {
        TEMP = ESTABLECER_VEL_INI();
    } while(TEMP != 0); 
     
        
    ROMPER_INERCIA();
    VALORES_INI_PWM();
     
    SENSOR = 0b00011000;
    E_ACTUAL = 'C';
    
    while(1)
    {        
        
        AVANZAR(SENSOR);
        __delay_ms(8);
        
        SENSOR = LEER_SENSORES();
        TRANSMITIR(13);
        
        E_ANTERIOR = E_ACTUAL;
        E_ACTUAL = DETERMINAR_ESTADO(SENSOR);
        
        DECIDIR_SENTIDO();
    }    
     
}
 
//-------------------------------------------------------
 
void CONF_PUERTOS(void)
{      
            //76543210
    TRISA = 0b00101111;
    // Configura 5 pines de Entrada para los 
    // canales Analógicos
    
            //76543210
    TRISD = 0b00000000;
    // Pines RB<3:0> son de salida y se emplean
    // de parejas para establecer el sentido de
    // giro de los motores al activar los pines
    // del puente H
 
            //76543210
    TRISE = 0b00000111;
    // Configura 3 pines de Entrada
    // canales Analógicos
 
            //76543210
    TRISC = 0b10000000;
    // TC<7> Entrada    --> Para el pin de recepción
    // TC<6> Salida     --> Para el pin de transmisión   
}
 
//-------------------------------------------------------
 
void BORRAR_BASURA(void)
{
    unsigned char i = 0;
     
    LATA = 0;
    LATD = 0;
    LATC = 0;    
         
    VAL_IZQ = 0;
    VAL_DER = 0;
     
                       
    E_ANTERIOR = 'C';
     
    for(i=0;i<10;i++)
    {
        AA[i]=0;
    }    
}
 
//-------------------------------------------------------
 
void CONF_ADC(void)
{
             //76543210
    ADCON0 = 0b10000001;
 
             //76543210
    ADCON1 = 0b01000000;
}
 
//-------------------------------------------------------
 
void CONF_PWM(void)
{
                //76543210
    CCP1CON =   0b00001100;
    CCP2CON =   0b00001100;
     
    CCPR1L  =   0;    // Valor inicial Ciclo Util del PWM1
    CCPR2L  =   0;    // Valor inicial Ciclo Util del PWM2
     
    PR2     =   255;    // Valor Periodo de 12 khz    
  
}
 
//-------------------------------------------------------
 
void CONF_TMR2(void)
{
    TMR2    = 0; // Incializa el timer( contador) en cero
  
                //76543210
    T2CON   =   0b00000111;
}
 
//-------------------------------------------------------
 
void CONF_USART(void)
{
            //76543210
    TXSTA = 0b00100010;
     
    RCSTA = 0b10010000;
     
    SPBRG = 64;
}
 
//-------------------------------------------------------
 
void ROMPER_INERCIA(void)
{
 
           //76543210
    LATD = 0b00000101;
    // Activa los pines de Control para que 
    // ambos motores giren hacia adelante
    
    
    CCPR1L = CCPR2L = 255;
    __delay_ms(80);    
}
 
//-------------------------------------------------------
 
int LEER_SENSORES(void)
{
 unsigned char TEMP;
 signed int CANAL; 
 int SENSOR = 0;
  
 SENSOR = 0;
  
    for(CANAL = 7; CANAL>=0;CANAL--)
    {
        ADCON0bits.CHS = CANAL;
        // Establece el canal de la conversion
 
         __delay_ms (2);
         // Retardo para que se cargue el condensador del Sample and Hold
 
         ADCON0bits.GO = 1;
         // Inicia la conversion
 
 
        // Espera a que finalice la conversión
        // del canal activo
        while(ADCON0bits.GO == 1)
        {}
 
        if(ADRESH>127)            
        // Detectó linea negra en el sensor dado
        {
            TEMP = '1';
            SENSOR = SENSOR | (1<<CANAL);
        } 
 
        else
        {
            TEMP = '0';
        }    
 
        TRANSMITIR(TEMP);
 
 
        if (CANAL == 0)
        //Indica que recorrió toda la regleta
        {            
            TEMP    =   13;
            TRANSMITIR(TEMP);
        }       
    }    
 
 
 return SENSOR;
 
}
 
//-------------------------------------------------------
 
void TRANSMITIR(unsigned char DATO)
{
     
    while(PIR1bits.TXIF == 0)
    {}
    // Espera a que finalice el envio del dato
         
    TXREG  = DATO ;   
}
 
//-------------------------------------------------------
 
int ESTABLECER_VEL_INI(void)
{
    unsigned char CONTAR_TRAMAS = 0;
    unsigned char ERROR = 0;
    unsigned char TEMP = 0;
    unsigned char i = 0;
     
    for(i=0;i<10;i++)       
    {
        while(PIR1bits.RCIF == 0)
        // Espera a que reciba SOLO UNA trama
        {}
 
        TEMP = RCREG;
        // Lee el dato recibido
 
        PIR1bits.RCIF = 0;
        // Baja bandera de dato leido
 
        switch (CONTAR_TRAMAS)
        {
            case 0:{
                    if(TEMP == 'A')
                    {
                        AA[CONTAR_TRAMAS] = TEMP;
                        CONTAR_TRAMAS++;
                    }
 
                    else
                    {ERROR++;}                   
 
                   }break;
 
            case 1:{
                    if(TEMP >= 48 && TEMP <= 50)
                    {
                        AA[CONTAR_TRAMAS] = TEMP;
                        CONTAR_TRAMAS++;
                    }
 
                    else
                    {ERROR++;} 
 
                   }break;       
 
            case 2 :{
                    if(TEMP >= 48 && TEMP <= 57)
                    {
                        AA[CONTAR_TRAMAS] = TEMP;
                        CONTAR_TRAMAS++;
                    }
 
                    else
                    {ERROR++;} 
 
                   }break;        
 
            case 3 :{
                    if(TEMP >= 48 && TEMP <= 57)
                    {
                        AA[CONTAR_TRAMAS] = TEMP;
                        CONTAR_TRAMAS++;
                    }
 
                    else
                    {ERROR++;} 
 
                   }break;
 
            case 4 :{
                    if(TEMP == 13)
                    {
                        AA[CONTAR_TRAMAS] = TEMP;
                        CONTAR_TRAMAS++;
                    }
 
                    else
                    {ERROR++;} 
 
                   }break;      
 
            case 5:{
                    if(TEMP == 'B')
                    {   
                        AA[CONTAR_TRAMAS] = TEMP;
                        CONTAR_TRAMAS++;
                    }
 
                    else
                    {ERROR++;}                   
 
                   }break;
 
            case 6:{
                    if(TEMP >= 48 && TEMP <= 50)
                    {
                        AA[CONTAR_TRAMAS] = TEMP;
                        CONTAR_TRAMAS++;
                    }
 
                    else
                    {ERROR++;} 
 
                   }break;       
 
            case 7 :{
                    if(TEMP >= 48 && TEMP <= 57)
                    {
                        AA[CONTAR_TRAMAS] = TEMP;
                        CONTAR_TRAMAS++;
                    }
 
                    else
                    {ERROR++;} 
 
                   }break;        
 
            case 8 :{
                    if(TEMP >= 48 && TEMP <= 57)
                    {
                        AA[CONTAR_TRAMAS] = TEMP;
                        CONTAR_TRAMAS++;
                    }
 
                    else
                    {ERROR++;} 
 
                   }break;
 
            case 9 :{
                    if(TEMP == 13)
                    {
                        AA[CONTAR_TRAMAS] = TEMP;
                        CONTAR_TRAMAS++;
                    }
 
                    else
                    {ERROR++;} 
 
                   }break;    
                    
            default:{
                     ERROR++;
                    }              
        }       
    }
     
    if (ERROR == 0 && CONTAR_TRAMAS ==10) 
    {
       TRANSMITIR('1');               
    }
        
    if(ERROR != 0 && CONTAR_TRAMAS ==10) 
    {
       TRANSMITIR('2');
        
    }
     
    return ERROR ;
     
}
 
//-------------------------------------------------------
void AVANZAR(int SENSOR)
{
           
    switch (SENSOR)
    {
                    
           
        
             //76543210                                              
        case 0b01100000 :{                        
                            CCPR1L = VAL_IZQ - 90;
                            CCPR2L = VAL_DER + 90;    
                         }break;                
                         
                         
             //76543210                                              
        case 0b00100000 :{                        
                            CCPR1L = VAL_IZQ - 50 ;
                            CCPR2L = VAL_DER + 60;    
                         }break;                
                         
                         
             //76543210                                              
        case 0b00110000 :{                        
                            CCPR1L = VAL_IZQ - 40;
                            CCPR2L = VAL_DER + 30;    
                         }break;                
 
                         
                         
             //76543210                      
        case 0b00010000: {                        
                            CCPR1L = VAL_IZQ - 15;
                            CCPR2L = VAL_DER + 15;    
                         }break;                
 
                         
             //76543210           
        case 0b00011000: {                        
                            CCPR1L = VAL_IZQ + 0;
                            CCPR2L = VAL_DER + 0;    
                         }break;
                         
             //76543210                      
        case 0b00001000: {                        
                            CCPR1L = VAL_IZQ + 15;
                            CCPR2L = VAL_DER - 15;    
                         }break;                
                         
             //76543210                      
        case 0b00001100: {                        
                            CCPR1L = VAL_IZQ + 30;
                            CCPR2L = VAL_DER - 40;    
                         }break;                
 
 
             //76543210                      
        case 0b00000100: {                        
                            CCPR1L = VAL_IZQ + 60;
                            CCPR2L = VAL_DER - 50;    
                         }break;                
 
             //76543210                      
        case 0b00000110: {                        
                            CCPR1L = VAL_IZQ + 90;
                            CCPR2L = VAL_DER - 90;    
                         }break;                 
                 
        default:break;
    }
     
}

//-------------------------------------------------------
 
void VALORES_INI_PWM(void)
{
 
    VAL_IZQ = ((AA[1]-48)*100) + ((AA[2]-48)*10)+(AA[3]-48);
    VAL_DER = ((AA[6]-48)*100) + ((AA[7]-48)*10)+(AA[8]-48);
     
    CCPR1L = VAL_IZQ;
    CCPR2L = VAL_DER;
}    
 
//-------------------------------------------------------
 
unsigned char DETERMINAR_ESTADO(int SENSOR)
{
    unsigned char ESTADO = 'C';
     
    switch(SENSOR)
    {
             //76543210
        case 0b00000000: ESTADO = 'B'; break;//BLANCO
        case 0b11111111: ESTADO = 'N'; break;//NEGRO
        case 0b11111000: ESTADO = 'I'; break;//IZQUIERDA
        case 0b11110000: ESTADO = 'I'; break;//IZQUIERDA
        case 0b11100000: ESTADO = 'I'; break;//IZQUIERDA
        case 0b01100000: ESTADO = 'C'; break;//CENTRO
        case 0b00100000: ESTADO = 'C'; break;//CENTRO
        case 0b00110000: ESTADO = 'C'; break;//CENTRO
        case 0b00010000: ESTADO = 'C'; break;//CENTRO
        case 0b00011000: ESTADO = 'C'; break;//CENTRO
        case 0b00001000: ESTADO = 'C'; break;//CENTRO
        case 0b00001100: ESTADO = 'C'; break;//CENTRO
        case 0b00000100: ESTADO = 'C'; break;//CENTRO
        case 0b00000110: ESTADO = 'C'; break;//CENTRO
        case 0b00011111: ESTADO = 'D'; break;//DERECHA
        case 0b00001111: ESTADO = 'D'; break;//DERECHA
        case 0b00000111: ESTADO = 'D'; break;//DERECHA
    }        
     
    return ESTADO;
}
 
//-------------------------------------------------------

void DECIDIR_SENTIDO(void)
{

    static int CONTADOR = 0;
    
    switch (E_ACTUAL)
    {
        case 'B':   {
                        if(E_ANTERIOR == 'I'){G_IZQUIERDA();}
                        else if(E_ANTERIOR =='N'){G_IZQUIERDA();}
                        else if(E_ANTERIOR =='C'){G_COMPLETO();}
                        else if(E_ANTERIOR =='D'){G_DERECHA();}
                    }break;
        
        case 'C':   {
                        if(E_ANTERIOR == 'I'){G_IZQUIERDA();}
                        else if(E_ANTERIOR =='N'){G_IZQUIERDA();}
                        else if(E_ANTERIOR =='D'){AVANZAR(0b00011000);}
                    }break;
                    
        /*case 'N':   {
                        if(E_ANTERIOR == 'N' && CONTADOR <3)
                        {
                            CONTADOR++;
                            AVANZAR(0b00011000);
                        }    
                        
                        else
                        {
                            DETENER();
                        
                        }    
                    };break;*/
    }        
}

//-------------------------------------------------------
void G_IZQUIERDA(void)
{
    unsigned char ESTADO = 0;
    unsigned int SENSOR = 0;
    
    DETENER();
    
           //76543210
    LATD = 0b00001001;
    // Establece el sentido de giro del M1 y M2
    // para que el robot gire sobre su propio eje
    
    CCPR1L = VAL_IZQ;
    CCPR2L = VAL_DER;
    
    do
    {
        SENSOR = LEER_SENSORES();       
        ESTADO = DETERMINAR_ESTADO(SENSOR);
        __delay_ms(2);
    
    } while(ESTADO != 'C');  
    
    DETENER();
    
           //76543210
    LATD = 0b00000101;
    // Establece el sentido de giro del M1 y M2
    // para que el robot Avance
    
    CCPR1L = VAL_IZQ;
    CCPR2L = VAL_DER;
    
    AVANZAR(0b00011000);
    __delay_ms(8);
    E_ACTUAL = 'C';
}
//-------------------------------------------------------
void G_COMPLETO(void)
{
    
    unsigned char ESTADO = 0;
    unsigned int SENSOR = 0;
    
    DETENER();
    
           //76543210
    LATD = 0b00001001;
    // Establece el sentido de giro del M1 y M2
    // para que el robot gire sobre su propio eje
    
    CCPR1L = VAL_IZQ;
    CCPR2L = VAL_DER;
    
    do
    {
        SENSOR = LEER_SENSORES();       
        ESTADO = DETERMINAR_ESTADO(SENSOR);
        __delay_ms(2);
    
    } while(ESTADO != 'C');  
    
    DETENER();
    
           //76543210
    LATD = 0b00000101;
    // Establece el sentido de giro del M1 y M2
    // para que el robot Avance
    
    CCPR1L = VAL_IZQ;
    CCPR2L = VAL_DER;
    
    AVANZAR(0b00011000);
    __delay_ms(8);
    E_ACTUAL = 'C';
}
//-------------------------------------------------------
void DETENER(void)
{
    CCPR1L = CCPR2L = 0;
    // Detiene los motores
       
    LATD = 0;
    // Abre los cuatro interruptores del puente H
    
    __delay_ms(2);
    // Retardo para evitar corto en el puente H
    // Tiempo muerto
}
//-------------------------------------------------------
void G_DERECHA(void)
{
    unsigned char ESTADO = 0;
    unsigned int SENSOR = 0;
    
    DETENER();
    
           //76543210
    LATD = 0b00000110;
    // Establece el sentido de giro del M1 y M2
    // para que el robot gire sobre su propio eje
    
    CCPR1L = VAL_IZQ-30;
    CCPR2L = VAL_DER-30;
    
    do
    {
        TRANSMITIR(13);
        TRANSMITIR('D');
        SENSOR = LEER_SENSORES();       
        ESTADO = DETERMINAR_ESTADO(SENSOR);
        __delay_ms(2);
    
    } while(SENSOR == 0b11000000 ||SENSOR == 0b01000000||SENSOR == 0b01100000);  
    
    DETENER();
    
           //76543210
    LATD = 0b00000101;
    // Establece el sentido de giro del M1 y M2
    // para que el robot Avance
    
    CCPR1L = VAL_IZQ;
    CCPR2L = VAL_DER;
    
    AVANZAR(0b00011000);
    __delay_ms(20);
    E_ACTUAL = 'C';
}
//-------------------------------------------------------
