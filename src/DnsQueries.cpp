/**
 * ISA Project - DNS resolver
 * 
 * @file DnsQueries.hpp
 * @brief Source file for DnsQueries class
 * @author Vojtech Czakan (xczaka00)
 * @date 20. 11. 2023 (deadline)
*/

#include "DnsQueries.hpp"

void DnsQueries::SetQueries(DnsParams params){
    bool isIpv6 = params.getAddress().find(':') != string::npos;
    // Set qname
    if (params.getReverse()) {
        string address = params.getAddress();

        if (isIpv6) {
            // Expanded IPv6 address
            address = expandIpv6Address(address);
        }

        this->qname = getDnsAddressFormat(reverseAddress(address,isIpv6));

    } else {
        // Set qname
        this->qname  = getDnsAddressFormat(params.getAddress());
    }

    // Set qtype
    if (params.getIpv6() && !params.getReverse()) {
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

string DnsQueries::reverseAddress(string address, bool isIpv6){
    string reversedAddress = "";
    int lastDot = address.length() - 1;

    if(!isIpv6){
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
    }
    else{
        // Reverse IPv6 address
        for (int i = address.length() - 1; i >= 0; i--) {
            if(address[i] == ':'){
                continue;
            }
            reversedAddress += address[i];
            reversedAddress += '.';
        }

        // Remove the last dot
        if (!reversedAddress.empty()) {
            reversedAddress.pop_back();
        }
    }
    
    cerr << "Reversed address: " << reversedAddress << endl;

    // Add in-addr.arpa
    if(isIpv6) {
        reversedAddress += ".ip6";
    }
    else{
        reversedAddress += ".in-addr";
    }

    reversedAddress += ".arpa";

    return reversedAddress;
}

string DnsQueries::expandIpv6Address(string address){
    istringstream iss(address);
    string token;
    ostringstream expandedIPv6;
    vector<string> groups;

    while (getline(iss, token, ':')) {
        groups.push_back(token);
    }

    for (size_t i = 0; i < groups.size(); ++i) {
        if (groups[i].empty()) {
            // Insert the appropriate number of 0000 groups
            int missingGroups = 8 - groups.size() + 1;
            while (missingGroups--) {
                expandedIPv6 << "0000:";
            }
        } else {
            // Add zeros to each hexadecimal block
            expandedIPv6 << std::setw(4) << std::setfill('0') << groups[i];
            if (i != groups.size() - 1) {
                expandedIPv6 << ":";
            }
        }
    }

    // Remove the last colon
    string result = expandedIPv6.str();
    
    if(result[result.length() - 1] == ':') {
        result.pop_back();
    }

    return result;
}

void DnsQueries::printStringAsHex(string str){
    for (long unsigned int i = 0; i < str.length(); i++) {
        printf("%02x ", (unsigned char)str[i]);
    }
}