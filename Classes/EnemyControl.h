//
//  EnemyControl.h
//  SimpleGame
//
//  Created by takashi-fukui on 2014/11/20.
//
//

#ifndef __SimpleGame__EnemyControl__
#define __SimpleGame__EnemyControl__

#include <cocos2d.h>
#include "Enemy.h"
#include "EnemyPopdata.h"

USING_NS_CC;

class EnemyControl
{
private:
    std::vector<EnemyPopData *> vecEnemyPopData;
    
public:
    EnemyControl();
    void init();
    Enemy* popEnemy(float time);
};


#endif /* defined(__SimpleGame__EnemyControl__) */
