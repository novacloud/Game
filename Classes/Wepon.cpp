//
//  Wepon.cpp
//  SimpleGame
//
//  Created by takashi-fukui on 2014/11/01.
//
//

#include "Wepon.h"

USING_NS_CC;

Wepon::Wepon(WeponType type)
: _weponType(type)
{
}

Wepon* Wepon::create(WeponType type, Vec2 touch)
{
    Wepon *wepon = new Wepon(type);
    
    if( wepon && wepon->init() )
    {
        wepon->setScale(0.3f, 0.3f);
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
    if( _weponType == weponType1 )
    {
        return "bullet_2.png";
    }
    
    return "bullet_2.png";
}

void Wepon::setInitPosision()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    Vec2 posision;
    
    if( _weponType == weponType1 )
    {
        posision = Vec2( visibleSize.width / 2, 0 );
    }

    setPosition(posision);
}

void Wepon::setAction(Vec2 touch)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    if( _weponType == weponType1 )
    {
        // 移動距離算出（画面下部中央から画面上部角まで）
        auto range = sqrtf( powf(visibleSize.width / 2, 2) + powf(visibleSize.height+10, 2) );

        // タッチ位置から角度算出
        auto angle = atan2f( touch.y, touch.x - visibleSize.width/2 );

        // x,y方向のそれぞれの移動距離算出
        auto rangeX = range * cosf( angle );
        auto rangeY = range * sinf( angle );
        
        // 画像の角度調整
        auto rotate = RotateTo::create(0, 90-(angle * 180 / M_PI));
     
        auto move = MoveTo::create(1.0f, Vec2(rangeX + visibleSize.width/2, rangeY));
        auto remove = RemoveSelf::create();
        auto seq = Sequence::create(rotate, move, remove, NULL);
     
        runAction(seq);
     }
}

void Wepon::setData()
{
    if( _weponType == weponType1 )
    {
        _power = 1;
        _state = State::move;
    }
}


void Wepon::hit()
{
    stopAllActions();
    
    auto remove = RemoveSelf::create();
    runAction(remove);
    
    _state = State::hit;
}

