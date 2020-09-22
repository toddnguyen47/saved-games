#include "nups_cli.hpp"

NupsCli::NupsCli(std::string gba_file_path, std::string ups_file_path) : gba_file_path_(gba_file_path),
                                                                         ups_file_path_(ups_file_path)
{
}

void NupsCli::execute()
{
  Ups ups(this->ups_file_path_);
  ups.isValidPatch();
}
