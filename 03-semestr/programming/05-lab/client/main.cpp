#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdio>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>

const std::string socketPath("/var/run/gunlab");

int main(int argc, char* argv[]) {
  const std::string pipePath("/tmp/gunlab");
  const std::string serverPath("./build/server");

  const std::vector<std::string> params(argv, argv + argc);

  if (params.size() < 3) {
    std::cerr << "too few arguments" << std::endl;
    std::exit(-1);
  }

  const std::string filename = params.at(1);
  const std::string replacer = params.at(2);

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