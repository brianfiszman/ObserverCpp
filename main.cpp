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
  FD_ZERO(master);
  FD_SET(server->getListeningFd(), master);
  select(FD_SETSIZE, master, NULL, NULL, NULL);

  if (FD_ISSET(server->getListeningFd(), master)) {
    lock_guard<std::mutex> guard(myMutex);
    cc->createClient(server->acceptClient());
  }

  return listenConnections(cc, server, master);
}

const void start(Server &server) {
  server.initAndListen();
  fd_set         master;
  ClientCluster *cc = server.getClientCluster();

  thread(listenConnections, cc, &server, &master).detach();

  do {
    if (cc->getClients().size() > 0) {
      cout << "Hola";
      for (auto client : cc->getClients()) {
        if (client.receive() <= 0) {
          cc->destroyClient(client);
          break;
        }
      }
    }
  } while (true);

  close(server.getListeningFd());
}

int main(int argc, char *argv[]) {
  chk_argn(&argc);

  const char *PORT = argv[1];

  Server server(PORT);

  start(server);

  return 0;
}