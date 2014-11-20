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
    
    enum class State
    {
        move,
        hit
    };
    
private:
    WeponType   _weponType;
    
    void setInitPosision();
    void setAction(Vec2 touch);
    void setData();
    
public:
    Wepon(WeponType type);
    static Wepon* create(WeponType type, Vec2 touch);
    virtual bool init();
    std::string getImageFileName();
    void hit();
    
    CC_SYNTHESIZE_READONLY(State, _state, State);
    CC_SYNTHESIZE_READONLY(int, _power, Power);
};

#endif /* defined(__SimpleGame__Wepon__) */
