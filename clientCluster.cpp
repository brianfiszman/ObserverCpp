#include "clientCluster.hpp"

const void ClientCluster::destroyClient(Client& c) {
  c.end();

  this->clients.remove(c);
}

const void ClientCluster::createClient(Client c) {
  this->clients.push_front(c);
}

list<Client> ClientCluster::getClients() { return this->clients; }