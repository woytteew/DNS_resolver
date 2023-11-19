/**
 * ISA Project - DNS resolver
 * 
 * @file parseParams.cpp
 * @brief Source file for DnsParams class
 * @author Vojtech Czakan (xczaka00)
 * @date 20. 11. 2023 (deadline) 
*/

#include "DnsParams.hpp"

void DnsParams::parseParams(int argc, char *argv[]) {
    int option;
    while ((option = getopt(argc, argv, "rx6s:p:")) != -1) {
        switch (option) {
            case 'r':
                recursion = true;
                break;
            case 'x':
                reverse = true;
                break;
            case '6':
                ipv6 = true;
                break;
            case 's':
                server = optarg;
                break;
            case 'p':
                port = atoi(optarg);
                break;
            default:
                this->help();
                exit(EXIT_FAILURE);
        }
    }

    // Check if address is set
    if (optind < argc) {
        address = argv[optind];
    } else {
        this->help();
        exit(EXIT_FAILURE);
    }

    // Check if -6 and -x are not set together
    if (ipv6 && reverse) {
        cerr << "Error: -6 and -x cannot be set together" << endl;
        exit(EXIT_FAILURE);
    }

    // Check if -x is set, address is IPv4 or IPv6
    if (reverse) {
        bool invalid = false;
        
        if(address.find(':') == string::npos && address.find('.') == string::npos) {
            invalid = true;  
        }
        else if (address.find('.') != string::npos) {
            // IPv4 has 4 parts and only digits
            invalid = !checkIPv4(address);
        }

        if (invalid) {
            cerr << "Error: address is not IPv4 or IPv6" << endl;
            exit(EXIT_FAILURE);
        }
    }
}

string DnsParams::getServerIP(){
    struct hostent *he;
    struct in_addr **addr_list;
    string ip;

    if ((he = gethostbyname(server.c_str())) == NULL) {
        cerr << "Error: gethostbyname failed" << endl;
        exit(EXIT_FAILURE);
    }

    addr_list = (struct in_addr **)he->h_addr_list;

    for (int i = 0; addr_list[i] != NULL; i++) {
        ip = inet_ntoa(*addr_list[i]);
    }

    return ip;
}

bool DnsParams::checkIPv4(string address){
    // IPv4 has 4 parts and only digits
    int parts = 1;
    for (long unsigned int i = 0; i < address.length(); i++) {
        if (address[i] == '.') {
            parts++;
        } else if (!isdigit(address[i])) {
            return false;
            break;
        }
    }
    if (parts != 4) {
        return false;
    }

    return true;
}

void DnsParams::help() {
    cout << "Usage: dns [-r] [-x] [-6] -s server [-p port] address" << endl;
}