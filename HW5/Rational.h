//404410053 CSIE2 張碩恩

#include <iostream>
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
		friend function: << + - * / ==
 */

#ifndef RATIONAL_H
#define RATIONAL_H

#include "BigInt.h"
using namespace BigInt_N;

namespace Rational_N{
	class Rational{
		public:
			Rational();
			Rational(BigInt wholeNumber);
			Rational(BigInt numeratorValue, BigInt denominatorValue);
			BigInt getNumerator() const;
			BigInt getDenominator() const;
			void normalize();
			friend ostream& operator <<(std::ostream& outs, const Rational& r);
			friend const Rational operator +(const Rational& r1, const Rational& r2);
			friend const Rational operator -(const Rational& r1, const Rational& r2);
			friend const Rational operator *(const Rational& r1, const Rational& r2);
			friend const Rational operator /(const Rational& r1, const Rational& r2);
			friend Rational operator -(Rational& r);
			friend bool operator ==(const Rational& r1, const Rational& r2);
			bool operator <(const Rational& r2) const;
			bool operator <=(const Rational& r2) const;
			bool operator >(const Rational& r2) const;
			bool operator >=(const Rational& r2) const;

		private:
			BigInt numerator;
			BigInt denominator;
	};
	
	BigInt GCD(const BigInt a, const BigInt b);
}

#endif
