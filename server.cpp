#include "server.hpp"
#include <iostream>

using namespace std;

Server::Server() { port = 0; }

Server::Server(const char port[]) : port((char *)port) { initAddrInfo(); };

char *Server::getPort() { return port; };

const void Server::initAddrInfo() {
  struct addrinfo hints;

  memset(&hints, 0, sizeof(struct addrinfo));

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  getaddrinfo(NULL, port, &hints, &res);
};

const void Server::start() {
  initAndListen();
  createClient();

  send(clients.front().getSockfd(), "Hello", sizeof("Hello"), 0);

  clients.front().end();
  close(sockfd);
};

const void Server::createClient() {
  Client c;

  int clientfd = accept(sockfd, (struct sockaddr *)c.getClientAddr(),
                        c.getClientAddrLen());

  c = Client(clientfd);

  if (c.getProcessId() == 0) {
    cout << "Welcome to child process";
  }

  clients.push_front(c);
}

const void Server::initAndListen() {
  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  setReusable(1);
  bind(sockfd, res->ai_addr, res->ai_addrlen);
  freeaddrinfo(res);
  listen(sockfd, 1);
};

const void Server::setReusable(int reuse = 1) {
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse,
                 sizeof(reuse)) < 0)
    perror("setsockopt(SO_REUSEADDR) failed");

#ifdef SO_REUSEPORT
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, (const char *)&reuse,
                 sizeof(reuse)) < 0)
    perror("setsockopt(SO_REUSEPORT) failed");
#endif
}