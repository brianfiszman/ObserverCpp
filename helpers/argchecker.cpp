#include "argchecker.hpp"
#include <iostream>

void error(char *err_msg) {
  perror(err_msg);
  exit(1);
}

int chk_argn(int *argc) {
  if (*argc < 2) {
    error((char *)"ERROR: indicate the server address and the port number!");
  }

  return 0;
}
