#include "clientCluster.hpp"

const void ClientCluster::destroyClient(Client& c) {
  c.end();

  this->clients.remove(c);
}

const Client ClientCluster::createClient(Client c) {
  this->clients.push_front(c);

  return c;
}

list<Client> ClientCluster::getClients() { return this->clients; }
const void   ClientCluster::notify(Client& c, bool isConnecting = false) {
  if (!isConnecting) {
    for (auto client : this->clients) {
      client.notifyDisconnection(inet_ntoa(c.getClientAddr()->sin_addr));
    }
  } else {
    for (auto client : this->clients) {
      client.notifyConnection(inet_ntoa(c.getClientAddr()->sin_addr));
    }
  }
}
