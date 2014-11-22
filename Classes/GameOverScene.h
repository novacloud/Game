//
//  GameOverScene.h
//  SimpleGame
//
//  Created by 西川 祐司 on 2014/08/30.
//
//

#ifndef __SimpleGame__GameOverScene__
#define __SimpleGame__GameOverScene__

#include "cocos2d.h"
#include "TitleScene.h"
#include <extensions/cocos-ext.h>

USING_NS_CC;
using namespace extension;

class GameOverScene : public cocos2d::Layer, public TableViewDataSource, public TableViewDelegate
{
public:
    std::vector<int> vecScoreRecord;
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    //TableViewDataSourceの抽象メソッド
    virtual Size cellSizeForTable(TableView* table);
    virtual TableViewCell* tableCellAtIndex(TableView* table,ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    //TableViewDelegateの抽象メソッド
    virtual void tableCellTouched(TableView* table,TableViewCell* cell);
    
    //TableViewDelegateが継承しているScrollViewの抽象メソッド
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view){};
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);
};


#endif /* defined(__SimpleGame__GameOverScene__) */
