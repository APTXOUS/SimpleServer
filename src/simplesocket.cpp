#include "simplesocket.h"
namespace SimpleSocket
{

SimpleSocket::SimpleSocket(Mode_Type type)
{
    this->socket_mode_ = type;
}

Status_Type SimpleSocket::InitServer(int port)
{
    if(socket_mode_ & UDP_MODE==UDP_MODE)
    {
        if(socket_mode_ & SERVER_MODE ==SERVER_MODE)
        {
            Status_Type serverstate = UdpServer::Initialize(port);
            if (serverstate == ERROR)
            {
                throw "Can't initialze server";
            }
        } 
        else if (socket_mode_ & CLIENT_MODE ==CLIENT_MODE)
        {
            /* code */
          
        }
        else
        {
             throw "Socket_mode error";
            /* code */
        }
        

    } else if(socket_mode_ & TCP_MODE ==TCP_MODE)
    {
        if(socket_mode_ & SERVER_MODE ==SERVER_MODE)
        {
            Status_Type serverstate = TcpServer::init(port,"0.0.0.0",SERVER_MODE);
            if (serverstate == ERROR)
            {
                throw "Can't initialze server";
            }
        } 
        else if (socket_mode_ & CLIENT_MODE ==CLIENT_MODE)
        {
            Status_Type serverstate = TcpServer::init(port,"0.0.0.0",CLIENT_MODE);
            if (serverstate == ERROR)
            {
                throw "Can't initialze server";
            }
            /* code */
        }
        else
        {
             throw "Socket_mode error";
            /* code */
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