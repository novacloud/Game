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
    popData = new PopData();
}

void Stage::createPopObject(Layer *layer, float time)
{
    for( int i = 0; i < popData->getPopMax(); i++)
    {
        if( popData->getPopFlag(i) )
            continue;
        
        if( time > popData->getPopTime(i) )
        {
            // POP時刻になった
            
            if( popData->getPopType(i) == 0 )
            {
                // 敵POP
                auto enemy = new Enemy();
                auto sprite = Sprite::create(enemy->getImageFileName());
                sprite->setPosition(Vec2(popData->getPopPointX(i), popData->getPopPointY(i)));
                sprite->setOpacity(0);
                enemy->registAction(sprite);
                
                layer->addChild(sprite);
                
                popData->setPopFlagTrue(i);
            }
        }
    }
}
