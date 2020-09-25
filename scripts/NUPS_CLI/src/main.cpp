#include "nups_cli.hpp"
#include <chrono>
#include <iostream>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Please supply a --gba and a --input file" << std::endl;
    exit(-1);
  }

  std::string gba_file_path = "";
  std::string ups_file_path = "";
  std::string output_file_path = "";
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

    else if (0 == token.compare("--output"))
    {
      index += 1;
      output_file_path = std::string(argv[index]);
    }

    else if (0 == token.compare("--help"))
    {
      std::cout << "Example usage:"
                << std::endl
                << "NupsCli.exe --gba Clean.gba --ups patch.ups"
                << std::endl << std::endl
                << "You can also optionally supply an `--output filename`. The program"
                << std::endl
                << "will save the output patched file with that name and the .gba extension."
                ;
      exit(0);
    }

    index += 1;
  }

  NupsCli nups_cli(gba_file_path, ups_file_path, output_file_path);
  auto start_time = std::chrono::high_resolution_clock::now();
  nups_cli.execute();
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
                  (end_time - start_time).count();
  std::cout << "Time elapsed: " << (duration / 1000.0f) << " seconds" << std::endl;
}
