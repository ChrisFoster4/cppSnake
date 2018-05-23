#pragma once
#include <math.h>
#include <unistd.h> //For sleep()
#include <iostream>
#include <GL/glut.h>

typedef struct snakePart{ //typedef for a linked list storing the cords of the parts of the snake
    float x,y;
    struct snakePart* next;
}snakePart;

class Projectile{
    float x,y,radius;
    snakePart* snakeHead=(snakePart*) malloc(sizeof(snakePart));
public:
    void movePosition(float x,float y);
    Projectile();
    void addSnakePart(float x,float y);
    void outputSnakeCords();
    float getRadius();
    float getX();
    float getY();
} ;
