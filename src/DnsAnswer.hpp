/**
 * ISA Project - DNS resolver
 * 
 * @file DnsAnswer.hpp
 * @brief Header file for DnsAnswer class
 * @author Vojtech Czakan (xczaka00)
 * @date 20. 11. 2023 (deadline)
*/

#ifndef DNSANSWER_HPP
#define DNSANSWER_HPP

#include <cstring>
#include "DnsQueries.hpp"

class DnsAnswer{
public:
    // Constructor
    DnsAnswer(unsigned char *buffer, int *len){ parseDnsAnswer(buffer, len); }

    void parseDnsAnswer(unsigned char *buffer, int *len);

    void parseFlags(unsigned char *flags,int *len);

    void parseQuery(unsigned char *query, int *len);

    string getNameFromDnsFormat(unsigned char *buffer);

    void printAnswer();

    void printBufferAsHex(unsigned char *buffer, int len);

        
private:
    DnsHeader header;
    DnsQueries queries;

};

#endif //DNSANSWER_HPP