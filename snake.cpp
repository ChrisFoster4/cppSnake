#include "snake.h"

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
 * Detects collisions between the snake and a wall and a collision between the snake and itself
 */
void Projectile::detectSnakeCollision(bool* gameRunning,int* length){
    //Detecting wall collisions
    if (this->x > 1) *gameRunning = false;
    if (this->x <-1) *gameRunning = false;
    if (this->y > 1) *gameRunning = false;
    if (this->y <-1) *gameRunning = false;

    float combinedRadius = this->radius *2;
    double distanceBetween=0;
    snakePart* currentSnakePart = this->snakeHead->next; //The first part of the snake not the first node of the linked list
    for (;currentSnakePart!=nullptr;currentSnakePart=currentSnakePart->next){
        if (currentSnakePart->x!=NULL){
            drawSnakePart(currentSnakePart->x,currentSnakePart->y);
        }
    }
    if (*length>1) { //TODO Check from a 3 long snake onwards
        snakePart *firstSnakePart = snakeHead->next;
        currentSnakePart = firstSnakePart->next;
        if (firstSnakePart->x == NULL) {
            std::cout << "firstSnakePart->x =NULL\n";
        } else {
            std::cout << "firstSnakePart ->x" << firstSnakePart->x << '\n';
        }

        int i = 1;
        std::cout << "Entering while loop\n";
         while (currentSnakePart != NULL){
        std::cout << "distanceBetween being calculated\n";
        float x2, x1, y2, y1;
        x2 = firstSnakePart->x;
        x1 = currentSnakePart->x;
        y2 = firstSnakePart->y;
        y1 = currentSnakePart->y;
        distanceBetween = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));

        std::cout << "distanceBetween calculated as :" << distanceBetween << '\n';
        if (distanceBetween < this->radius - 0.01) {
            std::cout << "Snake crash!\n";
            std::cout << "distance between= " << distanceBetween << '\n';
            std::cout << "firstSnakePart, x=" << firstSnakePart->x << " y=" << firstSnakePart->y << '\n';
            std::cout << "currentSnakePart, x=" << currentSnakePart->x << " y=" << currentSnakePart->y << '\n';
            std::cout << "i=" << i << " \n";
            *gameRunning = false;
        } else {
            std::cout << "distance between firstpart and current=" << distanceBetween << " where part=" << i << " \n";
        }
        currentSnakePart = currentSnakePart->next;
        i++;
    }
    }else{
        std::cout << "Not checking for collions\n";
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
        snakePart* remainderOfList = head->next;
        head->next=NULL; //Stopping the main linked list knowing about the to be removed tail

        while (remainderOfList){ //Deleting the remainder of the linked list to avoid a memory leak
            snakePart* old = remainderOfList;
            remainderOfList = remainderOfList->next;
            delete old;
        }
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
