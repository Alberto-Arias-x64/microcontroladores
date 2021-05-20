#include<iostream>
using namespace std;

class Persona
{
	private: 
		string nombre;
		int codigo; // caracteristicas
	
	public:
		Persona(string,int); // declaracion del constructor
		
		void escribir(); // metodos
};
//-------------------------------------------------------------
//crear el constructor

Persona:: Persona (string nombre1, int codigo1)
{
	nombre = nombre1;
	codigo = codigo1;
}
//------------------------------------------------------------

//creacion del metodos

void Persona::escribir ()
{
	cout<<"mi nombre es: "<<nombre;
	cout<<" con codigo :"<<codigo;
	cout<<" y acabo de esribir este texto";
}

int main()
{ // clase    nombre    clase    parametro
	string nombre;
	int codigo;
	cin>>nombre;
	cin>>codigo;
	Persona   per1   =  Persona (nombre,codigo);
	per1.escribir();
}
