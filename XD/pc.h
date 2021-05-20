#include <iostream>
using namespace std;

class Computador
{
	private:
		string procesador;
		float ram;
		int video;
		
	public:
		Computador(string,float,int);
		Computador(int,string,float);
		~Computador();
		void caracteristicas();
};
Computador::Computador(string procesador1,float ram1,int video1)
{
	procesador=procesador1;
	ram=ram1;
	video=video1;
}
Computador::Computador(int video2,string procesador2,float ram2)
{
	procesador=procesador2;
	ram=ram2;
	video=video2;
}
Computador::~Computador(){
}
void Computador::caracteristicas()
{
	cout<<"el computador tiene un procesador "<<procesador<<" con una cantidad de ram "<<ram<<" y una memoria de video de "<<video<<endl;
}
