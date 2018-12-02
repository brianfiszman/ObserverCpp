#ifndef CLIENT_CLUSTER
#define CLIENT_CLUSTER

#include <list>
#include "client.hpp"

class ClientCluster {
 private:
  list<Client> clients;

 public:
  ClientCluster(){};
  ~ClientCluster(){};

  list<Client> getClients();
  const void   createClient(Client);
  const void   destroyClient(Client& c);
};

#endif