cmake_minimum_required(VERSION 3.3)
project(cppnet)

INCLUDE_DIRECTORIES(../boost_1_57_0 include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    include/Acceptor.h
    include/Channel.h
    include/EpollPoller.h
    include/EventLoop.h
    include/noncopyable.h
    include/Poller.h
    include/socket.h
    src/Acceptor.cpp
    src/Channel.cpp
    src/EpollPoller.cpp
    src/EventLoop.cc
    src/main.cc
    src/Poller.cpp
    src/socket.cc
    src/InetAddr.cpp
    include/InetAddr.h
    src/TcpConnection.cpp
    include/TcpConnection.h
    src/TcpServer.cpp
    include/TcpServer.h
    include/Callbacks.h
    src/Buffer.cpp
    include/Buffer.h
    include/logger.h
    src/logger.cpp)

add_executable(cppnet ${SOURCE_FILES})