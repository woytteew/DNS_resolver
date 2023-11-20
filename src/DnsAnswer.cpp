/**
 * ISA Project - DNS resolver
 * 
 * @file DnsAnswer.cpp
 * @brief Source file for DnsAnswer class
 * @author Vojtech Czakan (xczaka00)
 * @date 20. 11. 2023 (deadline)
*/

#include "DnsAnswer.hpp"

void DnsAnswer::parseDnsAnswer(unsigned char *buffer, int *len){
    // Header section
    parseFlags(buffer, len);
    
    // Query section
    parseQuery(buffer, len);

    // Answer section
    //string answerSection = answer.substr(30);
    //cout << "Answer section: " << answerSection << endl;
}

void DnsAnswer::parseFlags(unsigned char *flags, int *len){
    DnsHeader header;

    // Parse ID (2 bytes) and remove from flags
    header.setId((flags[0] << 8) | flags[1]);

    // Parse flags (2 bytes)
    header.setFlags((flags[2] << 8) | flags[3]);
    
    // Parse qdcount (2 bytes)
    header.setQdcount((flags[4] << 8) | flags[5]);

    // Parse ancount (2 bytes)
    header.setAncount((flags[6] << 8) | flags[7]);

    // Parse nscount (2 bytes)
    header.setNscount((flags[8] << 8) | flags[9]);

    // Parse arcount (2 bytes)
    header.setArcount((flags[10] << 8) | flags[11]);

    // Remove header from buffer
    flags += 12;
    *len -= 12;
    
    cout << "Authoritative: " << ((header.getFlags() & 0x0400) ? "Yes" : "No") << ", ";
    cout << "Recursive: " << ((header.getFlags() & 0x0100) ? "Yes" : "No") << ", ";
    cout << "Truncated: " << ((header.getFlags() & 0x0200) ? "Yes" : "No") << endl;
    
    

}

void DnsAnswer::parseQuery(unsigned char *query, int *len){
    // Question section
    DnsQueries queries;

    // Parse qname dynamically
    /*
    // queries.setQname(answer.substr(12, 2));
    queries.setQtype((query[2] << 8) | query[3]);
    queries.setQclass((query[4] << 8) | query[5]);

    cout << "Qname: " << queries.getQname() << ", ";
    cout << "Qtype: " << queries.getQtype() << ", ";
    cout << "Qclass: " << queries.getQclass() << endl;*/
}

void DnsAnswer::printBufferAsHex(unsigned char *buffer, int len){
    for (int i = 0; i < len; i++) {
        printf("%02x ", buffer[i]);
    }
    cout << endl;
}