/**
 * ISA Project - DNS resolver
 *
 * @file DnsHeader.hpp
 * @brief Header file for DnsHeader class
 * @author Vojtech Czakan (xczaka00)
 * @date 20. 11. 2023 (deadline)
*/

#ifndef DNSHEADER_HPP
#define DNSHEADER_HPP

#include "DnsParams.hpp"

class DnsHeader {
public:
    // Constructor
    DnsHeader(DnsParams params){
        SetHeader(params);
    }

    // Methods
    void SetHeader(DnsParams params);

    // Getters
    string getQuery();

private:
    unsigned short id;

    // Flags
    unsigned short qr : 1;  // Query/Response flag
    unsigned short opcode : 4;  // Operation code
    unsigned short aa : 1;  // Authoritative answer flag
    unsigned short tc : 1;  // Truncated flag
    unsigned short rd : 1;  // Recursion desired
    unsigned short ra : 1;  // Recursion available
    unsigned short z : 1;  // Reserved for future use
    unsigned short aans : 1;  // Authenticated answer
    unsigned short ad : 1;  // Authenticated data
    unsigned short rcode : 4;  // Response code

    unsigned short qdcount;  // Number of entries in the question section
    unsigned short ancount;  // Number of resource records in the answer section
    unsigned short nscount;  // Number of name server resource records in the authority records section
    unsigned short arcount;  // Number of resource records in the additional records section

};

#endif //DNSHEADER_HPP
