#include <iostream>

#include "proto/message.pb.h"

int main(int argc, char const *argv[]) {
  message::Message m;
  std::cout << "Hello Proto!" << std::endl;
  return 0;
}