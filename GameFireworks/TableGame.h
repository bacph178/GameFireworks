//
//  TableGame.h
//  GameFireworks
//
//  Created by NgocDu on 13/10/25.
//
//

#ifndef GameFireworks_TableGame_h
#define GameFireworks_TableGame_h
#include "cocos2d.h"
using namespace cocos2d;
class TableGame : public CCObject
{
public:
    TableGame(int rows, int columns, CCPoint pOrigin, float w, float h);
private:
    CC_SYNTHESIZE(int, _rows, Rows);
    CC_SYNTHESIZE(int, _columns, Columns);
    CC_SYNTHESIZE(CCPoint, _pointOrigin, PointOrigin);
    CC_SYNTHESIZE(float, _width, Width);
    CC_SYNTHESIZE(float, _height, Height);
};
#endif
