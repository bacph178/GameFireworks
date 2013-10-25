//
//  TableGame.cpp
//  GameFireworks
//
//  Created by NgocDu on 13/10/25.
//
//

#include "TableGame.h"
TableGame::TableGame(int rows, int columns, CCPoint pOrigin, float w, float h) {
    this->setRows(rows);
    this->setColumns(columns);
    this->setPointOrigin(pOrigin);
    this->setWidth(w);
    this->setHeight(h);
}