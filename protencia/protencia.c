#include<p18f452.h>                // Libreria del pic18F452
int x,y,z,res;                     // Definicion de variables
unsigned char multi(int a,int b)   // Definicion de subrutina
{
	res=b;
	a--;
	while(a>0)
	{
		res=res+b;
		a--;
	}
	return(res);
}
void main(void)                    // Programa principal
{
	TRISB=0XFF;                    // Programacion puerto b como entrada
	TRISC=0XFF;                    // Programacion puerto c como entrada
	TRISD=0X00;                    // programacion puerto d como salida
	while(1)                       // Ciclo infinito 
	{
		x=PORTB;
		y=PORTC;
		if(y==0)
		{
			if(x==0)
			{
				PORTD=0XFF;       // Error matematico
			}
			else
			{
				PORTD=0X01;       // Numero elevado a la 0
			}
		}
		else
		{
			z=x;
			y--;
		while(y>0)
			{
				multi(x,z);
				y--;
				x=res;
			}
			PORTD=x;                // Imprime resultado
		}
	}
}
