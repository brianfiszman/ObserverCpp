#ifndef SERVER_H
#define SERVER_H

#define CHECK(errno)                                               \
  ({                                                               \
    int __errno = errno;                                           \
    (__errno == -1 ? ({                                            \
      fprintf(stderr, "ERROR (" __FILE__ ":%d) -- %s\n", __LINE__, \
              strerror(errno));                                    \
      exit(-1);                                                    \
      -1;                                                          \
    })                                                             \
                   : __errno);                                     \
  })

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
  const void       setReusable(int);
  char*            port;
  int              listenFd;

 public:
  Server();
  Server(const char port[]);
  ~Server() { delete clientCluster; };

  ClientCluster* getClientCluster();
  const void     initAndListen();
  Client         acceptClient();
  char*          getPort();
  int            getListeningFd();
};

#endif
