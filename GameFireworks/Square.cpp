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
    this->setIsMoveTouch(false);
}
void Square::changeRotation(int columns) {
    this->setIsMoveTouch(true);
    bool w = this->getWest();
    bool n = this->getNorth();
    bool e = this->getEast();
    bool s = this->getSouth();
    this->setNorth(w);
    this->setEast(n);
    this->setSouth(e);
    this->setWest(s);
        
    if (this->getTag() == 1 + columns * (this->getRow() - 1) && this->getWest() == true) {
        this->setStartPoint(true);
    }else this->setStartPoint(false);
    
    if (this->getTag() == this->getRow() * columns && this->getEast() == true) {
        this->setDestination(true);
    }else this->setDestination(false);
    
    CCRotateTo * rotate = CCRotateTo::create(0.0f, this->getRotation() + 90);
    this->runAction(rotate);
}