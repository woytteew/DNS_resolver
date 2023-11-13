/**
 * ISA Project - DNS resolver
 * 
 * @file DnsQueries.hpp
 * @author Vojtech Czakan (xczaka00)
 * @brief Source file for DnsQueries class
 * @date 20. 11. 2023 (deadline)
*/

#include "DnsQueries.hpp"

void DnsQueries::SetQueries(DnsParams params){
    // Set qname
    if (params.getReverse()) {
        // Set qname
        this->qname = getDnsAddressFormat(reverseAddress(params.getAddress()));

    } else {
        // Set qname
        this->qname  = getDnsAddressFormat(params.getAddress());
        printStringAsHex(this->qname);
    }

    // Set qtype
    if (params.getIpv6()) {
        this->qtype = 28;
    } 
    else if (params.getReverse()) {
        this->qtype = 12;
    }
    else {
        this->qtype = 1;
    }

    // Set qclass
    this->qclass = 1;
}

string DnsQueries::getDnsAddressFormat(string address){
    string dnsAddress = "";
    int lastDot = 0;
    int length = 0;

    // Add each part of address
    for (long unsigned int i = 0; i < address.length(); i++) {
        if (address[i] == '.') {
            length = i - lastDot;
            dnsAddress += (char)length;
            dnsAddress += address.substr(lastDot, length);
            lastDot = i + 1;
        }
    }

    // Add last part of address
    length = address.length() - lastDot;
    dnsAddress += (char)length;
    dnsAddress += address.substr(lastDot, length);

    // Add 0 at the end
    dnsAddress += (char)0;

    return dnsAddress;
}

string DnsQueries::getQuery(){
    string query = "";

    // Add qname
    query += this->qname;

    // Add qtype
    query += (char)(this->qtype >> 8);
    query += (char)(this->qtype & 0xFF);

    // Add qclass
    query += (char)(this->qclass >> 8);
    query += (char)(this->qclass & 0xFF);

    return query;
}

string DnsQueries::reverseAddress(string address){
    string reversedAddress = "";
    int lastDot = address.length() - 1;

    // Add each part of address
    for (int i = address.length() - 1; i >= 0; i--) {
        if (address[i] == '.') {
            reversedAddress += address.substr(i + 1, lastDot - i);
            reversedAddress += '.';
            lastDot = i - 1;
        }
    }

    // Add last part of address
    reversedAddress += address.substr(0, lastDot + 1);

    // Add in-addr.arpa
    reversedAddress += ".in-addr.arpa";

    return reversedAddress;
}

void DnsQueries::printStringAsHex(string str){
    for (long unsigned int i = 0; i < str.length(); i++) {
        printf("%02x ", (unsigned char)str[i]);
    }
}