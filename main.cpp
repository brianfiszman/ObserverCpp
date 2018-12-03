#include <fcntl.h>
#include <iostream>
#include <mutex>
#include <thread>
#include "server.hpp"

using namespace std;

mutex myMutex;

struct timeval selTimeout;

void error(char *err_msg) {
  perror(err_msg);
  exit(1);
}

int chk_argn(int *argc) {
  if (*argc < 1) {
    error((char *)"ERROR: indicate the server address and the port number!");
  }

  return 0;
}

const void listenConnections(ClientCluster *cc,
                             Server *       server,
                             fd_set *       listenSet) {
  while (true) {
    FD_ZERO(listenSet);
    FD_SET(server->getListeningFd(), listenSet);
    select(FD_SETSIZE, listenSet, NULL, NULL, NULL);

    if (FD_ISSET(server->getListeningFd(), listenSet)) {
      lock_guard<std::mutex> guard(myMutex);

      Client c = cc->createClient(server->acceptClient());
      cc->notify(c, true);
    }
  }
}

const void receiveMessages(ClientCluster *cc, fd_set *reader) {
  selTimeout.tv_sec  = 0; /* timeout (secs.) */
  selTimeout.tv_usec = 0; /* 0 microseconds */

  do {
    FD_ZERO(reader);
    if (cc->getClients().size() > 0) {
      for (auto client : cc->getClients()) FD_SET(client.getSockfd(), reader);

      select(FD_SETSIZE, reader, NULL, NULL, &selTimeout);
      lock_guard<std::mutex> guard(myMutex);
      for (auto client : cc->getClients()) {
        if (FD_ISSET(client.getSockfd(), reader) > 0) {
          if (client.receive() <= 0) {
            cc->destroyClient(client);
            cc->notify(client, false);
            continue;
          }
        }
      }
    }
  } while (true);
}

const void start(Server &server) {
  server.initAndListen();
  fd_set         listenSet, reader;
  ClientCluster *cc = server.getClientCluster();

  thread(listenConnections, cc, &server, &listenSet).detach();
  thread(receiveMessages, cc, &reader).join();

  close(server.getListeningFd());
}

int main(int argc, char *argv[]) {
  chk_argn(&argc);

  const char *PORT = argv[1];

  Server server(PORT);

  start(server);

  return 0;
}