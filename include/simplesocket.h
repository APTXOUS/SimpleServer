#ifndef SIMPLESOCKET
#define SIMPLESOCKET
#include "udpserver.h"
#include "tcpserver.h"

#define TCP_MODE 1
#define UDP_MODE 2

typedef int Mode_Type;
typedef int Status_Type;

namespace SimpleSocket
{
class SimpleSocket : public UdpServer, TcpServer
{

protected:
    int socket_mode_;

public:
    SimpleSocket(Mode_Type type);
    Status_Type SetGlobalCallBack(Status_Type (*callback_func)(class UdpServer *server, int nbytes, struct sockaddr_in client_addr, char *buff));
    Status_Type InitServer(int port);
    Status_Type Run();
    Status_Type RunOneTime();
};

} // namespace SimpleSocket

#endif