#pragma once
#include <math.h>
#include <unistd.h> //For sleep()
#include <iostream>
#include <GL/glut.h>
#include "fruit.h"

#define CREATE_RANDOM_CORD ((((rand()) % 200 + 1)-100)*0.01)//Generates a float between -1 and 1

typedef struct snakePart{ //typedef for a linked list storing the cords of the parts of the snake
    float x,y;
    struct snakePart* next;
}snakePart;

class Snake{
private:
    float x,y,radius;
    snakePart* snakeHead= new snakePart;
public:
    void movePosition(float x,float y);
    Snake();
    void addSnakePart(float x,float y);
    void setLength(int snakeLength);
    void detectFruitCollision(Fruit& fruit,int* score,int* length);
    void detectSnakeCollision(bool* gameRunning,int* length);
    void drawSnakePart(float x,float y);
    void moveToRandomPosition(void);
    float getRadius(void);
    float getX(void);
    float getY(void);
};
