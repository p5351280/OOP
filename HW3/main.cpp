//404410053 CSIE2 張碩恩
//compile on Mac OS 10.12.4
//command line: g++ main.cpp

#include <iostream>
#include <cstdlib>
using namespace std;

/*
	class Rational:
		use to store a rational number include numerator and denominator
	Constructor: 
		there are three kinds of constructor, which include zero, one, two parameter
		default parameter: set numerator to 0, and denominator to 1
		one parameter: set numerator to the number user want, and denominator to 1
		two parameter: set both to the number user want
	Access function:
		getNumerator: to get numerator
		getDenominator: to get denominator
	Member Function:
		normalize: to reduce fraction
	Operator overloading:
		friend function: << >> * / ==
		member function: < <= > >= []
		nonmember function: + -
*/

class Rational{
	public:
		Rational();
		Rational(int wholeNumber);
		Rational(int numeratorValue, int denominatorValue);
		int getNumerator() const;
		int getDenominator() const;
		void normalize();
		friend ostream& operator <<(ostream& outs, const Rational& r);
		friend istream& operator >>(istream& in, Rational& r);
		//non member function : +, -(subtraction), -(subtraction)
		friend Rational operator *(const Rational& r1, const Rational& r2);
		friend Rational operator /(const Rational& r1, const Rational& r2);
		friend bool operator ==(const Rational& r1, const Rational& r2);
		bool operator <(const Rational& r2) const;
		bool operator <=(const Rational& r2) const;
		bool operator >(const Rational& r2) const;
		bool operator >=(const Rational& r2) const;
		int& operator [](int index);

	private:
		int numerator;
		int denominator;
};

/*
	default constructor: set numerator to 0, denominator to 1
*/
Rational::Rational():numerator(0), denominator(1){

}

/*
	one parameter constructor: set numerator as user want, denominator to 1
*/
Rational::Rational(int wholeNumber):numerator(wholeNumber), denominator(1){

}

/*
	two parameter constructor: set numerator and denominator as user want
*/
Rational::Rational(int numeratorValue, int denominatorValue){
	if(denominatorValue == 0){
		cout << "\nERROR : Denominator cannot be 0.\n\n";
		exit(1);
	}
	else{
		numerator = numeratorValue;
		denominator = denominatorValue;
	}
}

/*
	get numerator
*/
int Rational::getNumerator() const{
	return numerator;
}

/*
	get denominator
*/
int Rational::getDenominator() const{
	return denominator;
}

/*
	GCD for normalize to use it
*/
int GCD(int a, int b){
	if(b==0)
		return a;
	else
		return GCD(b, a%b);
}

/*
	normalize to use it
*/
void Rational::normalize(){
	int gcd=GCD(abs(numerator), abs(denominator));
	numerator /= gcd;
	denominator /= gcd;
	if(denominator == 0){
		cout << "\nERROR : Denominator cannot be 0.\n\n";
		exit(1);
	}
	if(denominator < 0){
		numerator = -numerator;
		denominator = -denominator;
	}
}

//friend function operator overloading << for cout
ostream& operator <<(ostream& outs, const Rational& r){
	outs << r.numerator << '/' << r.denominator;
	return outs;
}

//friend function operator overloading >> for cin
istream& operator >>(istream& in, Rational& r){
	int numerator, denominator;
	char slash;
	in >> numerator >> slash >> denominator;
	if(denominator == 0){
		cout << "\nERROR : Denominator cannot be 0.\n\n";
		exit(1);
	}
	r.numerator = numerator;
	r.denominator = denominator;
	return in;
}

//nonmember function operator overloading + for plus
Rational operator +(const Rational& r1, const Rational& r2){
	int numerator = r1.getNumerator()*r2.getDenominator() + r2.getNumerator()*r1.getDenominator();
	int denominator = r1.getDenominator() * r2.getDenominator();
	return Rational(numerator, denominator);
}

//nonmember function operator overloading - for minus
Rational operator -(const Rational& r1, const Rational& r2){
	int numerator = r1.getNumerator()*r2.getDenominator() - r2.getNumerator()*r1.getDenominator();
	int denominator = r1.getDenominator() * r2.getDenominator();
	return Rational(numerator, denominator);
}

//nonmember function operator overloading - for negative
Rational operator -(const Rational& r){
	int numerator = -(r.getNumerator());
	int denominator = r.getDenominator();
	return Rational(numerator, denominator);
}

//friend function operator overloading * for multiple
Rational operator *(const Rational& r1, const Rational& r2){
	int numerator = r1.numerator * r2.numerator;
	int denominator = r1.denominator * r2.denominator;
	return Rational(numerator, denominator);
}

//friend function operator overloading / for divide
Rational operator /(const Rational& r1, const Rational& r2){
	int numerator = r1.numerator * r2.denominator;
	int denominator = r1.denominator * r2.numerator;
	return Rational(numerator, denominator);
}

//friend function operator overloading == for same or not
bool operator ==(const Rational& r1, const Rational& r2){
	return (r1.numerator*r2.denominator) == (r1.denominator*r2.numerator);
}

/* -------------member function operator overloading for compare------------- */
bool Rational::operator <(const Rational& r2) const{
	return (numerator*r2.denominator) < (denominator*r2.numerator);
}

//member
bool Rational::operator <=(const Rational& r2) const{
	return (numerator*r2.denominator) <= (denominator*r2.numerator);
}

//member
bool Rational::operator >(const Rational& r2) const{
	return (numerator*r2.denominator) > (denominator*r2.numerator);
}

//member
bool Rational::operator >=(const Rational& r2) const{
	return (numerator*r2.denominator) >= (denominator*r2.numerator);
}
/* --------------------------------------------------------------------------- */

//member function operator [] overloading for access value
int& Rational::operator [](int index){
	if(index == 0)
		return numerator;
	else if(index == 1)
		return denominator;
	else{
		cout<<"Wrong index.\n";
		exit(1);
	}
}

int main(){
	Rational a, b;
    Rational testConstructorZero, testConstructorOne(5);
    cout << "\n--------------------------- Test for constructor ---------------------------\n";
    cout << "testConstructorZero = " << testConstructorZero << endl;
    cout << "testConstructorOne = " << testConstructorOne << endl;
    cout << "\n------------------------- Test for others function -------------------------\n";
	cout << "Please input Number a, add slash between numerator and denominator.\n";
	cin >> a;
	cout << "Please input Number b, add slash between numerator and denominator.\n";
	cin >> b;
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

    cout << "\n-------------------------- Test for [] operation ---------------------------\n";
	int tmp;
	cout << "Input A's numerator : ";
	cin >> tmp;
	a[0] = tmp;
	cout << "Input A's denominator : ";
	cin >> tmp;
	a[1] = tmp;
	a.normalize();
	cout << "New a : " << a[0] << '/' << a[1] << endl;
	return 0;
}
