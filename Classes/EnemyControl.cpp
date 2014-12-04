//
//  EnemyControl.cpp
//  SimpleGame
//
//  Created by takashi-fukui on 2014/11/20.
//
//

#include "EnemyControl.h"

USING_NS_CC;

EnemyControl::EnemyControl()
{
}

void EnemyControl::init()
{
    enemyNum = 5;
    enemyPattern = 1;
    makeEnemy();
}

Enemy* EnemyControl::popEnemy(float time)
{
    for( int i = 0; i < vecEnemyPopData.size(); i++)
    {
        auto enemyPopData = vecEnemyPopData.at(i);
        
        if( enemyPopData->getPopFlag() )
            continue;
        
        if( time > enemyPopData->getPopTime() )
        {
            // 敵POP
            auto enemy = Enemy::create( enemyPopData->getEnemyType() );
            if( enemy )
            {
                enemy->setScale(0.7); // 一時対応、画像サイズ考える
            }
                
            enemyPopData->setPopFlag(true);
            
            return enemy;
        }
    }
    
    return NULL;
}

void EnemyControl::makeEnemy()
{
    srand((unsigned int)time(NULL));
    for( int i = 0; i < enemyNum; i++ )
    {
        auto enemyPopData = new EnemyPopData();
        
        enemyPopData->setPopTime(rand() % 20);
        enemyPopData->setEnemyType(Enemy::EnemyType(rand() % enemyPattern));
        enemyPopData->setPopFlag(false);
        
        vecEnemyPopData.push_back(enemyPopData);
    }
   
}

void EnemyControl::updateEnemyPattern()
{
    log("pattern = %d", enemyPattern);
    enemyPattern++;
    makeEnemy();
}