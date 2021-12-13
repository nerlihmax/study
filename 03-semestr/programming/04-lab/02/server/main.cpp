#include <iostream>
#include <fstream>
#include <filesystem>
#include <exception>

#include <sys/stat.h>

#include "lib.h"

bool checkFileExisting(std::string path) {
  return std::filesystem::exists(path);
}

void deleteFile(std::string path) {
  try {
    std::filesystem::remove(path);
  } catch (std::filesystem::filesystem_error err) {
    std::cerr << "file deleting failed" << std::endl;
    std::terminate();
  }
}

bool makeFifo(std::string path) {
  return mkfifo(path.c_str(), 0777);
}

int main(int argc, char* argv[]) {
  const std::string pipePath("/tmp/gunlab");

  if (checkFileExisting(pipePath)) {
    deleteFile(pipePath);
  } 

  if (makeFifo(pipePath) != 0) {
    std::cerr << "creating pipe failed" << std::endl;
    std::terminate();
  }

  std::ifstream pipe(pipePath);

  if (!pipe) {
    std::cerr << "opening pipe failed" << std::endl;
    std::terminate();
  }

  std::string filename;
  std::string replacer;
  pipe >> filename >> replacer;

  pipe.close();

  appendFile(filename, replacer);

  if (!std::filesystem::remove(pipePath)) {
    std::cerr << "failed to delete pipe" << std::endl;
    std::terminate();
  }

  return 0;
}