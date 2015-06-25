//
//  Actor.h
//  Maze
//
//  Created by Shane Carey on 11/13/14.
//  Copyright (c) 2014 Shane Carey. All rights reserved.
//

#ifndef __Maze__Actor__
#define __Maze__Actor__

#include <stdio.h>

#include "Maze.h"

enum Direction {
    UP,
    DOWN,
    EAST,
    WEST,
    NORTH,
    SOUTH
};

class Actor {
    
protected:
    Maze *maze;
    Cell *position;
    char identifier;
    
public:
    /* 
     Moves the actor
     */
    virtual void travel() = 0;
    
    /*
     Changes position of the actor
     @param newPosition The new position of the actor
     */
    void changePosition(Cell *newPosition);
    
    /*
     @return The cell the actor is occupying
     */
    Cell *getPosition();
    
    /*
     @return The character identifying the type of actor
     */
    char getIdentifier();
};

#endif /* defined(__Maze__Actor__) */
