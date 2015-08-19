#include "socket.h"
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <unistd.h>

using namespace fsociety::net;
int main()
{
    int fd = socket(AF_INET,SOCK_STREAM,0);
    Socket s(fd);
    if(!s.bindAddress("127.0.0.1",9930))
    {
        printf("unknown error on bind:%s",strerror(errno));
    }

    s.listen(2);
    Socket* socket = s.accept();
    if(socket!=NULL)
    {
        printf("socket accepted:ip(%s),port(%d)",socket->getIpStr().c_str(),socket->getPortNum());
        sleep(100);
        socket->close();
    }

}

