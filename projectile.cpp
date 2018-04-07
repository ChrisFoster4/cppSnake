#include "projectile.h"

void Projectile::setPosition(float x,float y,float radius){
    this->x = x;
    this->y = y;
// glClear(GL_COLOR_BUFFER_BIT); //Creates a black background to the window
    glBegin(GL_POLYGON);
    glVertex2f(x-(0.5*radius)  ,y+(0.75*radius));
    glVertex2f(x+(0.25*radius) ,y+(0.75*radius));
    glVertex2f(x+(0.75*radius) ,y+(0.25*radius));
    glVertex2f(x+(0.75*radius) ,y-(0.25*radius));
    glEnd();
    glutSwapBuffers();
    glFlush();
}

void Projectile::movePosition(float x,float y,float radius){
    (*this).x += x; //Same as this->x. Another method of writting it
    this->y += y;
    std::cout <<this->x;

    // glClear(GL_COLOR_BUFFER_BIT); //Creates a black background to the window
    glBegin(GL_POLYGON);
    glVertex2f(this->x-(0.5*radius)  ,this->y+(0.75*radius));
    glVertex2f(this->x+(0.25*radius) ,this->y+(0.75*radius));
    glVertex2f(this->x+(0.75*radius) ,this->y+(0.25*radius));
    glVertex2f(this->x+(0.75*radius) ,this->y-(0.25*radius));
    glEnd();
    glutSwapBuffers();
    glFlush();
}

Projectile Projectile::duplicate(Projectile& pro){
    Projectile foo;
    foo.x = pro.x;
    foo.y = pro.y;
    foo.diameter = pro.diameter;
    return foo;
}

void Projectile::output(){
    std::cout << this->x << std::endl;
}

float Projectile::getDiameter(){
    return this->diameter;
}

float Projectile::getX(){
    return this->x;
}

float Projectile::getY(){
    return this->y;
}
