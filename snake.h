#pragma once
#include <math.h>
#include <unistd.h> //For sleep()
#include <iostream>
#include <GL/glut.h>

#define CREATE_RANDOM_CORD ((((rand()) % 200 + 1)-100)*0.01)//Generates a float between -1 and 1

typedef struct snakePart{ //typedef for a linked list storing the cords of the parts of the snake
    float x,y;
    struct snakePart* next;
}snakePart;

class Projectile{
private:
    float x,y,radius;
    snakePart* snakeHead=(snakePart*) malloc(sizeof(snakePart));
public:
    void movePosition(float x,float y);
    Projectile();
    void addSnakePart(float x,float y);
    void setLength(int snakeLength);
    void detectFruitCollision(Projectile& fruit,int* score);
    void detectSnakeCollision(bool* gameRunning,int* length);
    void drawSnakePart(float x,float y);
    void outputSnakeCords();
    float getRadius();
    float getX();
    float getY();
} ;
