/**
 * ISA Project - DNS resolver
 * 
 * @file DnsResponse.cpp
 * @brief Source file for DnsResponse class
 * @author Vojtech Czakan (xczaka00)
 * @date 20. 11. 2023 (deadline)
*/

#include "DnsResponse.hpp"

void DnsResponse::parseDnsResponse(unsigned char *buffer, int *len){
    unsigned char* tempBuffer = new unsigned char[*len];
    int tempLen = *len;

    // Copy buffer to new buffer
    memcpy(tempBuffer, buffer, *len);


    // Header section
    parseFlagsSec(tempBuffer, &tempLen);
    // Query section
    parseQuerySec(tempBuffer, &tempLen);

    // Answer section
    parseAnswer(tempBuffer, &tempLen, buffer, "answer");

    

    // Authority section
    parseAnswer(tempBuffer, &tempLen, buffer, "authority");
/*
    // Additional section
    parseAnswer(tempBuffer, &tempLen, buffer, "additional");*/

}

void DnsResponse::parseFlagsSec(unsigned char *flags, int *len){
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

void DnsResponse::parseQuerySec(unsigned char *query, int *len){
    // Set qname
    string qname = getNameFromDnsFormat(query);
    this->queries.setQname(qname);

    // Remove qname from buffer
    memmove(query, query + qname.length() + 1, *len - qname.length() - 1);
    *len -= qname.length() + 1;

    // Set qtype
    this->queries.setQtype((query[0] << 8) | query[1]);

    // Set qclass
    this->queries.setQclass((query[2] << 8) | query[3]);

    // Remove query from buffer
    memmove(query, query + 4, *len - 4);
    *len -= 4;

}

void DnsResponse::parseAnswer(unsigned char *answer, int *len, unsigned char *buffer, string section){
    int count;
    
    if(section == "answer"){
        count = this->header.getAncount();
    }
    else if(section == "authority"){
        count = this->header.getNscount();
    }
    else if(section == "additional"){
        count = this->header.getArcount();
    }
    // Parse each answer
    for (int i = 0; i < count; i++) {
        // Parse name
        string name = decodeDnsName(answer, len, buffer);
        
        // Parse type
        unsigned short type = (answer[0] << 8) | answer[1];

        // Remove type from buffer
        memmove(answer, answer + 2, *len - 2);
        *len -= 2;

        // Parse class
        unsigned short dnsClass = (answer[0] << 8) | answer[1];

        // Remove class from buffer
        memmove(answer, answer + 2, *len - 2);
        *len -= 2;

        // Parse ttl
        unsigned int ttl = (answer[0] << 24) | (answer[1] << 16) | (answer[2] << 8) | answer[3];

        // Remove ttl from buffer
        memmove(answer, answer + 4, *len - 4);
        *len -= 4;

        // Parse rdlength
        unsigned short rdlength = (answer[0] << 8) | answer[1];

        // Remove rdlength from buffer
        memmove(answer, answer + 2, *len - 2);
        *len -= 2;

        // Parse rdata
        string rdata;
        if (type == 1) {
            // Parse A record
            rdata = to_string(answer[0]) + "." + to_string(answer[1]) + "." + to_string(answer[2]) + "." + to_string(answer[3]);

            // Remove rdata from buffer
            memmove(answer, answer + 4, *len - 4);
            *len -= 4;
        } else if (type == 28) {
            // Parse AAAA record
            rdata = "";
            for (int i = 0; i < rdlength; i += 2) {
                rdata += to_string((answer[i] << 8) | answer[i + 1]);
                if (i != rdlength - 2) {
                    rdata += ":";
                }
            }

            // Remove rdata from buffer
            memmove(answer, answer + rdlength, *len - rdlength);
            *len -= rdlength;
        } else {
            rdata = decodeDnsName(answer, len, buffer);
        }

        // Add answer to vector
        if(section == "answer"){
            this->answers.push_back(DnsAnswer(name, type, dnsClass, ttl, rdlength, rdata));
        }
        else if(section == "authority"){
            this->authorities.push_back(DnsAnswer(name, type, dnsClass, ttl, rdlength, rdata));
        }
        else if(section == "additional"){
            this->additionals.push_back(DnsAnswer(name, type, dnsClass, ttl, rdlength, rdata));
        }
        
    }     

}

string DnsResponse::getNameFromDnsFormat(unsigned char *buffer){
    unsigned char* qnamePtr = buffer;

    string dnsName;
    while (*qnamePtr != 0) {

        // Firs byte represents the length of next part of name
        int length = static_cast<int>(*qnamePtr);
        qnamePtr++;

        if((length & 0xC0) == 0xC0){
            // Get offset
            unsigned short offset = (qnamePtr[0] & 0x3F) << 8 | qnamePtr[1];

            // Get name from offset
            dnsName += getNameFromDnsFormat(buffer + offset);
            break;
        }

        if (!dnsName.empty()) {
            dnsName += ".";
        }

        dnsName += string(reinterpret_cast<const char*>(qnamePtr), length);
        qnamePtr += length;
        
    }

    dnsName += ".";

    return dnsName;
}

string DnsResponse::decodeDnsName(unsigned char *name, int *len, unsigned char* buffer){
    string dnsName;
    if ((name[0] & 0xC0) == 0xC0) {
        // Get offset
        unsigned short offset = (name[0] & 0x3F) << 8 | name[1];

        // Remove offset from buffer
        memmove(name, name + 2, *len - 2);
        *len -= 2;

        // Get name from offset
        dnsName = getNameFromDnsFormat(buffer + offset);
    }

    else{
        dnsName = getNameFromDnsFormat(name);

        // Remove name from buffer
        memmove(name, name + dnsName.length() + 1, *len - dnsName.length() - 1);
        *len -= dnsName.length() + 1;
    }

    return dnsName;
}

void DnsResponse::printResponse(){
    cout << "Authoritative: " << ((this->header.getFlags() & 0x0400) ? "Yes" : "No") << ", ";
    cout << "Recursive: " << ((this->header.getFlags() & 0x0100) ? "Yes" : "No") << ", ";
    cout << "Truncated: " << ((this->header.getFlags() & 0x0200) ? "Yes" : "No") << endl;

    cout << "Question section (" << this->header.getQdcount() << ")" << endl;
    cout << " " << this->queries.getQname() << ", " << this->queries.getQtype() << ", " << this->queries.getQclass() << endl;

    cout << "Answer section (" << this->header.getAncount() << ")" << endl;
    for (int i = 0; i < this->header.getAncount(); i++) {
        cout << " " << this->answers[i].getName() << ", " << this->answers[i].getType() << ", " << this->answers[i].getClass() << ", " << this->answers[i].getTtl() << ", " << this->answers[i].getRdata() << endl;
    
    }

    cout << "Authority section (" << this->header.getNscount() << ")" << endl;
    for (int i = 0; i < this->header.getNscount(); i++) {
        cout << " " << this->authorities[i].getName() << ", " << this->authorities[i].getType() << ", " << this->authorities[i].getClass() << ", " << this->authorities[i].getTtl() << ", " << this->authorities[i].getRdata() << endl;
    
    }

    cout << "Additional section (" << this->header.getArcount() << ")" << endl;
    for (int i = 0; i < this->header.getArcount(); i++) {
        cout << " " << this->additionals[i].getName() << ", " << this->additionals[i].getType() << ", " << this->additionals[i].getClass() << ", " << this->additionals[i].getTtl() << ", " << this->additionals[i].getRdata() << endl;
    
    }

}

void DnsResponse::printBufferAsHex(unsigned char *buffer, int len){
    for (int i = 0; i < len; i++) {
        printf("%02x ", buffer[i]);
    }
    cout << endl;
}