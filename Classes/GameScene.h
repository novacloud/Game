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
#include "Stage.h"

class GameScene : public cocos2d::Layer
{
public:
    float updateTime;
    Stage *stage;
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // schedul update
    void update(float delta);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif /* defined(__SimpleGame__GameScene__) */
