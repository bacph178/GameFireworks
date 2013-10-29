//
//  BeginScene.cpp
//  GameFireworks
//
//  Created by macbook_016 on 2013/10/29.
//
//

#include "BeginScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* BeginScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    BeginScene *layer = BeginScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool BeginScene::init() {
    if (!CCLayer::init()) {
        return false;
    }
    //menu
    //playItem
    CCMenuItemImage * playItem =
    CCMenuItemImage::create("play.png", "play.png",this,
                            menu_selector(BeginScene::menuPlay));
    playItem->setPosition(ccp(100, 100));
    //optionItem
    CCMenuItemImage * optionItem =
    CCMenuItemImage::create("option.png", "option.png", this,
                            menu_selector(BeginScene::menuOtion));
    optionItem->setPosition(ccp(100, 150));
    //high score
    CCMenuItemImage * highScoreItem =
    CCMenuItemImage::create("highscore.png", "highscore.png", this,
                            menu_selector(BeginScene::menuHighScore));
    highScoreItem->setPosition(ccp(100, 200));
    
    CCMenu * pMenu = CCMenu::create(playItem, optionItem, highScoreItem, NULL);
    this->addChild(pMenu, 1);
    return true;
}

void BeginScene::menuPlay(CCObject *pSender) {
    CCScene * scene = GamePlayScene::scene();
    CCDirector::sharedDirector()->replaceScene(scene);
}

void BeginScene::menuOtion(CCObject *pSender) {
}

void BeginScene::menuHighScore(CCObject * pSender) {
}