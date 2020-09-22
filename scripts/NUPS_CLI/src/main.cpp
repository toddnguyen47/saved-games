#include "nups_cli.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
  if (argc < 4)
  {
    std::cout << "Please supply a --gba and a --input file" << std::endl;
    exit(-1);
  }

  std::string gba_file_path = "";
  std::string ups_file_path = "";
  int index = 0;
  while (index < argc)
  {
    std::string token = std::string(argv[index]);
    if (0 == token.compare("--gba"))
    {
      index += 1;
      gba_file_path = std::string(argv[index]);
    }

    else if (0 == token.compare("--ups"))
    {
      index += 1;
      ups_file_path = std::string(argv[index]);
    }
    index += 1;
  }

  NupsCli nups_cli(gba_file_path, ups_file_path);
  nups_cli.execute();
}