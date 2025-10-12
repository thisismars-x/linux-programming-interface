#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdio.h>
#include<sys/socket.h>
#include<errno.h>
#include<string.h>

#define port 2000
#define ipv4_addr "127.0.0.1"
#define backlog 5

int main() {

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct in_addr address_ipv4;
  int status_ipv4 = inet_pton(AF_INET, ipv4_addr, &address_ipv4);
  if (status_ipv4 == -1) {
    perror("error converting between ipv4 string to 32-bit");
    return -1;
  }
  
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(struct sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr = address_ipv4;

  if ( bind(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) == -1 ) {
    perror("could not bind to localhost");
    return -1;
  }

  if ( listen(sockfd, backlog) == -1 ) {
    perror("could not listen");
    return -1;
  }

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
