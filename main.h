#pragma once
#include <GL/glut.h> //apt install freeglut3-dev for Debian based systems
#include <iostream> //Required for cout
#include <ctime> //Needed for srand ( time(NULL) );
#include <list> //Needed fro std::list
#include <pthread.h>
#include <cmath> //For sqrt
#include <string>
#include "projectile.h"

float createRandCord(void);
void displayMe(void);
void drawRectangle(void);
void keyPressed(unsigned char key,int x,int y);
void keyUp(unsigned char key,int x,int y);
void detectCollisions(void);
