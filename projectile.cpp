#include "projectile.h"

void Projectile::movePosition(float x,float y,float radius){
    this->radius=radius;
    (*this).x += x; //Same as this->x. Another method of writting it
    this->y += y;
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
    foo.radius = pro.radius;
    return foo;
}

void Projectile::output(){
    std::cout << this->x << '\n';
}

float Projectile::getRadius(){
    return this->radius;
}

float Projectile::getX(){
    return this->x;
}

float Projectile::getY(){
    return this->y;
}
