#include "workers.hpp"
#include "listenerWorker.hpp"
#include "receiverWorker.hpp"

const void start(Server &server) {
  fd_set listenSet, reader;

  server.initAndListen();

  ListenerWorker listenerWorker(server, listenSet);
  ReceiverWorker receiverWorker(server, reader);

  listenerWorker.run();
  receiverWorker.run();

  close(server.getListeningFd());
}
