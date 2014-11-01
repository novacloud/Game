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
#include "PopData.h"

USING_NS_CC;

class Stage
{
private:
    PopData *popData;
    
public:
    Stage();
    void initStage();
    void createPopObject(Layer *layer, float time);
};

#endif /* defined(__SimpleGame__Stage__) */
