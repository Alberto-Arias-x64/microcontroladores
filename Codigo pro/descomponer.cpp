#include<iostream>
#include<math.h>
using namespace std;
main(){
	int x,u,d,c;
	cout<<" introdusca en numero a descomponer ";
	cin>>x;
	u=x % 10;
	cout<<"Las unidades son "<<u<<endl;
	x=(x-u)/10;
	d=x % 10;
	cout<<"Las decenas son "<<d<<endl;
	x=(x-d)/10;
	c=x % 10;
	cout<<"Las centenas son "<<c<<endl;
}
