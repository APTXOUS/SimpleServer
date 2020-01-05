#ifndef SIMPLESOCKET
#define SIMPLESOCKET

#define TCP_MODE
#define UDP_MODE

typedef int Mode_Tpye


class SimpleSocket{

protected:




public:
    SimpleSocket(Mode_Tpye type);

    Server();
    Client();
    
    InitServer();
    Run();
    
}




#endif