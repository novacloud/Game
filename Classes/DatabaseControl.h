//
//  DatabaseControl.h
//  SimpleGame
//
//  Created by takashi-fukui on 2014/11/22.
//
//

#ifndef __SimpleGame__DatabaseControl__
#define __SimpleGame__DatabaseControl__

#include "cocos2d.h"
#include "sqlite3.h"

USING_NS_CC;

class DatabaseControl
{
private:
    //sqlite3
    sqlite3* useDataBase = NULL;
    char* errorMessage = NULL;

public:
    DatabaseControl();
    void init();
    bool open();
    void close();
    void insertRecord(int score);
    void selectRecord(std::vector<int>* record);
};

#endif /* defined(__SimpleGame__DatabaseControl__) */
