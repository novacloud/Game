//
//  EnemyPopData.h
//  SimpleGame
//
//  Created by takashi-fukui on 2014/11/20.
//
//

#ifndef __SimpleGame__EnemyPopData__
#define __SimpleGame__EnemyPopData__

#include <cocos2d.h>
#include "Enemy.h"

class EnemyPopData
{
public:
    EnemyPopData();
    
    CC_SYNTHESIZE(int, _popTime, PopTime);
    CC_SYNTHESIZE(Enemy::EnemyType, _enemyType, EnemyType);
    CC_SYNTHESIZE(bool, _popFlag, PopFlag);
};

#endif /* defined(__SimpleGame__EnemyPopData__) */
