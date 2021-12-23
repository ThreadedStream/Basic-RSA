// RSA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RSA.h"


int main()
{
	rsa::RSA instance = rsa::RSA::RSABuilder().P(61)
											  .Q(53)
											  .E(17)
											  .create();


	instance.mod_inverse();
	
	rsa::ull cipher = instance.encrypt(65);
	
	instance.decrypt(cipher);


	return 0;


}
