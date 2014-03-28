#include "Network.h"

static const int maxMaskLength = 32;

Network::Network(const IPv4Address& address, int maskLength) {
	setMask(maskLength);
	ip = IPv4Address(address.getUintValue() & this->uintMask);
	uintBroadcastValue = ip.getUintValue() | ~this->uintMask;
	setFirstUsableAddress();
	setLastUsableAddress();
	setTotalHosts();
}

bool Network::contains(const std::string& address) const {
	return ip.getUintValue() == (IPv4Address::strIpToUint(address) & this->uintMask);
}

void Network::setMask(int maskLength) {
	if ( this->intMaskLength > maxMaskLength ) {
		throw WrongMaskException();
	}
	this->intMaskLength = intMaskLength;
	this->uintMask = ((1 << this->intMaskLength) - 1) << (maxMaskLength - this->intMaskLength);
}

IPv4Address Network::getAddress() const {
	return this->ip;
}

IPv4Address Network::getBroadcastAddress() const {
	return this->broadcastAddress;
}

void Network::setTotalHosts() {
	if ( this->intMaskLength > (maxMaskLength - 2) ) {
		this->totalHosts = 0;
	} else {
		this->totalHosts = ~this->uintMask - 2;
	}	
}

void Network::setBroadcastAddress(){
	this->broadcastAddress = IPv4Address(this->uintBroadcastValue);
}

void Network::setFirstUsableAddress() {
	if ( this->intMaskLength > (maxMaskLength - 2) ) {
		this->firstUsableAddress = 0;
	} else {
		this->firstUsableAddress = IPv4Address(ip.getUintValue() + 1);
	}	
}

IPv4Address Network::getFirstUsableAddress() const {
	return this->firstUsableAddress;
}

void Network::setLastUsableAddress() {
	if ( this->intMaskLength > (maxMaskLength - 2) ) {
		this->lastUsableAddress = 0;
	} else {
		this->lastUsableAddress = IPv4Address(this->uintBroadcastValue - 1);
	}
}

IPv4Address Network::getLastUsableAddress() const {
	return this->lastUsableAddress;
}

int Network::getMaskLength() const {
	return this->intMaskLength;
}

unsigned int Network::getTotalHosts() const {
	return this->totalHosts;
}

unsigned int Network::getUintBroadcastValue() const {
	return this->uintBroadcastValue;
}

unsigned int Network::getUintMask() const {
	this->uintMask;
}

unsigned int Network::getUintNetAddress() const {
	return ip.getUintValue();
}

std::string Network::toString() {
	return ip.getStrValue() + "/" + std::to_string(this->intMaskLength);
}

bool Network::isSubnet(const Network& net) {
	return getUintNetAddress() <= net.getUintNetAddress() && 
		net.getUintNetAddress() < this->uintBroadcastValue;
}

bool Network::isPublic() {
	static Network firstPubNet  = Network(IPv4Address("10.0.0.0"), 8);
	static Network secondPubNet = Network(IPv4Address("176.16.0.0"), 12);
	static Network thirdPubNet  = Network(IPv4Address("192.168.0.0"), 16);

	return isSubnet(firstPubNet) && isSubnet(secondPubNet) && isSubnet(thirdPubNet);
}

void Network::setSubnets(std::set<class Network*>& subnets) {
	if ( this->intMaskLength > (maxMaskLength - 2) ) {
		return;
	}
	Network* firstSubnet = new Network(getAddress(), this->intMaskLength+1);
	unsigned int newUintNetAddress = firstSubnet->getUintBroadcastValue() + 1;
	Network* secondSubnet = new Network(IPv4Address::uintIpToString(newUintNetAddress), this->intMaskLength+1);
	
	subnets.insert(firstSubnet);
	subnets.insert(secondSubnet);
	delete firstSubnet;
	delete secondSubnet;
}
