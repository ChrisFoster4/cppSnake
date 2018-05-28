#pragma once
#include <GL/glut.h> //apt install freeglut3-dev for Debian based systems

#define CREATE_RANDOM_CORD ((((rand()) % 200 + 1)-100)*0.01)//Generates a float between -1 and 1

class Fruit {
private:
    float x,y=0;
    float radius =0.05;
public:
    Fruit();
    void moveToRandomPosition(void);
    void movePosition(float x,float y);
    float getRadius(void);
    float getX(void);
    float getY(void);
};


