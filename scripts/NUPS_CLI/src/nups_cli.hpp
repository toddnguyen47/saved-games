#ifndef SRC_NUPS_CLI_H_
#define SRC_NUPS_CLI_H_

#include "ups.hpp"

#include <iostream>
#include <string>

class NupsCli
{
public:
  NupsCli(std::string gba_file_path, std::string ups_file_path);
  void execute();

private:
  std::string gba_file_path_;
  std::string ups_file_path_;
};

#endif // SRC_NUPS_CLI_H_
