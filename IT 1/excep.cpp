#include<conio.h>
#include<iostream>
using namespace std;
void main(){
	int num = 100;
	cout << "number" << num<<endl;
	cout << "in decimal" << endl;
	cout.setf(ios::oct ios::basefield);
	cout << num << endl;
	_getch();

}