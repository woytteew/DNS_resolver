/**
 * ISA Project - DNS resolver
 *
 * @file parseParams.hpp
 * @author Vojtech Czakan (xczaka00)
 * @brief Header file for ParseParams class
 * @date 20. 11. 2023 (deadline)
*/

#ifndef PARSEPARAMS_HPP
#define PARSEPARAMS_HPP

#include <iostream>
#include <getopt.h>

using namespace std;

class DnsParams {
public:

    // Method for parsing arguments
    void parseParams(int argc, char *argv[]);

    // Print help
    void help();

    // Getters
    bool getRecursion() const { return recursion; }

    bool getReverse() const { return reverse; }

    bool getIpv6() const { return ipv6; }

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

#endif // PARSEPARAMS_HPP