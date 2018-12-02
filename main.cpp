#include <fcntl.h>
#include <iostream>
#include <mutex>
#include <thread>
#include "server.hpp"

using namespace std;

mutex myMutex;

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

const void listenConnections(ClientCluster *cc, Server *server,
                             fd_set *master) {
  while (true) {
    FD_ZERO(master);
    FD_SET(server->getListeningFd(), master);
    select(FD_SETSIZE, master, NULL, NULL, NULL);

    if (FD_ISSET(server->getListeningFd(), master)) {
      lock_guard<std::mutex> guard(myMutex);
      cc->createClient(server->acceptClient());
    }
  }
}

const void receiveMessages(ClientCluster *cc, fd_set *reader) {
  struct timeval selTimeout;
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
            continue;
          }
        }
      }
    }
  } while (true);
}

const void start(Server &server) {
  server.initAndListen();
  fd_set         master, reader;
  ClientCluster *cc = server.getClientCluster();

  thread(listenConnections, cc, &server, &master).detach();
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