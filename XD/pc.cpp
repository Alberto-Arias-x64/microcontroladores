#include <iostream>
#include "pc.h"
using namespace std;
int main()
{
	string procesador;
	float ram;
	int video;
	cout<<"introduzca la marca del procesador ";
	cin>>procesador;
	cout<<"introduzca la cantidad de memoria ram GB ";
	cin>>ram;
	cout<<"introduzca la cantidad de memoria grafica GB ";
	cin>>video;
	
	Computador pc(procesador,ram,video);
	Computador pc1(video,procesador,ram);
	pc.caracteristicas();
	pc1.caracteristicas();
	pc.~Computador();
	system("pause");
	return 0;
}
