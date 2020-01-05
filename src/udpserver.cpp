#include "udpserver.h"


/* public */
UdpServer::UdpServer()
{
    strcpy(ip,"0.0.0.0");
    // nothing to do
}
UdpServer::~UdpServer()
{
    // nothing to do
}

int UdpServer::Initialize(int Port)
{
    this->port=Port;
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);  //创建网络通信对象
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(this->port);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");

    int ret = bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0)
    {
        std::cerr << "Error: bind" << std::endl;
        return ERROR;
    }
    
    std::cout << "----------Server Start Running----------" << std::endl;
    return OK;
}

int UdpServer::Recv()
{
    int res = 0;
    socklen_t len = sizeof(client_addr);
    if((res = recvfrom(server_fd, buff, BuffLength, 0, (struct sockaddr*)&client_addr, &len)) < 0)
    {
        //cerr << "Failed to receive from client" << endl;
        return ERROR;
    }
    return res;
}
int UdpServer::Send(char *buff, struct sockaddr_in client_addr, int count)
{
    int res = 0;
    if((res = sendto(server_fd, buff, count, 0, (struct sockaddr*)&client_addr, sizeof(struct sockaddr))) < 0)
    {
       // cerr << "Failed to send to " << inet_ntoa(client_addr.sin_addr.s_addr) << "[" << ntohs(client_addr.port) << "]" << endl;
        return ERROR;
    }
    return res;
}

int UdpServer::MainActivity()
{
    //just do once
    socklen_t len = sizeof(client_addr);
    int res = recvfrom(server_fd, buff, BuffLength, MSG_DONTWAIT, (struct sockaddr *)&client_addr, &len);
    if (res <= 0)
        return NOPACK;
    else
        return dealpack(this, res, client_addr, buff);
}

int UdpServer::SetGlobalCallBack(int (*callback_func)(class UdpServer *server,struct sockaddr_in client_addr,  int nbytes, char *buff))
{
    this->callback=callback_func;
}
/* private */