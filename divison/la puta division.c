#include<p18f452.h>
int x,y,z;
void main (void)
{
    ADCON1=0x07;                               // Todos los pines analogo/digital en modo digital
	TRISAbits.RA0=1;                           // bitRA0 del PORTA como entrada
    TRISAbits.RA1=0;                           // bitRA1 del PORTA como salida
	TRISB=0xFF;                                // los 8 bits del PORTB como entradas
	TRISC=0xFF;                                // los 8 bits del PORTC como entradas
	TRISD=0x00;                                // los 8 bits del PORTD como salidas
	while(1)                                   // ciclo infinito
	{
		x=PORTB;
		y=PORTC;
		z=0;
        PORTAbits.RA1=0;
		if(y==0)                               // caso especial
		{
			PORTD=0xFF;
		}
		else
		{
			while(2)
			{
				if(y<=x)
			    {
				x=x-y;                         // operaciones matematicas
				z=z+1;
			    }
			    else
			    {
			    	if(PORTAbits.RA0==1)       // selector
			    	{
                        PORTD=z;               // imprime el resultado
                        PORTAbits.RA1=1;
                        break;
				    }
				    else
				    {
				    	PORTD=x;               // imprime el residuo
                        break;
					}
                }
		    }
	    }
	}
}
