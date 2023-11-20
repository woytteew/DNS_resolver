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

#include "DnsQueries.hpp"

class DnsAnswer{
public:
    // Constructor
    DnsAnswer(string name, unsigned short type, unsigned short class_, unsigned int ttl, unsigned short rdlength, string rdata){
        setAnswer(name, type, class_, ttl, rdlength, rdata);
    }

    // Setters
    void setAnswer(string name, unsigned short type, unsigned short class_, unsigned int ttl, unsigned short rdlength, string rdata);

    void setName(string name) { DnsAnswer::name = name; }

    void setType(unsigned short type) { DnsAnswer::type = type; }

    void setClass(unsigned short class_) { DnsAnswer::class_ = class_; }

    void setTtl(unsigned int ttl) { DnsAnswer::ttl = ttl; }

    void setRdlength(unsigned short rdlength) { DnsAnswer::rdlength = rdlength; }

    void setRdata(string rdata) { DnsAnswer::rdata = rdata; }


    // Getters
    string getName() const { return name; }

    string getType();

    string getClass();

    unsigned int getTtl() const { return ttl; }

    unsigned short getRdlength() const { return rdlength; }

    string getRdata() const { return rdata; }


private:
    string name;
    unsigned short type;
    unsigned short class_;
    unsigned int ttl;
    unsigned short rdlength;
    string rdata;
};


#endif //DNSANSWER_HPP