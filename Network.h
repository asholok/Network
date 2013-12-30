#ifndef NETWORK
#define NETWORK

#include <string>
#include <math.h>
#include "NetworkException.h"
 
 const int maxMaskLength = 32;
 const int capacity = 8;
 const std::string brodcastString = "255.255.255.255";

class Network {
	private:
		size_t intIpAddress;
		size_t netPart;
		int maskLength;
		int hostShift;
		size_t maxBrodcastValue;
		std::string strIpAddress;
		void validateIP(std::string address);
		size_t convertToSize_t(std::string str);
		std::string convertToString(size_t address);
		Network* subnets;

	public:
		Network(std::string address, int maskLength);
		bool contains(std::string address);
		std::string getAddress();
		std::string getBroadcastAddress();
		std::string getFirstUsableAddress();
		std::string getLastUsableAddress();
		std::string getMask();
		int getMaskLength();
		size_t getTotalHosts();
		bool isPublic();
		Network* getSubnets();

};

#endif // NETWORK