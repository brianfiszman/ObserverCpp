#ifndef LISTENER_WORKER
#define LISTENER_WORKER

#include "../server.hpp"
#include "worker.hpp"

class ListenerWorker : public Worker {
 public:
  ListenerWorker() = delete;
  ListenerWorker(Server &, fd_set &);
  const void listenConnections();
  const void run(Server &, fd_set &);
};

#endif
