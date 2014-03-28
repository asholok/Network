#ifndef NETWORK
#define NETWORK

#include <string>
#include <cmath>
#include <set>

#include "IPv4Address.h"
#include "NetworkException.h"

class Network {
	private:
		IPv4Address ip;
		int intMaskLength;
		unsigned int uintMask;
		unsigned int uintNetAddress;
		unsigned int totalHosts;
		unsigned int uintBroadcastValue;
		IPv4Address firstUsableAddress;
		IPv4Address lastUsableAddress;
		IPv4Address broadcastAddress;

		void setMask(int maskLength);
		void setBroadcastAddress();
		void setFirstUsableAddress();
		void setLastUsableAddress();
		bool isSubnet(const Network& net);
		void setTotalHosts();

	public:
		Network(const IPv4Address& address, int maskLength);
		~Network();
		bool contains(const std::string& address) const;
		IPv4Address getAddress() const;
		IPv4Address getBroadcastAddress() const;
		IPv4Address getFirstUsableAddress() const;
		IPv4Address getLastUsableAddress() const;
		std::string getMask() const;
		std::string toString();
		int getMaskLength() const;
		unsigned int getTotalHosts() const;
		unsigned int getUintNetAddress() const;
		unsigned int getUintBroadcastValue() const;
		unsigned int getUintMask() const;
		bool isPublic();
		void setSubnets(std::set<class Network*>& subnets);
};

#endif // NETWORK