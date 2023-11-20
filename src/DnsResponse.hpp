/**
 * ISA Project - DNS resolver
 * 
 * @file DnsResponse.hpp
 * @brief Header file for DnsResponse class
 * @author Vojtech Czakan (xczaka00)
 * @date 20. 11. 2023 (deadline)
*/

#ifndef DNSRESPONSE_HPP
#define DNSRESPONSE_HPP

#include <cstring>
#include "DnsAnswer.hpp"

class DnsResponse{
public:
    // Constructor
    DnsResponse(unsigned char *buffer, int *len){ parseDnsResponse(buffer, len); }

    void parseDnsResponse(unsigned char *buffer, int *len);

    void parseFlagsSec(unsigned char *flags,int *len);

    void parseQuerySec(unsigned char *query, int *len);

    void parseAnswer(unsigned char *answer, int *len, unsigned char *buffer, string section);

    string decodeDnsName(unsigned char *name, int *len, unsigned char* buffer);

    string getNameFromDnsFormat(unsigned char *buffer);

    void printResponse();

    void printBufferAsHex(unsigned char *buffer, int len);

        
private:
    DnsHeader header;
    DnsQueries queries;

    // Answer section
    vector<DnsAnswer> answers;

    // Authority section
    vector<DnsAnswer> authorities;

    // Additional section
    vector<DnsAnswer> additionals;
    

};

#endif //DNSRESPONSE_HPP