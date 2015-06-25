//
//  Renderer.h
//  Maze
//
//  Created by Shane Carey on 11/15/14.
//  Copyright (c) 2014 Shane Carey. All rights reserved.
//

#ifndef __Maze__Renderer__
#define __Maze__Renderer__

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

class Game;
class Cell;

class Renderer {
    
public:
    /*
     Initializes the renderer
     @param game The game to initialize the renderer with
     */
    static void initRenderer(Game *game);
    
    /*
     Updates the display of the maze
     @param cell The cell to reference when drawing level of the maze
     */
    static void updateDisplay(Cell *cell);
    
private:
    static void processKeys(int key, int x, int y);
    static void renderScene();
    static void renderEndGame();
};

#endif /* defined(__Maze__Renderer__) */
