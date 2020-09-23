#include "nups_cli.hpp"

NupsCli::NupsCli(std::string gba_file_path, std::string ups_file_path)
  : gba_file_path_(gba_file_path),
    ups_file_path_(ups_file_path)
{
}

void NupsCli::execute()
{
  this->set_output_filename();
  std::vector<uint8_t> ups_file = this->read_patch_check_valid_patch();
  std::vector<uint8_t> gba_file = this->read_gba_check_valid();
  // Patch
  std::vector<uint8_t> patched_gba_file = this->ups_.apply_patch(gba_file);
  this->output(patched_gba_file);
}

// ***************************************************
// | PRIVATE FUNCTIONS
// ***************************************************
std::vector<uint8_t> NupsCli::read_patch_check_valid_patch()
{
  std::ifstream ups_file_input_stream(this->ups_file_path_, std::ios::binary);
  // copies all data into buffer
  std::vector<uint8_t> ups_file(std::istreambuf_iterator<char>(ups_file_input_stream), {});
  // Check valid patch
  if (!this->ups_.is_valid_patch(ups_file))
  {
    std::cerr << "The patch is corrupt.";
    exit(-1);
  }

  ups_file_input_stream.close();
  return ups_file;
}

std::vector<uint8_t> NupsCli::read_gba_check_valid()
{
  // Check valid file
  std::ifstream gba_file_input_stream(this->gba_file_path_, std::ios::binary);
  // copies all data into buffer
  std::vector<uint8_t> gba_file(std::istreambuf_iterator<char>(gba_file_input_stream), {});
  if (!this->ups_.is_file_valid_to_apply(gba_file))
  {
    std::cerr << "GBA File does not match the Patch.";
    exit(-1);
  }
  gba_file_input_stream.close();
  return gba_file;
}

void NupsCli::output(std::vector<uint8_t> patched_gba_file)
{
  std::ofstream new_filename_ofstream(this->full_output_path_, std::ios::binary);

  for (uint8_t byte : patched_gba_file)
  {
    char *temp = reinterpret_cast<char *>(&byte);
    new_filename_ofstream.write(temp, sizeof(uint8_t));
  }

  new_filename_ofstream.close();
  std::cout << "Finished patching to file: '" << this->full_output_path_ << "'" <<
            std::endl;
}

void NupsCli::set_output_filename()
{
  const size_t index = this->gba_file_path_.find_last_of("\\/");
  if (std::string::npos == index)
  {
    std::cout << "GBA filepath is wrong.\n'" << this->gba_file_path_ << "'" << std::endl;
    exit(-1);
  }

  const std::string gba_folder = this->gba_file_path_.substr(0, index + 1);
  std::cout << "FOLDER: " << gba_folder << std::endl;

  const std::string new_filename = this->gba_file_path_.substr(index + 1);
  // Find extension
  const size_t rpos = new_filename.rfind(".");
  if (std::string::npos == rpos)
  {
    std::cout << "File does not have an extension\n'" << new_filename << "'" << std::endl;
    exit(-1);
  }

  std::string new_filename_no_ext = new_filename.substr(0, rpos);
  new_filename_no_ext.append("-patched");
  const std::string extension = new_filename.substr(rpos);
  new_filename_no_ext.append(extension);

  this->full_output_path_ = gba_folder + new_filename_no_ext;
}
