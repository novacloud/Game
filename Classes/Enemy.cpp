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
        case karakasa:
            return "karakasa.png";
        case ittan:
            return "ittan.png";
        case nurikabe:
            return "nurikabe.png";
        case medama:
            return "medama.png";
        default:
            return "enemy.png";
    }
}

void Enemy::setInitPosision()
{
    srand((unsigned int)time(NULL));
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 posision;
    
    switch( _enemyType )
    {
        case karakasa:
            posision = Vec2( rand() % ((int)visibleSize.width / 3) + (int)visibleSize.width / 3, visibleSize.height - 250 );
            break;
        case ittan:
            posision = Vec2( rand() % ((int)visibleSize.width / 3) + (int)visibleSize.width / 3, visibleSize.height - rand() % 100 - 50 );
            break;
        case nurikabe:
            posision = Vec2( rand() % ((int)visibleSize.width / 3) + (int)visibleSize.width / 3, visibleSize.height - 250 );
            break;
        case medama:
            posision = Vec2( rand() % ((int)visibleSize.width / 3) + (int)visibleSize.width / 3, visibleSize.height - 300 );
            break;
        default:
            posision = Vec2( rand() % ((int)visibleSize.width / 3) + (int)visibleSize.width / 3, visibleSize.height - 250 );
            break;
    }

    setPosition(posision);
}

void Enemy::setAction()
{
    srand((unsigned int)time(NULL));
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // ウニウニ動かす
    auto upX = ScaleBy::create(0.5, 1.1f, 0.9f);
    auto upY = ScaleBy::create(0.5, 0.9f, 1.1f);
    auto scaleSeq = Sequence::create(upX, upY, NULL);
    auto scaleRepeat = Repeat::create(scaleSeq, 10);

    
    //移動アクションを生成
    switch( _enemyType )
    {
        case karakasa:
        {
            auto move = MoveTo::create(8, Vec2( getPositionX(), visibleSize.height * -0.1));
            auto remove = RemoveSelf::create();
            auto seq = Sequence::create(move, remove, NULL);
            auto spawn = Spawn::create(seq, scaleRepeat, NULL);
            runAction(spawn);
            break;
        }
        case ittan:
        {
            auto move = MoveTo::create(8, Vec2( getPositionX(), visibleSize.height * -0.1));
        
            // ジグザグ動作
            auto left = MoveBy::create(rand() % 2 + 2, Vec2( -visibleSize.width / 2, 0));
            auto right = MoveBy::create(rand() % 2 + 2, Vec2( visibleSize.width / 2, 0));
            auto widthSeq = Sequence::create(left, right, NULL);
            if( rand() % 2 )
            {
                widthSeq = Sequence::create(right, left, NULL);
            }
            auto repeat = Repeat::create(widthSeq, 6);

            auto spawn = Spawn::create(repeat, move, scaleRepeat, NULL);
            auto remove = RemoveSelf::create();
            auto seq = Sequence::create(spawn, remove, NULL);
            runAction(seq);
            break;
        }
        case nurikabe:
        {
            // 動いて止まるを繰り返す
            auto move = MoveBy::create(rand() % 2 + 2, Vec2( 0, -visibleSize.height / 4 + rand() % 50));
            auto delay = DelayTime::create(rand() % 3);
            auto moveDelay = Sequence::create(move, delay, NULL);
            auto repeat = Repeat::create(moveDelay, 4);

            auto remove = RemoveSelf::create();
            auto seq = Sequence::create(repeat, remove, NULL);
            auto spawn = Spawn::create(seq, scaleRepeat, NULL);
            runAction(spawn);
            break;
        }
        case medama:
        {
            auto delay = DelayTime::create(2.0f);
            auto move = MoveTo::create(3, Vec2( getPositionX(), visibleSize.height * -0.1));
            auto delayMove = Sequence::create(delay, move, NULL);
            auto remove = RemoveSelf::create();
            auto scale = ScaleBy::create(0, 0.1f);
            auto seq = Sequence::create(scale, delayMove, remove, NULL);
            auto spawn = Spawn::create(seq, scaleRepeat, NULL);
            runAction(spawn);
            break;
        }
        
        default:
        {
            auto move = MoveTo::create(10, Vec2( getPositionX(), visibleSize.height * -0.1));
            auto remove = RemoveSelf::create();
            auto seq = Sequence::create(move, remove, NULL);
            auto spawn = Spawn::create(seq, scaleRepeat, NULL);
            runAction(spawn);
        }
    }
}

void Enemy::setData()
{
    switch( _enemyType )
    {
        case karakasa:
            _life = 2;
            _score = 100;
            _state = State::move;
            break;
        case ittan:
            _life = 3;
            _score = 200;
            _state = State::move;
            break;
        case nurikabe:
            _life = 4;
            _score = 150;
            _state = State::move;
            break;
        case medama:
            _life = 1;
            _score = 250;
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

int Enemy::getEnemyType()
{
    return _enemyType;
}
