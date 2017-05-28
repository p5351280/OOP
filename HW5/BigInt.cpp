/*Mike Chen,404220029,2017/5/26/4:30*/
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include "BigInt.h"
using namespace std;

namespace BigInt_N{
#define DEFAULT_CAPACITY 300

	BigInt BigInt::abs(){
		BigInt temp = *this;
		temp.sign = 0;
		return temp;
	}

	BigInt::BigInt()
		:capacity(DEFAULT_CAPACITY), realUsage(1), sign(0)
	{
		digit = new int[capacity];

		//set all digits to 0
		for(int i(0);i<capacity;i++)
			digit[i] = 0;
	}

	BigInt::BigInt(int initial)
		:capacity(DEFAULT_CAPACITY), realUsage(0)
	{
		digit = new int[capacity];

		if(initial < 0)
		{
			sign = 1;
			initial = -initial;
		}
		else
			sign = 0;

		if(initial == 0)
		{
			realUsage = 1;
			digit[0] = 0;
		}
		//input numbers to digit[]
		while(initial > 0)
		{
			digit[realUsage] = initial % 10;
			initial = initial / 10;
			realUsage++;
		}
		//set the remaining digits to 0
		for(int i(realUsage);i<capacity;i++)
			digit[i] = 0;
	}

	BigInt::BigInt(const char initial[])
		:capacity(DEFAULT_CAPACITY), realUsage(strlen(initial))
	{
		int i(0);
		bool factorial(0);

		//check if there is '-' at start
		if(initial[0] == '-')
		{
			sign = 1;
			realUsage--;
		}
		else
			sign = 0;

		//check if there is '!' at end
		if(initial[realUsage+sign-1] == '!')
		{
			factorial = 1;
			realUsage--;
		}

		//extend capacity
		while(capacity < realUsage)
			capacity = capacity*2;

		digit = new int[capacity];

		//input numbers but not input '-' and '!' to digit[]
		for(i=realUsage+sign;i>sign;i--)
			digit[realUsage+sign-i] = initial[i-1] - 48;

		//set the remaining digits to 0
		for(i=realUsage;i<capacity;i++)
			digit[i] = 0;

		//operate on factorial (!)
		if(factorial)
		{
			if(realUsage == 1 && digit[0] == 0)
			{
				sign = 0;
				digit[0] = 1;
			}
			else
			{
				bool memorySign = sign;
				sign = 0;
				BigInt Mplier(*this - 1);		

				while(Mplier >= 2)
				{
					*this = *this * Mplier;
					Mplier = Mplier - 1;
				}

				sign = memorySign;
			}
		}

		this->realUsageAdjust();
		this->signAdjust();
	}

	BigInt::BigInt(const BigInt& initial)
		:capacity(initial.capacity), realUsage(initial.realUsage), sign(initial.sign)
	{
		int i(0);
		digit = new int[capacity];

		for(i=0;i<initial.realUsage;i++)
			digit[i] = initial.digit[i];

		//set the remaining digits to 0
		for(i=i;i<initial.capacity;i++)
			digit[i] = 0;
	}

	BigInt::~BigInt()
	{
		delete[] digit;
	}

	void BigInt::capacityExtend(const int needCapacity)
	{
		int i(0);

		if(capacity < needCapacity)
		{
			while(capacity < needCapacity)
				capacity = capacity * 2;

			int *olddigit = digit;
			digit = new int[capacity];

			for(i=0;i<realUsage;i++)
				digit[i] = olddigit[i];

			//set the remaining digits to 0
			for(i=i;i<capacity;i++)
				digit[i] = 0;

			delete[] olddigit;
		}
	}

	void BigInt::realUsageAdjust()
	{
		int i(capacity-1);

		while(i >= 1 && digit[i] == 0)
			i--;

		realUsage = i + 1;
	}

	void BigInt::signAdjust()
	{
		if(realUsage == 1 && digit[0] == 0)
			sign = 0;
	}

	const int BigInt::getCapacity() const
	{
		return capacity;
	}

	const int BigInt::getRealUsage() const
	{
		return realUsage;
	}

	const int BigInt::getDigit(const int location) const
	{
		return ((location > realUsage || location < 1) ? 0:digit[location - 1]);
	}

	const bool BigInt::getSign() const
	{
		return sign;
	}

	const bool BigInt::setCapacity(int newCapacity)
	{
		if(newCapacity < realUsage)
			return 0;
		else
		{
			int i(0), *olddigit = digit;
			digit = new int[newCapacity];
			capacity = newCapacity;

			for(i=0;i<realUsage;i++)
				digit[i] = olddigit[i];

			//set the remaining digits to 0
			for(i=i;i<capacity;i++)
				digit[i] = 0;

			delete[] olddigit;
			return 1;
		}
	}

