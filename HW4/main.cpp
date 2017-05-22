//404410053 CSIE2 張碩恩
//compile on Mac OS 10.12.4
//command line: g++ main.cpp

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

/*
	class BigInt:
		use to do store BigInt, include positive and negative
	Constructor:
		there are three kinds of constructor
		1. default constructor, set number to 0
		2. constructor for the argument which is integer
		3. constructor for the arguement which is char array
		4. constructor for the arguement which is BigInt (Copy Constructor)
	Operator overloading:
		friend function: << + -
		member function: =
	Others:
		1. Destructor
		2. Compare function (friend function)
*/

class BigInt{
	public:
		BigInt();
		~BigInt();
		BigInt(const int num);
		BigInt(const char *numArray);
		BigInt(const BigInt& inObject);
		BigInt& operator =(const BigInt& rtValue);
		friend ostream& operator <<(ostream& output, const BigInt& a);
		friend BigInt operator +(BigInt a, BigInt b);
		friend BigInt operator -(BigInt a, BigInt b);
		friend int cmp(BigInt a, BigInt b);	
	private:
		int *digit;
		int size;
		bool negative;
};

/*
	Compare the absolute value of BigInt.
	If absolute value is the same, then will compare number include negative.
	The function will be used in implement of overloading operator +
	
	Return 1 if first parameter larger than second
	Return 2 if second parameter larger than first
	Return 0 if both are the same
*/
int cmp(BigInt a, BigInt b){
	if(a.size > b.size)
		return 1;
	else if(a.size < b.size)
		return 2;
	else{
		for(int i=a.size-1; i>=0; i--){
			if(a.digit[i] > b.digit[i])
				return 1;
			else if(a.digit[i] < b.digit[i])
				return 2;
		}
	}
	if(a.negative && !b.negative)
		return 2;
	if(!a.negative && b.negative)
		return 1;
	return 0;
}

/*
	Default constructor: set BigInt to 0
*/
BigInt::BigInt(){
	size = 1;
	digit = new int[size];
	digit[0] = 0;
	negative = false;
}

/*
	Destructor
*/
BigInt::~BigInt(){
	delete [] digit;
	digit = NULL;
}

/*
	Constructor with integer
*/
BigInt::BigInt(int num){
	if(num<0)
		negative = true;
	else
		negative = false;

	num = abs(num);	//change into absolute number
	if(num>0)
		size = log10(num)+1;	//find how long the number is
	else
		size = 1;

	digit = new int[size];	//get amemory with size 'size'

	for(int i=0; i<size; i++){	//store into class
		digit[i] = num%10;
		num /= 10;
	}
}

/*
	Constructor with char array
*/
BigInt::BigInt(const char *numArray){
	int start=0;
	int sizeArray = strlen(numArray);
	if(numArray[0] == '-'){		//find if the number is negative
		negative = true;
		start = 1;
		for(start=start; start<sizeArray; start++)
			if(numArray[start] != '0')	break;	//check if there have extra 0
		size = sizeArray-start;	//if yes, minus them
	}
	else{	//is positive
		negative = false;
        if(numArray[0] == '+')	start = 1;
		for(start=start; start<sizeArray; start++)
            if(numArray[start] != '0')	break;	//check if there have extra 0
        size = sizeArray-start;	//if yes, minus them
	}
    if(start == sizeArray){	//if all the number is 0
        size = 1;
        digit = new int[size];
        digit[0] = 0;
        negative = false;
    }
    else{
        digit = new int[size];	//get a memory with size 'size'
        int cnt=0;
        for(int i=start; i<sizeArray; i++)	//copy from start
            digit[cnt++] = numArray[i]-'0';	//store into class (for negative)
        reverse(digit, digit+size);
    }
}

/*
	Copy Constructor
*/
BigInt::BigInt(const BigInt& inObject){
	negative = inObject.negative;
	size = inObject.size;
	digit = new int[size];
	for(int i=0; i<size; i++)
		digit[i] = inObject.digit[i];
}

