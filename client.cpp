#include "client.hpp"
#include <unistd.h>

Client::Client(){};
Client::Client(int sockfd) : sockfd(sockfd){};
void Client::end() { close(sockfd); };
int Client::getSockfd() { return sockfd; };
void Client::setSockfd(int sockfd) { this->sockfd = sockfd; };
socklen_t *Client::getClientAddrLen() { return &clientAddr.addrLen; };

struct sockaddr_in *Client::getClientAddr() {
  return &clientAddr.addr;
};

void Client::setClientAddr(struct sockaddr_in clientAddr) {
  this->clientAddr.addr = clientAddr;
};