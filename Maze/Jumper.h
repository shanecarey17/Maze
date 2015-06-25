//
//  Jumper.h
//  Maze
//
//  Created by Shane Carey on 11/13/14.
//  Copyright (c) 2014 Shane Carey. All rights reserved.
//

#ifndef __Maze__Jumper__
#define __Maze__Jumper__

#include <stdio.h>

#include "Creature.h"

class Jumper : public Creature {
    
public:
    /* 
     Constucts a jumper
     @param maze The maze to place the jumper within
     */
    Jumper(Maze *maze);
    
    /*
     Moves the jumper in any direction to
     an open cell two blocks away, including
     over walls
     */
    void travel();
    
};

#endif /* defined(__Maze__Jumper__) */
