//
//  Maze.h
//  Maze
//
//  Created by Shane Carey on 11/4/14.
//  Copyright (c) 2014 Shane Carey. All rights reserved.
//

#ifndef __Maze__Maze__
#define __Maze__Maze__

#include <stdio.h>
#include <array>
#include <random>
#include <iostream>

#include "Cell.h"

struct CellDistance {
    Cell *cell;
    int distance;
};

class Maze {
    int height, depth, width;
    Cell ****maze;
    Cell *start;
    Cell *finish;
    
public:
    
    /*
     Initializes an uncarved maze of given dimensions
     @param z The height of the maze (vertical)
     @param x The width of the maze (horizontal)
     @param y The depth of the maze (anti-horizontal)
     */
    Maze(int height, int width, int depth);
    
    /*
     Destructor for maze
     */
    ~Maze();
    
    /*
     Returns heigh of the maze
     @return The height of the maze
     */
    int getHeight();
    
    /*
     Returns depth of the maze
     @return The width of the maze
     */
    int getWidth();
    
    /*
     Returns depth of the maze
     @return The depth of the maze
     */
    int getDepth();
    
    /*
     Returns start cell of maze
     @return The start cell of the maze
     */
    Cell *getStartCell();
    
    /*
     Returns finish cell of maze
     @return The finish cell of the maze
     */
    Cell *getFinishCell();
    
    /*
     Returns cell at given coordinates
     @param z The z position of the cell
     @param x The x position of the cell
     @param y The y position of the cell
     @return The cell at coordinated
     */
    Cell *cellAtPosition(int z, int x, int y);
    
    /*
     The cell above
     @param The adjacent cell from which to test
     @return The neighboring cell or NULL if there is not one
     */
    Cell *upperNeighbor(Cell *cell);
    
    /*
     The cell below
     @param The adjacent cell from which to test
     @return The neighboring cell or NULL if there is not one
     */
    Cell *lowerNeighbor(Cell *cell);
    
    /*
     The cell west
     @param The adjacent cell from which to test
     @return The neighboring cell or NULL if there is not one
     */
    Cell *westernNeighbor(Cell *cell);
    
    /*
     The cell east
     @param The adjacent cell from which to test
     @return The neighboring cell or NULL if there is not one
     */
    Cell *easternNeighbor(Cell *cell);
    
    /*
     The cell north
     @param The adjacent cell from which to test
     @return The neighboring cell or NULL if there is not one
     */
    Cell *northernNeighbor(Cell *cell);
    
    /*
     The cell south
     @param The adjacent cell from which to test
     @return The neighboring cell or NULL if there is not one
     */
    Cell *southernNeighbor(Cell *cell);
    
    /*
     Prints maze as a text array to std out
     */
    void printMaze();
    
private:
    void buildMazeStructure();
    void carveRandomMaze();
    Cell *setStartCell();
    CellDistance carveCellIfValid(Cell *cell, Cell *prevCell, int recDepth);
    bool isValidCellToCarve(Cell *cell, Cell *prevCell);
    CellDistance carveMazeRecursive(Cell *cell, int recDepth);
};

#endif /* defined(__Maze__Maze__) */
