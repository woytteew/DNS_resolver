/**
 * ISA Project - DNS resolver
 *
 * @file DnsHeader.cpp
 * @author Vojtech Czakan (xczaka00)
 * @brief Source file for DnsHeader class
 * @date 20. 11. 2023 (deadline)
 * 
*/

#include "DnsHeader.hpp"

void DnsHeader::SetHeader(DnsParams params){
    this->id = 0x1234;

    this->qr = 0;
    this->opcode = 0;
    this->tc = 0;
    this->rd = params.getRecursion();
    this->ad = 0;

    this->qdcount = 1;
    this->ancount = 0;
    this->nscount = 0;
    this->arcount = 0;
}

string DnsHeader::getQuery(){
    string query = "";

    // ID
    query += (char)(this->id >> 8);
    query += (char)(this->id & 0xFF);

    // Flags
    query += (char)((this->qr << 7) | (this->opcode << 3) | (this->aa << 2) | (this->tc << 1) | this->rd);
    query += (char)((this->ra << 7) | (this->z << 6) | (this->ad << 5) | (this->aans << 4) | this->rcode);

    // qdcount
    query += (char)(this->qdcount >> 8);
    query += (char)(this->qdcount & 0xFF);

    // ancount
    query += (char)(this->ancount >> 8);
    query += (char)(this->ancount & 0xFF);

    // nscount
    query += (char)(this->nscount >> 8);
    query += (char)(this->nscount & 0xFF);

    // arcount
    query += (char)(this->arcount >> 8);
    query += (char)(this->arcount & 0xFF);


    return query;
}