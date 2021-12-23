#include <iostream>
#include <string>
#include <fstream>

#include <pthread.h>

#include "lib.h"

void* appendFile(void* arguments) {
  RoutineArguments* args = static_cast<RoutineArguments*>(arguments);

  std::string filename(args->filename);
  std::string replacer(args->replacer);

  delete args;

  std::cout << "from threads with file: " << filename << std::endl;

  std::ifstream input(filename);

  if (!input) {
    std::cerr << "can't open " << filename << std::endl;
    int8_t* code = new int8_t(-1);
    pthread_exit(static_cast<void*>(code));
  }

  std::string outFilename = filename;
  int dot = filename.find('.');
  outFilename.replace(outFilename.begin() + dot, outFilename.end(), ".out");

  std::ofstream output(outFilename, std::ios::app);

  if (!output) {
    std::cerr << "can't write to " << outFilename << std::endl;
    int8_t* code = new int8_t(-1);
    pthread_exit(static_cast<void*>(code));
  }

  while (input) {
    std::string buff;
    input >> buff;

    if (!input) break;

    output << buff << replacer << std::endl;
  }

  int8_t* code = new int8_t(0);
  pthread_exit(static_cast<void*>(code));
}
