//
//  Test.cpp
//  Maze
//
//  Created by Shane Carey on 11/6/14.
//  Copyright (c) 2014 Shane Carey. All rights reserved.
//

#include "Test.h"

bool Test::testCell() {
    Cell cell = Cell(0, 1, 2);
    if(cell.getZ() != 0) {
        return false;
    }
    if(cell.getX() != 1) {
        return false;
    }
    if(cell.getY() != 2) {
        return false;
    }
    if(cell.getState() != CLOSED) {
        return false;
    }
    cell.setState(OPEN);
    if(cell.getState() != OPEN) {
        return false;
    }
    return true;
}

bool Test::testMaze() {
    Maze maze = Maze(3, 4, 5);
    if(maze.getHeight() != 3) {
        return false;
    }
    if(maze.getWidth() != 3) {
        return false;
    }
    if(maze.getDepth() != 3) {
        return false;
    }
    if(maze.cellAtPosition(3,3,3) != NULL) {
        return false;
    }
    if(maze.getStartCell() != NULL && maze.getFinishCell() != NULL) {
        return false;
    }
    return true;
}
