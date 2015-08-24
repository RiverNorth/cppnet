//
// Created by root on 8/24/15.
//

#ifndef CPPNET_CALLBACKS_H_H
#define CPPNET_CALLBACKS_H_H
#include "InetAddr.h"
#include <boost/function.hpp>
/*
typedef boost::function<void (TcpConnection const* ,
                              Buffer*,
                              Timestamp)> MessageCallback;
*/
typedef boost::function<void(int fd, const InetAddr& addr)> NewConnectionCallback;

#endif //CPPNET_CALLBACKS_H_H
