#include <iostream>
#include "simplesocket.h"
#include "Common.h"
#include<sys/types.h> 
#include<sys/stat.h>
#include <string>
#include <cstring>

int work(UdpServer *server, struct sockaddr_in client_addr, int nbytes, char *buff)
{
    std::cout<<buff<<std::endl;
    return 0;
}

int main()
{
    SimpleSocket::SimpleSocket server(UDP_MODE|SERVER_MODE);
    server.InitServer(9090);
    server.SetGlobalCallBack(work);
    try
    {
        server.Run();
    }catch (const char* msg) {
        std::cerr << msg << std::endl;
    }
    return 0;
}