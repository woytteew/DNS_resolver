/**
 * ISA Project - DNS resolver
 * 
 * @file dns.cpp
 * @brief Main file for DNS resolver program
 * @author Vojtech Czakan (xczaka00)
 * @date 20. 11. 2023 (deadline)
*/

#include <sys/socket.h>
#include <unistd.h>

#include "DnsAnswer.hpp"

int main(int argc, char *argv[]) {
    DnsParams params;

    // Parse arguments
    params.parseParams(argc, argv);

    DnsHeader header(params);

    // Create socket
    int sock;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        cerr << "Error: socket creation failed" << endl;
        exit(EXIT_FAILURE);
    }

    // Set timeout
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
        cerr << "Error: setsockopt failed" << endl;
        exit(EXIT_FAILURE);
    }

    // Prepare server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(params.getPort());
    server_addr.sin_addr.s_addr = inet_addr(params.getServerIP().c_str());
    

    // Create query
    string query = header.getQuery();

    DnsQueries queries(params);

    query += queries.getQuery();

    // Send query to server
    if (sendto(sock, query.c_str(), query.length(), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        cerr << "Error: sendto failed" << endl;
        exit(EXIT_FAILURE);
    }

    // Receive response from server
    unsigned char buffer[10000];
    int len;
    if ((len = recvfrom(sock, buffer, 10000, 0, NULL, NULL)) < 0) {
        cerr << "Error: recvfrom failed" << endl;
        exit(EXIT_FAILURE);
    }

    // Parse response
    DnsAnswer answer(buffer, &len);

    answer.printAnswer();

    close(sock);

    return 0;
}
