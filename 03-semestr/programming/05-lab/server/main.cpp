#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "lib.h"

const std::string socketPath("/var/run/gunlab");

int main(int argc, char* argv[]) {
  int sock = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sock == -1) {
    std::cerr << "could not create socket" << std::endl;
    std::exit(-1);
  }

  sockaddr_un addr;
  {
    addr.sun_family = AF_UNIX;
    char pathBuff[104];
    std::size_t copied = socketPath.copy(addr.sun_path, socketPath.size());
    pathBuff[copied] = '\0';
    addr.sun_len = copied;
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
    unlink(socketPath.c_str());
    std::exit(-1);
  }
  const std::string message(buff);

  std::size_t delimer = message.find(' ');
  std::string filename = message.substr(0, delimer);
  std::string replacer = message.substr(delimer + 1);

  if (appendFile(filename, replacer) == -1) {
    close(connection);
    close(sock);
    unlink(socketPath.c_str());
    std::exit(-1);  
  }

  close(connection);

  close(sock);
  unlink(socketPath.c_str());

  return 0;
}