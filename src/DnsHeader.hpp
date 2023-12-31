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
    DnsHeader();

    DnsHeader(DnsParams params){ SetHeader(params); }

    // Setters
    void SetHeader(DnsParams params);

    void setId(unsigned short id) { DnsHeader::id = id; }

    void setFlags(unsigned short flags);

    void setQdcount(unsigned short qdcount) { DnsHeader::qdcount = qdcount; }

    void setAncount(unsigned short ancount) { DnsHeader::ancount = ancount; }

    void setNscount(unsigned short nscount) { DnsHeader::nscount = nscount; }

    void setArcount(unsigned short arcount) { DnsHeader::arcount = arcount; }

    // Getters
    string getQuery();

    unsigned short getId() const { return id; }

    unsigned short getFlags() const { return (qr << 15) | (opcode << 11) | (aa << 10) | (tc << 9) | (rd << 8) | (ra << 7) | (z << 6) | (ad << 5) | (aans << 4) | (rcode << 0);}

    int getQdcount() const { return qdcount; }

    int getAncount() const { return ancount; }

    int getNscount() const { return nscount; }

    int getArcount() const { return arcount; }

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
