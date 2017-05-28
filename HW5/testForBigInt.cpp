#include <iostream>
#include <cstdlib>
#include "BigInt.h"
using namespace std;
using namespace BigInt_N;
int main()
{
    BigInt a("100"), b("100"), c, g;
	
	cin >> a;
	cin >> b;
	
	cout << "a = " << a << endl << "b = " << b << endl;
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

