/**
 * ISA Project - DNS resolver
 * 
 * @file DnsAnswer.cpp
 * @brief Source file for DnsAnswer class
 * @author Vojtech Czakan (xczaka00)
 * @date 20. 11. 2023 (deadline)
*/

#include "DnsAnswer.hpp"

void DnsAnswer::setAnswer(string name, unsigned short type, unsigned short class_, unsigned int ttl, unsigned short rdlength, string rdata){
    this->name = name;
    this->type = type;
    this->class_ = class_;
    this->ttl = ttl;
    this->rdlength = rdlength;
    this->rdata = rdata;
}

string DnsAnswer::getType(){
    switch (this->type) {
        case 1:
            return "A";
        case 2:
            return "NS";
        case 5:
            return "CNAME";
        case 6:
            return "SOA";
        case 12:
            return "PTR";
        case 15:
            return "MX";
        case 28:
            return "AAAA";
        default:
            return "Unknown";
    }
}

string DnsAnswer::getClass(){
    switch (this->class_){
        case 1:
            return "IN";
        case 2:
            return "CS";
        case 3:
            return "CH";
        case 4:
            return "HS";
        default:
            return "Unknown";
    }
}