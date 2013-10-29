//
//  Coin.h
//  GameFireworks
//
//  Created by MinhNT on 13/10/28.
//
//

#ifndef GameFireworks_Coin_h
#define GameFireworks_Coin_h

#include "cocos2d.h"
using namespace cocos2d;
class Coin : public CCSprite
{
public:
    Coin();
private:
    CC_SYNTHESIZE(int, _row, Row);
    CC_SYNTHESIZE(int, _column, Column);
    CC_SYNTHESIZE(float, _speed, Speed);
    CC_SYNTHESIZE(int *, _path, Path);
    CC_SYNTHESIZE(int , _numberPoint, NumberPoint);
};
#endif
