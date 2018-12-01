#include "client.hpp"
#include <unistd.h>

Client::Client(){};
Client::Client(int sockfd) : sockfd(sockfd), pid(fork()){};
socklen_t *Client::getClientAddrLen() { return &clientAddr.addrLen; };
pid_t      Client::getProcessId() { return pid; };
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

  while (pid != 0) {
    bzero(buf, sizeof(buf));
    cin >> buf;
    ::send(sockfd, buf, sizeof(buf), 0);
  }
}

const void Client::receive() {
  ssize_t recvRes;
  char    buf[1024];

  while (pid == 0) {
    recvRes = recv(sockfd, buf, sizeof(buf), 0);

    if (recvRes != 0) {
      cout << buf << endl;
      bzero(buf, sizeof(buf));
    } else if (recvRes == 0) {
      cout << "CLIENT DISCONNECTED, CLOSING SOCKET." << endl;
      break;
    }
  }
}