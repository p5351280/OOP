#include <iostream>
#include <cstdlib>
#include "BigInt.h"
#include "Rational.h"
#include "Complex.h"

using namespace std;
using namespace BigInt_N;
using namespace Rational_N;
using namespace Complex_N;



int main() {


	Complex C1("1/3-6/17i"),C2("81!/320!+128!/520!i");
	//Complex C1("1/3","-6/17"), C1("81!/320!","128!/520!");


	cout<<"C1 = "<<C1<<endl;
	cout<<"C2 = "<<C2<<endl;
	cout<<"C1/C2 = "<<C1/C2<<endl;

	return 0;
}
