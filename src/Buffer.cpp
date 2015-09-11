//
// Created by root on 8/24/15.
//

#include "Buffer.h"
char* Buffer::getWriteBuff(size_t& buffCount)
{
    if(writeIndex_>=readIndex_)
    {
        if(writeIndex_== buff_.capacity()-1)
        {
            if(readIndex_==0)
            {
                resizeVectorSize();
            }
            else
            {
                writeIndex_ = 0;
            }
        }
        buffCount = buff_. - writeIndex_;
    }
    else
    {
        if(writeIndex_==readIndex_-1)
        {
            resizeVectorSize();
        }
        buffCount = readIndex_-1;
    }
    return &buff_[writeIndex_];
}