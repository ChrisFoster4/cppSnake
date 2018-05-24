#include "projectile.h"

Projectile::Projectile(){
    y=0;
    x=0;
    radius=0.05;
}

void Projectile::addSnakePart(float x,float y){
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
    snakePart* head = this->snakeHead;
    head=head->next;//So the head of the list isn't printed out.It stores nothing.
    for (int i=0;head!=nullptr;i++){
        std::cout << "The data at position: "<<i<<" is, x="<<head->x<<" y="<<head->y<<'\n';
        head = head->next;
    }
    std::cout << "End of list\n";
}

/*
 * Detects a collision between the snake and the the fruit
 */
void Projectile::detectFruitCollision(Projectile& fruit,int* score){ //todo move to snake file. pass fruit via pointer
    float combinedRadius = this->radius + fruit.getRadius();
    float distanceBetween = sqrt(pow(fruit.getX()-this->x,2)+pow(fruit.getY()-this->y,2));

    if (distanceBetween <= combinedRadius){
        *score=*score+1;
        std::cout<< "Score: " << *score << '\n';
        fruit.movePosition(CREATE_RANDOM_CORD,CREATE_RANDOM_CORD);
    }
}

/*
 * Detects collisions between the snake a wall and a collision the snake and itself
 */
void Projectile::detectSnakeCollision(bool* gameRunning,int* length){
    //Detecting wall collisions
    if (this->x > 1) *gameRunning = false;
    if (this->x <-1) *gameRunning = false;
    if (this->y > 1) *gameRunning = false;
    if (this->y <-1) *gameRunning = false;
    std::cout <<this->snakeHead->x<<"\n";
    std::cout <<this->snakeHead->next->x<<"\n";

    float combinedRadius = this->radius *2;
    float distanceBetween;
    snakePart* head = this->snakeHead;
    head=head->next;//So the head of the list isn't printed out.It stores nothing.
    for (int i=0;head!=nullptr;i++){
        std::cout << "The data at position: "<<i<<" is, x="<<snakeHead->next->x<<" y="<<snakeHead->next->y<<'\n';
        distanceBetween = sqrt(pow(head->x-snakeHead->next->x,2)+pow(head->y-snakeHead->next->y,2));
        if (head->x!=NULL){
            drawSnakePart(head->x,head->y);
        }
        if (i!=0){

        }
//            if ((distanceBetween <= combinedRadius)&&distanceBetween !=0) { //2nd part of && to stop programing ending instantly
//                std::cout<<"Snake crashed into itself!!\n";
//                *gameRunning=false;
//            }
        head = head->next;
    }
}

void Projectile::movePosition(float x,float y){
    (*this).x += x; //Same as this->x. Another method of writing it
    this->y += y;
    glBegin(GL_POLYGON);
    glVertex2f(this->x+(0.5*radius) ,this->y+(0.5*radius));
    glVertex2f(this->x-(0.5*radius) ,this->y+(0.5*radius));
    glVertex2f(this->x-(0.5*radius) ,this->y-(0.5*radius));
    glVertex2f(this->x+(0.5*radius) ,this->y-(0.5*radius));
    glEnd();
    glutSwapBuffers();
    glFlush();
}

void Projectile::drawSnakePart(float x,float y){
    glBegin(GL_POLYGON);
    glVertex2f(x+(0.5*radius) ,y+(0.5*radius));
    glVertex2f(x-(0.5*radius) ,y+(0.5*radius));
    glVertex2f(x-(0.5*radius) ,y-(0.5*radius));
    glVertex2f(x+(0.5*radius) ,y-(0.5*radius));
    glEnd();
    glutSwapBuffers();
    glFlush();
}

void Projectile::setLength(int snakeLength){
        snakePart* head = (snakePart*) malloc(sizeof(snakePart));
        head=this->snakeHead;
        for (int i=0;i<=snakeLength;i++){
            head=head->next;
        }
        head->next=NULL;
        //TODO free remainder of linked list. THIS IS A MEMORY LEAK!!!!
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
