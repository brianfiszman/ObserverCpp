#include "receiverWorker.hpp"

ReceiverWorker::ReceiverWorker(Server &server, fd_set &workerSet)
    : Worker(server, workerSet){};

const void ReceiverWorker::run() {
  t = thread(&ReceiverWorker::receiveMessages, this);
  t.join();
}

const bool ReceiverWorker::isAnyoneConnected(ClientCluster *cc) {
  lock_guard<std::mutex> guard(sockLock);
  return cc->getClients().size() > 0;
}

const void ReceiverWorker::receiveMessages() {
  do {
    FD_ZERO(&workerSet);

    if (isAnyoneConnected(server.getClientCluster())) {
      lock_guard<std::mutex> guard(sockLock);
      for (auto client : server.getClientCluster()->getClients())
        FD_SET(client.getSockfd(), &workerSet);

      FD_SET(server.getListeningFd(), &workerSet);
      select(FD_SETSIZE, &workerSet, NULL, NULL, NULL);

      for (auto client : server.getClientCluster()->getClients()) {
        if (FD_ISSET(client.getSockfd(), &workerSet) > 0) {
          if (client.receive() <= 0) {
            server.getClientCluster()->destroyClient(client);
            server.getClientCluster()->notify(client, false);
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
