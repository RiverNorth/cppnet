//
// Created by root on 8/24/15.
//

#ifndef CPPNET_CALLBACKS_H_H
#define CPPNET_CALLBACKS_H_H
#include "InetAddr.h"
#include <boost/function.hpp>
#include "TcpConnection.h"
#include "Buffer.h"

/*
typedef boost::function<void (TcpConnection const* ,
                              Buffer*,
                              Timestamp)> MessageCallback;
*/

typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;
typedef boost::function<void(int fd, const InetAddr& addr)> NewConnectionCallback;
typedef boost::function<void(TcpConnectionPtr& ptr)> TcpConnectionCallback;
typedef boost::function<void(TcpConnectionPtr& ptr)> MessageCallback;
typedef boost::function<void (const TcpConnectionPtr& ptr)> WriteCompleteCallback;
typedef boost::function<void(TcpConnectionPtr& ptr)> CloseCallback;

#endif //CPPNET_CALLBACKS_H_H
