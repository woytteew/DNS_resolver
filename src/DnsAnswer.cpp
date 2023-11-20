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
    // Parse ID (2 bytes)
    this->header.setId((flags[0] << 8) | flags[1]);

    // Parse flags (2 bytes)
    this->header.setFlags((flags[2] << 8) | flags[3]);
    
    // Parse qdcount (2 bytes)
    this->header.setQdcount((flags[4] << 8) | flags[5]);

    // Parse ancount (2 bytes)
    this->header.setAncount((flags[6] << 8) | flags[7]);

    // Parse nscount (2 bytes)
    this->header.setNscount((flags[8] << 8) | flags[9]);

    // Parse arcount (2 bytes)
    this->header.setArcount((flags[10] << 8) | flags[11]);

    // Remove header from buffer (12 bytes)
    memmove(flags, flags + 12, *len - 12);
    *len -= 12;

}

void DnsAnswer::parseQuery(unsigned char *query, int *len){
    // Set qname
    string qname = getNameFromDnsFormat(query);
    this->queries.setQname(qname);

    // Remove qname from buffer
    memmove(query, query + qname.length() + 2, *len - qname.length() - 2);
    *len -= qname.length() + 2;

    // Set qtype
    this->queries.setQtype((query[0] << 8) | query[1]);

    // Set qclass
    this->queries.setQclass((query[2] << 8) | query[3]);

    // Remove query from buffer
    memmove(query, query + 4, *len - 4);
    *len -= 4;

}

string DnsAnswer::getNameFromDnsFormat(unsigned char *buffer){
    unsigned char* qnamePtr = buffer;

    string dnsName;
    while (*qnamePtr != 0) {

        // Firs byte represents the length of next part of name
        int length = static_cast<int>(*qnamePtr);
        qnamePtr++;

        if (!dnsName.empty()) {
            dnsName += ".";
        }

        dnsName += string(reinterpret_cast<const char*>(qnamePtr), length);
        qnamePtr += length;
    }

    return dnsName;
}

void DnsAnswer::printAnswer(){
    cout << "Authoritative: " << ((this->header.getFlags() & 0x0400) ? "Yes" : "No") << ", ";
    cout << "Recursive: " << ((this->header.getFlags() & 0x0100) ? "Yes" : "No") << ", ";
    cout << "Truncated: " << ((this->header.getFlags() & 0x0200) ? "Yes" : "No") << endl;

    cout << "Question section (" << this->header.getQdcount() << ")" << endl;
    cout << " " << this->queries.getQname() << ", " << this->queries.getQtype() << ", " << this->queries.getQclass() << endl;

}

void DnsAnswer::printBufferAsHex(unsigned char *buffer, int len){
    for (int i = 0; i < len; i++) {
        printf("%02x ", buffer[i]);
    }
    cout << endl;
}