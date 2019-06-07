#ifndef LISTENER_WORKER
#define LISTENER_WORKER

#include "../server.hpp"
#include "worker.hpp"

class ListenerWorker : public Worker {
 public:
  ListenerWorker(Server &, fd_set &);
  const void run();

 private:
  const void listenConnections();
};

#endif
