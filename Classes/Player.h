//
//  Player.h
//  SimpleGame
//
//  Created by takashi-fukui on 2014/09/23.
//
//

#ifndef __SimpleGame__Player__
#define __SimpleGame__Player__

#include <iostream>
#include <cocos2d.h>

USING_NS_CC;

class Player
{
private:
    Player();
    static Player* singleton;
    
    int     _life;
    
    Vector<Sprite *> vecWeponSprite;
    std::string weponImage;
    int     weponPower;
    int     weponMax;
    int     weponRest;

public:
    static Player*  getInstance();
    void    init(Layer *layer);
    bool    attack();
    void    reload();
    std::string getWeponImage();
    int     getWeponPower();
    
    void    addScore(int score);
};

#endif /* defined(__SimpleGame__Player__) */
