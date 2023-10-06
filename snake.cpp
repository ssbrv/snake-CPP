#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "helpers.h"
#include "staticObjects.h"
#include "interactiveObjects.h"
#include "constValues.h"

/* global variables */

int id_window;
Grid grid;
Snake snake;
Apple apple;
RNGenerator generatorX;
RNGenerator generatorY;

/* helping function */

/* set-up helpers */

void setupWindowSize(const Size &size) 
{
    glutInitWindowSize(size.m_x, size.m_y);
}

void setupWindowPosition(const Position &position) 
{
    glutInitWindowPosition(position.m_x, position.m_y);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, GRID_WIDTH, 0.0, GRID_HEIGHT, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void gameStateUpdate(int)
{
    snake.move();
    if (snake.inCollision()) 
    {
        std::cout << "LOSS!" << std::endl;
        std::cout << "SCORE: " << snake.m_score << "/" << GRID_WIDTH * GRID_HEIGHT << std::endl;
        glutDestroyWindow(id_window);
        exit(1);
    }
    if (snake.attemptEat(apple))
    {
        snake.eat();
        if (snake.m_score == GRID_WIDTH * GRID_HEIGHT)
        {
            std::cout << "VICTORY!" << std::endl;
            std::cout << "SCORE: " << snake.m_score << "/" << GRID_WIDTH * GRID_HEIGHT << std::endl;
            glutDestroyWindow(id_window);
            exit(1);
        }
        do 
        { 
            apple.respawn({(float)generatorX.generate(), (float)generatorY.generate()});
        } while (snake.attemptEat(apple));
    }


    // apple.blink();
    glutTimerFunc(1000 / FPS, gameStateUpdate, 0);
}

void keyboard(int key, int, int)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        snake.setVelosity(ONE_UP);
        break;

    case GLUT_KEY_DOWN:
        snake.setVelosity(ONE_DOWN);
        break;

    case GLUT_KEY_LEFT:
        snake.setVelosity(ONE_LEFT);
        break;

    case GLUT_KEY_RIGHT:
        snake.setVelosity(ONE_RIGHT);
        break;
    
    default:
        break;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    apple.draw();
    snake.draw();
    grid.draw();
    glutSwapBuffers();
    glutPostRedisplay();
}

/* set-up */

void setup(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    setupWindowSize(WINDOW_SIZE);
    setupWindowPosition(WINDOW_POSITION);
    glutCreateWindow(WINDOW_NAME);
    id_window = glutGetWindow();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    glutTimerFunc(0, gameStateUpdate, 0);
    // glutKeyboardFunc(keyboard); keybord(char, int, int)
    glutSpecialFunc(keyboard);
}

/* init helpers */

void initBackground(const Color &backgroundColor)
{
    glClearColor(backgroundColor.m_R, backgroundColor.m_G, backgroundColor.m_B, 1.0);
}

void initGrid(const Size &size, const Size &sizeBox, const Box &gridBox, const Box &boundaryBox)
{
    grid = Grid{size, sizeBox, gridBox, boundaryBox};
}

void initSnake(const Position &initPosition, const Vector &velocity, const Size &sizeRectangle, const Rectangle &headRectangle, const Rectangle &bodyRectangle)
{
    snake = Snake{initPosition, velocity, sizeRectangle, headRectangle, bodyRectangle};
}

void initApple(const Position &initPosition, const Size &size, const Rectangle &rectangle) 
{
    apple = Apple{initPosition, size, rectangle};
}

void initGenerator(const int &minX, const int &maxX, const int &minY, const int &maxY)
{
    generatorX = RNGenerator{minX, maxX};
    generatorY = RNGenerator{minY, maxY};
}

/* init */

void init()
{
    initBackground(WINDOW_COLOR);
    initGrid(GRID_SIZE, STANDARD_BOX_SIZE, GRID_BOX, BOUNDARY_BOX);
    initSnake(SNAKE_INIT_POSITION, ONE_UP, STANDARD_BOX_SIZE, SNAKE_HEAD_RECTANGLE, SNAKE_BODY_RECTANGLE);
    initApple(APPLE_INIT_POSITION, STANDARD_BOX_SIZE, APPLE_RECTANGLE);
    initGenerator(MIN_X_RANDOM, MAX_X_RANDOM, MIN_Y_RANDOM, MAX_Y_RANDOM);
}

int main(int argc, char **argv)
{
    setup(argc, argv);
    init();
    glutMainLoop();
    return 0;
}