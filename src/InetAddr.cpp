//
// Created by root on 8/23/15.
//

#include "InetAddr.h"
#include <strings.h>
#include <arpa/inet.h>

InetAddr::InetAddr(uint16_t port)
{
    ipStr_ = "0.0.0.0";
    port_ = port;

    bzero(&sockAddr_,sizeof(sockAddr_));
    sockAddr_.sin_family = AF_INET;
    sockAddr_.sin_addr.s_addr = htonl(INADDR_ANY);
    sockAddr_.sin_port = htons(port);
}

InetAddr::InetAddr(const std::string &ipAddr, uint16_t port)
{
    ipStr_ = ipAddr;
    port_ = port;

    bzero(&sockAddr_,sizeof(sockAddr_));
    sockAddr_.sin_family = AF_INET;
    sockAddr_.sin_addr.s_addr = inet_addr(ipAddr.c_str());
    sockAddr_.sin_port = htons(port);
}

std::string InetAddr::getIpPortStr() const
{
    char buff[32];
    snprintf(buff,32,"%s:%u",ipStr_.c_str(),port_);
    return buff;
}
