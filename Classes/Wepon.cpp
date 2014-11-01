//
//  Wepon.cpp
//  SimpleGame
//
//  Created by takashi-fukui on 2014/11/01.
//
//

#include "Wepon.h"

Wepon::Wepon()
{
    power = 1;
    max = 5;
}

int Wepon::getPower()
{
    return power;
}

int Wepon::getMax()
{
    return max;
}