//
//  Player.cpp
//  Maze
//
//  Created by Shane Carey on 11/13/14.
//  Copyright (c) 2014 Shane Carey. All rights reserved.
//

#include "Player.h"

Player::Player(Maze *maze) {
    // Maze reference
    this->maze = maze;
    
    // Place player at the start of the maze
    Cell *start = maze->getStartCell();
    this->position = start;
    start->setActor(this);
    
    // Set identifier
    identifier = 'P';
}

void Player::movePlayerDirection(Direction direction) {
    switch (direction) {
        case EAST:
            movePlayerToCell(maze->easternNeighbor(position));
            break;
        case WEST:
            movePlayerToCell(maze->westernNeighbor(position));
            break;
        case NORTH:
            movePlayerToCell(maze->northernNeighbor(position));
            break;
        case SOUTH:
            movePlayerToCell(maze->southernNeighbor(position));
            break;
        case DOWN:
            movePlayerToCell(maze->lowerNeighbor(position));
            break;
        case UP:
            movePlayerToCell(maze->upperNeighbor(position));
            break;
        default:
            break;
    }
}

bool Player::movePlayerToCell(Cell *destination) {
    // Null check
    if(destination != NULL) {
        // Is the cell open or the start or finish cell
        if(destination->getState() != CLOSED) {
            // Move to the cell
            changePosition(destination);
            return true;
        }
    }
    return false;
}

void Player::solveMaze() {
    std::stack<Cell *> *cellStack = new std::stack<Cell *>();
    solveMazeRecursive(cellStack);
}

bool Player::solveMazeRecursive(std::stack<Cell *> *cellStack) {
    // Wait
    usleep(50000);
    
    // We have finished if we reach the finish cell
    if(position == maze->getFinishCell()) {
        return true;
    }
    
    // Mark cell as visited and add to stack
    position->setState(VISITED);
    cellStack->push(position);
    
    // Try to move to all neighbors
    if(maze->easternNeighbor(position) != NULL && maze->easternNeighbor(position)->getState() != VISITED && movePlayerToCell(maze->easternNeighbor(position))) {
        if(solveMazeRecursive(cellStack)) {
            return true;
        }
    }
    if(maze->westernNeighbor(position) != NULL && maze->westernNeighbor(position)->getState() != VISITED && movePlayerToCell(maze->westernNeighbor(position))) {
        if(solveMazeRecursive(cellStack)) {
            return true;
        }
    }
    if(maze->northernNeighbor(position) != NULL && maze->northernNeighbor(position)->getState() != VISITED && movePlayerToCell(maze->northernNeighbor(position))) {
        if(solveMazeRecursive(cellStack)) {
            return true;
        }
    }
    if(maze->southernNeighbor(position) != NULL && maze->southernNeighbor(position)->getState() != VISITED && movePlayerToCell(maze->southernNeighbor(position))) {
        if(solveMazeRecursive(cellStack)) {
            return true;
        }
    }
    if(maze->upperNeighbor(position) != NULL && maze->upperNeighbor(position)->getState() != VISITED && movePlayerToCell(maze->upperNeighbor(position))) {
        if(solveMazeRecursive(cellStack)) {
            return true;
        }
    }
    if(maze->lowerNeighbor(position) != NULL && maze->lowerNeighbor(position)->getState() != VISITED && movePlayerToCell(maze->lowerNeighbor(position))) {
        if(solveMazeRecursive(cellStack)) {
            return true;
        }
    }
    
    // If all of the recursive solutions fail, we are in a duff branch
    // Pop the position from the stack and move back to the top element
    // Wait
    cellStack->pop();
    movePlayerToCell(cellStack->top());
    usleep(50000);
    return false;
}


















