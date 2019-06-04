#ifndef RECEIVER_WORKER
#define RECEIVER_WORKER

#include "../server.hpp"
#include "worker.hpp"

class ReceiverWorker : public Worker {
 public:
  ReceiverWorker(Server &, fd_set &);
  const void run(Server &, fd_set &);

 private:
  const bool isAnyoneConnected(ClientCluster *);
  const void receiveMessages();
};

#endif
