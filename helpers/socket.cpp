#include "./socket.hpp"

int sock::socket(addrinfo* res) {
  int __sock = ::socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  if (__sock < 0) throw std::runtime_error("Error in socket()");

  return __sock;
}

int sock::bind(int& __sock, addrinfo* res) {
  sock::setReusable(__sock, 1);

  int statusCode = ::bind(__sock, res->ai_addr, res->ai_addrlen);

  if (statusCode < 0) throw std::runtime_error("Error in bind()");

  freeaddrinfo(res);

  return statusCode;
}

int sock::listen(int& __sock, const int __n) {
  int statusCode = ::listen(__sock, __n);

  if (statusCode < 0) throw std::runtime_error("Error in listen()");

  return statusCode;
};

int sock::setReusable(int& __sock, const int reuse) {
  int statusCode = ::setsockopt(__sock,
                                SOL_SOCKET,
                                SO_REUSEADDR | SO_REUSEPORT,
                                (const char*)&reuse,
                                sizeof(reuse));

  if (statusCode < 0) throw std::runtime_error("Error in setsockopt()");

  return statusCode;
}

int sock::accept(int& __sock, Client& __c) {
  sockaddr*  clientAddr    = (struct sockaddr*)__c.getClientAddr();
  socklen_t* clientAddrLen = __c.getClientAddrLen();

  int __csock = accept(__sock, clientAddr, clientAddrLen);

  if (__csock < 0) throw std::runtime_error("Error in accept()");

  return __csock;
};
