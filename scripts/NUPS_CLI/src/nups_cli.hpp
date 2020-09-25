#ifndef SRC_NUPS_CLI_H_
#define SRC_NUPS_CLI_H_

#include "ups.hpp"

#include <cstdint>
#include <future>
#include <iostream>
#include <string>
#include <vector>

class NupsCli {
public:
  NupsCli(const std::string &gba_file_path, const std::string &ups_file_path,
          const std::string &full_output_path);
  void execute();

private:
  Ups ups_;

  std::string gba_file_path_;
  std::string ups_file_path_;
  std::string full_output_path_;

  std::vector<uint8_t> read_patch_check_valid_patch();
  std::vector<uint8_t> read_gba_file();

  void set_output_filename();
  void output(const std::vector<uint8_t> &patched_gba_file);
};

#endif // SRC_NUPS_CLI_H_
