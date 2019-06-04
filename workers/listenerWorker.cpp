#include "listenerWorker.hpp"
ListenerWorker::ListenerWorker(Server &server, fd_set &workerSet)
    : Worker(server, workerSet){};

const void ListenerWorker::run() {
  t = thread(&ListenerWorker::listenConnections, this);
  t.detach();
}

const void ListenerWorker::listenConnections() {
  while (true) {
    FD_ZERO(&workerSet);
    FD_SET(server.getListeningFd(), &workerSet);
    select(FD_SETSIZE, &workerSet, NULL, NULL, NULL);

    if (FD_ISSET(server.getListeningFd(), &workerSet)) {
      sem_post(&recvLock);

      lock_guard<std::mutex> guard(sockLock);

      Client c = server.getClientCluster()->createClient(server.acceptClient());
      server.getClientCluster()->notify(c, true);
    }
  }
}
