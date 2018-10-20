#include "server.hpp"

Server::Server() { port = 0; }

Server::Server(const char port[]) : port((char *)port) {
  memset(&hints, 0, sizeof(struct addrinfo));

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  getaddrinfo(NULL, port, &hints, &res);

  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  bind(sockfd, res->ai_addr, res->ai_addrlen);
  freeaddrinfo(res);
  listen(sockfd, 1);

  struct sockaddr_in c_addr;
  socklen_t c_addrlen = sizeof(c_addr);

  newsockfd = accept(sockfd, (struct sockaddr *)&c_addr, &c_addrlen);

  send(newsockfd, "Hello", sizeof("Hello"), 0);

  close(newsockfd);
  close(sockfd);
};

char *Server::getPort() { return port; };