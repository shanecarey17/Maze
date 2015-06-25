//
//  Creature.h
//  Maze
//
//  Created by Shane Carey on 11/13/14.
//  Copyright (c) 2014 Shane Carey. All rights reserved.
//

#ifndef __Maze__Creature__
#define __Maze__Creature__

#include <stdio.h>

#include "Actor.h"

class Creature : public Actor {
    
public:
    /* 
     Constructs a creature
     @param maze The maze to place the creature within
     */
    Creature(Maze *maze);
    
    /*
     Moves the creature in its own fashion
     */
    virtual void travel() = 0;
    
};

#endif /* defined(__Maze__Creature__) */
