#include<p18f452.h>
#include<delays.h>
int contu, contd, tiempo;
unsigned char display [10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
void main (void)
{
	TRISB=0x00;
	TRISA=0x1c;
	ADCON1=0x07;
	PORTAbits.RA0=1;
	PORTAbits.RA1=1;//Apagar diplays
	if(PORTAbits.RA3==0 && PORTAbits.RA4==0) 	
	{
	while(1)
		{	
	    contu=0;
		contd=0;
			while(contd<10)
			{
				while(contu<10)
				{
					tiempo=0;
					while (tiempo<20)
					{
						if(PORTAbits.RA3==0 && PORTAbits.RA4==0) 
						{
							PORTB=display [contu];
							PORTAbits.RA0=0;
							Delay10KTCYx(1);
							PORTAbits.RA0=1;
							PORTB=display[contd];
							PORTAbits.RA1=0;
							Delay10KTCYx(1);
							PORTAbits.RA1=1;
							if(PORTAbits.RA2==1)
							{
								contu=0;
								contd=0;
								tiempo=20;
								contu=contu-3;
							}
							tiempo++;
	 	 				}
						else
						{
							return 0;
						}		
					}
					contu=contu+3;
				}
	            contu=contu-10;
				contd++;
			}
		}	
	}
	else 
	{
		if(PORTAbits.RA3==1 && PORTAbits.RA4==0)
		{
			while(1)
			{	
				contd=9;
	   			contu=8;
				while(contd>=0)
				{
					while(contu>=0)
					{
						tiempo=0;
						while (tiempo<20)
						{
		               		if(PORTAbits.RA3==1 && PORTAbits.RA4==0)
		               		{
								PORTB=display [contu];
								PORTAbits.RA0=0;
								Delay1KTCYx(10);
								PORTAbits.RA0=1;
								PORTB=display[contd];
								PORTAbits.RA1=0;
								Delay1KTCYx(10);
								PORTAbits.RA1=1;
								if(PORTAbits.RA2==1)
								{
									contu=8;
									contd=9;
									tiempo=20;
									contu=contu+2;
								}
							tiempo++;
	                   		}
	                     	else 
		                   	{
		                  		return 0;
		                  	} 
						}
						contu=contu-2;
					}
		       	contu=contu+10;
				contd--;
				}
			}	
		}
	else
		{
		if(PORTAbits.RA3==0 && PORTAbits.RA4==1) 	
		{
		while(1)
			{	
		    contu=0;
			contd=0;
				while(contd<10)
				{
					while(contu<10)
					{
						tiempo=0;
						while (tiempo<20)
						{
							if(PORTAbits.RA3==0 && PORTAbits.RA4==1) 
							{
							PORTB=display [contu];
							PORTAbits.RA0=0;
							Delay10KTCYx(1);
							PORTAbits.RA0=1;
							PORTB=display[contd];
							PORTAbits.RA1=0;
							Delay10KTCYx(1);
							PORTAbits.RA1=1;
							if(PORTAbits.RA2==1)
							{
								contu=0;
								contd=0;
								tiempo=20;
								contu=contu-4;
							}
							tiempo++;
		 	 				}
						else
						{
							return 0;
						}		
					}
					contu=contu+4;
				}
			contu=contu-10;
			contd++;
			}
		}	
	}
	else 
		{
			if(PORTAbits.RA3==1 && PORTAbits.RA4==1) 	
				{
				while(1)
					{	
				    contu=0;
					contd=9;
						while(contd>=0)
						{
							contd=9;
							while(contd>=0)
							{
								tiempo=0;
								while (tiempo<20)
								{
									if(PORTAbits.RA3==1 && PORTAbits.RA4==1) 
									{
									PORTB=display [contu];
									PORTAbits.RA0=0;
									Delay10KTCYx(1);
									PORTAbits.RA0=1;
									PORTB=display[contd];
									PORTAbits.RA1=0;
									Delay10KTCYx(1);
									PORTAbits.RA1=1;
									if(PORTAbits.RA2==1)
									{
										contu=9;
										contd=0;
										tiempo=20;
									}
									tiempo++;
				 	 				}
								else
								{
									return 0;
								}		
							}
							contd--;
							}
						}
					}		
				}
			}
		}
	}
}
