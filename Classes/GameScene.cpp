//
//  GameScene.cpp
//  SimpleGame
//
//  Created by takashi-fukui on 2014/09/23.
//
//

#include "GameScene.h"
#include "GameOverScene.h"

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
    
    updateTime = 0;

    // プレイヤー初期化
    auto player = Player::getInstance();
    player->init(this);
    
    
    // ステージを構成
    stage = new Stage();
    
    this->scheduleUpdate();
    
    return true;
}


void GameScene::update(float delta)
{
    updateTime += delta;
    //log("time = %f", updateTime);
    
    // POPオプジェクと作成
    stage->createPopObject(this, updateTime);
   
    // 
    if( updateTime > 60 )
    {
        Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, GameOverScene::createScene()));
    }
    
}
