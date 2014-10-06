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
    
    updateTime = 0;
    
    auto spriteReload = Sprite::create("haka.png");
    spriteReload->setPosition(Vec2(100, 200));
    
    this->addChild(spriteReload);
    /*
    // プレイヤー初期化
    auto player = Player::getInstance();
    player->init();
    */
    // ステージを構成
    stage = new Stage();
    
    this->scheduleUpdate();
    
    return true;
}


void GameScene::update(float delta)
{
    updateTime += delta;
    log("time = %f", updateTime);
    
    stage->makeEnemy(updateTime);
    
    Sprite *spriteEnemy;
    
    while( (spriteEnemy = stage->getNewEnemySprite()) != NULL )
        this->addChild(spriteEnemy);
    
    if( updateTime > 30 )
    {
        Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, GameOverScene::createScene()));
    }
    
}
