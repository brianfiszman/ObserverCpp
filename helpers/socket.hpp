#ifndef SOCK_LIB
#define SOCK_LIB

#include <netdb.h>
#include <sys/socket.h>
#include "../client.hpp"

namespace sock {
int socket(addrinfo* res);
int bind(int&, addrinfo*);
int listen(int&, int);
int setReusable(int&, const int reuse);
int accept(int&, Client&);
}  // namespace sock

#endif
