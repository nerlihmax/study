#include <string>

struct RoutineArguments {
  std::string filename;
  std::string replacer;
};

void* appendFile(void* arguments);
