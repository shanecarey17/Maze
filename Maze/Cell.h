//
//  Cell.h
//  Maze
//
//  Created by Shane Carey on 11/4/14.
//  Copyright (c) 2014 Shane Carey. All rights reserved.
//

#ifndef __Maze__Cell__
#define __Maze__Cell__

#include <stdio.h>

class Actor;

enum CellState {
    OPEN,
    CLOSED,
    START,
    FINISH,
    VISITED
};

class Cell {
    int zPosition, xPosition, yPosition;
    CellState state;
    Actor *actor;
    
public:
    /*
     Initializes a cell with coordinates
     @param z The z position of the cell
     @param x The x position of the cell
     @param y The y position of the cell
     */
    Cell(int z, int x, int y);
    
    /*
     The state of the cell within the maze
     @return CellState enum denoting state of cell
     */
    CellState getState();
    
    /*
     The z position of the cell
     @return Z position
     */
    int getZ();
    
    /*
     The x position of the cell
     @return X position
     */
    int getX();
    
    /*
     The y position of the cell
     @return Y position
     */
    int getY();
    
    /*
     Sets state of the cell
     @param state The state to set the cell
     */
    void setState(CellState state);
    
    /*
     Returns pointer to the actor occupying the cell
     @return A pointer to the actor occupying the cell
     */
    Actor *getActor();
    
    /*
     Sets the actor of the cell
     @param actor A pointer to the actor to occupy the cell
     */
    void setActor(Actor *actor);
    
};

#endif /* defined(__Maze__Cell__) */
