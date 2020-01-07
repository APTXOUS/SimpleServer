#include "tcpserver.h"

int TcpServer::init(int port, const char *ip, int mode)
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
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0)
        {
            close(sock);
            return -1; //socket create error
        }
        int flags = fcntl(sock, F_GETFL, 0);
        if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0)
        {
           // perror("fcntl");
            close(sock);
            return -1;
        }
        FD_ZERO(&rfds);
        FD_ZERO(&rfds_b);
        FD_ZERO(&wfds);
        FD_ZERO(&wfds_b);
        FD_SET(sock, &rfds);
        FD_SET(sock, &wfds);
        rfds_b = rfds;
        wfds_b = wfds;
        
        struct sockaddr_in local;
        local.sin_family = AF_INET;
        local.sin_port = htons(port);
        local.sin_addr.s_addr = inet_addr(ip);
        socklen_t len = sizeof(local);
        int rcv_size=1;
        if (-1 == setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &rcv_size, sizeof(rcv_size)))
        {
            close(sock);
            return -1;
        }
        if (select(sock + 1, &rfds, &wfds, NULL, NULL) > 0)
        {
            if (bind(sock, (struct sockaddr *)&local, len) < 0)
            {
               close(sock);
                return -1;
            }
        }
        rfds = rfds_b;
        wfds = wfds_b;
        if (select(sock + 1, &rfds, &wfds, NULL, NULL) > 0)
            if (listen(sock,100 ) < 0)
            {
               close(sock);
                return -1;
            }
        this->Socket = sock;
        this->port = port;
        FD_ZERO(&rfds);
        FD_ZERO(&rfds_b);
        FD_ZERO(&wfds);
        FD_ZERO(&wfds_b);
        return sock;
    }
    else
    {
        return 0;
    }
}

int TcpServer::Connect(int port, const char *ip)
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

int TcpServer::status()
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
int TcpServer::updateMaxfd(fd_set fds, int maxfd)
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

int TcpServer::hasnewconnect()
{
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 10;

    FD_ZERO(&rfds);
    FD_ZERO(&wfds);
    FD_SET(Socket, &rfds);
    FD_SET(Socket, &wfds);
    return select(Socket + 1, &rfds, &wfds, NULL, &timeout);
}
