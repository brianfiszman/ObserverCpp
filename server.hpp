#ifndef SERVER_H
#define SERVER_H

#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "client.hpp"
#include "clientCluster.hpp"

using namespace std;

class Server {
 private:
  ClientCluster*   clientCluster;
  struct addrinfo* res;
  const void       initAddrInfo();
  char*            port;
  int              listenFd;

 public:
  Server();
  Server(const char port[]);
  ~Server() { 
    delete clientCluster;
    close(this->listenFd); 
  };

  ClientCluster* getClientCluster();
  const void     initAndListen();
  Client         acceptClient();
  char*          getPort();
  int            getListeningFd();
};

#endif
