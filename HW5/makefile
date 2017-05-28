all:Rational.o BigInt.o testForRational.cpp testForBigInt.cpp
	g++ -O2 -g -o Rational.test Rational.o BigInt.o testForRational.cpp
	g++ -O2 -g -o BigInt.test BigInt.o testForBigInt.cpp
Rational.o:Rational.h Rational.cpp
	g++ -c Rational.cpp

BigInt.o:BigInt.h BigInt.cpp
	g++ -c BigInt.cpp

clear:
	rm -r *.o *.test
