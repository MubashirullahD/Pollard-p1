// DAA project_Integer factorization.cpp : .
// Muhammad Mubashirullah Durrani BSCS 6C 202209
// Arbaz Khan					  BSCS 6C 191095
// Umair						  BSCS 6C 145495

#include "stdafx.h"
#include <iostream>
#include <math.h>       /* pow */

using namespace std;

//Euclidian Algorithm
unsigned long long int gcd(unsigned long long int a, unsigned long long int b) {
	unsigned long long int remainder;
	while (b != 0) {
		remainder = a % b;
		a = b;
		b = remainder;
	}
	return a;
}

unsigned long long int gcd_local(unsigned long long int a, unsigned long long int b) {
	unsigned long long int remainder;
	while (a % b != 0) {
		remainder = a % b;
		a = b;
		b = remainder;
	}
	return b;
}

unsigned long long int fast_pow(unsigned long long int base, unsigned long long int k, unsigned long long int N)
{
	if (k == 0) {
		return 1;
	}
	if (k == 1)
	{
		return base;
	}

	unsigned long long int half = fast_pow(base, k/2, N);

	if (k % 2 == 0)
	{
		return ((half * half) % N);
	}
	else
	{
		unsigned long long int value = ((((half * half) % N) * base) % N); //odd cases
		return value;
	}
}

//1403, 1577, 107 * 61,2053 * 2039, 571*97
//15770708441 overflow for p-1 on 64 bit machine. This number requires 2^180! to be computed before getting modulated. 
//15485867ull * 32452843
//104395303ull * 122949823
//961748941ull * 982451653

int main() {

	//Pollard p-1
	cout << "Pollard p-1" << endl;
	unsigned long long int N = 982451653;// The value to factorize(Upto 9 digits for p-1, theoretically 21 digits) Some numbers even under the limit give wrong answers.
	unsigned long long int a = 2;//The value that should not have a co-factor with N.
	unsigned long long int k = 2;//The exponent of a
	unsigned long long int factorial_product = pow(a, k);
	unsigned long long int gcd_value = gcd_local((factorial_product)-1, N);
	bool overflow = false;

	while ((gcd_value == 1)) {
		
		k++;
		factorial_product = fast_pow(factorial_product,k,N);

		if (factorial_product == 0)
		{
			cout << "overflow for 64 bits..." << endl;
			overflow = true;
			break;
		}
		gcd_value = gcd_local((factorial_product)-1, N);
	}
	
	if (!overflow)
	{
		unsigned long long int divisor = gcd(factorial_product - 1, N);
		cout << divisor << " and " << N / divisor << endl;
	}



	//Pollard Rho, wiki
	cout << "\nPollard Rho" << endl;
	unsigned long long int value = N;
	unsigned long long int number = value, x_fixed = 2, cycle_size = 2, x = 2, factor = 1;

	while (factor == 1) {
		for (int count = 1; count <= cycle_size && factor <= 1; count++) {
			x = (x*x + 1) % number;
			factor = gcd(x - x_fixed, number);
		}

		cycle_size *= 2;
		x_fixed = x;
	}
	
	cout << "The factors are  " << factor << " and " << N / factor <<endl;
	
}