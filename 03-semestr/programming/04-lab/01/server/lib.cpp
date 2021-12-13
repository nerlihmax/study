#include <iostream>
#include <string>
#include <fstream>

void appendFile(std::string filename, std::string symbol) {
  std::ifstream input(filename);

  if (!input) {
    std::cerr << "Can't open " << filename << std::endl;
    std::terminate();
  }

  std::string outFilename = filename;
  int dot = filename.find('.');
  outFilename.replace(outFilename.begin() + dot, outFilename.end(), ".out");

  std::ofstream output(outFilename, std::ios::app);

  if (!output) {
    std::cerr << "Can't write to " << outFilename << std::endl;
  }

  while (input) {
    std::string buff;
    input >> buff;

    if (!input) break;

    output << buff << symbol << std::endl;
  }
}
