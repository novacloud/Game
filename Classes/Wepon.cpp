//
//  Wepon.cpp
//  SimpleGame
//
//  Created by takashi-fukui on 2014/11/01.
//
//

#include <math.h>
#include "Wepon.h"

USING_NS_CC;

Wepon::Wepon(WeponType type)
: weponType(type)
{
}

Wepon* Wepon::create(WeponType type, Vec2 touch)
{
    Wepon *wepon = new Wepon(type);
    
    if( wepon && wepon->init() )
    {
        wepon->setInitPosision();
        wepon->setAction(touch);
        wepon->setData();
        
        return wepon;
    }
    
    CC_SAFE_DELETE(wepon);
    return NULL;
}

bool Wepon::init()
{
    if (!Sprite::initWithFile(getImageFileName()))
    {
        return false;
    }
    
    return true;
}

std::string Wepon::getImageFileName()
{
    if( weponType == weponType1 )
    {
        return "bullet.png";
    }
    
    return "bullet.png";
}

void Wepon::setInitPosision()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    Vec2 posision;
    
    if( weponType == weponType1 )
    {
        posision = Vec2( visibleSize.width / 2, 0 );
    }

    setPosition(posision);
}

void Wepon::setAction(Vec2 touch)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    if( weponType == weponType1 )
    {
        // 移動距離算出
        auto range = sqrtf( powf(visibleSize.width / 2, 2) + powf(visibleSize.height, 2) );
        log( "range = %f", range );
        log( "touch = %f, %f", touch.x, touch.y );
        // タッチ位置から角度算出
        auto angle = atan2f( touch.y, touch.x - visibleSize.width/2 );
        log( "angle = %f", angle );
     
        // x,y方向のそれぞれの移動距離算出
        auto rangeX = range * cosf( angle );
        auto rangeY = range * sinf( angle );
        
        log( "rangeXY = %f, %f", rangeX, rangeY );
     
        auto move = MoveTo::create(1.0f, Vec2(rangeX + visibleSize.width/2, rangeY));
        auto remove = RemoveSelf::create();
        auto seq = Sequence::create(move, remove, NULL);
     
        runAction(seq);
     }
}

void Wepon::setData()
{
    
}


