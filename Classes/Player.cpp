//
//  Player.cpp
//  SimpleGame
//
//  Created by takashi-fukui on 2014/09/23.
//
//

#include "Player.h"

Player* Player::singleton = NULL;

Player::Player()
{
    
}

Player* Player::getInstance()
{
    if( singleton == NULL )
    {
        singleton = new Player();
    }
    
    return singleton;
}


void Player::init(Layer *layer)
{
    score = 0;
    life = 5;
    weponImage = "bullet.png";
    weponPower = 1;
    weponMax = 5;
    weponRest = 5;
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // 墓表示
    auto spriteReload = Sprite::create("haka.png");
    spriteReload->setPosition(Vec2( visibleSize.width - spriteReload->getContentSize().width/2 - 10,
                           spriteReload->getContentSize().height/2 + 10));
    layer->addChild(spriteReload, 1);

    
    auto listenerReload = EventListenerTouchOneByOne::create();
    listenerReload->setSwallowTouches(true);
    listenerReload->onTouchBegan = [&](Touch* touch, Event* event)
    {
        auto target = (Sprite*)event->getCurrentTarget();
        auto targetBox = target->getBoundingBox();
        auto location = touch->getLocation();
        
        if( targetBox.containsPoint(location) )
        {
            reload();
            
            return true;
        }
        
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerReload, spriteReload);
    
    // 武器表示
    for( int i = 0; i < weponRest; i++ )
    {
        auto sprite = Sprite::create(weponImage);
        auto width = sprite->getContentSize().width;
        auto height = sprite->getContentSize().height;
        
        sprite->setPosition(Vec2((width * i + width/2 + 10), height/2 + 10 ));
        layer->addChild(sprite);
        
        vecWeponSprite.pushBack(sprite);
    }
}

bool Player::attack()
{
    if( weponRest > 0 )
    {
        // 残弾数表示変更
        weponRest -= 1;
        for( int i = 0; i < vecWeponSprite.size(); i++ )
        {
            if( i < weponRest )
            {
                vecWeponSprite.at(i)->setVisible(true);
            }
            else
            {
                vecWeponSprite.at(i)->setVisible(false);
            }
        }
        
        return true;
    }
    
    return false;
}

void Player::reload()
{
    weponRest = weponMax;
    
    for( int i = 0; i < vecWeponSprite.size(); i++ )
    {
        vecWeponSprite.at(i)->setVisible(true);
    }
}

std::string Player::getWeponImage()
{
    return weponImage;
}

int Player::getWeponPower()
{
    return weponPower;
}