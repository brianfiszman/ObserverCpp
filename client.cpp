#include "client.hpp"

Client::Client(){};
Client::Client(int sockfd) : sockfd(sockfd){};
socklen_t *Client::getClientAddrLen() { return &clientAddr.addrLen; };
void       Client::setSockfd(int sockfd) { this->sockfd = sockfd; };
void       Client::end() { close(sockfd); };
int        Client::getSockfd() { return sockfd; };

struct sockaddr_in *Client::getClientAddr() {
  return &clientAddr.addr;
};

void Client::setClientAddr(struct sockaddr_in clientAddr) {
  this->clientAddr.addr = clientAddr;
};

const void Client::send() {
  char buf[1024];

  bzero(buf, sizeof(buf));
  cin >> buf;
  ::send(sockfd, buf, sizeof(buf), 0);
}

const void Client::notifyDisconnection(char *ipAddress) {
  char message[64] = "The client: ";
  char buf[64]     = " has disconnected.\n\r";

  strncat(message, ipAddress, sizeof(message));
  strncat(message, buf, sizeof(message));

  ::send(sockfd, message, sizeof(message), 0);
}

const void Client::notifyConnection(char *ipAddress) {
  char message[64] = "The client: ";
  char buf[64]     = " has connected.\n\r";

  strncat(message, ipAddress, sizeof(message));
  strncat(message, buf, sizeof(message));

  ::send(sockfd, message, sizeof(message), 0);
}

const ssize_t Client::receive() {
  ssize_t recvRes;
  char    buf[1024];
  bzero(buf, sizeof(buf));

  recvRes = recv(sockfd, buf, sizeof(buf), 0);
  cout << inet_ntoa(this->clientAddr.addr.sin_addr) << ": " << buf;

  return recvRes;
}
