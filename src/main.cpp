/**
 * ISA Project - DNS resolver
 * 
 * @file main.cpp
 * @brief Main file for DNS resolver program
 * @author Vojtech Czakan (xczaka00)
 * @date 20. 11. 2023 (deadline)
*/

#include <sys/socket.h>
#include <arpa/inet.h>

#include "ParseParams.hpp"

// Class for storing parameters

int main(int argc, char *argv[]) {
    DnsParams params;

    params.parseParams(argc, argv);

    /*// Create socket
    int sock;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        cerr << "Error: socket creation failed" << endl;
        exit(EXIT_FAILURE);
    }*/

    return 0;
}