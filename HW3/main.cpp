#include <iostream>
#include <cstdlib>
using namespace std;

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

Rational::Rational():numerator(0), denominator(1){

}

Rational::Rational(int wholeNumber):numerator(wholeNumber), denominator(1){

}

Rational::Rational(int numeratorValue, int denominatorValue){
	if(denominatorValue == 0)
		cout<<"DenominatorValue cannot be 0.\n";
	else{
		numerator = numeratorValue;
		denominator = denominatorValue;
	}
}

int Rational::getNumerator() const{
	return numerator;
}

int Rational::getDenominator() const{
	return denominator;
}

int GCD(int a, int b){
	if(b==0)
		return a;
	else
		return GCD(b, a%b);
}

void Rational::normalize(){
	int gcd=GCD(abs(numerator), abs(denominator));
	numerator /= gcd;
	denominator /= gcd;
	if(denominator < 0){
		numerator = -numerator;
		denominator = -denominator;
	}
}

//friend
ostream& operator <<(ostream& outs, const Rational& r){

}

//friend
istream& operator >>(istream& in, Rational& r){

}

//nonmember
Rational operator +(const Rational& r1, const Rational& r2){
	int numerator = r1.getNumerator()*r2.getDenominator() + r2.getNumerator()*r1.getDenominator();
	int denominator = r1.getDenominator() * r2.getDenominator();
	return Rational(numerator, denominator);
}

//nonmember
Rational operator -(const Rational& r1, const Rational& r2){
	int numerator = r1.getNumerator()*r2.getDenominator() - r2.getNumerator()*r1.getDenominator();
	int denominator = r1.getDenominator() * r2.getDenominator();
	return Rational(numerator, denominator);
}

//nonmember
Rational operator -(const Rational& r){
	int numerator = -(r.getNumerator());
	int denominator = r.getDenominator();
	return Rational(numerator, denominator);
}

//friend
Rational operator *(const Rational& r1, const Rational& r2){
	int numerator = r1.numerator * r2.numerator;
	int denominator = r2.numerator * r2.numerator;
	return Rational(numerator, denominator);
}

//friend
Rational operator /(const Rational& r1, const Rational& r2){
	int numerator = r1.numerator * r2.denominator;
	int denominator = r1.denominator * r1.numerator;
	return Rational(numerator, denominator);
}

//friend
bool operator ==(const Rational& r1, const Rational& r2){
	return (r1.numerator*r2.denominator) == (r1.denominator*r2.numerator);
}

//member
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

//member
int& Rational::operator [](int index){
	if(index == 0)
		return numerator;
	else if(index == 1)
		return denominator;
	else
		cout<<"Wrong index.\n";
}

int main(){
	return 0;
}
