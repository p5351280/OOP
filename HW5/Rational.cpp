//404410053 CSIE2 張碩恩
//compile on Mac OS 10.12.4
//command line: g++ main.cpp

#include <iostream>
#include <cstdlib>
#include <cstring>
#include "BigInt.h"
#include "Rational.h"

using namespace std;

namespace Rational_N{

	Rational::Rational():numerator(0), denominator(1){

	}

	Rational::Rational(BigInt wholeNumber):numerator(wholeNumber), denominator(1){

	}

	Rational::Rational(BigInt numeratorValue, BigInt denominatorValue){
		if(denominatorValue == 0){
			cout << "\nERROR : Denominator cannot be 0.\n\n";
			exit(1);
		}
		else{
			numerator = numeratorValue;
			denominator = denominatorValue;
		}
	}
	Rational::Rational(const char *str){
	    char strN[1000]={0},strD[1000]={0};
	    int index=0,flag=0;
	    
		for(int i=0;i<strlen(str);i++){
			if(str[i]=='/'){
	            strN[index]='\0';
				index=0;
	            flag=1;
	            continue;
			}
			if(flag==0){
				strN[index++]=str[i];
		    }
			else if(flag==1){
	            strD[index++]=str[i];
			}
		} 
		if(flag==0){strD[0]='1';strD[1]='\0';}
		else strD[index]='\0';

		BigInt n(strN),d(strD);
		numerator=n;
		denominator=d;   	
	}

	BigInt Rational::getNumerator() const{
		return numerator;
	}

	BigInt Rational::getDenominator() const{
		return denominator;
	}

	/*
	   GCD for normalize to use it
	 */
	BigInt GCD(BigInt a, BigInt b){
        //cout<<"GCD"<<b<<endl;
		if(b==0)
			return a;
		else
			return GCD(b, a%b);
	}

	/*
	   normalize to use it
	 */
	void Rational::normalize(){
		BigInt gcd=GCD(numerator.abs(), denominator.abs());
		numerator = numerator/gcd;
		denominator = denominator/gcd;
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
    istream& operator>>(istream& inputStream,Rational& r){
	        char c;
	    	inputStream>>r.numerator;
			inputStream>>c;

			inputStream>>r.denominator;
	        return inputStream;
    }

	//friend function operator overloading + for plus
	const Rational operator +(const Rational& r1, const Rational& r2){
		BigInt numerator = r1.numerator*r2.denominator + r2.numerator*r1.denominator;
		BigInt denominator = r1.denominator * r2.denominator;
		return Rational(numerator, denominator);
	}

	//friend function operator overloading - for minus
	const Rational operator -(const Rational& r1, const Rational& r2){
		BigInt numerator = r1.numerator*r2.denominator - r2.numerator*r1.denominator;
		BigInt denominator = r1.denominator * r2.denominator;
		return Rational(numerator, denominator);
	}

	//friend function operator overloading - for negative
	Rational operator -(Rational& r){
		BigInt numerator = -(r.numerator);
		BigInt denominator = r.denominator;
		return Rational(numerator, denominator);
	}

	//friend function operator overloading * for multiple
	const Rational operator *(const Rational& r1, const Rational& r2){
		BigInt numerator = r1.numerator * r2.numerator;
		BigInt denominator = r1.denominator * r2.denominator;
		return Rational(numerator, denominator);
	}

	//friend function operator overloading / for divide
	const Rational operator /(const Rational& r1, const Rational& r2){
		BigInt numerator = r1.numerator * r2.denominator;
		BigInt denominator = r1.denominator * r2.numerator;
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


}
