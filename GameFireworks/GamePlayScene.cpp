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
#include <stdio.h>
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
    srandom(time(NULL));
    
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->setTouchEnabled(true);
    size = CCDirector::sharedDirector()->getWinSize();
    _arraySquare = new CCArray();
    _arrayRemove = new CCArray();
    _numberPath = 0;
    
    this->addTableGame(9, 6);
    this->loadMatrix();
//    this->printMatrix();
    this->checkTableGame();

    this->addCoins();
    this->addMissiles();
    
    return true;
}
void GamePlayScene::addTableGame(int rows, int columns) {
    CCPoint pOrigin = CCPoint(- size.width / 20, 0);
    float WithTable = size.width * 5 / 7;
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
void GamePlayScene::addCoins() {
    for (int i = 1; i <= tableGame->getRows(); i++) {
        Coin *coin = new Coin();
        coin->initWithFile("Icon.png");
        coin->setScale(0.5f);
        Square * sq = (Square*)this->getChildByTag(1 + tableGame->getColumns() * (i - 1));
        CCPoint p = CCPoint(sq->getPosition().x - sq->getContentSize().width * sq->getScaleX(), sq->getPosition().y);
        coin->setPosition(p);
        coin->setTag(100 + i);
        this->addChild(coin, 10);
    }
}
void GamePlayScene::addCoin(int row, float speed) {
    
}
void GamePlayScene::addMissiles() {
    for (int i = 1; i <= tableGame->getRows(); i++) {
        Missile *missile = new Missile();
        missile->initWithFile("Icon.png");
        missile->setScale(0.5f);
        missile->setColor(ccc3(255, 0, 0));
        Square * sq = (Square*)this->getChildByTag(tableGame->getColumns() * i);
        CCPoint p = CCPoint(sq->getPosition().x + sq->getContentSize().width * sq->getScaleX(), sq->getPosition().y);
        missile->setPosition(p);
        missile->setTag(200 + i);
        this->addChild(missile, 10);
    }
}
void GamePlayScene::ccTouchesBegan(cocos2d::CCSet * touch,cocos2d::CCEvent* event)
{
   
//    if (tableGame->getArraySquare()->count()>=49)
    {

        CCTouch *touch1 = (CCTouch*)(touch->anyObject());
        CCPoint p2 = touch1->getLocationInView();
        touchLocation=CCDirector::sharedDirector()->convertToGL(p2);
        Square * sq1 = (Square*)_arraySquare->objectAtIndex(1);
        //        sq1->tinto_rotation();
//        if (touchLocation.x >= tableGame->getPointOrigin().x + sq1->getContentSize().width / 2 &&
//            touchLocation.x <= tableGame->getPointOrigin().x + tableGame->getWidth() + sq1->getContentSize().width &&
//            touchLocation.y >= tableGame->getPointOrigin().y + sq1->getContentSize().height / 2 &&
//            touchLocation.y <= tableGame->getPointOrigin().y + tableGame->getHeight()  + sq1->getContentSize().height) {
//            
//            int H = (int)(tableGame->getHeight() / tableGame->getRows());
//            int W = (int)(tableGame->getWidth() / tableGame->getColumns());
//            int px = (int)(tableGame->getPointOrigin().x +  sq1->getContentSize().width * sq1->getScaleX());
//            int py = (int)(tableGame->getPointOrigin().y +  sq1->getContentSize().height * sq1->getScaleY());
//            int col = (int)((touchLocation.x - px) / W ) + 1;
//            int row = (int)((touchLocation.y - py) / H ) + 1;
//            int tag = (row - 1) * tableGame->getColumns() + col;
//            
//            if (this->getChildByTag(tag) != NULL) {
//                Square * sqSelected1 = (Square*)this->getChildByTag(tag);
////                CCSprite * sp = CCSprite::create("Icon.png");
////                sp->setScale(0.5f);
////                sp->setPosition(sqSelected1->getPosition());
////                this->addChild(sp, 10);
////                CCRotateTo * rotate = CCRotateTo::create(0.0f, sqSelected1->getRotation() + 90);
////                sqSelected1->runAction(rotate);
//                sqSelected1->changeRotation(tableGame->getColumns());
////                this->loadMatrix();
//                this->changeMatrix(sqSelected1);
//               
////                this->backTracking(5);
////                this->backTracking(8);
////                this->backTracking(11);
////                daxet[1] = 1;
////                pa[1] = 1;
////                c = 0;
////                this->backTracking(2);
////                this->printMatrix();
//                this->checkTableGame();
//            }
//        }
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
                    
//                    CCRotateTo * rotate = CCRotateTo::create(0.0f, sqSelected1->getRotation() + 90);
//                    sqSelected1->runAction(rotate);
                    sqSelected1->changeRotation(tableGame->getColumns());
//                    this->changeMatrix(sqSelected1);
//                    this->loadMatrix();
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
    Square * sq1 = (Square*)_arraySquare->objectAtIndex(1);
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
            //                CCRotateTo * rotate = CCRotateTo::create(0.0f, sqSelected1->getRotation() + 90);
            //                sqSelected1->runAction(rotate);
            sqSelected1->changeRotation(tableGame->getColumns());
            this->loadMatrix();
//            this->changeMatrix(sqSelected1);
            
            //                this->backTracking(5);
            //                this->backTracking(8);
            //                this->backTracking(11);
            //                daxet[1] = 1;
            //                pa[1] = 1;
            //                c = 0;
            //                this->backTracking(2);
            //                this->printMatrix();
            this->checkTableGame();
        }
    }
}
void GamePlayScene::checkTableGame() {
    for (int i = 1; i <= tableGame->getRows(); i ++) {
        int k = 1 + (i - 1) * tableGame->getColumns() ;
        Square * sq = (Square*)this->getChildByTag(k);
        if (sq->getStartPoint() == true)
        {
            pa[1] = k;
            daxet[pa[1]] = 1;
            c = 0;
            //            this->loadMatrix();
            for (int j = 1; j <= tableGame->getRows(); j ++) {
                Square * sqTaget = (Square*)this->getChildByTag(j * tableGame->getColumns());
                if (sqTaget->getDestination()) {
                    this->backTrackingNew(2, sqTaget);
                    
                }
            }            
        }
    }
    
    this->printMatrix(arrayPath, _numberPath, 25);
    _numberPath = 0;
    this->resetArrayTow(arrayPath);
}
void GamePlayScene::backTracking(int i) {
    int n = tableGame->getRows() * tableGame->getColumns();
    for(int j=2; j<=n; j++)
        if(daxet[j] != 1 && matran[pa[i-1]][j] == 1)
        {
            pa[i] = j;
            daxet[j] = 1;
            c += matran[pa[i-1]][j];
            Square * sq = (Square*)this->getChildByTag(j);
            if(sq->getDestination() == true)
            {
//                sq->setDestination(false);
//                if(matran[pa[n]][1])
                {
//                    chiphi = c;
//                    chiphi += matran[pa[n]][1];
//                    pa[n+1] = 1;
//                    InPa();
                    _numberPath ++;
                    this->addArrayInArray(arrayPath, pa, _numberPath, i);
//                    for (int k = 1; k < 20; k++) {
//                        printf("%i   ", pa[k]);
//                    }
//                    printf("\n so dinh cua duong di :%i", i);
//                    this->resetArray(pa); // them dong nay vao la khong tim duoc het phuong an
                }
            }else backTracking(i+1);
            
            daxet[j] = 0;
            c -= matran[pa[i-1]][j];
        }
}
void GamePlayScene::backTrackingNew(int i, Square * sqTaget) {
    int n = tableGame->getRows() * tableGame->getColumns();
    for(int j=2; j<=n; j++)
        if(daxet[j] != 1 && matran[pa[i-1]][j] == 1)
        {
            
            pa[i] = j;
            daxet[j] = 1;
            c += matran[pa[i-1]][j];
            if(sqTaget->getTag() == j)
            {
                _numberPath ++;
                this->addArrayInArray(arrayPath, pa, _numberPath, i);
            }else backTrackingNew(i+1, sqTaget);
            
            daxet[j] = 0;
            c -= matran[pa[i-1]][j];
        }
}
void GamePlayScene::loadStartPointAndDestination() {
    int dS = 0;
    int dD = 0;
    CCObject *i;
    CCARRAY_FOREACH(_arraySquare, i) {
        Square * sq = (Square*)i;
        if (sq->getStartPoint()) {
            dS ++ ;
            arrayStart[dS] = sq->getTag();
        }
        if (sq->getDestination()) {
            dD ++;
            arrarDestination[dD] = sq->getTag();
        }
    }
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
                        }else matran[i][i+1] = 0;
                    }
                }
                                
                // i - 1
                if (i - 1 > 0 && sq->getColumn() != 1) {
                    if (this->getChildByTag(i - 1) ) {
                        Square *sq1 = (Square*)this->getChildByTag(i - 1);
                        if (sq1->getEast() && sq->getWest()) {
                            matran[i][i-1] = 1;
                        }else matran[i][i-1] = 0;
                    }
                }
                
                // i + columns
                if (i + tableGame->getColumns() <= tableGame->getColumns() * tableGame->getRows() &&
                    sq->getRow() != tableGame->getRows()) {
                    if (this->getChildByTag(i + tableGame->getColumns()) ) {
                        Square *sq1 = (Square*)this->getChildByTag(i + tableGame->getColumns());
                        if (sq1->getSouth() && sq->getNorth()) {
                            matran[i][i + tableGame->getColumns()] = 1;
                        }else matran[i][i + tableGame->getColumns()] = 0;
                    }
                }
                // i - columns
                if (i - tableGame->getColumns() > 0 && sq->getRow() != 1) {
                    if (this->getChildByTag(i - tableGame->getColumns()) ) {
                        Square *sq1 = (Square*)this->getChildByTag(i - tableGame->getColumns());
                        if (sq->getSouth() && sq1->getNorth()) {
                            matran[i][i - tableGame->getColumns()] = 1;
                        }else matran[i][i - tableGame->getColumns()] = 0;
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
                matran[i][i+1] = 0;
                matran[i+1][i] = 0;
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
                matran[i-1][i] = 0;
                matran[i][i-1] = 0;
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
                matran[i][i + tableGame->getColumns()] = 0;
                matran[i + tableGame->getColumns()][i] = 0;
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
                matran[i][i - tableGame->getColumns()] = 0;
                matran[i- tableGame->getColumns()][i] = 0;
            }
        }
    }
}
void GamePlayScene::printMatrix(int (*matran)[100], int row, int column) {
    for (int i = 1; i <= row ; i++) {
        for (int j = 1; j <= column ; j++) {
            printf("%i  ", matran[i][j]);
        }
        printf("\n");
    }
}
void GamePlayScene::InPa()
{
    CCLOG("kjnkjkjkjkjkjkkjjjjjj");
}
void GamePlayScene::resetArray(int a[]) {
    for (int i = 0; i < max; i++) {
        a[i] = 0;
    }
}
void GamePlayScene::resetArrayTow(int (*a)[100]) {
    for (int i = 0; i < 20; i ++) {
        for (int j = 0; j < 50; j++) {
            a[i][j] = 0;
        }
    }
}
void GamePlayScene::addArrayInArray(int (*arrayPaths)[100], int *arrayPath, int row, int sizeArray) {
    for (int i = 1; i <= sizeArray; i ++) {
        arrayPaths[row][i] = arrayPath[i];
//        Square * sq = (Square*)this->getChildByTag(arrayPath[i]);
//        if (sq->getDestination()) {
//            this->addCoins();
//            break;
//        }
    }
}