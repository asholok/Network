#ifndef IPV4ADDRESS
#define IPV4ADDRESS

#include <string>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "NetworkException.h"

class IPv4Address {
	private:
		static const int maxIpStrLength = 15;
		static const int quantityOctets = 4;

		unsigned int uintIpValue;
		std::string strIpValue;


	public:	
		IPv4Address(unsigned int address = 0);
		IPv4Address(const std::string& address);
		static unsigned int strIpToUint(const std::string& address);
		static std::string uintIpToString(unsigned int address);
		bool lessThan(IPv4Address address);
		bool greaterThan(IPv4Address address);
		bool equals(IPv4Address address);
		unsigned int getUintValue() const;
		std::string getStrValue() const;

};

#endif // IPV4ADDRESS