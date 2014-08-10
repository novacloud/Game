#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
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
    
    label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
    
    
    sprite = Sprite::create("target.jpg");
    
    //位置を設定
    sprite->setPosition(Vec2(100,100));

    // add the sprite as a child to this layer
    this->addChild(sprite);
    
    this->schedule(schedule_selector(HelloWorld::move));
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    // タッチイベント　ラムダ式
    listener->onTouchBegan = [&](Touch* touch, Event* event) {
        
        Point point = touch->getLocation();
        
        float width = sprite->getContentSize().width;
        float height = sprite->getContentSize().height;
        
        auto rect = Rect(sprite->getPositionX() - width/2, sprite->getPositionY() - height/2, width, height );
        
        // クリックエリアをチェックする。
        if (rect.containsPoint(point))
        {
            score += 100;
            std::string str = StringUtils::format("%i", score);
            
            label->setString(str);
        }

        
        return true;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite);
    
    return true;
}


void HelloWorld::move(float delta)
{
    //これが連続することで、なめらかに動いているように見えます。
    sprite->setPosition(Point(sprite->getPositionX() + moveX, sprite->getPositionY() + moveY));
    
    if(sprite->getPositionX() < 0) {
        moveX = -moveX;
    }
    
    if(sprite->getPositionX() > 1136) {
        moveX = -moveX;
    }
    
    if(sprite->getPositionY() < 0) {
        moveY = -moveY;
    }
    
    if(sprite->getPositionY() > 640) {
        moveY = -moveY;
    }
    
    
}


void HelloWorld::menuCloseCallback(Ref* pSender)
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
