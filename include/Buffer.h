//
// Created by root on 8/24/15.
//

#ifndef CPPNET_BUFFER_H
#define CPPNET_BUFFER_H
#include <vector>
#include "logger.h"
class Buffer {
public:
    typedef std::vector<int>::size_type VectorSize;
    static const VectorSize MAX_BUFF_SIZE = 50*1000;
    Buffer(int initBuffCap):buff_(initBuffCap,0),
                            (0),readIndex_(0),writeIndex_(0){}
    char* getWriteBuff(int& buffCount);

private:
    void resizeVectorSize()
    {
        VectorSize newSize =  buff_.size()*2;
        if(newSize>MAX_BUFF_SIZE)
        {
            logger::console->critical("Buffer size over limit:{}",newSize);
        }
        buff_.resize(newSize,0);
    }
    std::vector<char> buff_;
    int beginIndex_;
    int readIndex_;
    int writeIndex_;
};


#endif //CPPNET_BUFFER_H
