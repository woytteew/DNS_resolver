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
    DnsQueries();

    DnsQueries(DnsParams params){ SetQueries(params); }

    // Methods
    void SetQueries(DnsParams params);

    string reverseAddress(string address, bool isIpv6);

    string expandIpv6Address(string address);

    string getDnsAddressFormat(string address);

    // Setters
    void setQname(string qname) { DnsQueries::qname = qname; }

    void setQtype(unsigned short qtype) { DnsQueries::qtype = qtype; }

    void setQclass(unsigned short qclass) { DnsQueries::qclass = qclass; }

    // Getters
    string getQuery();

    string getQname() const { return qname; }

    string getQtype();

    string getQclass();

private:
    string qname;
    unsigned short qtype;
    unsigned short qclass;
};

#endif //DNSQUERIES_HPP