	const bool BigInt::setDigit(int location, int newDigit)
	{
		if(newDigit > 9 || newDigit < 0 || location < 1)
			return 0;
		else
		{
			if(location > capacity)
				this->capacityExtend(location);

			digit[location - 1] = newDigit;

			this->realUsageAdjust();
			this->signAdjust();

			return 1;
		}
	}

	const bool BigInt::setSign(bool newSign)
	{
		sign = newSign;
		this->signAdjust();
		return 1;
	}

	const BigInt operator +(const BigInt& num1, const BigInt& num2)
	{
		if(num1.sign == num2.sign)
		{
			BigInt fin;
			int i(0), carry(0), flag(0);

			fin.capacityExtend(max(num1.realUsage, num2.realUsage) + 1);
			fin.sign = num1.sign;
			fin.realUsage = max(num1.realUsage, num2.realUsage) + 1;

			for(i=0;i<max(num1.realUsage, num2.realUsage);i++)
			{
				if(flag == 0)
				{
					fin.digit[i] = num1.digit[i] + num2.digit[i] + carry;
					if(i == num2.realUsage-1)
						flag = 1;
					else if(i == num1.realUsage-1)
						flag = 2;
				}
				else if(flag == 1)
					fin.digit[i] = num1.digit[i] + carry;
				else if(flag == 2)
					fin.digit[i] = num2.digit[i] + carry;

				if(fin.digit[i] >= 10)
				{
					fin.digit[i] -= 10;
					carry = 1;
				}
				else
					carry = 0;			}

			if(carry == 1)
				fin.digit[i] = carry;
			else
				fin.realUsage--;


			return fin;
		}
		else if(num1.sign == 0)
		{
			BigInt tmp(num2);
			tmp.sign = 0;

			return (num1-tmp);
		}
		else
		{
			BigInt tmp(num1);
			tmp.sign = 0;

			return (num2-tmp);
		}
	}

	const BigInt operator -(const BigInt& num1, const BigInt& num2)
	{
		if(num1.sign == num2.sign)
		{
			BigInt fin;
			int i(0), carry(0), flag(0);

			if((num1.sign == 0 && num1 >= num2) || (num1.sign == 1 && num2 >= num1))
			{
				fin.capacityExtend(num1.realUsage);
				fin.sign = num1.sign;
				for(i=0;i<num1.realUsage;i++)
				{
					if(flag == 0)
					{
						fin.digit[i] = num1.digit[i] - num2.digit[i] - carry;
						if(i == num2.realUsage-1)
							flag = 1;
					}
					else if(flag == 1)
						fin.digit[i] = num1.digit[i] - carry;

					if(fin.digit[i] < 0)
					{
						fin.digit[i] += 10;
						carry = 1;
					}
					else
						carry = 0;
				}
			}
			else
			{
				fin.capacityExtend(num2.realUsage);
				fin.sign = !num2.sign;

				for(i=0;i<num2.realUsage;i++)
				{
					if(flag == 0)
					{
						fin.digit[i] = num2.digit[i] - num1.digit[i] - carry;
						if(i == num1.realUsage-1)
							flag = 2;
					}
					else if(flag == 2)
						fin.digit[i] = num2.digit[i] - carry;

					if(fin.digit[i] < 0)
					{
						fin.digit[i] += 10;
						carry = 1;
					}
					else
						carry = 0;
				}
			}

			fin.realUsageAdjust();
			fin.signAdjust();

			return fin;
		}
		else if(num1.sign == 0)
		{
			BigInt tmp(num2);
			tmp.sign = 0;

			return (num1+tmp);
		}
		else
		{
			BigInt tmp(num2);
			tmp.sign = 1;

			return (num1+tmp);
		}
	}

	const BigInt operator -(const BigInt& num)
	{
		BigInt fin(num);
		if(fin.realUsage != 0 || fin.digit[0] != 0)
			fin.sign = !fin.sign;

		return fin;
	}

	const BigInt operator *(const BigInt& num1, const BigInt& num2)
	{
		BigInt fin;
		int i(0), j(0), carry(0);

		fin.capacityExtend(num1.realUsage + num2.realUsage);
		fin.sign = num1.sign ^ num2.sign;

		for(j=0;j<num2.realUsage;j++)
		{
			for(i=0;i<num1.realUsage;i++)
			{
				fin.digit[i+j] += num1.digit[i] * num2.digit[j] + carry;
				carry = fin.digit[i+j]/10;
				fin.digit[i+j] %= 10;
			}

			fin.digit[i+j] += carry;
			carry = 0;
		}

		fin.realUsageAdjust();
		fin.signAdjust();
		return fin;
	}

