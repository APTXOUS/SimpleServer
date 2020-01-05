#include <iostream>
#include "simplesocket.h"



int work(SimpleSocket *server,Package currentpack, struct sockaddr_in client_addr, int nbytes, char *buff)
{
    std::cout<<buff<<std::endl;
}

int main()
{
    SimpleSocket server(UDP_MODE);
    SimpleSocket::PackageManager packmanager;
    SimpleSocket::Package Helloworld;
    packmanager.add(Helloworld,work);
    server.SetPackageManager(packmanager);
    try
    {
        server.run();
    }catch (const char* msg) {
        std::cerr << msg << std::endl;
    }
    return 0;
}