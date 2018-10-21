#ifndef SERVER_H
#define SERVER_H

#include "client.hpp"
#include <list>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

class Server {
private:
  char *port;
  int sockfd;
  list<Client> clients;
  struct addrinfo *res;
  const void initAddrInfo();
  const void setReusable(int);

public:
  Server();
  Server(const char port[]);
  char *getPort();
  const void start();
  const void createClient();
  const void destroyClient(Client &c);
  const void initAndListen();
};
#endif
