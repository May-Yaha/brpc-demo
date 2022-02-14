#include <iostream>

#include "gflags/gflags.h"

DEFINE_string(in, "", "input string --in=xxx");
int main(int argc, char **argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  std::cout << "hello gflags : " << FLAGS_in << std::endl;
  return 0;
}