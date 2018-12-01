#include <iostream>
#include "server.hpp"

using namespace std;

void error(char *err_msg) {
  perror(err_msg);
  exit(1);
}

int chk_argn(int *argc) {
  if (*argc < 1) {
    error((char *)"ERROR: indicate the server address and the port number!");
  }

  return 0;
}

int main(int argc, char *argv[]) {
  chk_argn(&argc);

  const char *PORT = argv[1];

  Server server(PORT);

  server.start();

  return 0;
}