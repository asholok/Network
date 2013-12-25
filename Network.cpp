#include "Network.h"

size_t Network::convertToSize_t(std::string str) {
	size_t result = 0;

	for ( int i = 0, order = 10; i < str.length(); i++ ) {
		char symbol = str[i];
		
		if ( symbol < '0' || symbol > '9' ) {
			throw NetworkException(1);
		}
		result = result * order + (int(symbol) - 48);;
	}

	return result;
}

std::string Network::convertToIpString(size_t address) {
	std::string result;
	size_t previusValue = 0;

	for ( int i = 1, order = maxMaskLength - capacity; i <= quantityOctets; i++, order -= capacity ) {
		size_t baseValue = previusValue << capacity;
		size_t currentValue = address >> order;
 		size_t resultValue = currentValue - baseValue;
        
 		previusValue = currentValue;
 		result += std::to_string(resultValue);
 		if ( i < quantityOctets ) {
 			result += ".";
 		}
	}

	return result;
}

size_t Network::validateIP(std::string address) {
	int size = address.length();
	int count = 1;
	size_t buff;
	size_t result = 0;

	if ( size > maxSize ) {
		throw NetworkException(1);
	}
	for ( int i = 0; i < size ; i++, count++ ) {
		std::string part;
		
		for ( char c = address[i]; c != '.' && i < size; i++, c = address[i] ) {
			part += c;
		}
		if ( part.length() == 0 ) {
			throw NetworkException(1);
		}
		buff = convertToSize_t(part);
		if ( buff > maxOctetValue ) {
			throw NetworkException(1);
		}
		result = result << capacity;
		result += buff;
	}
	if ( count != quantityOctets ) {
		throw NetworkException(1);
	}
	return result;
}

int validateMask(int maskLength) {
	if ( maskLength < 0 || maskLength > maxMaskLength ) {
		throw NetworkException(2);
	}
	return maskLength;
}

Network::Network(std::string address, int maskLength) {
	this->intIpAddress = validateIP(address);
	this->maskLength = validateMask(maskLength);
	this->strIpAddress = address;
	this->hostShift = maxMaskLength - maskLength;
	this->netPart = (intIpAddress >> hostShift) << hostShift;
	this->maxBrodcastValue = validateIP(brodcastString);
}

bool Network::contains(std::string address) {
	size_t newNetPart = (validateIP(address) >> hostShift) << hostShift;

	if ( netPart == newNetPart ) {
		return true;
	}
	return false;
}

std::string Network::getAddress() {
	return strIpAddress;
}

std::string Network::getBroadcastAddress() {
	size_t brodcastSufix = maxBrodcastValue - ((maxBrodcastValue >> hostShift) << hostShift);
	size_t currentBrodcastValue = netPart ^ brodcastSufix;
	std::string result = convertToIpString(currentBrodcastValue);

	return result;
}

std::string Network::getFirstUsableAddress() {
	size_t firstUsableAddress = netPart + 1;
	std::string result = convertToIpString(firstUsableAddress);

	return result;
}

std::string Network::getLastUsableAddress() {
	size_t lastAddressSufix = maxBrodcastValue - ((maxBrodcastValue >> hostShift) << hostShift) - 1;
	size_t lastUsableIp = netPart ^ lastAddressSufix;
	std::string result = convertToIpString(lastUsableIp);

	return result;
}

std::string Network::getMask() {
	std::string result = convertToIpString(netPart);

	return result;
}

int Network::getMaskLength() {
	return maskLength;
}

int Network::getTotalHosts() {
	return pow(2, 32-maskLength) - 2;
}

bool Network::isPublic() {
	Network* firstPubNet = new Network("10.0.0.0", 8);
	Network* secondPubNet = new Network("172.16.0.0", 12);
	Network* thirdPubNet = new Network("192.168.0.0", 16);
	
	if ( firstPubNet->netPart == netPart || secondPubNet->netPart == netPart || thirdPubNet->netPart == netPart ) {
		return true;
	}

	return false;
}

Network* Network::getSubnets() {
	
}
