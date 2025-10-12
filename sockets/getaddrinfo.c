#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<netdb.h>
#include<string.h>

#define hostname "www.google.com"
#define port "80"

void log_exit(const char* msg) {
    perror(msg);
    exit(-1);
}

int main() {
    
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_flags = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *result;
    if( getaddrinfo(hostname, port, &hints, &result) != 0) {
        log_exit("could not get addr info call");
    }

    struct addrinfo *temp;
    for(temp = result; temp != NULL; temp = temp->ai_next) {
        char buffer[INET6_ADDRSTRLEN];

        void* addr;
        if (temp->ai_family == AF_INET) {
            struct sockaddr_in* ipv4 = (struct sockaddr_in *)temp->ai_addr;
            addr = &(ipv4->sin_addr);
        } else {
            struct sockaddr_in6* ipv6 = (struct sockaddr_in6 *)temp->ai_addr;
            addr = &(ipv6->sin6_addr);
        }

        inet_ntop(temp->ai_family, addr, buffer, sizeof buffer);
        printf("Resolved ip: %s\n", buffer);

    }
    

}
