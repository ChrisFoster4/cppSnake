#pragma once
#include <GL/glut.h> //apt install freeglut3-dev for Debian based systems
#include <iostream> //Required for cout
#include <ctime> //Needed for srand ( time(NULL) );
#include <pthread.h>
#include <cmath> //For sqrt
#include <stdlib.h>
#include "snake.h"
#include "fruit.h"

#define TICK_DELAY 1 //Delay is seconds
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define CREATE_RANDOM_CORD ((((rand()) % 200 + 1)-100)*0.01)//Generates a float between -1 and 1


float createRandCord(void);
void displayMe(void);
void drawRectangle(void);
void keyPressed(unsigned char key,int x,int y);
void keyUp(unsigned char key,int x,int y);
void detectFruitCollision(void);

Snake snake; //TODO find a better way to make this accesible to display func than global variable
Fruit fruit;
bool lIsPressed = false;
bool hIsPressed = false;
bool jIsPressed = false;
bool kIsPressed = false;
bool gameRunning = true;
int direction = 12; //12 = up  3 = right 6 = down 9 = left
int score = 0;
int length=2;
