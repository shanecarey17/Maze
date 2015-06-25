//
//  Runner.cpp
//  Maze
//
//  Created by Shane Carey on 11/13/14.
//  Copyright (c) 2014 Shane Carey. All rights reserved.
//

#include "Runner.h"

Runner::Runner(Maze *maze) : Creature(maze) {
    identifier = 'R';
    this->direction = EAST;
}

void Runner::travel() {
    Cell *destination = NULL;
    switch (direction) {
        case EAST:
            if((destination = maze->easternNeighbor(position)) != NULL && destination->getState() != CLOSED) {
                changePosition(destination);
                return;
            }
            break;
        case WEST:
            if((destination = maze->westernNeighbor(position)) != NULL && destination->getState() != CLOSED) {
                changePosition(destination);
                return;
            }
            break;
        case NORTH:
            if((destination = maze->northernNeighbor(position)) != NULL && destination->getState() != CLOSED) {
                changePosition(destination);
                return;
            }
            break;
        case SOUTH:
            if((destination = maze->southernNeighbor(position)) != NULL && destination->getState() != CLOSED) {
                changePosition(destination);
                return;
            }
            break;
        case UP:
            if((destination = maze->upperNeighbor(position)) != NULL && destination->getState() != CLOSED) {
                changePosition(destination);
                return;
            }
            break;
        case DOWN:
            if((destination = maze->lowerNeighbor(position)) != NULL && destination->getState() != CLOSED) {
                changePosition(destination);
                return;
            }
            break;
    }
    changeDirection();
}

void Runner::changeDirection() {
    direction = Direction(rand() % 6);
    travel();
}
