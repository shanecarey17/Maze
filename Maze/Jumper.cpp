//
//  Jumper.cpp
//  Maze
//
//  Created by Shane Carey on 11/13/14.
//  Copyright (c) 2014 Shane Carey. All rights reserved.
//

#include "Jumper.h"

Jumper::Jumper(Maze *maze) : Creature(maze) {
    identifier = 'J';
}

void Jumper::travel() {
    // Choose a random direction
    int random = rand() % 6;
    
    // We check that our cell two blocks away exists and is open
    Cell *intermediate, *destination;
    switch (random) {
        case 0:
            if((intermediate = maze->easternNeighbor(position)) != NULL) {
                if((destination = maze->easternNeighbor(intermediate)) != NULL && destination->getState() != CLOSED) {
                    changePosition(destination);
                    return;
                }
            }
            break;
        case 1:
            if((intermediate = maze->westernNeighbor(position)) != NULL) {
                if((destination = maze->westernNeighbor(intermediate)) != NULL && destination->getState() != CLOSED) {
                    changePosition(destination);
                    return;
                }
            }
            break;
        case 2:
            if((intermediate = maze->northernNeighbor(position)) != NULL) {
                if((destination = maze->northernNeighbor(intermediate)) != NULL && destination->getState() != CLOSED) {
                    changePosition(destination);
                    return;
                }
            }
            break;
        case 3:
            if((intermediate = maze->southernNeighbor(position)) != NULL) {
                if((destination = maze->southernNeighbor(intermediate)) != NULL && destination->getState() != CLOSED) {
                    changePosition(destination);
                    return;
                }
            }
            break;
        case 4:
            if((intermediate = maze->upperNeighbor(position)) != NULL) {
                if((destination = maze->upperNeighbor(intermediate)) != NULL && destination->getState() != CLOSED) {
                    changePosition(destination);
                    return;
                }
            }
            break;
        case 5:
            if((intermediate = maze->lowerNeighbor(position)) != NULL) {
                if((destination = maze->lowerNeighbor(intermediate)) != NULL && destination->getState() != CLOSED) {
                    changePosition(destination);
                    return;
                }
            }
            break;
    }
}
