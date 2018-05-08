#pragma once
#include <math.h>
#include <unistd.h> //For sleep()
#include <iostream>
#include <GL/glut.h>

class Projectile{
    float x,y,diameter;
public:
    void setPosition(float x,float y,float radius);;
    void movePosition(float x,float y,float radius);
    void output();
    Projectile duplicate(Projectile& pro);
    float getDiameter();
    float getX();
    float getY();
    std::string describe();
} ;
