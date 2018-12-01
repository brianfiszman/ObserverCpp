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
#include <list>
#include "client.hpp"

using namespace std;

class Server {
 private:
  struct addrinfo *res;
  list<Client>     clients;
  const void       initAddrInfo();
  const void       setReusable(int);
  char *           port;
  int              sockfd;

 public:
  Server();
  Server(const char port[]);

  const Client createClient();
  const void   start();
  const void   destroyClient(Client &c);
  const void   initAndListen();
  char *       getPort();
};
#endif
