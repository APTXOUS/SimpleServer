#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

#include <stddef.h>
#include <arpa/inet.h>
#include <errno.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/prctl.h>
#include <sys/times.h>
#include <string.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <fstream>
#include <string>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/un.h>
#include <sys/file.h>

#include <sys/times.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/un.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>


#define CLIENT_MODE 1
#define SERVER_MODE 2

using namespace std;

class Tcpsocket
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
    int updateMaxfd(fd_set rfds,int maxfd);
};


