//
//  Maze.cpp
//  Maze
//
//  Created by Shane Carey on 11/4/14.
//  Copyright (c) 2014 Shane Carey. All rights reserved.
//

#include "Maze.h"

Maze::Maze(int height, int width, int depth) {
    // Set bounds
    this->height = height;
    this->width = width;
    this->depth = depth;
    // Build maze in memory
    buildMazeStructure();
    carveRandomMaze();
}

void Maze::buildMazeStructure() {
    // Set our start and finish to null
    start = NULL;
    finish = NULL;
    // Create top level array
    this->maze = new Cell ***[height];
    for (int i = 0; i < height; i++) {
        // Create second level array
        this->maze[i] = new Cell **[width];
        for (int j = 0; j < width; j++) {
            // Create third level array
            this->maze[i][j] = new Cell *[depth];
            for (int k = 0; k < depth; k++) {
                // Create new cell
                this->maze[i][j][k] = new Cell(i, j, k);
            }
        }
    }
}

Maze::~Maze() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < depth; k++) {
                // Delete cell
                delete this->maze[i][j][k];
            }
            // Delete third level array
            delete[] this->maze[i][j];
        }
        // Delete second level array
        delete[] this->maze[i];
    }
    // Delete top level array
    delete[] this->maze;
}

#pragma mark - maze carving logic

void Maze::carveRandomMaze() {
    // Get our start cell and recurse the maze from it, returning the deepest cell pointer, set that to our finish
    Cell *start = setStartCell();
    CellDistance finishStruct = carveMazeRecursive(start, 0);
    finishStruct.cell->setState(FINISH);
    this->finish = finishStruct.cell;
    
    // Braids the maze by removing dead ends
}

Cell *Maze::setStartCell() {
    // Pick random coordinates
    int z = rand() % height;
    int x = rand() % width;
    int y = rand() % depth;
    
    // Set the cell at that position to start
    Cell *startCell = cellAtPosition(z, x, y);
    startCell->setState(START);
    this->start = startCell;
    
    // Return the cell
    return startCell;
}

CellDistance Maze::carveMazeRecursive(Cell *cell, int recDepth) {
    // We carve our cell by setting it to open (unless it marks the start)
    if(cell->getState() != START) {
        cell->setState(OPEN);
    }
    
    // Create a shuffled array of integers 0-5
    std::array<int,6> randomOrder {0,1,2,3,4,5};
    unsigned long seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (randomOrder.begin(), randomOrder.end(), std::default_random_engine((int)seed));
    
    // Here is our struct to test returns against
    CellDistance distStruct = {NULL, 0};
    
    // Randomly we choose a neighbor of our cell
    for (int i = 0; i < 6; i++) {
        Cell *neighbor = NULL;
        switch (randomOrder[i]) {
            case 0:
                neighbor = upperNeighbor(cell);
                break;
            case 1:
                neighbor = lowerNeighbor(cell);
                break;
            case 2:
                neighbor = westernNeighbor(cell);
                break;
            case 3:
                neighbor = easternNeighbor(cell);
                break;
            case 4:
                neighbor = northernNeighbor(cell);
                break;
            case 5:
                neighbor = southernNeighbor(cell);
                break;
        }
        
        // We recurse the cell then compare its return struct to our current struct, keeping the deepest
        CellDistance tempDistStruct = carveCellIfValid(neighbor, cell, ++recDepth);
        if(tempDistStruct.distance > distStruct.distance) {
            distStruct = tempDistStruct;
        }
    }
    
    // If there is no valid return value (aka our struct is not overwritten) then return this cell and its depth
    // Otherwise return our deepest cell
    if(distStruct.cell == NULL) {
        return {cell, recDepth};
    } else return distStruct;
}

CellDistance Maze::carveCellIfValid(Cell *cell, Cell *prevCell, int recDepth) {
    // Check if the cell exists
    if(cell != NULL) {
        // If the cell is valid to carve, recursively carve it
        if(isValidCellToCarve(cell, prevCell)) {
            // Return a struct with the deepest cell pointer in the recursion
            return carveMazeRecursive(cell, recDepth);
        }
    }
    // Otherwise return an empty struct
    return {NULL, 0};
}

bool Maze::isValidCellToCarve(Cell *cell, Cell *prevCell) {
    // Create array of neighbors
    Cell *neighbors[6] = {upperNeighbor(cell), lowerNeighbor(cell),
        westernNeighbor(cell), easternNeighbor(cell),
        northernNeighbor(cell), southernNeighbor(cell)};
    
    // For each neighbor to the cell, if the neighbor is open then we cannot carve this cell
    for (int i = 0; i < 6; i++) {
        Cell *neighbor = neighbors[i];
        if(neighbor != NULL && neighbor != prevCell) {
            if(neighbor->getState() == OPEN || neighbor->getState() == START) {
                // This is not a valid cell to carve
                return false;
            }
        }
    }
    
    // Our cell is valid to carve
    return true;
}

#pragma mark - getters for maze information and cells

int Maze::getHeight() {
    // Return height
    return this->height;
}

int Maze::getWidth() {
    // Return width
    return this->width;
}

int Maze::getDepth() {
    // Return depth
    return this->depth;
}

Cell *Maze::getStartCell() {
    // Return start cell
    return this->start;
}

Cell *Maze::getFinishCell() {
    return this->finish;
}

Cell *Maze::cellAtPosition(int z, int x, int y) {
    // Return cell at position
    if(z >= height || x >= width || y >= depth) {
        return NULL;
    }
    return this->maze[z][x][y];
}

Cell *Maze::upperNeighbor(Cell *cell) {
    // Return upper neihgbor if exists
    if(cell->getZ() == 0)
        return NULL;
    return this->maze[cell->getZ() - 1][cell->getX()][cell->getY()];
}

Cell *Maze::lowerNeighbor(Cell *cell) {
    // Return lower neihgbor if exists
    if(cell->getZ() == height - 1)
        return NULL;
    return this->maze[cell->getZ() + 1][cell->getX()][cell->getY()];
}

Cell *Maze::westernNeighbor(Cell *cell) {
    // Return western neihgbor if exists
    if(cell->getX() == 0)
        return NULL;
    return this->maze[cell->getZ()][cell->getX() - 1][cell->getY()];
}

Cell *Maze::easternNeighbor(Cell *cell) {
    // Return eastern neihgbor if exists
    if(cell->getX() == width - 1)
        return NULL;
    return this->maze[cell->getZ()][cell->getX() + 1][cell->getY()];
}

Cell *Maze::northernNeighbor(Cell *cell) {
    // Return northern neihgbor if exists
    if(cell->getY() == 0)
        return NULL;
    return this->maze[cell->getZ()][cell->getX()][cell->getY() - 1];

}

Cell *Maze::southernNeighbor(Cell *cell) {
    // Return southern neihgbor if exists
    if(cell->getY() == depth - 1)
        return NULL;
    return this->maze[cell->getZ()][cell->getX()][cell->getY() + 1];
}
