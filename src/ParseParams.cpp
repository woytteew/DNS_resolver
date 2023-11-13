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

void DnsParams::help() {
    cout << "Usage: dns [-r] [-x] [-6] -s server [-p port] address" << endl;
}