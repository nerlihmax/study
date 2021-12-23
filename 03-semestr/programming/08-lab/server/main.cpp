#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "lib.h"

int main(int argc, char* argv[]) {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    std::cerr << "could not create socket" << std::endl;
    std::exit(-1);
  }

  sockaddr_in addr;
  {
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3000);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  }

  if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
    std::cerr << "could not bind socket" << std::endl;
    std::exit(-1);
  }

  if (listen(sock, 1) == -1) {
    std::cerr << "could not open socket to listening" << std::endl;
    std::exit(-1);
  }

  int connection = accept(sock, nullptr, nullptr);
  if (connection == -1) {
    std::cerr << "could not accept incoming connection" << std::endl;
    std::exit(-1);
  }

  char buff[128];
  if (read(connection, buff, 128) == -1) {
    std::cerr << "failed to read message" << std::endl;
    close(connection);
    close(sock);
    std::exit(-1);
  }
  const std::string message(buff);

  std::size_t delimer = message.find(' ');
  std::string filename = message.substr(0, delimer);
  std::string replacer = message.substr(delimer + 1);

  if (appendFile(filename, replacer) == -1) {
    close(connection);
    close(sock);
    std::exit(-1);  
  }

  close(connection);

  close(sock);

  return 0;
}