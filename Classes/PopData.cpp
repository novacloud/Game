//
//  PopData.cpp
//  SimpleGame
//
//  Created by takashi-fukui on 2014/10/26.
//
//

#include "PopData.h"

USING_NS_CC;

PopData::PopData()
{
    popMax = 8;
    
    int time;
    
    for( int i = 0; i < popMax; i++ )
    {
        time = rand() % 30;

        
        vecPopTime.push_back(time);
        vecPopType.push_back(0);
        vecPopFlag.push_back(false);
    }
}

int PopData::getPopMax()
{
    return popMax;
}

int PopData::getPopTime( int num )
{
    return vecPopTime.at(num);
}

int PopData::getPopType( int num )
{
    return vecPopType.at(num);
}

bool PopData::getPopFlag( int num )
{
    return vecPopFlag.at(num);
}

void PopData::setPopFlagTrue( int num )
{
    vecPopFlag.at(num) = true;
}