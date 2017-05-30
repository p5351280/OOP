//402520022,Hwang

/*
	class Complex:
		use to store a complex number include two rational number real and imag
	Constructor: 
		there are four kinds of constructor, which include zero,two rational numbre, two string
		1.default parameter: do no thing
		2.two rational numbre parameter: set both real and imag to the number user want
		3.two string parameter: set both real and imag to the number user want
		4.one string parameter: set both real and imag to the number user want
	Access function:
		getReal: to get real
		getImag: to get imag		
	Operator overloading:
		friend function: <<,/
 */
#include <iostream>
#include <string>

#ifndef COMPLEX_H
#define COMPLEX_H

#include "Rational.h"

using namespace std;
using namespace BigInt_N;
using namespace Rational_N;

namespace Complex_N {

	class Complex {
		public:
			Complex();
			
			Complex(Rational r,Rational i);
			//Precindition:Can input like Complex(3,5)-> 3+5i etc.
			Complex(const char *strR,const char *strI);
			//Precindition:Can input like Complex("3/5","810!")-> 3/5+810!i etc.
			Complex(const char *str);
			//Precindition:Can input like Complex("3/5+810!i")-> 3/5+810!i etc.
			
			Rational getReal() const;
			//Postcondition: return the real of the object.
			Rational getImag() const;
			//Postcondition: return the imag of the object.
			
			friend Complex operator /(const Complex& num1, Complex& num2);//(a+bi)/(c+di)={ (ac+bd) + (bc-ad)i } / c^2 + d^2
			
			friend ostream& operator<<(ostream& outputStream,const Complex& num);

		private:          //A+Bi
			Rational real;//A
			Rational imag;//Bi

	};
	void invertString(char *str);
	//Postcondition: return the invert of string
}
#endif
