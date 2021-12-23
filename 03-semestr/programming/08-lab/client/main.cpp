#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdio>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>

int main(int argc, char* argv[]) {
  const std::vector<std::string> params(argv, argv + argc);

  if (params.size() < 3) {
    std::cerr << "too few arguments" << std::endl;
    std::exit(-1);
  }

  const std::string filename = params.at(1);
  const std::string replacer = params.at(2);

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

  if (connect(sock, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
    std::cerr << "could not connect" << std::endl;
    std::exit(-1);
  }

  std::stringstream ss;
  ss << filename << " " << replacer;
  std::string str = ss.str();
  char buff[128];
  buff[str.copy(buff, str.length())] = '\0';
  
  if (write(sock, buff, 128) == -1) {
    std::cerr << "failed to write message" << std::endl;
    close(sock);
    std::exit(-1);
  }

  close(sock);

  return 0;
}