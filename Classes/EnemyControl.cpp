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
    for( int i = 0; i < 20; i++ )
    {
        auto enemyPopData = new EnemyPopData();
        
        enemyPopData->setPopTime(rand() % 60);
        enemyPopData->setEnemyType(Enemy::EnemyType(rand() % 3));
        enemyPopData->setPopFlag(false);
        
        vecEnemyPopData.push_back(enemyPopData);
    }
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