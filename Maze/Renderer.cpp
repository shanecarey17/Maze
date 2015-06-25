//
//  Renderer.cpp
//  Maze
//
//  Created by Shane Carey on 11/15/14.
//  Copyright (c) 2014 Shane Carey. All rights reserved.
//

#include "Renderer.h"
#include "Game.h"

#define PIXELS_PER_SQUARE 10

Game *refGame;
Cell *referenceCell;

void Renderer::initRenderer(Game *game) {
    // Global references (no way to avoid with C interface)
    refGame = game;
    referenceCell = game->getMaze()->getStartCell();
    
    // Window intialization
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(game->getMaze()->getWidth() * PIXELS_PER_SQUARE, game->getMaze()->getDepth() * PIXELS_PER_SQUARE);
    glutCreateWindow("Maze");
    
    // Callbacks for rendering and keyboard input
    glutDisplayFunc(Renderer::renderScene);
    glutIdleFunc(Renderer::renderScene);
    glutSpecialFunc(Renderer::processKeys);
    
    // We enter the main loop on the main thread
    glutMainLoop();
}

void Renderer::updateDisplay(Cell *cell) {
    // Update our global cell reference
    referenceCell = cell;
    
    // Post a redisplay with the new reference, calls our render callback
    glutPostRedisplay();
}

void Renderer::renderScene() {
    // Clear color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Lock game for display, otherwise refGame->maze() may return different instances and cells may be null
    refGame->mutex.lock();
    
    // This is the 2d level of the maze we are displaying
    int level = referenceCell->getZ();
    
    // Loop through the grid
    for (int i = 0; i < refGame->getMaze()->getWidth(); i++) {
        for (int j = 0; j < refGame->getMaze()->getDepth(); j++) {
            // Acquire a reference to our cell
            Cell *cellAtPosition = refGame->getMaze()->cellAtPosition(level, i, j);
            
            // Choose color based on cell state
            if(cellAtPosition->getActor() != NULL && cellAtPosition->getActor()->getIdentifier() == 'P') {
                glColor3f(1, 0, 1);
            } else if(cellAtPosition->getActor() != NULL) {
                glColor3f(1, 0, 0);
            } else if(cellAtPosition->getState() == START) {
                glColor3f(0, 1, 0);
            } else if (cellAtPosition->getState() == FINISH) {
                glColor3f(0, 0, 1);
            } else if(cellAtPosition->getState() != CLOSED) {
                glColor3f(1, 1, 1);
            } else {
                glColor3f(0, 0, 0);
            }
            
            // Normalize coordinates to [-0.5, 0.5]
            float x = 2 * (i / (float)refGame->getMaze()->getWidth()) - 1.0;
            float y = 2 * (j / (float)refGame->getMaze()->getDepth()) - 1.0;
            float x1 = 2 * ((i + 1) / (float)refGame->getMaze()->getWidth()) - 1.0;
            float y1 = 2 * ((j + 1) / (float)refGame->getMaze()->getDepth()) - 1.0;
            
            // Draw the rectangle at given coordinates
            glRectf(x, y, x1, y1);
        }
    }
    
    // Unlock after we have finished collecting input from the maze
    refGame->mutex.unlock();
    
    // Submit our changes
    glutSwapBuffers();
}

void Renderer::processKeys(int key, int x, int y) {
    // Calls to controller to update model
    switch (key) {
        case 'f':
            refGame->movePlayer(EAST);
            break;
        case 'd':
            refGame->movePlayer(WEST);
            break;
        case 'g':
            refGame->movePlayer(NORTH);
            break;
        case 'e':
            refGame->movePlayer(SOUTH);
            break;
        case 'x':
            refGame->movePlayer(UP);
            break;
        case 'z':
            refGame->movePlayer(DOWN);
            break;
        case 's':
            refGame->solveMaze();
            break;
        case 'r':
            refGame->resetMaze();
            break;
        case 'q':
            exit(EXIT_SUCCESS);
        default:
            break;
    }
}
