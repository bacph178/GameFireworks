//
//  Missile.h
//  GameFireworks
//
//  Created by MinhNT on 13/10/28.
//
//

#ifndef GameFireworks_Missile_h
#define GameFireworks_Missile_h

#include "cocos2d.h"
using namespace cocos2d;
class Missile : public CCSprite
{
public:
    Missile();
private:
    CC_SYNTHESIZE(int, _row, Row);
    CC_SYNTHESIZE(int, _column, Column);
    CC_SYNTHESIZE(float, _numberPath, NumberPath);
};
#endif
