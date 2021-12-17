#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <unistd.h>

int main(int argc, char* argv[]) {
  const std::string pipePath("/tmp/gunlab");
  const std::string serverPath("./build/server");

  const std::vector<std::string> params(argv, argv + argc);

  if (params.size() < 3) {
    std::cerr << "too few arguments" << std::endl;
    std::terminate();
  }

  const std::string filename = params.at(1);
  const std::string symbol = params.at(2);
  
  pid_t pid = fork();
  if (pid == -1) {
    std::cerr << "failed to create child process" << std::endl;
    std::terminate();
  }

  if (pid > 0) {
    // parent process
    while (!std::filesystem::exists(pipePath)) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::ofstream pipe(pipePath);
    if (!pipe) {
      std::cerr << "failed to open pipe" << std::endl;
      std::terminate();
    }

    pipe << filename << " " << symbol;

    pipe.close();

    waitpid(pid, nullptr, 0);
  } else {
    // child process
    if (execlp(serverPath.c_str(), serverPath.c_str(), NULL) == -1) {
        std::cerr << "failed to exec server" << std::endl;
        std::terminate();
    }
  }

  return 0;
}