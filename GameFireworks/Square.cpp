//
//  Square.cpp
//  GameFireworks
//
//  Created by NgocDu on 13/10/25.
//
//

#include "Square.h"
Square::Square()
{
    
}
Square::Square(bool notContain, bool w, bool e, bool n, bool s, int row, int column,
               bool statPoint, bool destination) {
    this->setNotContain(notContain);
    this->setWest(w);
    this->setEast(e);
    this->setNorth(n);
    this->setSouth(s);
    this->setRow(row);
    this->setColumn(column);
    this->setStartPoint(statPoint);
    this->setDestination(destination);
}