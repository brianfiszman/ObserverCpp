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

  const Client createClient(Client);
  list<Client> getClients();
  const void   destroyClient(Client&);
  const void   notify(Client&, bool);
};

#endif
