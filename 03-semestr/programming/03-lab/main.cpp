#include "lib.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]) {
  const vector<string> params(argv, argv + argc);

  if (params.size() < 3) {
    cerr << "Too few arguments" << endl;
    return -1;
  }

  const string filename = params.at(1);
  const string symbol = params.at(2);

  pid_t pid = fork();

  if (pid == 0) {
    appendFile(filename, symbol);
  } else {
    waitpid(pid, nullptr, 0);
    cout << "child process exited" << endl;
  }

  return 0;
}