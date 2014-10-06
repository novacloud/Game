//
//  Player.h
//  SimpleGame
//
//  Created by takashi-fukui on 2014/09/23.
//
//

#ifndef __SimpleGame__Player__
#define __SimpleGame__Player__

#include <cocos2d.h>

class Player
{
private:
    int     score;
    int     life;
    int     power;
    int     bulletMax;
    int     bulletRest;
    
    Player();

public:
    static Player* getInstance();
    void init();
    void reload();
};

#endif /* defined(__SimpleGame__Player__) */
