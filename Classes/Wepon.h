//
//  Wepon.h
//  SimpleGame
//
//  Created by takashi-fukui on 2014/11/01.
//
//

#ifndef __SimpleGame__Wepon__
#define __SimpleGame__Wepon__

#include <cocos2d.h>

USING_NS_CC;

class Wepon{
private:
    int     power;
    int     max;
    
public:
    Wepon();
    int     getPower();
    int     getMax();
};

#endif /* defined(__SimpleGame__Wepon__) */
