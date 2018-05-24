#pragma once
#include <GL/glut.h> //apt install freeglut3-dev for Debian based systems
#include <iostream> //Required for cout
#include <ctime> //Needed for srand ( time(NULL) );
#include <list> //Needed fro std::list
#include <pthread.h>
#include <cmath> //For sqrt
#include <string>
#include <stdlib.h>
#include "projectile.h"

#define TICK_DELAY 1
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define CREATE_RANDOM_CORD ((((rand()) % 200 + 1)-100)*0.01)//Generates a float between -1 and 1
#define DEBUG 1 //Set to 1 for debug statements


float createRandCord(void);
void displayMe(void);
void drawRectangle(void);
void keyPressed(unsigned char key,int x,int y);
void keyUp(unsigned char key,int x,int y);
void detectFruitCollision(void);

//void addSnakePart(snakePart* head,float x,float y);
//
//
//void outputSnakeCords(snakePart* head);
