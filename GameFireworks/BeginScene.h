//
//  BeginScene.h
//  GameFireworks
//
//  Created by macbook_016 on 2013/10/29.
//
//

#ifndef __GameFireworks__BeginScene__
#define __GameFireworks__BeginScene__

#include <iostream>
#include "cocos2d.h"
#include "GamePlayScene.h"
class BeginScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuPlay(CCObject* pSender);
    void menuOtion(CCObject * pSender);
    void menuHighScore(CCObject * pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(BeginScene);
};

#endif /* defined(__GameFireworks__BeginScene__) */
