//404410053 CSIE2 張碩恩
//compile on Mac OS 10.12.4
//command line: g++ main.cpp

#include <iostream>
#include <cstdlib>
#include "BigInt.h"
#include "Rational.h"

using namespace std;
using namespace BigInt_N;
using namespace Rational_N;

int main(){
	Rational a, b;
    Rational testConstructorZero, testConstructorOne(5);
	char num[1000], deno[1000];
    cout << "\n--------------------------- Test for constructor ---------------------------\n";
    cout << "testConstructorZero = " << testConstructorZero << endl;
    cout << "testConstructorOne = " << testConstructorOne << endl;
    cout << "\n------------------------- Test for others function -------------------------\n";
	cout << "Please input Number a's numerator:";
	cin >> num;
	cout << "Please input Number a's denominator:";
	cin >> deno;
	a = Rational(num, deno);
	cout << "Please input Number b's numerator:";
	cin >> num;
	cout << "Please input Number b's denominator:";
	cin >> deno;
	b = Rational(num, deno);
	cout << "\nAll the answer will print after normalize.\n\n";
	a.normalize();
	b.normalize();
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	Rational ans;

	ans = a+b;
	ans.normalize();
	cout << "a + b = " << ans << endl;

	ans = a-b;
	ans.normalize();
	cout << "a - b = " << ans << endl;

	ans = -a;
	ans.normalize();
	cout << "-a = " << ans << endl;

	ans = a*b;
	ans.normalize();
	cout << "a * b = " << ans << endl;

	ans = a/b;
	ans.normalize();
	cout << "a / b = " << ans << endl;

	if(a==b)	cout << a << " = " << b << endl;
	if(a<b)		cout << a << " < " << b << endl;
	if(a<=b)	cout << a << " <= " << b << endl;
	if(a>b)		cout << a << " > " << b << endl;
	if(a>=b)	cout << a << " >= " << b << endl;

	return 0;
}
