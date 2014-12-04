//
//  TitleScene.cpp
//  SimpleGame
//
//  Created by 西川 祐司 on 2014/08/30.
//
//

#include "TitleScene.h"


USING_NS_CC;

Scene* TitleScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TitleScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // データベース初期化処理
    auto database = new DatabaseControl();
    database->init();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
//    auto spriteBackground = Sprite::create("title.jpg");
    auto spriteBackground = Sprite::create("main_2.png");
    spriteBackground->setPosition(Vec2(origin.x + visibleSize.width/2,
                                       origin.y + visibleSize.height/2));
    spriteBackground->setScale( 1.55f, 1.55f );
    this->addChild(spriteBackground, 0);
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(TitleScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithSystemFont("妖怪タッチ", "Ariel", 40);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2 - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
        
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    // タッチイベント　ラムダ式
    listener->onTouchBegan = [&](Touch* touch, Event* event) {
        
        // シーン移動
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameScene::createScene(), Color3B::WHITE));
        
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void TitleScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
