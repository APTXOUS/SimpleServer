# SimpleSocket

![](https://img.shields.io/badge/status-on%20develop-orange) 
![](https://img.shields.io/badge/language-c++-green.svg)
![](https://img.shields.io/github/last-commit/aptxous/SimpleServer)

SimpleSocket is a toy socket server project based on Linux socket.

We have use this library to compete these projects:

1. [One Room](https://github.com/kagaya85/OneRoom): A PC chatting software using Qt as user interface and SimpleSocket as backend.
2. [Game Server](https://github.com/TaihouDaisuki/GameSever): A plane game backend progream. The game client is here:[AircraftWarClient](https://github.com/kagaya85/AircraftWarClient)
3. Analog bank teller communication protocol. 

All of those are course projects, so we need time to divide the SimpleSocket library from those projects.

If you want to see how SimpleSocket will perform, please check the links above.

## Build
```bash
mkdir build
cmake ..
make
```

## How to use

```c++
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
```

## Develop List
### 2020 02 28
* create CMakeLists 

### 2020 01 07
* add mode control
* add task: Buffer and Buffermanager

### 2020 01 05
* add simple tested udpserver
* add simple untested tcpserver

## Tack List

- [x] Initial Project
- [ ] Add Socket Class
- [ ] Add TcpSocket Class
- [ ] Add UdpSocket Class
- [ ] Add TcpServer Class
- [x] Add UdpServer Class
- [x] Add Logger Class
- [x] Add SimpleSocket Class
- [ ] Add PackageManager Class
- [ ] Add Package Class
- [ ] Add BufferManager Class
- [ ] Add Buffer Class
