#include "server.hpp"
#include <arpa/inet.h>
#include <iostream>
#include "helpers/socket.hpp"

using namespace std;
using namespace sock;

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

Client Server::acceptClient() {
  Client c = Client();

  int csock = sock::accept(this->listenFd, c);

  c.setSockfd(csock);

  return c;
}

const void Server::initAndListen() {
  try {
    this->listenFd = socket(res);

    sock::bind(this->listenFd, res);
    sock::listen(this->listenFd, 3);
  } catch (const std::exception &e) { std::cerr << e.what() << '\n'; }
}
