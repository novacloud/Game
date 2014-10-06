//
//  Enemy.cpp
//  SimpleGame
//
//  Created by takashi-fukui on 2014/09/20.
//
//

#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy()
{
    life = 5;
    imageFileName = "enemy.png";
}

std::string Enemy::getImageFileName()
{
    return imageFileName;
}

void Enemy::registAction(cocos2d::Sprite *sprite)
{
    // 出現〜移動
    auto fadeIn = FadeIn::create(0.5f);
    auto move = MoveTo::create(10.0f, Vec2(300, 100));
    auto sequence = Sequence::create(fadeIn, move, NULL);
    
    sprite->runAction(sequence);
    
    // タッチイベント登録
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        log( "touch enemy" );
        
        life -= 1;
        
        if( life == 0 )
        {
            // 倒す
        }
        
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);
}