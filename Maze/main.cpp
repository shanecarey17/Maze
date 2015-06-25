//
//  main.cpp
//  Maze
//
//  Created by Shane Carey on 11/4/14.
//  Copyright (c) 2014 Shane Carey. All rights reserved.
//

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

#include "Renderer.h"
#include "Game.h"

int main(int argc, char * argv[]) {
    // Some initializations
    srand((unsigned int)time(0));
    glutInit(&argc, argv);
    
    // Game and rendering
    Game *newGame = new Game(1, 50, 50, 5);
    Renderer::initRenderer(newGame);
    
    // Outta here
    return 0;
}
