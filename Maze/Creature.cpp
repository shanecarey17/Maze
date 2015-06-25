//
//  Creature.cpp
//  Maze
//
//  Created by Shane Carey on 11/13/14.
//  Copyright (c) 2014 Shane Carey. All rights reserved.
//

#include "Creature.h"

Creature::Creature(Maze *maze) {
    // References
    this->maze = maze;
    this->position = NULL;  // NULL out for safety
    
    // Until we find a valid position
    while (this->position == NULL) {
        // Choose a random cell
        int zPos = rand() % (maze->getHeight());
        int xPos = rand() % (maze->getWidth());
        int yPos = rand() % (maze->getDepth());
        
        // If this cell is open and unoccupied, move to it
        Cell *cell;
        if((cell = maze->cellAtPosition(zPos, xPos, yPos))->getState() == OPEN && cell->getActor() == NULL) {
            changePosition(cell);
        }
    }
}
