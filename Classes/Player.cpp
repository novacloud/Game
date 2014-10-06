//
//  Player.cpp
//  SimpleGame
//
//  Created by takashi-fukui on 2014/09/23.
//
//

#include "Player.h"

Player* Player::getInstance()
{
    static Player* singleton;
    return singleton;
}