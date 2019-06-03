#include <iostream>
#include "helpers/argchecker.hpp"
#include "workers/workers.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  chk_argn(&argc);

  const char *PORT = argv[1];

  Server server(PORT);

  start(server);

  return 0;
}
