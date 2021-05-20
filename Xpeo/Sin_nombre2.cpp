#include<iostream>
using namespace std;

class Circulo
{
	private: 
		float radio; // caracteristicas
	
	public:
		Circulo(float); // declaracion del constructor
		
		float calArea(); // metodos
		float calPerimetro();
};
//-------------------------------------------------------------
//crear el constructor

Circulo:: Circulo (float radius)
{
	radio = radius;
}
//------------------------------------------------------------

//ceeacion de metodos

float Circulo::calArea ()
{
	float area;
	area = 3.1416 * radio * radio;
	return area;
}

float Circulo::calPerimetro()
{
	
}
int main()
{ // clase    nombre    clase    parametro
	float x,y;
	cin>>x;
	cin>>y;
	 Circulo   cir1   = Circulo   (x); // creacion de objetos
	 Circulo cir2(y); // creando un metodo 2
	
	float area = 0;
	cir1.calArea();
	area = cir1.calArea();
	cout<<"el area es: "<<area<<endl;	 
	 cir1.calPerimetro();
	 cir2.calArea();
	 cir2.calPerimetro(); 
}
