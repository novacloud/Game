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
    int x;
    int y;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    for( int i = 0; i < popMax; i++ )
    {
        time = rand() % 60;
        x = rand() % (int)visibleSize.width;
        y = visibleSize.height - 50;
        
        vecPopTime.push_back(time);
        vecPopPointX.push_back(x);
        vecPopPointY.push_back(y);
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

int PopData::getPopPointX( int num )
{
    return vecPopPointX.at(num);
}

int PopData::getPopPointY( int num )
{
    return vecPopPointY.at(num);
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