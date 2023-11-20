/**
 * ISA Project - DNS resolver
 *
 * @file parseParams.hpp
 * @brief Header file for DnsParams class
 * @author Vojtech Czakan (xczaka00)
 * @date 20. 11. 2023 (deadline)
*/

#ifndef DNSPARAMS_HPP
#define DNSPARAMS_HPP

#include <iostream>
#include <getopt.h>
#include <netdb.h>
#include <arpa/inet.h>

using namespace std;

class DnsParams {
public:
    // Method for parsing arguments
    void parseParams(int argc, char *argv[]);

    bool checkIPv4(string address);   

    // Print help
    void help();

    // Getters
    bool getRecursion() const { return recursion; }

    bool getReverse() const { return reverse; }

    bool getIpv6() const { return ipv6; }

    string getServerIP();

    string getServer() const { return server; }

    int getPort() const { return port; }

    string getAddress() const { return address; }


private:
    bool recursion = false;
    bool reverse = false;
    bool ipv6 = false;
    string server;
    int port = 53;
    string address;
};

#endif // DNSPARAMS_HPP