//
//  Runner.h
//  Maze
//
//  Created by Shane Carey on 11/13/14.
//  Copyright (c) 2014 Shane Carey. All rights reserved.
//

#ifndef __Maze__Runner__
#define __Maze__Runner__

#include <stdio.h>
#include <random>

#include "Creature.h"

class Runner : public Creature {
    Direction direction;
    
public:
    /* 
     Initializes a runner
     @param maze The maze to place the runner in
     */
    Runner(Maze *maze);
    
    /*
     Moves the runner in a single direction
     until the runner cannot move in that direction
     anymore, then changes direction and moves that way
     */
    void travel();
    
private:
    void changeDirection();
    
};

#endif /* defined(__Maze__Runner__) */
