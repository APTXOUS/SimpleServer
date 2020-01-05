#include "Tcpsocket.h"

int Tcpsocket::init(int port, const char *ip, int mode)
{
    if (mode == CLIENT_MODE)
    {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0)
        {
            close(sock);
            return -1; //socket create error
        }
        int flags = fcntl(sock, F_GETFL, 0);             
        fcntl(sock, F_SETFL, flags | O_NONBLOCK); 
        this->Socket = sock;
        this->port = port;
        strcpy(this->ip, ip);
        FD_ZERO(&rfds);
        FD_ZERO(&rfds_b);
        FD_ZERO(&wfds);
        FD_ZERO(&wfds_b);
        return sock;
    }
    else if (mode == SERVER_MODE)
    {
        return 0;
    }
    else
    {
        return 0;
    }
}

int Tcpsocket::Connect(int port, const char *ip)
{
    int slct_ready;
    struct sockaddr_in serv_addr;
    fd_set wset;
    memset(&serv_addr, 0, sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;          
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port); //�˿�
    int sock = this->Socket;

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        FD_ZERO(&wset);
        FD_SET(this->Socket, &wset);
        struct timeval con_time;
        con_time.tv_sec = 1;
        con_time.tv_usec = 0;
        slct_ready = select(sock + 1, NULL, &wset, NULL, &con_time);
        if (slct_ready == -1)
        {
            // perror("connect");
            return -2;
        }
        if (slct_ready == 0)
        {
            // perror("connect time out");
            return -3;
        }
        if (slct_ready < -1)
        {
            // perror("connect other error");
            return -4;
        }

    }
    //success add the sock into the select fd
    if (sock > max_fd)
        max_fd = sock;
    FD_SET(sock, &this->rfds_b);
    FD_SET(sock, &this->wfds_b);
    return sock;
}

int Tcpsocket::status()
{
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    this->rfds = this->rfds_b;
    this->wfds = this->wfds_b;
    this->max_fd = updateMaxfd(rfds, this->max_fd);
    int res = select(max_fd + 1, &rfds, &wfds, NULL, &timeout);
    if (res == -1 && errno != EINTR)
    {
        return res;
    }
    else if (res == 0)
    {
        return res;
    }
    else
        return res;
}
int Tcpsocket::updateMaxfd(fd_set fds, int maxfd)
{
    int i;
    int new_maxfd = 0;
    for (i = 0; i <= maxfd; i++)
    {
        if (FD_ISSET(i, &fds) && i > new_maxfd)
            new_maxfd = i;
    }
    return new_maxfd;
}
