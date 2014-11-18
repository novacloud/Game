//
//  Wepon.h
//  SimpleGame
//
//  Created by takashi-fukui on 2014/11/01.
//
//

#ifndef __SimpleGame__Wepon__
#define __SimpleGame__Wepon__

#include <cocos2d.h>
#include <math.h>

USING_NS_CC;

class Wepon : public Sprite
{
public:
    enum WeponType
    {
        weponType1,
        weponType2
    };
    
private:
    WeponType   weponType;
    int         power;
    
public:
    
    Wepon(WeponType type);
    static Wepon* create(WeponType type, Vec2 touch);
    virtual bool init();
    std::string getImageFileName();
    void setInitPosision();
    void setAction(Vec2 touch);
    void setData();
};

#endif /* defined(__SimpleGame__Wepon__) */
