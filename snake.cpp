#include "snake.h"

Snake::Snake(){
    y=0;
    x=0;
    radius=0.05;
}

void Snake::addSnakePart(float x,float y){
    snakePart* newPart = new snakePart;
    newPart->x=x;
    newPart->y=y;
    newPart->next=this->snakeHead->next;
    snakePart* firstSnakePart = new snakePart;
    firstSnakePart = snakeHead->next;
    snakeHead->next = newPart;
    newPart->next = firstSnakePart;
}


/*
 * Detects a collision between the snake and the the fruit
 */
void Snake::detectFruitCollision(Fruit& fruit,int* score){ //todo move to snake file. pass fruit via pointer
    float combinedRadius = this->radius + fruit.getRadius();
    float distanceBetween = sqrt(pow(fruit.getX()-this->x,2)+pow(fruit.getY()-this->y,2));

    if (distanceBetween <= combinedRadius){
        *score=*score+1;
        std::cout<< "Score: " << *score << '\n';
        fruit.moveToRandomPosition();
    }
}

/*
 * Detects collisions between the snake and a wall and a collision between the snake and itself
 */
void Snake::detectSnakeCollision(bool* gameRunning,int* length){
    //Detecting wall collisions
    if (this->x > 1) *gameRunning = false;
    if (this->x <-1) *gameRunning = false;
    if (this->y > 1) *gameRunning = false;
    if (this->y <-1) *gameRunning = false;

    double distanceBetween=0;
    snakePart* currentSnakePart = this->snakeHead->next; //The first part of the snake not the first node of the linked list
    for (;currentSnakePart!=nullptr;currentSnakePart=currentSnakePart->next){
            drawSnakePart(currentSnakePart->x,currentSnakePart->y);
    }
    if (*length>1) { //TODO Check from a 3 long snake onwards
        snakePart *firstSnakePart = snakeHead->next;
        currentSnakePart = firstSnakePart->next;
        int i = 1;
        while (currentSnakePart != NULL){
            float x2, x1, y2, y1;
            x2 = firstSnakePart->x;
            x1 = currentSnakePart->x;
            y2 = firstSnakePart->y;
            y1 = currentSnakePart->y;
            distanceBetween = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));

            if (distanceBetween < this->radius - 0.01) {
                std::cout << "Snake crash!\n";
                *gameRunning = false;
            }
            currentSnakePart = currentSnakePart->next;
            i++;
        }
    }
}

void Snake::movePosition(float x,float y){
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


void Snake::drawSnakePart(float x,float y){
    glBegin(GL_POLYGON);
    glVertex2f(x+(0.5*radius) ,y+(0.5*radius));
    glVertex2f(x-(0.5*radius) ,y+(0.5*radius));
    glVertex2f(x-(0.5*radius) ,y-(0.5*radius));
    glVertex2f(x+(0.5*radius) ,y-(0.5*radius));
    glEnd();
    glutSwapBuffers();
    glFlush();
}

void Snake::setLength(int snakeLength){
        snakePart* head = new snakePart;
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


float Snake::getX(void){
    return this->x;
}

float Snake::getY(void){
    return this->y;
}
