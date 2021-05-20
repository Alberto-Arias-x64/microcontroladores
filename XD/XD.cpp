#include <iostream>
#include "pc.h"
using namespace std;

int main()
{
	string procesador;
	float ram;
	int video;

	int dato;
	
	if (dato>0)
	{
		video++;
		
	}
	
	Computador pc(procesador,ram,video);
	Computador pc1(video,procesador,ram);
	pc.caracteristicas();
	pc1.caracteristicas();
	pc.~Computador();
	system("pause");
	return 0;
}
