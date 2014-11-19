//
//  Enemy.cpp
//  SimpleGame
//
//  Created by takashi-fukui on 2014/09/20.
//
//

#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy(EnemyType type)
: _enemyType(type)
{
}

Enemy* Enemy::create(EnemyType type)
{
    Enemy *enemy = new Enemy(type);
    
    if( enemy && enemy->init() )
    {
        enemy->setInitPosision();
        enemy->setAction();
        enemy->setData();
        return enemy;
    }
    
    CC_SAFE_DELETE(enemy);
    return NULL;
}

bool Enemy::init()
{
    if (!Sprite::initWithFile(getImageFileName()))
    {
        return false;
    }
    
    return true;
}

std::string Enemy::getImageFileName()
{
    if( _enemyType == enemyType1 )
    {
        return "enemy.png";
    }
    
    return "enemy.png";
}

void Enemy::setInitPosision()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 posision;
    
    if( _enemyType == enemyType1 )
    {
        posision = Vec2( rand() % (int)visibleSize.width, visibleSize.height - 50 );
    }
    
    setPosition(posision);
}

void Enemy::setAction()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    //移動アクションを生成
    if( _enemyType == enemyType1 )
    {
        auto move = MoveTo::create(20, Vec2( getPositionX(), visibleSize.height * -0.1));
        auto remove = RemoveSelf::create();
        auto seq = Sequence::create(move, remove, NULL);
    
        runAction(seq);
    }
}

void Enemy::setData()
{
    if( _enemyType == enemyType1 )
    {
        _life = 2;
        _score = 100;
        _state = State::move;
    }
}


void Enemy::damage(int power)
{
    _life -= power;
    
    if(_life <= 0 )
    {
        // アクション停止
        stopAllActions();
        
        auto remove = RemoveSelf::create();
        runAction(remove);
        
        _state = State::dead;
    }
    else
    {
        // 点滅
        auto blink = Blink::create(0.2, 2);
        runAction(blink);
    }
}
