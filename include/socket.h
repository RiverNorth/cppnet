#ifndef SOCKET_H
#define SOCKET_H

#include "noncopyable.h"
#include <string>
#include <sys/types.h>
#include <stdint.h>
#include <netinet/in.h>


namespace fsociety
{
namespace net
{
//forward implementation

class InetAddr;
class Socket:private Noncopyable
{
  private:
	int socketfd_;
    std::string ipAddr_;
    uint16_t port_;
  public:
  	//explicit Socket(int sockfd):socketfd_(socketfd){};
	explicit Socket(int sockfd):socketfd_(sockfd){};
	Socket(int sockfd, struct sockaddr_in addr);
	~Socket(){if(socketfd_>0) close();}
    std::string getIpStr();
    uint16_t getPortNum();
    int getSocketFd(){return socketfd_;}
    bool setNonBlocking();
    bool setReuseAddr();
    bool bindAddress(InetAddr const* inetAddr);
    bool listen(int backlog);
    int accept(InetAddr* addr);
    bool close();

};

}
}
#endif
