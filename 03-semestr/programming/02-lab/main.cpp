#include "lib.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
  const vector<string> params(argv, argv + argc);

  if (params.size() < 3) {
    cerr << "Too few arguments" << endl;
    return -1;
  }

  const string filename = params.at(1);
  const string symbol = params.at(2);

  appendFile(filename, symbol);

  return 0;
}