//
//  Game.cpp
//  Maze
//
//  Created by Shane Carey on 11/13/14.
//  Copyright (c) 2014 Shane Carey. All rights reserved.
//

#include "Game.h"

Game::Game(int levels, int width, int depth, int creatures) {
    // Construct the maze
    maze = new Maze(levels, width, depth);
    
    // Construct the player
    player = new Player(maze);
    
    // We need an array of creatures
    createCreatures(creatures);
    
    // Launch our game logic in another thread
    // we need to save our main thread for graphics
    gameLoopThread = std::thread(&Game::runGameLoop, this);
}

Game::~Game() {
    // Join the game logic thread
    gameLoopThread.join();
    
    // Delete everything
    delete maze;
    delete player;
    for (Creature **creature = creatures; *creature != NULL; creature++) {
        delete creature;
    }
    delete [] creatures;
}

void Game::createCreatures(int numCreatures) {
    // This is a null terminated array, so we need an extra space
    creatures = new Creature *[numCreatures + 1];
    
    // Loop through and create creatures
    for (int i = 0; i <= numCreatures; i++) {
        // Create the creatures
        if(i < numCreatures) {
            // Somehow we need to choose what type of creature to create
            if(i % 2 == 0 )
                creatures[i] = new Runner(maze);
            else creatures[i] = new Jumper(maze);
        } else {
            // On the last space, set it null
            creatures[i] = NULL;
        }
    }
}

void Game::runGameLoop() {
    // This thread never ends
    while (true) {
        // Until the player reaches the end
        while (player->getPosition() != maze->getFinishCell()) {
            // Update the display with respect to the player's position
            Renderer::updateDisplay(player->getPosition());
            
            // We need to lock our creatures down for their move cycle
            mutex.lock();
            
            // All the creatures make their move
            for (int i = 0; creatures[i] != NULL; i++) {
                creatures[i]->travel();
            }
            
            // Now we are safe to move onward
            mutex.unlock();
            
            // Slow everything down to human speeds
            usleep(100000);
        }
        
        // We may need to wait for the solving thread to finish (to prevent segfault)
        try {
            solveThread.join();
        } catch (std::__1::system_error error) {
            // No thread to join
        }
            
        // Once the game is over get a new maze!
        resetMaze();
    }
}

void Game::movePlayer(Direction direction) {
    // Move the player
    player->movePlayerDirection(direction);
    
    // Update the graphics
    Renderer::updateDisplay(player->getPosition());
}

Maze *Game::getMaze() {
    // Give them a reference to the maze
    return maze;
}

void Game::solveMaze() {
    // If we are not already solving the maze
    if(!isSolving) {
        // Set the flag and solve the maze on another thread
        isSolving = true;
        solveThread = std::thread(&Game::solveMazeThread, this);
    }
}

void Game::solveMazeThread() {
    // Initiate recursive solving of the maze via the player
    player->solveMaze();
    // Set the flag that solving is done
    isSolving = false;
}

void Game::resetMaze() {
    // If the game is solving itself, we cannot reset (will disturb other solving thread)
    if(isSolving)
        return;
    
    // Lock the mutex
    mutex.lock();
    
    // Delete in game stuff
    int numCreatures = 0;
    for (Creature **creature = &creatures[0]; *creature != NULL; creature++) {
        delete *creature;
        numCreatures++;
    }
    delete [] creatures;
    delete player;
    
    // New maze
    int levels = maze->getHeight();
    int width = maze->getWidth();
    int depth = maze->getDepth();
    delete maze;
    
    // Re initialize everything
    maze = new Maze(levels, width, depth);
    player = new Player(maze);
    createCreatures(numCreatures);
    
    // Update display
    Renderer::updateDisplay(maze->getStartCell());
    
    // Now we can unlock
    mutex.unlock();
}
