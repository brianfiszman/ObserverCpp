#include "clientCluster.hpp"
#include <arpa/inet.h>

const void ClientCluster::destroyClient(Client& c) {
  c.end();

  this->clients.remove(c);
}

const void ClientCluster::createClient(Client c) {
  this->clients.push_front(c);
}

list<Client> ClientCluster::getClients() { return this->clients; }
const void   ClientCluster::notify(Client& c) {
  for (auto client : this->clients) {
    client.notifyDisconnection(inet_ntoa(c.getClientAddr()->sin_addr));
  }
}