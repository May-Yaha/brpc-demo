
#include <iostream>
#include <dirent.h>

#include "leveldb/db.h"

int main(int argc, char** argv) {
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status db_status =
      leveldb::DB::Open(options, "./tmp/leveldb_test", &db);
  if (db_status.ok()) {
    std::cout << "connect leveldb ok" << std::endl;
    return 0;
  }

  std::cout << " not connect leveldb!" << std::endl;
  return -1;
}