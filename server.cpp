#include "server.hpp"
#include <iostream>

using namespace std;

const void error(const char *error) {
  perror(error);
  exit(EXIT_FAILURE);
}

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

  send();
  receive();

  destroyClient(clients.front());
  close(sockfd);
}

const void Server::createClient() {
  Client c;

  int clientfd;

  if ((clientfd = accept(sockfd, (struct sockaddr *)c.getClientAddr(),
                         c.getClientAddrLen())) < 0) {
    error("accept failed");
  }

  c = Client(clientfd);

  clients.push_front(c);
}

const void Server::destroyClient(Client &c) {
  c.end();
  clients.remove(c);
}

const void Server::initAndListen() {
  if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) <
      0) {
    error("Problem in creating the listening socket");
  }

  if (bind(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
    error("bind failed");
  }

  freeaddrinfo(res);
  setReusable(1);

  if (listen(sockfd, 3) < 0) {
    error("listen failed");
  }
}

const void Server::send() {
  char buf[1024];

  while (clients.front().getProcessId() != 0) {
    bzero(buf, sizeof(buf));
    cin >> buf;
    ::send(clients.front().getSockfd(), buf, sizeof(buf), 0);
  }
}

const void Server::receive() {
  char buf[1024];
  ssize_t recvRes;

  while (clients.front().getProcessId() == 0) {
    recvRes = recv(clients.front().getSockfd(), buf, sizeof(buf), 0);

    if (recvRes != 0) {
      cout << buf << endl;
      bzero(buf, sizeof(buf));
    } else if (recvRes == 0) {
      cout << "CLIENT DISCONNECTED, CLOSING SOCKET." << endl;
      break;
    }
  }
}

const void Server::setReusable(int reuse = 1) {
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                 (const char *)&reuse, sizeof(reuse)) < 0) {
    error("setsockopt failed");
  }
}