//
//  Stage.h
//  SimpleGame
//
//  Created by takashi-fukui on 2014/09/23.
//
//

#ifndef __SimpleGame__Stage__
#define __SimpleGame__Stage__

#include <cocos2d.h>

class Stage
{
private:
    cocos2d::Vector<cocos2d::Sprite *> vecSpriteEnemy;
    int enemyPopupTime = 3;
    int enemyPopupX = 500;
    int enemyPopupY = 800;
    int enemyPopFlag = 0;
    
public:
    Stage();
    
    void makeEnemy(float time);
    cocos2d::Sprite* getNewEnemySprite();
};

#endif /* defined(__SimpleGame__Stage__) */
