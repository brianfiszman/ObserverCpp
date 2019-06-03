#ifndef WORKERS
#define WORKERS

#include <fcntl.h>
#include <semaphore.h>
#include <mutex>
#include <thread>
#include "../server.hpp"

const bool isAnyoneConnected(ClientCluster *cc);
const void listenConnections(Server *server, fd_set *listenSet);
const void receiveMessages(Server *server, fd_set *reader);
const void start(Server &server);

#endif
