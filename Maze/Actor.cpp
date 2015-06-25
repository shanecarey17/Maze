//
//  Actor.cpp
//  Maze
//
//  Created by Shane Carey on 11/13/14.
//  Copyright (c) 2014 Shane Carey. All rights reserved.
//

#include "Actor.h"

void Actor::changePosition(Cell *newPosition) {
    // If our position is not null (a.k.a. this is not the first placement)
    if(position != NULL)
        // The old position is not longer occupying anything
        position->setActor(NULL);
    
    // We move to the new position and hold a reference
    newPosition->setActor(this);
    position = newPosition;
}

char Actor::getIdentifier() {
    return identifier;
}

Cell *Actor::getPosition() {
    return position;
}