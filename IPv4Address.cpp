#include "IPv4Address.h"

IPv4Address::IPv4Address(unsigned int address) {
    this->uintIpValue = address;
    this->strIpValue =  uintIpToString(address);
}

IPv4Address::IPv4Address(const std::string& address) {
    this->uintIpValue = strIpToUint(address);
    this->strIpValue =  address;
}

unsigned int IPv4Address::strIpToUint(const std::string& address) {
    int size = address.length();
    unsigned int result = 0;
    unsigned char octets[quantityOctets];
    int count = sscanf(address.c_str(), "%u.%u.%u.%u", octets[0], octets[1], octets[2], octets[3]);

    if ( count != quantityOctets || size > maxIpStrLength ) {
        throw IPException();
    }

    return (octets[0] << 24) | (octets[1] << 16) | (octets[2] << 8) | octets[3]; 
}

bool IPv4Address::lessThan(IPv4Address address) {
    return this->uintIpValue < address.getUintValue();
}

bool IPv4Address::greaterThan(IPv4Address address) {
    return this->uintIpValue > address.getUintValue();
}

bool IPv4Address::equals(IPv4Address address) {
    return this->uintIpValue == address.getUintValue();
}

std::string IPv4Address::uintIpToString(unsigned int address) {
    unsigned char octets[quantityOctets];
    std::string result;

    octets[0] = address & 0xFF000000;
    octets[1] = address & 0x00FF0000;
    octets[2] = address & 0x0000FF00;
    octets[3] = address & 0x000000FF;

    result = std::to_string(octets[0]) + "." + std::to_string(octets[1]) + 
        "." + std::to_string(octets[2]) + "." + std::to_string(octets[3]);
    
    return result;
}

unsigned int IPv4Address::getUintValue() const {
    return this->uintIpValue;
}

std::string IPv4Address::getStrValue() const {
    return this->strIpValue;
}
