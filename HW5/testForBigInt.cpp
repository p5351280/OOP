#include <iostream>
#include <cstdlib>
#include "BigInt.h"
using namespace std;
using namespace BigInt_N;
int main()
{
    BigInt a("123!"), b("101"), c, g;
	
	cin >> a;
	cin >> b;
	cout << "a : " << a << endl << "b : " << b << endl;
	c = a + b;
    cout << a << " + " << b << " = " << c << endl;
	
	c = a - b;
    cout << a << " - " << b << " = " << c << endl;
	
	c = a * b;
    cout << a << " * " << b << " = " << c << endl;
	
	c = a / b;
	cout << a << " / " << b << " = " << c << endl;

	c = a % b;
	cout << a << " % " << b << " = " << c << endl;
    return 0;
}

