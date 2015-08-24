//
// Created by root on 8/23/15.
//

#ifndef CPPNET_INETADDR_H
#define CPPNET_INETADDR_H

#include <stdint.h>
#include <string>
#include <netinet/in.h>
#include <strings.h>

class InetAddr {
public:
    InetAddr():ipStr_(NULL),port_(0)
    {
        bzero((void*)&sockAddr_,sizeof(sockAddr_));
    }
    InetAddr(uint16_t port);
    InetAddr(const std::string& ipAddr, uint16_t port);
    std::string getIp() const {return ipStr_;}
    uint16_t getPortNum() const {return port_;};
    std::string getIpPortStr() const;
private:
    std::string ipStr_;
    uint16_t port_;
    struct sockaddr_in sockAddr_;
};


#endif //CPPNET_INETADDR_H
