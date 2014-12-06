//
//  Enemy.h
//  SimpleGame
//
//  Created by takashi-fukui on 2014/09/20.
//
//

#ifndef __SimpleGame__Enemy__
#define __SimpleGame__Enemy__

#include "cocos2d.h"

USING_NS_CC;

class Enemy : public Sprite
{
public:
    enum EnemyType
    {
        karakasa,
        ittan,
        nurikabe,
        medama,
        fusuma
    };
    
    enum class State
    {
        move,
        attack,
        dead
    };
    
private:
    EnemyType   _enemyType;
    int         _life;
    
    void setInitPosision();
    void setAction();
    void setData();
    void setAttack();
    
public:
    Enemy(EnemyType type);
    static Enemy* create(EnemyType type);
    virtual bool init();
    std::string getImageFileName();
    void damage(int power);
    int getEnemyType();
    
    CC_SYNTHESIZE_READONLY(int, _score, Score);
    CC_SYNTHESIZE_READONLY(State, _state, State);
};

#endif /* defined(__SimpleGame__Enemy__) */
