#ifndef WORKER_CLASS
#define WORKER_CLASS

#include <fcntl.h>
#include <semaphore.h>
#include <mutex>
#include <thread>
#include "../server.hpp"

class Worker {
 public:
  Worker();
  Worker(Server&, fd_set&);
  ~Worker();

 protected:
  std::thread           t;
  Server                server;
  fd_set                workerSet;
  static sem_t          recvLock;
  static std::mutex     sockLock;
  static struct timeval selTimeout;
  virtual const void    run() = 0;
};

#endif
