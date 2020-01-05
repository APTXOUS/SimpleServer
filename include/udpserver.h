#ifndef UDPSERVER
#define UDPSERVER

#include "common.h"


class UdpServer
{
/* Member */
public:
    char buff[BuffLength];
    int nbytes;
    struct sockaddr_in client_addr;

    int (*callback)(class UdpServer *server, struct sockaddr_in client_addr,int nbytes,  char *buff);

private:
    int port;
    char ip[9];

    struct sockaddr_in server_addr;
    int server_fd;

/* Function */
public:
    UdpServer();
    ~UdpServer();

    int Initialize(int);

    int MainActivity();

    int SetGlobalCallBack(int (*callback)(class UdpServer *server, struct sockaddr_in client_addr,  int nbytes,char *buff));

    int Recv();
    int Send(char *buff, struct sockaddr_in client_addr, int count);

    int (*dealpack)(class UdpServer* s, int nbytes, struct sockaddr_in sock_addr, char* buff);
private:
};


#endif