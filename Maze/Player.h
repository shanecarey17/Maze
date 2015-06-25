//
//  Player.h
//  Maze
//
//  Created by Shane Carey on 11/13/14.
//  Copyright (c) 2014 Shane Carey. All rights reserved.
//

#ifndef __Maze__Player__
#define __Maze__Player__

#include <stdio.h>
#include <thread>
#include <stack>
#include <unistd.h>

#include "Actor.h"

class Player : public Actor {
    
public:
    /*
     Constructs a player
     @param maze The maze to place the player in
     */
    Player(Maze *maze);
    
    /*
     Does nothing, here for sake of polymorphism
     */
    void travel() { /* NOTHING */};
    
    /*
     Moves player with given keystroke
     @param input The keystroke defining the player's movement
     */
    void movePlayerDirection(Direction direction);
    
    /*
     Solve the maze
     */
    void solveMaze();
    
private:
    bool movePlayerToCell(Cell *cell);
    bool solveMazeRecursive(std::stack<Cell *> *cellStack);
    
};

#endif /* defined(__Maze__Player__) */
