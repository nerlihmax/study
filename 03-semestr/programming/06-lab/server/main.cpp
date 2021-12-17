#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>

#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "lib.h"

const std::string semaphoreName("/gunlab-sem");
const std::string sharedFile("/tmp/gunlab-sf");

int main(int argc, char* argv[]) {
  int file = open(sharedFile.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  if (file == -1) {
    std::cerr << "could not open shared file" << std::endl;
    std::exit(-1);
  }

  if (ftruncate(file, 128) == -1) {
    std::cerr << "could not truncate file" << std::endl;
    close(file);
    std::exit(-1);
  }

  void* shared = mmap(0, 128, PROT_WRITE | PROT_READ, MAP_SHARED, file, 0);
  if (shared == MAP_FAILED) {
    std::cerr << "could not map file on memory" << std::endl;
    close(file);
    std::exit(-1);
  }

  if (close(file) == -1) {
    std::cerr << "could not close shared file" << std::endl;
    std::exit(-1);
    munmap(shared, 128);
  }

  sem_t* sem = sem_open(semaphoreName.c_str(), O_CREAT, 0777, 0);
  if (sem == SEM_FAILED) {
    std::cerr << "could not open semaphore" << std::endl;
    munmap(shared, 128);
    std::exit(-1);
  }
  
  sem_wait(sem);

  std::string message((char*) shared);
  std::cout << message << std::endl;

  std::size_t delimer = message.find(' ');
  std::string filename = message.substr(0, delimer);
  std::string replacer = message.substr(delimer + 1);

  if (appendFile(filename, replacer) == -1) {
    std::exit(-1);  
  }

  sem_unlink(semaphoreName.c_str());
  munmap(shared, 128);

  return 0;
}