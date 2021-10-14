#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void appendFile(string filename, string symbol) {
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
}