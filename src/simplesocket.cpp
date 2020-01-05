#include "simplesocket.h"
namespace SimpleSocket
{

SimpleSocket::SimpleSocket(Mode_Type type)
{
    this->socket_mode_ = type;
}

Status_Type SimpleSocket::InitServer(int port)
{
    if(socket_mode_==UDP_MODE)
    {
        Status_Type serverstate = UdpServer::Initialize(port);
        if (serverstate == ERROR)
        {
            throw "Can't initialze server";
        }

    }
}

Status_Type SimpleSocket::SetGlobalCallBack(Status_Type (*callback_func)(class UdpServer *server, struct sockaddr_in client_addr,int nbytes, char *buff))
{
    UdpServer::SetGlobalCallBack(callback_func);
    return OK;
}

Status_Type SimpleSocket:: Run()
{
    if(socket_mode_==UDP_MODE)
    {
        while (1)
        {
            if (UdpServer::MainActivity() == NOPACK)
                usleep(100000);
        }
    }
}

Status_Type SimpleSocket:: RunOneTime()
{
    if(socket_mode_==UDP_MODE)
    {
        return UdpServer::MainActivity();
    }
}


} // namespace SimpleSocket