#ifndef CLIENT_H
#define CLIENT_H
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;
class Client {
 private:
  int sockfd;
  struct clientAddr {
    struct sockaddr_in addr;
    socklen_t          addrLen = sizeof(addr);
  } clientAddr;

 public:
  bool operator==(const Client &c) const { return this->sockfd == c.sockfd; }
  bool operator!=(const Client &c) const { return !operator==(c); }
  Client(), Client(int);
  struct sockaddr_in *getClientAddr();
  const ssize_t       receive();
  socklen_t *         getClientAddrLen();
  const void          send();
  const void          notifyDisconnection(char *);
  const void          notifyConnection(char *);
  void                setSockfd(int), setClientAddr(struct sockaddr_in), end();
  int                 getSockfd();
};
#endif
