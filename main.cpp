#include "main.h"


/*
 Tutorials used.
 https://www.badprog.com/c-opengl-hello-world
 https://www.youtube.com/watch?v=7k8RCVfTS7w
 http://www.swiftless.com/tutorials/opengl/keyboard.html
 https://stackoverflow.com/questions/44828434/how-do-i-draw-a-shape-on-key-press-using-glut
*/


Projectile proj; //TODO find a better way to make this accesible to display func than global variable
Projectile fruit;
bool nIsPressed = false;
bool lIsPressed = false;
bool hIsPressed = false;
bool jIsPressed = false;
bool kIsPressed = false;
bool wIsPressed = false;
bool sIsPressed = false;
bool aIsPressed = false;
bool dIsPressed = false;
bool gameRunning = true;
int direction = 12; //12 = up  3 = right 6 = down 9 = left
int score = 0;


#define TICK_DELAY 1
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define CREATE_RANDOM_CORD ((((rand()) % 200 + 1)-100)*0.01)//Generates a float between -1 and 1
#define DEBUG 1 //Set to 1 for debug statements

/*
 * Detects a collision between the snake and the the fruit
 */
void detectFruitCollision(void){ //TODO move to util file
    float projX = proj.getX();
    float projY = proj.getY();
    float proj2X = fruit.getX();
    float combinedRadius = proj.getRadius() + fruit.getRadius();
    float distanceBetween = sqrt(pow(proj2X-projX,2)+pow(fruit.getY()-proj.getY(),2));

    if (distanceBetween <= combinedRadius){
        score++;
        std::cout<< "Score: " << score << '\n';
        fruit.movePosition(CREATE_RANDOM_CORD,CREATE_RANDOM_CORD);

    }
}

/*
 * Detects collisions between the snake a wall and a collision the snake and itself
 */
void detectSnakeCollision(){
    float projX = proj.getX();
    float projY = proj.getY();
    //Detecting wall collisions
    if (projX > 1) gameRunning = false;
    if (projX <-1) gameRunning = false;
    if (projY > 1) gameRunning = false;
    if (projY <-1) gameRunning = false;

}


void addSnakePart(snakePart* head,float x,float y){
 snakePart* newPart = (snakePart*) malloc(sizeof(snakePart));
 newPart->x = x;
 newPart->y = y;
 newPart->next=head->next;
 head->next=newPart;
}

void outputSnakeCords(snakePart* head){
    std::cout<<"Outputing snake cords\n";
    head=head->next;//So the head of the list isn't printed out.It stores nothing.
        for (int i=0;head!=NULL;i++){
        std::cout << "The data at position: "<<i<<" is, x="<<head->x<<" y="<<head->y<<'\n';
        head = head->next;
    }
    std::cout << "End of list\n";
}

/*
 This function is called whilst the system is idle in the glutMainLoop
*/
void display(void){
    glClear(GL_COLOR_BUFFER_BIT); //Creates a black background to the window
    //Can't use switch statement as it will block key combinations

    if (lIsPressed) direction=3;
    if (jIsPressed) direction=6;
    if (hIsPressed) direction=9;
    if (kIsPressed) direction=12;

    proj.movePosition(0,0); //Forcing to draw the shapes every frame. TODO this seems kinda hacky
    fruit.movePosition(0,0);
    detectFruitCollision();
    detectSnakeCollision();
}

void glutCallbackTimer(int extra)
{
    glutPostRedisplay();
    glutTimerFunc(30, glutCallbackTimer, 0);
}

void *timer(void *threadID){ //TODO make timer appear on screen //TODO move to util file
    float duration = 0;
    while(gameRunning){
        duration += TICK_DELAY;
        switch (direction){ //TODO Move snake functionality should be moved to it's own thread
            case 3:
                proj.movePosition(0.05,0);
                proj.addSnakePart(proj.getX(),proj.getY());
                glutPostRedisplay();
                break;
            case 6:
                proj.movePosition(0,-0.05);
                proj.addSnakePart(proj.getX(),proj.getY());
                glutPostRedisplay();
                break;
            case 9:
                proj.movePosition(-0.05,0);
                proj.addSnakePart(proj.getX(),proj.getY());
                glutPostRedisplay();
                break;
            case 12:
                proj.movePosition(0,0.05);
                proj.addSnakePart(proj.getX(),proj.getY());
                glutPostRedisplay();
                break;
        }
        proj.outputSnakeCords();
        sleep(TICK_DELAY);
    }
    std::cout<<"Game ran for: " << duration <<" seconds\n";
    exit(0);

}

int main(int argc, char** argv){
    srand(time(NULL)); //Seeds the random number generator. Without it same numbers generated every time the program is run
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("openGlStuff");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
    glutTimerFunc(0, glutCallbackTimer, 0);

    //Creating our objects
    proj.movePosition(CREATE_RANDOM_CORD,CREATE_RANDOM_CORD);

    //Creating a new thread for the timer
    pthread_t timerThread; //Only 1 thread for now so no need to store it in an array.
    pthread_create(&timerThread,NULL,timer,(void *)1); //Has to pass a pointer to a function not a function by value.

    glutMainLoop();
    std::cout<<"Game over!\n";
    return 0;
}

void keyPressed(unsigned char key,int x,int y){ //x and y are the position of the mouse when the key is pressed
    switch(key){
        case 27:
            gameRunning = false;
            break;
        case 'n':
            nIsPressed = true;
            break;
        case 'l':
            lIsPressed = true;
            break;
        case 'h':
            hIsPressed = true;
            break;
        case 'j':
            jIsPressed = true;
            break;
        case 'k':
            kIsPressed = true;
            break;
        case 'w':
            wIsPressed = true;
            break;
        case 'a':
            aIsPressed = true;
            break;
        case 's':
            sIsPressed = true;
            break;
        case 'd':
            dIsPressed = true;
            break;
    }
    glutPostRedisplay();
    // glutPostRedisplay merely sets a flag for the main loop to call the display function if no further events are pending, so timing a frame redraw through that is not very accurate.https://stackoverflow.com/questions/30381064/how-to-reduce-opengl-cpu-usage-and-or-how-to-use-opengl-properly
}

void keyUp(unsigned char key,int x,int y){
    switch (key){
        case 'n':
            nIsPressed = false;
            break;
        case 'l':
            lIsPressed = false;
            break;
        case 'h':
            hIsPressed = false;
            break;
        case 'j':
            jIsPressed = false;
            break;
        case 'k':
            kIsPressed = false;
        case 'w':
            wIsPressed = false;
            break;
        case 'a':
            aIsPressed = false;
            break;
        case 's':
            sIsPressed = false;
            break;
        case 'd':
            dIsPressed = false;
            break;
    }
    glutPostRedisplay();
}

