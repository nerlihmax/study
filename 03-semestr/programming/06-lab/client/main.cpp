#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

const std::string semaphoreName("/gunlab-sem");
const std::string sharedFile("/tmp/gunlab-sf");

int main(int argc, char* argv[]) {
  const std::vector<std::string> params(argv, argv + argc);

  if (params.size() < 3) {
    std::cerr << "too few arguments" << std::endl;
    std::exit(-1);
  }

  const std::string filename = params.at(1);
  const std::string replacer = params.at(2);

  int file = open(sharedFile.c_str(), O_RDWR, S_IRUSR | S_IWUSR);
  if (file == -1) {
    std::cerr << "could not open shared file" << std::endl;
    std::exit(-1);
  }

  void* shared = mmap(0, 128, PROT_WRITE | PROT_READ, MAP_SHARED, file, 0);
  if (shared == MAP_FAILED) {
    std::cerr << "could not map file on memory" << std::endl;
    std::exit(-1);
  }

  if (close(file) == -1) {
    std::cerr << "could not close shared file" << std::endl;
    std::exit(-1);
  }

  sem_t* sem = sem_open(semaphoreName.c_str(), O_RDWR);
  if (sem == SEM_FAILED) {
    std::cerr << "could not open semaphore" << std::endl;
    std::exit(-1);
  }

  std::stringstream ss;
  ss << filename << " " << replacer;
  std::string message = ss.str();
  char buff[128];
  buff[message.copy(buff, message.length())] = '\0';
  message.copy((char*) shared, message.size());

  sem_post(sem);

  return 0;
}