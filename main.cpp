#include <fcntl.h>
#include <semaphore.h>
#include <iostream>
#include <mutex>
#include <thread>
#include "server.hpp"

using namespace std;

mutex sockLock;
sem_t recvLock;

struct timeval selTimeout;

void error(char *err_msg) {
  perror(err_msg);
  exit(1);
}

int chk_argn(int *argc) {
  if (*argc < 2) {
    error((char *)"ERROR: indicate the server address and the port number!");
  }

  return 0;
}

const bool isAnyoneConnected(ClientCluster *cc) {
  lock_guard<std::mutex> guard(sockLock);
  return cc->getClients().size() > 0;
}

const void listenConnections(Server *server, fd_set *listenSet) {
  while (true) {
    FD_ZERO(listenSet);
    FD_SET(server->getListeningFd(), listenSet);
    select(FD_SETSIZE, listenSet, NULL, NULL, NULL);

    if (FD_ISSET(server->getListeningFd(), listenSet)) {
      sem_post(&recvLock);

      lock_guard<std::mutex> guard(sockLock);

      Client c =
          server->getClientCluster()->createClient(server->acceptClient());
      server->getClientCluster()->notify(c, true);
    }
  }
}

const void receiveMessages(Server *server, fd_set *reader) {
  do {
    FD_ZERO(reader);

    if (isAnyoneConnected(server->getClientCluster())) {
      lock_guard<std::mutex> guard(sockLock);
      for (auto client : server->getClientCluster()->getClients())
        FD_SET(client.getSockfd(), reader);

      FD_SET(server->getListeningFd(), reader);
      select(FD_SETSIZE, reader, NULL, NULL, NULL);

      for (auto client : server->getClientCluster()->getClients()) {
        if (FD_ISSET(client.getSockfd(), reader) > 0) {
          if (client.receive() <= 0) {
            server->getClientCluster()->destroyClient(client);
            server->getClientCluster()->notify(client, false);
            continue;
          }
        }
      }
    } else {
      sem_init(&recvLock, 0, 0);
      sem_wait(&recvLock);
    }
  } while (true);
}

const void start(Server &server) {
  fd_set listenSet, reader;

  server.initAndListen();

  thread(listenConnections, &server, &listenSet).detach();
  thread(receiveMessages, &server, &reader).join();

  sem_destroy(&recvLock);

  close(server.getListeningFd());
}

int main(int argc, char *argv[]) {
  chk_argn(&argc);

  const char *PORT = argv[1];

  Server server(PORT);

  start(server);

  return 0;
}
