#include "server.hpp"
#include <iostream>

using namespace std;

Server::Server() { port = 0; }
Server::Server(const char port[]) : port((char *)port) { initAddrInfo(); }
char *Server::getPort() { return port; };

const void Server::initAddrInfo() {
  struct addrinfo hints;

  memset(&hints, 0, sizeof(struct addrinfo));

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  getaddrinfo(NULL, port, &hints, &res);
}

const void Server::start() {
  initAndListen();
  createClient();

  clients.front().send();
  clients.front().receive();

  destroyClient(clients.front());
  close(sockfd);
}

const void Server::createClient() {
  Client c;

  int clientfd;

  CHECK(clientfd = accept(sockfd, (struct sockaddr *)c.getClientAddr(),
                          c.getClientAddrLen()));

  c = Client(clientfd);

  clients.push_front(c);
}

const void Server::destroyClient(Client &c) {
  c.end();
  clients.remove(c);
}

const void Server::initAndListen() {
  CHECK(sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol));
  CHECK(bind(sockfd, res->ai_addr, res->ai_addrlen));

  freeaddrinfo(res);
  setReusable(1);

  CHECK(listen(sockfd, 3));
}

const void Server::setReusable(const int reuse = 1) {
  CHECK(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   (const char *)&reuse, sizeof(reuse)));
}