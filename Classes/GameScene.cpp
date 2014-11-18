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
    
    auto spriteBackground = Sprite::create("background.png");
    spriteBackground->setPosition(Vec2(origin.x + visibleSize.width/2,
                                       origin.y + visibleSize.height/2));
    this->addChild(spriteBackground, 0);
    
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
    
    updateTime = 0;
    this->scheduleUpdate();
    
    return true;
}


void GameScene::update(float delta)
{
    updateTime += delta;
    //log("time = %f", updateTime);
    
    // POP OBJECT作成
    createPopObject(updateTime);
    
    
    // Object動作
    Vector<Node*> children = getChildren();
    
    for( auto child: children )
    {
        if( child->getTag() == kTagEnemy )
        {
            
        }
        
        if( child->getTag() == kTagWepon )
        {
            
        }
    }
   
    // 
    if( updateTime > 60 )
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
