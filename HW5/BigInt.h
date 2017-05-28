//404220029 MikeChen
/*
   class BigInt:
   use to store a Bigint, include digit, sign, capacity, realUsage.
   if realUsage exceed capacity, will automatically extend capacity to twice size of the original.
negative: sign = 1, positive: sign = 0
 */

#ifndef BIGINT_H
#define BIGINT_H

using namespace std;

namespace BigInt_N{
	class BigInt
	{
		public:

			BigInt abs();
			BigInt();
			//Postcondition: initialize to 0.
			BigInt(int);
			//Postcondition: initialize to <int>.
			BigInt(const char *);
			//Precindition	 Can input like "5642", "-55681!", etc.
			//Postcondition: initialize to <char*>.
			BigInt(const BigInt &);
			//Postcondition: initialize to object (copy constructor).
			~BigInt();
			void capacityExtend(const int);
			//Postcondition: extend the capacity of the object.
			void realUsageAdjust();
			//Postcondition: adjust the realUsage of the object.

			//Accessor functions
			const int getCapacity() const;
			//Postcondition: return the capacity of the object.
			const int getRealUsage() const;
			//Postcondition: return the realUsage of the object.
			const int getDigit(int location) const;
			//Postcondition: return digit at location <int>.
			const bool getSign() const;
			//Postcondition: return the sign of the objec.
			//				 0 is positive, 1 is negative.

			//Mutator functions
			const bool setCapacity(int);
			//Postcondition: set the capacity of the object.
			//				 return 1 if success, otherwise 0.
			const bool setDigit(int location, int newDigit);
			//Postcondition: set the digit of the object.
			//				 return 1 if success, otherwise 0.
			const bool setSign(bool);
			//Postcondition: set the sign of the object.
			//				 return 1 if success, otherwise 0.

			friend const BigInt operator +(const BigInt& , const BigInt&);
			friend const BigInt operator -(const BigInt& , const BigInt&);
			friend const BigInt operator -(const BigInt&);
			friend const BigInt operator *(const BigInt& , const BigInt&);
			friend const BigInt operator /(BigInt , BigInt);
			friend const BigInt operator %(BigInt , BigInt);
			friend ostream& operator <<(ostream&, const BigInt&);
			friend istream& operator >>(istream&, BigInt&);
			const BigInt operator =(const BigInt&);
			const bool operator >(const BigInt&) const;
			const bool operator <(const BigInt&) const;
			const bool operator >=(const BigInt&) const;
			const bool operator <=(const BigInt&) const;
			const bool operator !=(const BigInt&) const;
			const bool operator ==(const BigInt&) const;

		private:
			int capacity;
			int realUsage;
			int *digit;
			bool sign;
	};
}
#endif
