#include "common.h"

class TcpServer
{
public:
  char ip[20];
  int port;
  int init();

  int Socket;

  fd_set rfds, wfds;
  fd_set rfds_b, wfds_b;
  int max_fd = 0;

  int fd_book = 0;

  int init(int port, const char *ip, int mode);
  int Connect(int port, const char *ip);
  int status();
  int updateMaxfd(fd_set rfds, int maxfd);
  int hasnewconnect();
};
