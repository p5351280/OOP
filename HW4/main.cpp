#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

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
		int *number;
		int size;
		bool negative;
};

int cmp(BigInt a, BigInt b){
	if(a.size > b.size)
		return 1;
	else if(a.size < b.size)
		return 2;
	else{
		for(int i=a.size-1; i>=0; i--){
			if(a.number[i] > b.number[i])
				return 1;
			else if(a.number[i] < b.number[i])
				return 2;
		}
	}
	if(a.negative && !b.negative)
		return 2;
	if(!a.negative && b.negative)
		return 1;
	return 0;
}

BigInt::BigInt(){
	size = 1;
	number = new int[size];
	number[0] = 0;
	negative = false;
}

BigInt::~BigInt(){
	delete [] number;
	number = NULL;
}

BigInt::BigInt(int num){
	if(num<0)
		negative = true;
	else
		negative = false;

	num = abs(num);
	if(num>0)
		size = log10(num)+1;
	else
		size = 1;

	number = new int[size];

	for(int i=0; i<size; i++){
		number[i] = num%10;
		num /= 10;
	}
}

BigInt::BigInt(const char *numArray){
	if(numArray[0] == '-'){
		negative = true;
		size = strlen(numArray)-1;
	}
	else{
		negative = false;
		size = strlen(numArray);
	}

	number = new int[size];

	if(negative)
		for(int i=0; i<size; i++)
			number[i] = numArray[i+1]-'0';
	else
		for(int i=0; i<size; i++)
			number[i] = numArray[i]-'0';
	reverse(number, number+size);
}

BigInt::BigInt(const BigInt& inObject){
	negative = inObject.negative;
	size = inObject.size;
	number = new int[size];
	for(int i=0; i<size; i++)
		number[i] = inObject.number[i];
}

BigInt& BigInt::operator =(const BigInt& rtValue){
	if(this == &rtValue)
		return *this;
	else{
		negative = rtValue.negative;
		size = rtValue.size;
		delete [] number;
		number = new int[size];
		for(int i=0; i<size; i++)
			number[i] = rtValue.number[i];
		return *this;
	}
}

ostream& operator <<(ostream& output, const BigInt& a){
	if(a.negative)
		output << "-";
	for(int i=a.size-1; i>=0; i--)
		output << a.number[i];
	return output;
}

BigInt operator +(BigInt a, BigInt b){
    if(cmp(a, b) == 2){
        BigInt temp;
        temp = a;
        a = b;
        b = temp;
    }
    BigInt result;
    int maxSize = a.size, minSize = b.size;
    result.number = new int[maxSize+1];
    for(int i=0; i<=maxSize; i++)
		result.number[i] = 0;
	if(a.negative == b.negative){
		if(a.negative)
			result.negative = true;
		else
			result.negative = false;
		
		for(int i=0; i<minSize; i++)
			result.number[i] += a.number[i]+b.number[i];
		for(int i=minSize; i<maxSize; i++)
			result.number[i] += a.number[i];
		for(int i=0; i<maxSize; i++){
			result.number[i+1] += result.number[i]/10;
			result.number[i] %= 10;
		}
		if(result.number[maxSize])
			result.size = maxSize+1;
		else
			result.size = maxSize;
	}

	else if(!a.negative){
		result.negative = false;
		for(int i=0; i<b.size; i++)
			b.number[i] = -b.number[i];
		for(int i=0; i<minSize; i++){
			result.number[i] += a.number[i]+b.number[i];
			if(result.number[i] < 0){
				result.number[i+1]--;
				result.number[i] += 10;
			}
		}
		for(int i=minSize; i<maxSize; i++)
			result.number[i] += a.number[i];

		for(int i=0; i<maxSize; i++){
			result.number[i+1] += result.number[i]/10;
			result.number[i] %=10;
		}
		for(int i=maxSize-1; i>=0; i--)
			if(result.number[i]){
				result.size = i+1;
				break;
			}	
	}
 	
	/* -a+b = -( -(-a)+(-b) ) */
    else{
        a.negative ^= 1;
        b.negative ^= 1;
        result = a+b;
        result.negative ^= 1;
    }

	return result;
}

BigInt operator -(BigInt a, BigInt b){
	b.negative ^= 1;
	return a+b;
}

int main(){
	BigInt a("-929"), b("928"), c;
	c = a+b;
	cout << c << endl;
}
