#include "worker.hpp"

Worker::Worker(){};
Worker::Worker(Server& server, fd_set& workerSet)
    : server(server), workerSet(workerSet){};
Worker::~Worker() { sem_destroy(&recvLock); };

sem_t          Worker::recvLock;
std::mutex     Worker::sockLock;
struct timeval Worker::selTimeout;
