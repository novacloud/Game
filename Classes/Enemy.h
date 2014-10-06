//
//  Enemy.h
//  SimpleGame
//
//  Created by takashi-fukui on 2014/09/20.
//
//

#ifndef __SimpleGame__Enemy__
#define __SimpleGame__Enemy__

#include <cocos2d.h>

class Enemy
{
private:
    int     life;
    std::string imageFileName;
    
public:
    /** コンストラクタ */
    Enemy();
    
    /** ファイル名取得 */
    std::string getImageFileName();
    
    /** アクションの登録 */
    void registAction(cocos2d::Sprite *sprite);
    
    /** タッチイベント登録 */
    void touchEvent();
    
private:
    
};

#endif /* defined(__SimpleGame__Enemy__) */
