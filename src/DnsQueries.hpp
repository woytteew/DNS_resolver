/**
 * ISA Project - DNS resolver
 * 
 * @file DnsQueries.hpp
 * @brief Header file for DnsQueries class
 * @author Vojtech Czakan (xczaka00)
 * @date 20. 11. 2023 (deadline)
*/

#ifndef DNSQUERIES_HPP
#define DNSQUERIES_HPP

#include <algorithm>
#include <sstream>
#include <iomanip>
#include <vector>
#include "DnsHeader.hpp"

class DnsQueries {
public:
    // Constructor
    DnsQueries(DnsParams params){
        SetQueries(params);
    }

    // Methods
    void SetQueries(DnsParams params);

    // TODO - remove
    void printStringAsHex(string str);

    string reverseAddress(string address, bool isIpv6);

    string expandIpv6Address(string address);

    string getDnsAddressFormat(string address);

    // Getters
    string getQuery();

private:
    string qname;
    unsigned short qtype;
    unsigned short qclass;
};

#endif //DNSQUERIES_HPP