#include<unistd.h>
#include<arpa/inet.h>
#include<errno.h>
#include<string.h>
#include<stdio.h>
#include<sys/socket.h>

#define port 2000
#define backlog 5
#define localhost "127.0.0.1"

int main() {
  
  int sockfd = socket(AF_INET6, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("could not create sockets");
    return -1;
  }

  // IN6_ADDR_ANY
  // http://[::]:2000/
  struct in6_addr ipv6_address = { .s6_addr = {0} };

  struct sockaddr_in6 address_ipv6;
  memset(&address_ipv6, 0, sizeof(struct sockaddr_in6));
  address_ipv6.sin6_family = AF_INET6;
  address_ipv6.sin6_port = htons(port);
  address_ipv6.sin6_addr = ipv6_address;

  if ( (bind(sockfd, (struct sockaddr*)&address_ipv6, sizeof(struct sockaddr_in6))) == -1) {
    perror("could not bind");
    return -1;
  }

  if ( (listen(sockfd, backlog)) == -1 ) {
    perror("could not listen");
    return -1;
  }

  while(true) {
    int sockfd_accept = accept(sockfd, NULL, NULL);
    if ( sockfd_accept == -1 ) {
      perror("could not accept incoming connection");
      return -1;
    }

    const char* body = "the intelligence has been compromised";

    char response[1024];
    snprintf(response, sizeof(response),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: %lu\r\n"
        "\r\n"
        "%s",
        strlen(body), body);

    write(sockfd_accept, response, strlen(response));
  }

}
