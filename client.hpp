#ifndef CLIENT_H
#define CLIENT_H
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

class Client {
private:
  int sockfd;
  socklen_t clientAddrLen = sizeof(clientAddr);
  struct sockaddr_in clientAddr;

public:
  Client(), Client(int);
  int getSockfd();
  void setSockfd(int), setClientAddr(struct sockaddr_in), end();
  struct sockaddr_in *getClientAddr();
  socklen_t *getClientAddrLen();
};
#endif