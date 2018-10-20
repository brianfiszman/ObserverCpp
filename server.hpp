#ifndef SERVER_H
#define SERVER_H

#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

class Server {
private:
  char *port;
  int sockfd, newsockfd;
  struct addrinfo *res;
  const void initAddrInfo();

public:
  Server();
  Server(const char port[]);
  char *getPort();
  const void start();
};
#endif
