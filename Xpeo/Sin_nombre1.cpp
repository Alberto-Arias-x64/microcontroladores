#include<iostream>
using namespace std;

class Circulo
{
	private: 
		float radio; // caracteristicas
	
	public:
		Circulo(float); // declaracion del constructor
		
		void calArea(); // metodos
		void calPerimetro();
};
//-------------------------------------------------------------
//crear el constructor

Circulo:: Circulo (float radius)
{
	radio = radius;
}
//------------------------------------------------------------

//ceeacion de metodos

void Circulo::calArea ()
{
	cout<<"el area del Circulo es: " << 3.1416 * radio*radio <<endl;
}

void Circulo::calPerimetro()
{
	cout<<"el perimetro es: "<<2*3.1416*radio<<endl;
}
int main()
{ // clase    nombre    clase    parametro
	int x,y;
	cin>>x;
	cin>>y;
	 Circulo   cir1   = Circulo   (x); // creacion de objetos
	 Circulo cir2(y); // creando un metodo 2
	 
	 cir1.calArea();
	 cir1.calPerimetro();
	 
	 cir2.calArea();
	 cir2.calPerimetro(); 
	 
	 system("pause");
	 return 0; 
}
