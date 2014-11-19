//
//  GameScene.cpp
//  SimpleGame
//
//  Created by takashi-fukui on 2014/09/23.
//
//

#include "GameScene.h"
#include "GameOverScene.h"
#include "Enemy.h"
#include "Wepon.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto _bg = LayerColor::create(Color4B::WHITE, visibleSize.width, visibleSize.height);
    this->addChild(_bg, 0);
    
    // 背景
    auto spriteBackground = Sprite::create("background.png");
    spriteBackground->setPosition(Vec2(origin.x + visibleSize.width/2,
                                       origin.y + visibleSize.height/2));
    this->addChild(spriteBackground, kZOrderBackground, kTagBackgound);
    
    // スコア
    scoreLabel = LabelTTF::create("0", "Arial", 40);
    scoreLabel->setColor(Color3B::BLACK);
    scoreLabel->setPosition(Vec2(visibleSize.width - 50, visibleSize.height - 50));
    this->addChild(scoreLabel, kZOrderScore, kTagScore);
    
    // ステージを構成
    popData = new PopData();

    // プレイヤー初期化
    auto player = Player::getInstance();
    player->init(this);
    
    
    // タッチイベントの登録
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        auto player = Player::getInstance();
        
        if( player->attack() )
        {
            // 攻撃モーション
            auto location = touch->getLocation();
            auto wepon = Wepon::create(Wepon::weponType1, location);
            if( wepon )
            {
                this->addChild(wepon, kZOrderWepon, kTagWepon);
            }
            
            return true;
        }
        
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    _score = 0;
    _updateTime = 0;
    this->scheduleUpdate();
    
    return true;
}


void GameScene::update(float delta)
{
    _updateTime += delta;
    //log("time = %f", updateTime);
    
    // POP OBJECT作成
    createPopObject(_updateTime);
    
    
    // Object動作
    Vector<Node*> children = getChildren();
    Vector<Node*> enemies;
    Vector<Node*> wepons;
    
    for( auto child: children )
    {
        switch (child->getTag())
        {
            case kTagEnemy: enemies.pushBack(child); break;
            case kTagWepon: wepons.pushBack(child); break;
            default:break;
        }
    }
    
    
    // 当たり判定
    for( auto nodeEnemy: enemies )
    {
        auto enemy = (Enemy*)nodeEnemy;
        auto enemyRect = enemy->getBoundingBox();
        
        if( enemy->getState() == Enemy::State::dead )
            continue;
        
        for( auto nodeWepon: wepons )
        {
            auto wepon = (Wepon*)nodeWepon;
            auto weponRect = wepon->getBoundingBox();
            
            if( wepon->getState() == Wepon::State::hit )
                continue;
            
            if( enemyRect.intersectsRect(weponRect))
            {
                // 攻撃が当たった
                enemy->damage( wepon->getPower() );
                wepon->hit();
                
                if( enemy->getState() == Enemy::State::dead )
                    addScore( enemy->getScore() );
            }
        }
    }
    
   
    // 強制終了
    if( _updateTime > 60 )
    {
        Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, GameOverScene::createScene()));
    }
    
}


void GameScene::createPopObject(float time)
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
                auto enemy = Enemy::create( Enemy::enemyType1 );
                if( enemy )
                {
                    this->addChild(enemy, kZOrderEnemy, kTagEnemy);
                }
                
                popData->setPopFlagTrue(i);
            }
        }
    }
}



void GameScene::addScore(int score)
{
    _score += score;
    
    std::string strScore = std::to_string(_score);
    scoreLabel->setString(strScore);
}