/*
	Operator overloading =
*/
BigInt& BigInt::operator =(const BigInt& rtValue){
	if(this == &rtValue)	//if having a=a, just return a
		return *this;
	else{
		negative = rtValue.negative;
		size = rtValue.size;
		delete [] digit;
		digit = new int[size];
		for(int i=0; i<size; i++)
			digit[i] = rtValue.digit[i];
		return *this;
	}
}

/*
	Operator overloading <<, make the class can use for cout
*/
ostream& operator <<(ostream& output, const BigInt& a){
	if(a.negative)
		output << "-";
	for(int i=a.size-1; i>=0; i--)
		output << a.digit[i];
	return output;
}

/*
	Operator overloading +
*/
BigInt operator +(BigInt a, BigInt b){	//because will change a b value, so use call by value
    if(cmp(a, b) == 2){	//first use compare function to make the bigger ones put in front
        BigInt temp;
        temp = a;
        a = b;
        b = temp;
    }
    BigInt result;
    int maxSize = a.size, minSize = b.size;
    result.digit = new int[maxSize+1];
    for(int i=0; i<=maxSize; i++)
		result.digit[i] = 0;
	if(a.negative == b.negative){	//for a+b or (-a)+(-b)=>-(a+b)
		if(a.negative)
			result.negative = true;
		else
			result.negative = false;

		/* doing BigInt plus */
		for(int i=0; i<minSize; i++)
			result.digit[i] += a.digit[i]+b.digit[i];
		for(int i=minSize; i<maxSize; i++)
			result.digit[i] += a.digit[i];
		for(int i=0; i<maxSize; i++){
			result.digit[i+1] += result.digit[i]/10;
			result.digit[i] %= 10;
		}

		/* check if there have one more digit */
		if(result.digit[maxSize])
			result.size = maxSize+1;
		else
			result.size = maxSize;
	}

	else if(!a.negative){	//doing a+(-b)
		result.negative = false;	//because |a|>|b|, we can know solution is positive
		
		/* doing BigInt plus */
		for(int i=0; i<b.size; i++)
			b.digit[i] = -b.digit[i];	//change every digits of B into negative
		for(int i=0; i<minSize; i++)
			result.digit[i] += a.digit[i]+b.digit[i];
		for(int i=minSize; i<maxSize; i++)
			result.digit[i] += a.digit[i];
		for(int i=0; i<maxSize; i++){
			if(result.digit[i] < 0){	//if some digit is negative
				result.digit[i+1]--;	//borrow from next digit
				result.digit[i] += 10;
			}
			result.digit[i+1] += result.digit[i]/10;
			result.digit[i] %=10;
		}
		
		/* to check how long is the solution */
		for(int i=maxSize-1; i>=0; i--)
			if(result.digit[i]){
				result.size = i+1;
				break;
			}	
	}
 	
	else{		//doing -a+b , it the same as -( -(-a)+(-b) )
        a.negative ^= 1;	//change a sign
        b.negative ^= 1;	//change b sign
        result = a+b;
        result.negative ^= 1;
    }

	return result;
}
/*
	Operator overloading -
*/
BigInt operator -(BigInt a, BigInt b){
	b.negative ^= 1;	//change b sign
	return a+b;			//then doing a+b is equal to a-b
}

int main(){
	BigInt a("314159265358979323846264338327950288419716939937510"), c(a);
	BigInt *b = new BigInt(1618033988);

	cout << "Test by default" << endl;
	c = a + *b;
	cout << a << " + " << *b << " = " << c << endl; 
	c = a - *b;
	cout << a << " - " << *b << " = " << c << endl;

	cout << endl << "Test by user" << endl;
	cout << "Input x and y" << endl;
    char x[1000]={0}, y[1000]={0};
	while(1){
		cout << "x : ";
		cin >> x;
		cout <<"y : ";
		cin >> y;
		BigInt A(x), B(y), C;
		C = A + B;
		cout << A << " + " << B << " = " << C << endl;
		C = A - B;
		cout << A << " - " << B << " = " << C << endl;
        memset(x, 0, sizeof(x));
        memset(y, 0, sizeof(y));
	}
}
