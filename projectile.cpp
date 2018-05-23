#include "projectile.h"

Projectile::Projectile(){
    y=0;
    x=0;
    radius=0.05;
}

void Projectile::addSnakePart(float x,float y){
    std::cout << "addSnakePart called\n";
    snakePart* newPart = (snakePart*) malloc(sizeof(snakePart));
    newPart->x=x;
    newPart->y=y;
    newPart->next=this->snakeHead->next;
    snakePart* firstSnakePart = (snakePart*) malloc(sizeof(snakePart));
    firstSnakePart = snakeHead->next;
    snakeHead->next = newPart;
    newPart->next = firstSnakePart;

}

void Projectile::outputSnakeCords(){
    std::cout<<"Outputing snake cords\n";
    snakePart* head = this->snakeHead;
    head=head->next;//So the head of the list isn't printed out.It stores nothing.
    for (int i=0;head!=nullptr;i++){
        std::cout << "The data at position: "<<i<<" is, x="<<head->x<<" y="<<head->y<<'\n';
        head = head->next;
    }
    std::cout << "End of list\n";
}

void Projectile::movePosition(float x,float y){
    (*this).x += x; //Same as this->x. Another method of writting it
    this->y += y;
    glBegin(GL_POLYGON);
    glVertex2f(this->x+(0.5*radius) ,this->y+(0.5*radius));
    glVertex2f(this->x-(0.5*radius)  ,this->y+(0.5*radius));
    glVertex2f(this->x-(0.5*radius) ,this->y-(0.5*radius));
    glVertex2f(this->x+(0.5*radius) ,this->y-(0.5*radius));
    glEnd();
    glutSwapBuffers();
    glFlush();
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
