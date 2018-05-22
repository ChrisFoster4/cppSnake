#pragma once
#include <math.h>
#include <unistd.h> //For sleep()
#include <iostream>
#include <GL/glut.h>

class Projectile{
    float x,y,radius =0;
public:
    void movePosition(float x,float y,float radius);
    void output();
    Projectile duplicate(Projectile& pro);
    float getRadius();
    float getX();
    float getY();
    std::string describe();
} ;
