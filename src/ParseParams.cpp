/**
 * ISA Project - DNS resolver
 * 
 * @file parseParams.cpp
 * @brief Source file for ParseParams class
 * @author Vojtech Czakan (xczaka00)
 * @date 20. 11. 2023 (deadline) 
*/

#include "ParseParams.hpp"

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
                cerr << "Usage: dns [-r] [-x] [-6] -s server [-p port] adress" << endl;
                exit(EXIT_FAILURE);
        }
    }

    // Check if address is set
    if (optind < argc) {
        address = argv[optind];
    } else {
        cerr << "Usage: dns [-r] [-x] [-6] -s server [-p port] adress" << endl;
        exit(EXIT_FAILURE);
    }
}

void DnsParams::help() {
    cout << "Usage: dns [-r] [-x] [-6] -s server [-p port] address" << endl;
}