	const BigInt operator /(BigInt num1, BigInt num2)
	{
		BigInt fin(0), temp(0);
		int i(0), j(0);
		bool si = num1.sign ^ num2.sign;

		if(num2 == 0)
		{
			cout << "Error: can't divide 0\n";
			return fin;
		}

		num1.sign = 0;
		num2.sign = 0;
		for(i=num1.realUsage-1; i>=0; i--){
			int cnt(0);
			temp = temp*10;
			temp = temp+num1.digit[i];

			while(num2*(cnt+1) <= temp)	cnt++;
			temp = temp - num2*cnt;
			fin = fin*10;
			fin = fin+cnt;
		}
		fin.sign = si;
		fin.realUsageAdjust();
		fin.signAdjust();
		return fin;
	}

	const BigInt operator %(BigInt num1, BigInt num2){

		if(num2 == 0)
			return BigInt(num1);

		BigInt fin = num1-(num1/num2)*num2;
		if(fin<0)
			fin = fin+num2.abs();
		return fin;
	}

	const BigInt BigInt::operator =(const BigInt& num2)
	{
		int i(0);

		this->capacityExtend(num2.realUsage);
		this->sign = num2.sign;
		this->realUsage = num2.realUsage;

		for(i=0;i<this->realUsage;i++)
			this->digit[i] = num2.digit[i];

		for(i=i;i<this->capacity;i++)
			this->digit[i] = 0;

		return BigInt(num2);
	}

	const bool BigInt::operator >(const BigInt& num) const
	{
		if(this->sign != num.sign)
			return (this->sign ? 0:1);

		if(this->realUsage > num.realUsage)
			return (this->sign ? 0:1);
		else if(this->realUsage < num.realUsage)
			return (this->sign ? 1:0);

		int i(this->realUsage - 1);

		while(i>=0 && this->digit[i] == num.digit[i])
			i--;

		if(i<0)
			return 0;

		if(this->digit[i] > num.digit[i])
			return (this->sign ? 0:1);
		else
			return (this->sign ? 1:0);	
	}

	const bool BigInt::operator <(const BigInt& num) const
	{
		if(this->sign != num.sign)
			return (this->sign ? 1:0);

		if(this->realUsage > num.realUsage)
			return (this->sign ? 1:0);
		else if(this->realUsage < num.realUsage)
			return (this->sign ? 0:1);

		int i(this->realUsage - 1);

		while(i>=0 && this->digit[i] == num.digit[i])
			i--;

		if(i<0)
			return 0;

		if(this->digit[i] > num.digit[i])
			return (this->sign ? 1:0);
		else
			return (this->sign ? 0:1);	
	}

	const bool BigInt::operator >=(const BigInt& num) const
	{
		if(this->sign != num.sign)
			return (this->sign ? 0:1);

		if(this->realUsage > num.realUsage)
			return (this->sign ? 0:1);
		else if(this->realUsage < num.realUsage)
			return (this->sign ? 1:0);

		int i(this->realUsage - 1);

		while(i>=0 && this->digit[i] == num.digit[i])
			i--;

		if(i<0)
			return 1;

		if(this->digit[i] > num.digit[i])
			return (this->sign ? 0:1);
		else
			return (this->sign ? 1:0);	
	}

	const bool BigInt::operator <=(const BigInt& num) const
	{
		if(this->sign != num.sign)
			return (this->sign ? 1:0);

		if(this->realUsage > num.realUsage)
			return (this->sign ? 1:0);
		else if(this->realUsage < num.realUsage)
			return (this->sign ? 0:1);

		int i(this->realUsage - 1);

		while(i>=0 && this->digit[i] == num.digit[i])
			i--;

		if(i<0)
			return 1;

		if(this->digit[i] > num.digit[i])
			return (this->sign ? 1:0);
		else
			return (this->sign ? 0:1);	
	}

	const bool BigInt::operator !=(const BigInt& num) const
	{
		if(this->sign != num.sign || this->realUsage != num.realUsage)
			return 1;

		int i(this->realUsage - 1);

		while(i >= 0 && this->digit[i] == num.digit[i])
			i--;

		return (i<0 ? 0:1); 
	}

	const bool BigInt::operator ==(const BigInt& num) const
	{
		if(this->sign != num.sign || this->realUsage != num.realUsage)
			return 0;

		int i(this->realUsage - 1);

		while(i >= 0 && this->digit[i] == num.digit[i])
			i--;

		return (i<0 ? 1:0); 
	}

	ostream& operator <<(ostream& outputStream, const BigInt& num)
	{
		if(num.sign == 1)
			outputStream << "-";

		for(int i=num.realUsage-1;i>=0;i--)
			outputStream <<num.digit[i];

		return outputStream;
	}

	istream& operator >>(istream& inputStream, BigInt& num)
	{
		char str[1024];

		cin >> str;

		num = BigInt(str);

		return inputStream;
	}
}
