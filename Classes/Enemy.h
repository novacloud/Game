//
//  Enemy.h
//  SimpleGame
//
//  Created by takashi-fukui on 2014/09/20.
//
//

#ifndef __SimpleGame__Enemy__
#define __SimpleGame__Enemy__

#include <cocos2d.h>

USING_NS_CC;

class Enemy : public Sprite
{
public:
    enum EnemyType
    {
        enemyType1,
        enemyType2
    };
    
private:
    EnemyType enemyType;
    int     life;
    
public:
    Enemy(EnemyType type);
    static Enemy* create(EnemyType type);
    virtual bool init();
    std::string getImageFileName();
    void setInitPosision();
    void setAction();
    void setData();
};

#endif /* defined(__SimpleGame__Enemy__) */
