#include "server.hpp"
#include <arpa/inet.h>
#include <iostream>

using namespace std;

Server::Server() { port = 0; }
Server::Server(const char port[])
    : clientCluster(new ClientCluster()), port((char *)port) {
  this->initAddrInfo();
}

const void Server::initAddrInfo() {
  struct addrinfo hints;

  memset(&hints, 0, sizeof(struct addrinfo));

  hints.ai_socktype = SOCK_STREAM;
  hints.ai_family   = AF_INET;
  hints.ai_flags    = AI_PASSIVE;

  getaddrinfo(NULL, port, &hints, &res);
}

ClientCluster *Server::getClientCluster() { return this->clientCluster; }
char *         Server::getPort() { return this->port; };
int            Server::getListeningFd() { return this->listenFd; }
const void     Server::setReusable(const int reuse = 1) {
  CHECK(setsockopt(this->listenFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   (const char *)&reuse, sizeof(reuse)));
}

Client Server::acceptClient() {
  Client c = Client();

  c.setSockfd(CHECK(accept(this->listenFd, (struct sockaddr *)c.getClientAddr(),
                           c.getClientAddrLen())));

  return c;
}

const void Server::initAndListen() {
  CHECK(this->listenFd =
            socket(res->ai_family, res->ai_socktype, res->ai_protocol));
  CHECK(bind(this->listenFd, res->ai_addr, res->ai_addrlen));

  freeaddrinfo(res);
  setReusable(1);

  CHECK(listen(this->listenFd, 3));
}
