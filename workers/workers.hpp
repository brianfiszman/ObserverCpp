#ifndef WORKERS
#define WORKERS

#include <fcntl.h>
#include <semaphore.h>
#include <mutex>
#include <thread>
#include "../server.hpp"

const void start(Server &);

#endif
