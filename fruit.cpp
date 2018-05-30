#include "fruit.h"


Fruit::Fruit(){
    this->x=0;
    this->y=0;
    this->radius=0.05;
}
void Fruit::moveToRandomPosition(void){
    this->x = CREATE_RANDOM_CORD;
    this->y = CREATE_RANDOM_CORD;

    glBegin(GL_POLYGON);
    glVertex2f(this->x+(0.5*radius) ,this->y+(0.5*radius));
    glVertex2f(this->x-(0.5*radius) ,this->y+(0.5*radius));
    glVertex2f(this->x-(0.5*radius) ,this->y-(0.5*radius));
    glVertex2f(this->x+(0.5*radius) ,this->y-(0.5*radius));
    glEnd();
    glutSwapBuffers();
    glFlush(); //Forces defined openGL command to be run

}

void Fruit::movePosition(float x,float y){
    this->y += y; //Can also be writen (*this).x +=x;
    this->x += x;
    glBegin(GL_POLYGON);
    glVertex2f(this->x+(0.5*radius) ,this->y+(0.5*radius));
    glVertex2f(this->x-(0.5*radius) ,this->y+(0.5*radius));
    glVertex2f(this->x-(0.5*radius) ,this->y-(0.5*radius));
    glVertex2f(this->x+(0.5*radius) ,this->y-(0.5*radius));
    glEnd();
    glutSwapBuffers();
    glFlush();
}

float Fruit::getRadius(void){
    return this->radius;
}

float Fruit::getX(void){
    return this->x;
}

float Fruit::getY(void){
    return this->y;
}
