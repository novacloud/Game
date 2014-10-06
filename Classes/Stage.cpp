//
//  Stage.cpp
//  SimpleGame
//
//  Created by takashi-fukui on 2014/09/23.
//
//

#include <cocos2d.h>
#include "Stage.h"
#include "Enemy.h"

USING_NS_CC;

Stage::Stage()
{
}

void Stage::makeEnemy(float time)
{
    if( time > enemyPopupTime )
    {
        if( enemyPopFlag == 0 )
        {
            auto enemy = new Enemy();
            auto sprite = Sprite::create(enemy->getImageFileName());
            sprite->setPosition(Vec2(enemyPopupX, enemyPopupY));
            sprite->setOpacity(0);
            enemy->registAction(sprite);
            
            vecSpriteEnemy.pushBack(sprite);
            
            enemyPopFlag = 1;
        }
    }
}

cocos2d::Sprite* Stage::getNewEnemySprite()
{
    if( vecSpriteEnemy.empty() )
        return NULL;
    
    auto sprite = vecSpriteEnemy.back();
    vecSpriteEnemy.popBack();
    
    return sprite;
}