#include "workers.hpp"
#include "listenerWorker.hpp"
#include "receiverWorker.hpp"

const void start(Server &server) {
  fd_set listenSet, reader;

  server.initAndListen();

  ListenerWorker listenerWorker(server, listenSet);
  ReceiverWorker receiverWorker(server, reader);

  listenerWorker.run(server, listenSet);
  receiverWorker.run(server, reader);

  close(server.getListeningFd());
}
