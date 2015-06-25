//
//  Cell.cpp
//  Maze
//
//  Created by Shane Carey on 11/4/14.
//  Copyright (c) 2014 Shane Carey. All rights reserved.
//

#include "Cell.h"

Cell::Cell(int z, int x, int y) {
    // Initialize coordinates
    this->zPosition = z;
    this->xPosition = x;
    this->yPosition = y;
    // Set state to default closed
    this->state = CLOSED;
    // No occupying actor
    this->actor = NULL;
}
    
void Cell::setState(CellState newState) {
    // Set the state of the cell
    this->state = newState;
}
    
CellState Cell::getState() {
    // return state position
    return this->state;
}
    
int Cell::getZ() {
    // return z position
    return this->zPosition;
}
    
int Cell::getX() {
    // return x position
    return this->xPosition;
}
    
int Cell::getY() {
    // return y position
    return this->yPosition;
}

Actor *Cell::getActor() {
    return this->actor;
}

void Cell::setActor(Actor *actor) {
    this->actor = actor;
}