//402520022,Hwang
#include "Complex.h"
#include <cstring>
#include <iostream>

using namespace std;


namespace Complex_N {
	
	Complex::Complex() {};

	Complex::Complex(Rational r,Rational i) {
		real=r;
		imag=i;
	}
	Complex::Complex(const char *strR, const char *strI){
		Rational r(strR),i(strI);
	    real=r;
		imag=i;	
	}
	Complex::Complex(const char *str){                   
		char strR[1000]={0},strI[1000]={0};
		int index=0,flag=0;
		for(int i=strlen(str)-2;i>=0;i--){     
			if(flag==0 && str[i]=='+'){
				flag=1;
				strI[index]='\0';
				index=0;
			}
			else if(flag==0 && str[i]=='-' && str[i-1]!='/') {
				strI[index++]='-';
				flag=1;
				strI[index]='\0';
				index=0;
			}
			else if(flag==0)strI[index++]=str[i];
			else if(flag==1)strR[index++]=str[i];
			
		}
		if(flag==0){strR[0]='0';strR[1]='\0';}
		else strR[index]='\0';
		invertString(strR);
		invertString(strI);
		Rational r(strR),i(strI);
	    real=r;
		imag=i;	
	}
	Rational Complex::getReal() const{
		return real;
	}
	Rational Complex::getImag() const{
		return imag;
	}
	    	
    //(a+bi)/(c+di)={ (ac+bd) + (bc-ad)i } /(c^2 + d^2)
	Complex operator / (const Complex& N1, Complex& N2) {
		Rational realOfAns,imagOfAns;
        Rational deom=N2.real*N2.real+N2.imag*N2.imag;
        
		realOfAns=(N1.real * N2.real + N1.imag*N2.imag)/deom;
        realOfAns.normalize();
        
		imagOfAns=(N1.imag*N2.real-N1.real*N2.imag)/deom;
		imagOfAns.normalize();

		Complex Ans(realOfAns,imagOfAns);
		return Ans;
	}

	ostream& operator<<(ostream& outputStream,const Complex& num) {
		Rational Zero(0,1);
		
		outputStream<<num.real<<endl;
        
		if(num.imag >= Zero)outputStream<<"+";
        
		outputStream<<num.imag <<"i";

		return outputStream;
	}
	void invertString(char *str){
	    char temp;
		int i=0,j=0;
		for(i=0,j=strlen(str)-1;i<strlen(str)/2;i++,j--){
			temp=str[j];
			str[j]=str[i];
			str[i]=temp;
		}    	
	}
}

