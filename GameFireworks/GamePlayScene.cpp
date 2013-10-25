//
//  GamePlayScene.cpp
//  GameFireworks
//
//  Created by NgocDu on 13/10/25.
//
//

#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "Square.h"
using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GamePlayScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GamePlayScene *layer = GamePlayScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GamePlayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->setTouchEnabled(true);
    size = CCDirector::sharedDirector()->getWinSize();
    _arraySquare = new CCArray();
    this->addTableGame(4, 3);
   
    return true;
}
void GamePlayScene::addTableGame(int rows, int columns) {
    CCPoint pOrigin = CCPoint(-150, -100);
    float WithTable = size.width * 5 / 6;
    float HeightTable = size.height * 5 / 6;
    tableGame = new TableGame(rows, columns, pOrigin, WithTable, HeightTable);
    float with = tableGame->getWidth() / tableGame->getColumns() * 1.0f;
    float height = tableGame->getHeight() / tableGame->getRows() * 1.0f;
    int dem = 0;
    int k = 1;
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= columns; j++) {
            dem++;
            int category = rand() % 4;
            char tileName[7][20];
            strcpy(tileName[0], "Square1");
            strcpy(tileName[1], "Square2");
            strcpy(tileName[2], "Square3");
            strcpy(tileName[3], "Square4");
            char spriteName[100];
            sprintf(spriteName, "%s.png", tileName[category]);
            bool notContain = false;
            bool w = true;
            bool e = true;
            bool n = true;
            bool s = true;
            bool statPoint = true;
            bool destination = true;
            if (category == 0) {
                 w = true;
                 e = true;
                 n = false;
                 s = false;
            }else if(category == 1) {
                 w = false;
                 e = true;
                 n = true;
                 s = false;
            }else if(category == 2) {
                 w = true;
                 e = true;
                 n = true;
                 s = false;
            }else if(category == 3) {
                 w = true;
                 e = true;
                 n = true;
                 s = true;
            }

            if (dem == 1 + columns * (i - 1) && w == true) {
                statPoint = true;
            }else statPoint = false;
            if (dem == i * columns && e == true) {
                destination = true;
            }else destination = false;
            Square *sq = new  Square(notContain, w, e, n, s, i, j, statPoint, destination );
//            sq->setSelected(false);
            sq->initWithFile(spriteName);
            if (statPoint) {
                sq->setColor(ccc3(255, 0, 0));
            }else if (destination) sq->setColor(ccc3(255, 100, 100));
            float sx = with * 1.0f / sq->getContentSize().width;
            float sy = height * 1.0f / sq->getContentSize().height;
            sq->setScaleX(sx);
            sq->setScaleY(sy);
            CCPoint p = ccp(pOrigin.x + (j + 0.5f) * sq->getContentSize().width * sx,
                            pOrigin.y + (i + 0.5f) * sq->getContentSize().height * (sy));
            sq->setPosition(p);
//            sq->setPoint(p);
            
            _arraySquare->addObject(sq);
            this->addChild(sq, 1, dem);
            sq->setTag(dem);
            char strTime[20] = {0};
            sprintf(strTime, "%i, %i , %t-i", i, j, dem);
            CCLabelTTF *lable = CCLabelTTF::create(strTime, "Time New Roman", 13);
            lable->setPosition(p);
            this->addChild(lable, 10);
        }
    }

}
void GamePlayScene::ccTouchesBegan(cocos2d::CCSet * touch,cocos2d::CCEvent* event)
{
    this->loadMatrix();
    this->printMatrix();
//    if (tableGame->getArraySquare()->count()>=49)
    {

        CCTouch *touch1 = (CCTouch*)(touch->anyObject());
        CCPoint p2 = touch1->getLocationInView();
        touchLocation=CCDirector::sharedDirector()->convertToGL(p2);
        Square * sq1 = (Square*)_arraySquare->objectAtIndex(1);
        //        sq1->tinto_rotation();
        if (touchLocation.x >= tableGame->getPointOrigin().x + sq1->getContentSize().width / 2 &&
            touchLocation.x <= tableGame->getPointOrigin().x + tableGame->getWidth() + sq1->getContentSize().width &&
            touchLocation.y >= tableGame->getPointOrigin().y + sq1->getContentSize().height / 2 &&
            touchLocation.y <= tableGame->getPointOrigin().y + tableGame->getHeight()  + sq1->getContentSize().height) {
            
            int H = (int)(tableGame->getHeight() / tableGame->getRows());
            int W = (int)(tableGame->getWidth() / tableGame->getColumns());
            int px = (int)(tableGame->getPointOrigin().x +  sq1->getContentSize().width * sq1->getScaleX());
            int py = (int)(tableGame->getPointOrigin().y +  sq1->getContentSize().height * sq1->getScaleY());
            int col = (int)((touchLocation.x - px) / W ) + 1;
            int row = (int)((touchLocation.y - py) / H ) + 1;
            int tag = (row - 1) * tableGame->getColumns() + col;
            
            if (this->getChildByTag(tag) != NULL) {
                Square * sqSelected1 = (Square*)this->getChildByTag(tag);
//                CCSprite * sp = CCSprite::create("Icon.png");
//                sp->setScale(0.5f);
//                sp->setPosition(sqSelected1->getPosition());
//                this->addChild(sp, 10);
                CCRotateTo * rotate = CCRotateTo::create(0.0f, sqSelected1->getRotation() + 90);
                sqSelected1->runAction(rotate);
            }
        }
    }
}
void GamePlayScene::ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event) {
//    if (sqSelected)
    {
        
        CCTouch *touch = (CCTouch*)touches->anyObject();
        CCPoint p2 = touch->getLocationInView();
        CCPoint touchpoint = CCDirector::sharedDirector()->convertToGL(p2);
        
        Square * sq1 = (Square*)_arraySquare->objectAtIndex(1);
        if (touchpoint.x >= tableGame->getPointOrigin().x + sq1->getContentSize().width / 2 &&
            touchpoint.x <= tableGame->getPointOrigin().x + tableGame->getWidth() + sq1->getContentSize().width &&
            touchpoint.y >= tableGame->getPointOrigin().y + sq1->getContentSize().height / 2 &&
            touchpoint.y <= tableGame->getPointOrigin().y + tableGame->getHeight()  + sq1->getContentSize().height) {
            int H = (int)(tableGame->getHeight() / tableGame->getRows());
            int W = (int)(tableGame->getWidth() / tableGame->getColumns());
            int px = (int)(tableGame->getPointOrigin().x +  sq1->getContentSize().width * sq1->getScaleX());
            int py = (int)(tableGame->getPointOrigin().y +  sq1->getContentSize().height * sq1->getScaleY());
            int col = (int)((touchpoint.x - px) / W ) + 1;
            int row = (int)((touchpoint.y - py) / H ) + 1;
            int tag = (row - 1) * tableGame->getColumns() + col;
            if (this->getChildByTag(tag) != NULL) {
                Square * sqSelected1 = (Square*)this->getChildByTag(tag);
                if (!sqSelected1->getIsMoveTouch()) {
                    //                CCSprite * sp = CCSprite::create("Icon.png");
                    //                sp->setScale(0.5f);
                    //                sp->setPosition(sqSelected1->getPosition());
                    //                this->addChild(sp, 10);
                    
                    CCRotateTo * rotate = CCRotateTo::create(0.0f, sqSelected1->getRotation() + 90);
                    sqSelected1->runAction(rotate);
                }
            }
        }
    }
}
void GamePlayScene::ccTouchesEnded(cocos2d::CCSet* touches,cocos2d::CCEvent* event)
{
    CCObject * i;
    CCARRAY_FOREACH(_arraySquare, i) {
        Square * sq = (Square*)i;
        sq->setIsMoveTouch(false);
    }
    //    this->schedule(schedule_selector(GamePlay::update), 1/50);
//    if (touchmove == false) {
//        CCTouch *touch1 = (CCTouch*)(touches->anyObject());
//        CCPoint p2 = touch1->getLocationInView();
//        CCPoint touchpoint = CCDirector::sharedDirector()->convertToGL(p2);
//        int k1 = 0;
//        int k2 = 0;
//        if (sqSelected != NULL && sqSelected2 != NULL && sqSelected->getSelected() == true &&
//            sqSelected2->getSelected() == true) {
//            int c = asb(sqSelected->getCol() - sqSelected2->getCol());
//            int r = asb(sqSelected2->getRow() - sqSelected->getRow());
//            if (c == 1 && r == 0) {
//                if (sqSelected->getCol() - sqSelected2->getCol() == -1) {
//                    sqSelected->moveTop();
//                    sqSelected2->moveDown();
//                    directionMoveSqSelected = 2;
//                    k1 = 2;
//                    k2 = 1;
//                }else if (sqSelected->getCol() - sqSelected2->getCol() == 1) {
//                    sqSelected2->moveTop();
//                    sqSelected->moveDown();
//                    directionMoveSqSelected = 1;
//                    k1 = 1;
//                    k2 = 2;
//                }
//            }else if(r == 1 && c == 0) {
//                if (sqSelected2->getRow() - sqSelected->getRow() == -1) {
//                    sqSelected2->moveRight();
//                    sqSelected->moveLeft();
//                    directionMoveSqSelected = 4;
//                    k1 = 3;
//                    k2 = 4;
//                }else if (sqSelected2->getRow() - sqSelected->getRow() == 1) {
//                    sqSelected->moveRight();
//                    sqSelected2->moveLeft();
//                    directionMoveSqSelected = 3;
//                    k1 = 4;
//                    k2 = 3;
//                }
//            }
//            if (this->checkSquareMove(sqSelected) == false && this->checkSquareMove(sqSelected2) == false) {
//                switch (k1) {
//                    case 1:
//                        sqSelected->moveTop();
//                        break;
//                    case 2:
//                        sqSelected->moveDown();
//                        break;
//                    case 3:
//                        sqSelected->moveRight();
//                        break;
//                    case 4:
//                        sqSelected->moveLeft();
//                        break;
//                    default:
//                        break;
//                }
//                switch (k2) {
//                    case 1:
//                        sqSelected2->moveTop();
//                        break;
//                    case 2:
//                        sqSelected2->moveDown();
//                        break;
//                    case 3:
//                        sqSelected2->moveRight();
//                        break;
//                    case 4:
//                        sqSelected2->moveLeft();
//                        break;
//                    default:
//                        break;
//                }
//            }
//            sqSelected2 = NULL;
//            sqSelected = NULL;
//            CCObject *i;
//            CCARRAY_FOREACH(tableGame->getArraySquare(), i) {
//                Square * sq = (Square*) i;
//                if (sq->getSelected() == true) {
//                    sq->setSelected(false);
//                    sq->removeAllChildren();
//                }
//            }
//        }
//    }
//    else if (touchmove == true) {
//        sqSelected = NULL;
//        sqSelected2 = NULL;
//    }
}
void GamePlayScene::loadMatrix() {
    if (_arraySquare->count() >= tableGame->getColumns() * tableGame->getRows()) {
        for (int i = 1; i <= tableGame->getColumns() * tableGame->getRows(); i++) {
            if (this->getChildByTag(i) ) {
                 Square *sq = (Square*)this->getChildByTag(i);
                // i + 1
                if (i + 1 <= tableGame->getColumns() * tableGame->getRows() &&
                    sq->getColumn() != tableGame->getColumns()) {
                    if (this->getChildByTag(i + 1) ) {
                        Square *sq1 = (Square*)this->getChildByTag(i + 1);
                        if (sq->getEast() && sq1->getWest()) {
                            matran[i][i+1] = 1;
                        }else matran[i][i+1] = -1;
                    }
                }
                                
                // i - 1
                if (i - 1 > 0 && sq->getColumn() != 1) {
                    if (this->getChildByTag(i - 1) ) {
                        Square *sq1 = (Square*)this->getChildByTag(i - 1);
                        if (sq1->getEast() && sq->getWest()) {
                            matran[i][i-1] = 1;
                        }else matran[i][i-1] = -1;
                    }
                }
                
                // i + columns
                if (i + tableGame->getColumns() <= tableGame->getColumns() * tableGame->getRows() &&
                    sq->getRow() != tableGame->getRows()) {
                    if (this->getChildByTag(i + tableGame->getColumns()) ) {
                        Square *sq1 = (Square*)this->getChildByTag(i + tableGame->getColumns());
                        if (sq1->getSouth() && sq->getNorth()) {
                            matran[i][i + tableGame->getColumns()] = 1;
                        }else matran[i][i + tableGame->getColumns()] = -1;
                    }
                }
                // i - columns
                if (i - tableGame->getColumns() > 0 && sq->getRow() != 1) {
                    if (this->getChildByTag(i - tableGame->getColumns()) ) {
                        Square *sq1 = (Square*)this->getChildByTag(i - tableGame->getColumns());
                        if (sq->getSouth() && sq1->getNorth()) {
                            matran[i][i - tableGame->getColumns()] = 1;
                        }else matran[i][i - tableGame->getColumns()] = -1;
                    }
                } 
            }
        }
    }
}
void GamePlayScene::changeMatrix(Square *sq) {
    int i = sq->getTag();
    // i + 1
    if (i + 1 <= tableGame->getColumns() * tableGame->getRows() &&
        sq->getColumn() != tableGame->getColumns()) {
        if (this->getChildByTag(i + 1)) {
            Square *sq1 = (Square*)this->getChildByTag(i + 1);
            if (sq->getEast() && sq1->getWest()) {
                matran[i][i+1] = 1;
                matran[i+1][i] = 1;
            }else {
                matran[i][i+1] = -1;
                matran[i+1][i] = -1;
            }
        }
    }
    // i - 1
    if (i - 1 > 0 && sq->getColumn() != 1) {
        if (this->getChildByTag(i - 1)) {
            Square *sq1 = (Square*)this->getChildByTag(i - 1);
            if (sq1->getEast() && sq->getWest()) {
                matran[i][i-1] = 1;
                matran[i-1][i] = 1;
            }else {
                matran[i-1][i] = -1;
                matran[i][i-1] = -1;
            }
        }
    }
    // i + columns
    if (i + tableGame->getColumns() <= tableGame->getColumns() * tableGame->getRows() &&
        sq->getRow() != tableGame->getRows()) {
        if (this->getChildByTag(i + tableGame->getColumns()) != NULL) {
            Square *sq1 = (Square*)this->getChildByTag(i + tableGame->getColumns());
            if (sq1->getSouth() && sq->getNorth()) {
                matran[i][i + tableGame->getColumns()] = 1;
                matran[i + tableGame->getColumns()][i] = 1;
            }else {
                matran[i][i + tableGame->getColumns()] = -1;
                matran[i + tableGame->getColumns()][i] = -1;
            }
        }

    }
    // i - columns
    if (i - tableGame->getColumns() > 0 && sq->getRow() != 1) {
        if (this->getChildByTag(i - tableGame->getColumns()) != NULL) {
            Square *sq1 = (Square*)this->getChildByTag(i - tableGame->getColumns());
            if (sq->getSouth() && sq1->getNorth()) {
                matran[i][i - tableGame->getColumns()] = 1;
                matran[i- tableGame->getColumns()][i] = 1;
            }else {
                matran[i][i - tableGame->getColumns()] = -1;
                matran[i- tableGame->getColumns()][i] = -1;
            }
        }
    }
}
void GamePlayScene::printMatrix() {
    for (int i = 1; i <= tableGame->getColumns() * tableGame->getRows() ; i++) {
        for (int j = 1; j <= tableGame->getColumns() * tableGame->getRows() ; j++) {
            printf("%i  ", matran[i][j]);
        }
        printf("\n");
    }
}