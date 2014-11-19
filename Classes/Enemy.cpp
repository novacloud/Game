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
    switch( _enemyType )
    {
        case 0:
            return "hitotsume.png";
        case 1:
            return "ittan.png";
        case 2:
            return "nurikabe.png";
        default:
            return "enemy.png";
    }
}

void Enemy::setInitPosision()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 posision;
    
    switch( _enemyType )
    {
        case 0:
            posision = Vec2( rand() % (int)visibleSize.width, visibleSize.height - 50 );
            break;
        case 1:
            posision = Vec2( rand() % (int)visibleSize.width, visibleSize.height - 50 );
            break;
        default:
            posision = Vec2( rand() % (int)visibleSize.width, visibleSize.height - 50 );
            break;
    }

    setPosition(posision);
}

void Enemy::setAction()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    
    //移動アクションを生成
    if( _enemyType == enemyType1 )       // ひとつめこぞう
    {
        auto move = MoveTo::create(20, Vec2( getPositionX(), visibleSize.height * -0.1));
        auto remove = RemoveSelf::create();
        auto seq = Sequence::create(move, remove, NULL);
        runAction(seq);
    
    }
    else if( _enemyType == enemyType2 )  // いったんもめん
    {
        auto move = MoveTo::create(20, Vec2( getPositionX(), visibleSize.height * -0.1));
        
        // ジグザグ動作
        auto left = MoveBy::create(5, Vec2( -visibleSize.width / 2, 0));
        auto right = MoveBy::create(5, Vec2( visibleSize.width / 2, 0));
        auto widthSeq = Sequence::create(left, right, NULL);
        auto repeat = Repeat::create(widthSeq, 2);

        auto spawn = Spawn::create(repeat, move, NULL);
        auto remove = RemoveSelf::create();
        auto seq = Sequence::create(spawn, remove, NULL);
        runAction(seq);
    }
    else if ( _enemyType == enemyType3 ) // ぬりかべ
    {
        // 動いて止まるを繰り返す
        auto move = MoveBy::create(5, Vec2( 0, -visibleSize.height / 4));
        auto delay = DelayTime::create(2.0f);
        auto moveDelay = Sequence::create(move, delay, NULL);
        auto repeat = Repeat::create(moveDelay, 4);

        auto remove = RemoveSelf::create();
        auto seq = Sequence::create(repeat, remove, NULL);
        runAction(seq);
    }

    else
    {
        auto move = MoveTo::create(20, Vec2( getPositionX(), visibleSize.height * -0.1));
        auto remove = RemoveSelf::create();
        auto seq = Sequence::create(move, remove, NULL);
        runAction(seq);
    }

    
}

void Enemy::setData()
{
    switch( _enemyType )
    {
        case 0:
            _life = 2;
            _score = 100;
            _state = State::move;
            break;
        case 1:
            _life = 3;
            _score = 150;
            _state = State::move;
            break;
        case 2:
            _life = 4;
            _score = 200;
            _state = State::move;
            break;
        default:
            _life = 2;
            _score = 100;
            _state = State::move;
            break;
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
