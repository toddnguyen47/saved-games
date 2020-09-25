#include "nups_cli.hpp"

NupsCli::NupsCli(const std::string &gba_file_path, const std::string &ups_file_path,
                 const std::string &full_output_path)
  : gba_file_path_(gba_file_path),
    ups_file_path_(ups_file_path),
    full_output_path_(full_output_path) {
}

void NupsCli::execute() {
  std::cout << "Patching..." << std::endl;
  auto output_filename_future = std::async(std::launch::async,
                                &NupsCli::set_output_filename,
                                this);

  auto future_ups = std::async(std::launch::async,
                               &NupsCli::read_patch_check_valid_patch, this);
  auto future_gba = std::async(std::launch::async,
                               &NupsCli::read_gba_file, this);

  // Patch
  std::vector<uint8_t> ups_file = future_ups.get();
  std::vector<uint8_t> gba_file = future_gba.get();

  if (!this->ups_.is_file_valid_to_apply(gba_file)) {
    std::cerr << "GBA File does not match the Patch.";
    exit(-1);
  }
  std::vector<uint8_t> patched_gba_file = this->ups_.apply_patch(gba_file);
  this->output(patched_gba_file);

  output_filename_future.wait();
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// | PRIVATE FUNCTIONS
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
std::vector<uint8_t> NupsCli::read_patch_check_valid_patch() {
  std::cout << "Reading & Checking in UPS patch file" << std::endl;

  std::ifstream ups_file_input_stream(this->ups_file_path_, std::ios::binary);

  // copies all data into buffer
  std::vector<uint8_t> ups_file(std::istreambuf_iterator<char>(ups_file_input_stream), {});

  if (ups_file.size() <= 0) {
    std::cerr << "UPS File does not exist:" << std::endl
              << "  '" << this->ups_file_path_ << "'" << std::endl;
    exit(-1);
  }

  ups_file_input_stream.close();
  // Check valid patch
  if (!this->ups_.is_valid_patch(ups_file)) {
    std::cerr << "The patch is corrupt.";
    exit(-1);
  }

  std::cout << "FINISHED: Reading & Checking in UPS patch file" << std::endl;
  return ups_file;
}

std::vector<uint8_t> NupsCli::read_gba_file() {
  std::cout << "Reading in GBA clean ROM" << std::endl;

  // Check valid file
  // Ref: http://www.cplusplus.com/doc/tutorial/files/
  // std::ios::ate: seek to the end of stream immediately after open
  std::ifstream gba_file_input_stream(this->gba_file_path_,
                                      std::ios::binary | std::ios::ate);
  std::streampos size = gba_file_input_stream.tellg();

  if (size <= 0) {
    std::cerr << "GBA File does not exist:" << std::endl
              << "  '" << this->gba_file_path_ << "'" << std::endl;
    exit(-1);
  }

  char *memblock = new char[size]; // new[], so we must call delete[]!
  std::vector<uint8_t> gba_file(size);
  uint8_t *gba_file_ptr = &gba_file[0];

  gba_file_input_stream.seekg(0, std::ios::beg);
  gba_file_input_stream.read(memblock, size);

  unsigned int begin = 0;
  unsigned int end = static_cast<unsigned int>(size);
  for (unsigned int j = begin; j < end; j++)
    gba_file_ptr[j] = memblock[j];

  delete[] memblock;

  std::cout << "FINISHED: Reading in GBA clean ROM" << std::endl;
  return gba_file;
}

void NupsCli::output(std::vector<uint8_t> &patched_gba_file) {
  std::cout << "Writing to a new patched file." << std::endl;
  std::ofstream new_filename_ofstream(this->full_output_path_, std::ios::binary);
  new_filename_ofstream.write(reinterpret_cast<char *>(&patched_gba_file[0]),
                              patched_gba_file.size());

  new_filename_ofstream.close();
  std::cout << "Finished patching to file:" << std::endl
            << "  '" << this->full_output_path_ << "'"
            << std::endl;
}

void NupsCli::set_output_filename() {
  const size_t index = this->gba_file_path_.find_last_of("\\/");
  if (std::string::npos == index) {
    std::cout << "GBA filepath is wrong.\n'" << this->gba_file_path_ << "'" << std::endl;
    exit(-1);
  }

  const std::string gba_folder = this->gba_file_path_.substr(0, index + 1);

  const std::string new_filename = this->gba_file_path_.substr(index + 1);
  // Find extension
  const size_t rpos = new_filename.rfind(".");
  if (std::string::npos == rpos) {
    std::cout << "File does not have an extension\n'" << new_filename << "'" << std::endl;
    exit(-1);
  }

  std::string new_filename_no_ext = new_filename.substr(0, rpos);
  new_filename_no_ext.append("-patched");
  const std::string extension = new_filename.substr(rpos);
  new_filename_no_ext.append(extension);

  if (0 == this->full_output_path_.compare(""))
    this->full_output_path_ = gba_folder + new_filename_no_ext;
  else
    this->full_output_path_ = gba_folder + this->full_output_path_ + extension;

  std::cout << "OUTPUT: " << this->full_output_path_ << std::endl;
}
