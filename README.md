# ISA - Project
## DNS - Resolver
### Author: Vojtech Czakan (xczaka00)
#### Date: 20.11.2023

### Description
The Dns Resolver application is a DNS (Domain Name System) client that can resolve domain names into IP addresses and vice versa. It sends DNS query packets to a DNS server and processes the responses. The application is capable of sending A, AAAA, and PTR type queries, and can process response types A, AAAA, NS, PTR, and CNAME.

#### Limitation: 
The application has a limitation when processing responses with encoded DNS names. If the encoded DNS name is not the first element (for example, 'f.ip6-servers.arpa' where 'ip6-servers.arpa' is encoded but not the first element, 'f.' is before that), the DNS name is displayed incorrectly as 'f..'. Encoding is only supported if the entire domain name is encoded."

### Execution
`make`

`./dns[-r] [-x] [-6] -s server [-p port] address`

### Submitted files
dns.cpp
DnsAnswer.(cpp/hpp)
DnsHeader.(cpp/hpp)
DnsParams.(cpp/hpp)
DnsQueries.(cpp/hpp)
DnsResponse.(cpp/hpp)
Makefile
README.md
manual.pdf