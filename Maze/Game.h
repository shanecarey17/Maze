//
//  Game.h
//  Maze
//
//  Created by Shane Carey on 11/13/14.
//  Copyright (c) 2014 Shane Carey. All rights reserved.
//

#ifndef __Maze__Game__
#define __Maze__Game__

#include <stdio.h>
#include <unistd.h>

#include "Player.h"
#include "Runner.h"
#include "Jumper.h"

#include "Renderer.h"

class Game {
    Maze *maze;
    Creature **creatures;
    Player *player;
    
    std::thread gameLoopThread, solveThread;
    std::atomic<bool> isSolving;
    
public:
    /*
     Initializes a new game
     @param levels Levels to the maze
     @param width Width of the maze
     @param depth Depth of the maze
     @param creatures No. of enemies in the maze
     */
    Game(int levels, int width, int depth, int creatures);
    
    /*
     Destructor for the game
     */
    ~Game();
    
    /*
     Interface for moving the player
     @param key The keypress to hand to the player for movement
     */
    void movePlayer(Direction direction);
    
    /*
     @return a reference to the maze of the game
     */
    Maze *getMaze();
    
    /*
     Solve the maze
     */
    void solveMaze();
    
    /*
     Reset the maze
     */
    void resetMaze();
    
    /*
     Mutex for game logic, may need to be accessed outside of game
     */
    std::mutex mutex;
    
private:
    void createCreatures(int numCreatures);
    void runGameLoop();
    void solveMazeThread();
};

#endif /* defined(__Maze__Game__) */
