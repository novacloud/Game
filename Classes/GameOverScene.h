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
#include "HelloWorldScene.h"

USING_NS_CC;

class GameOverScene : public cocos2d::Layer
{
public:
    LabelTTF *label;
    
    int score = 0;
    
    int moveX = 10;
    int moveY = 10;
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);
};


#endif /* defined(__SimpleGame__GameOverScene__) */
