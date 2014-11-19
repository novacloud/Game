//
//  GameScene.h
//  SimpleGame
//
//  Created by takashi-fukui on 2014/09/23.
//
//

#ifndef __SimpleGame__GameScene__
#define __SimpleGame__GameScene__

#include "cocos2d.h"
#include "GameOverScene.h"
#include "Player.h"
#include "PopData.h"


enum kZOrder
{
    kZOrderBackground,
    kZOrderPlayer,
    kZOrderWepon,
    kZOrderEnemy,
    kZOrderItem
};

enum kTag
{
    kTagBackgound,
    kTagPlayer,
    kTagWepon,
    kTagEnemy,
    kTagItem
};


class GameScene : public cocos2d::Layer
{
private:
    int _score;
    
    
public:
    float _updateTime;
    PopData *popData;
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // schedul update
    void update(float delta);
    
    void createPopObject(float time);
    void addScore(int score);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif /* defined(__SimpleGame__GameScene__) */
