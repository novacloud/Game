//
//  Enemy.cpp
//  SimpleGame
//
//  Created by takashi-fukui on 2014/09/20.
//
//

#include "Enemy.h"
#include "Player.h"

USING_NS_CC;

Enemy::Enemy()
{
    life = 5;
    existFlag = true;
    imageFileName = "enemy.png";
}

std::string Enemy::getImageFileName()
{
    return imageFileName;
}

void Enemy::registAction(cocos2d::Sprite *sprite)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
 
    // 出現・移動イベントの登録
    auto fadeIn = FadeIn::create(0.5f);
    auto move = MoveTo::create(3.0f, Vec2(visibleSize.width/2, 100));
    auto sequence = Sequence::create(fadeIn, move, NULL);
    sprite->runAction(sequence);
    
    
    // タッチイベントの登録
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        auto target = (Sprite*)event->getCurrentTarget();
        auto targetBox = target->getBoundingBox();
        auto location = touch->getLocation();
        
        // タッチ位置判定
        if( targetBox.containsPoint(location) )
        {
            auto player = Player::getInstance();
            
            // 攻撃判定
            if( player->attack() )
            {
                // 攻撃エフェクト表示
                auto sprite = Sprite::create(player->getWeponImage());
                sprite->setPosition(location);
                Director::getInstance()->getRunningScene()->addChild(sprite);
                
                auto scaleTo = ScaleTo::create( 0.2f, 2.0f );
                auto fadeOut = FadeOut::create( 0.2f );
                auto sequence = Sequence::create( scaleTo, fadeOut, NULL );
                sprite->runAction(sequence);
                
                if( life > 0 )
                {
                    life -= player->getWeponPower();
                }
            
                if( life <= 0 )
                {
                    if( existFlag )
                    {
                        auto fadeOut = FadeOut::create(0.5f);
                        target->runAction(fadeOut);
                        existFlag = false;
                    }
                }
            }
            
            return true;
        }
        
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprite);
}