//VUT FIT ISA - DNS resolver

#include <iostream>
#include <getopt.h>

using namespace std;

// Class for storing parameters
class DnsParams {
public:
    bool recursion = false;
    bool reverse = false;
    bool ipv6 = false;
    string server;
    int port = 53;
    string address;

    // Method for parsing arguments
    void parseParams(int argc, char *argv[]) {
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

    void help() {
        cout << "Usage: dns [-r] [-x] [-6] -s server [-p port] adress" << endl;
    }
};

int main(int argc, char *argv[]) {
    DnsParams params;

    params.parseParams(argc, argv);

    

    return 0;
}