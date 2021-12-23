#include <iostream>
#include <vector>
#include <cstdlib>

#include <pthread.h>

#include "lib.h"

int main(int argc, char* argv[]) {
  const std::vector<std::string> filenames(argv + 1, argv + argc - 1);
  const size_t filesCount = filenames.size();

  if (argc < 3) {
    std::cerr << "too few arguments" << std::endl;
    std::exit(-1);
  }

  const std::string replacer(argv[argc - 1]);

  pthread_t threads[filesCount];

  for (uint8_t i = 0; i < filesCount; i++) {
    RoutineArguments* args = new RoutineArguments;
    args->filename = filenames.at(i);
    args->replacer = replacer;

    std::cout << "file: " << args->filename << std::endl;

    if (pthread_create(&threads[i], nullptr, appendFile, static_cast<void*>(args))) {
      std::cerr << "failed to create thread" << std::endl;
      std::exit(-1);
    }
  }

  for (uint8_t i = 0; i < filesCount; i++) {
    int8_t* code;
    pthread_join(threads[i], reinterpret_cast<void**>(&code));
    std::cout << "thread exited with code " << static_cast<int>(*code) << std::endl;
    delete code;
  }

  pthread_exit(nullptr);
}
