//
//  GameOverScene.cpp
//  SimpleGame
//
//  Created by 西川 祐司 on 2014/08/30.
//
//

#include "GameOverScene.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto database = new DatabaseControl();
    if( database->open() )
    {
        database->selectRecord(&vecScoreRecord);
        database->close();
    }
    
    log("size = %zd", vecScoreRecord.size() );
    
    // TableView作成
    TableView* tableView = TableView::create(this, visibleSize);
    // 展開方向
    tableView->setDirection(TableView::Direction::VERTICAL);
    // 表示順序上からしたへ
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    // スクロール停止
    tableView->setTouchEnabled(false);
    
    // 追加
    tableView->setDelegate(this);
    addChild(tableView);
    tableView->reloadData();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameOverScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    // タッチイベント　ラムダ式
    listener->onTouchBegan = [&](Touch* touch, Event* event) {
        
        // シーン移動
        Director::getInstance()->replaceScene(TitleScene::createScene());
        
        return true;
    };
    
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}


// セルの大きさを設定する
Size GameOverScene::cellSizeForTable(TableView *table)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    return Size(visibleSize.width, visibleSize.height/10);
}

// 1セルに表示させるValueをセット
TableViewCell* GameOverScene::tableCellAtIndex(TableView* table, ssize_t idx)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    std::string rank;
    std::string score;
    
    rank = StringUtils::format("%zd 位", idx + 1);
    
    // データをセット
    if( idx < vecScoreRecord.size() )
    {
        score = StringUtils::format("%d 点", vecScoreRecord.at(idx));
    }
    else
    {
        score = std::string("No record");
    }
    
    TableViewCell *cell = table->dequeueCell();
    cell = new TableViewCell();
    cell->autorelease();
    
    // セル背景
    Sprite* bg = Sprite::create();
    bg->setAnchorPoint(Point(0, 0));
    bg->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height/10));
    bg->setColor(Color3B(255,255,255));
    cell->addChild(bg);
    
    // ボーダーライン
    Sprite* line = Sprite::create();
    line->setAnchorPoint(Point(0, 0));
    line->setTextureRect(Rect(0, 0, visibleSize.width, 1));
    line->setColor(Color3B(0,0,0));
    cell->addChild(line);
    
    // ID部分
    auto *label_1 = Label::createWithSystemFont(rank, "Ariel", 50);
    label_1->setAnchorPoint(Point(0, 0));
    label_1->setPosition(Point(visibleSize.width/5, 0));
    label_1->setColor(Color3B(0,0,0));
    cell->addChild(label_1);
    
    // スコア部分
    auto *label_2 = Label::createWithSystemFont(score, "Ariel", 50);
    label_2->setAnchorPoint(Point(0, 0));
    label_2->setPosition(Point(visibleSize.width/2, 0));
    label_2->setColor(Color3B(0,0,0));
    cell->addChild(label_2);
    
    return cell;
}

// セル数
ssize_t GameOverScene::numberOfCellsInTableView(TableView *table)
{
    return 10;
}

// セルがタッチされた時のcallback
void GameOverScene::tableCellTouched(TableView* table, TableViewCell* cell)
{
    log("%ziのセルがタッチされました", cell->getIdx());
}




void GameOverScene::menuCloseCallback(Ref* pSender)
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
