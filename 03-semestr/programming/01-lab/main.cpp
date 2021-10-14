#include <fstream>
#include <iostream>
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

  ifstream input(filename);

  if (!input) {
    cerr << "Can't open " << filename << endl;
  }

  string outFilename = filename;
  int dot = filename.find('.');
  outFilename.replace(outFilename.begin() + dot, outFilename.end(), ".out");

  ofstream output(outFilename, ios::app);

  if (!output) {
    cerr << "Can't write to " << outFilename << endl;
  }

  while (input) {
    string buff;
    input >> buff;

    output << buff << symbol << endl;
  }

  return 0;
}