#include <iostream>
#include <string>
#include <fstream>

int appendFile(std::string filename, std::string symbol) {
  std::ifstream input(filename);

  if (!input) {
    std::cerr << "can't open " << filename << std::endl;
    return -1;
  }

  std::string outFilename = filename;
  int dot = filename.find('.');
  outFilename.replace(outFilename.begin() + dot, outFilename.end(), ".out");

  std::ofstream output(outFilename, std::ios::app);

  if (!output) {
    std::cerr << "can't write to " << outFilename << std::endl;
    return -1;
  }

  while (input) {
    std::string buff;
    input >> buff;

    if (!input) break;

    output << buff << symbol << std::endl;
  }

  return 0;
}
