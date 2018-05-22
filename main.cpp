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
int score = 0;

#define tickSpeed 0.1
#define screenWidth 1920
#define screenHeight 1080
#define CREATE_RANDOM_CORD ((((rand()) % 200 + 1)-100)*0.01)//Generates a float between -1 and 1
#define DEBUG 0 //Change to 1 for debug statments



void detectCollisions(void){ //TODO move to util file
    float projX = proj.getX();
    float projY = proj.getY();
    float proj2X = fruit.getX();
    float combinedRadius = proj.getRadius() + fruit.getRadius();
    float distanceBetween = sqrt(pow(proj2X-projX,2)+pow(fruit.getY()-proj.getY(),2));

    if (DEBUG) {
        std::cout << "Distance between=" << distanceBetween << '\n';
        std::cout << "combined" << combinedRadius << '\n';
    }
    if (distanceBetween <= combinedRadius){
     score += 1;
     std::cout<< "Score: " << score << '\n';
     fruit.movePosition(CREATE_RANDOM_CORD,CREATE_RANDOM_CORD,0.05);
    }
    if (projX > 1) gameRunning = false;
    if (projX <-1) gameRunning = false;
    if (projY > 1) gameRunning = false;
    if (projY <-1) gameRunning = false;
}


/*
 This function is called whilst the system is idle in the glutMainLoop
*/
void display(void){
    //Can't use switch statement as it will block key combinations
glClear(GL_COLOR_BUFFER_BIT); //Creates a black background to the window
    if (lIsPressed) proj.movePosition(0.05,0,0.05);
    if (hIsPressed) proj.movePosition(-0.05,0,0.05);
    if (kIsPressed) proj.movePosition(0,0.05,0.05);
    if (jIsPressed) proj.movePosition(0,-0.05,0.05);

    proj.movePosition(0,0,0.05); //Forcing to draw the shapes every frame. TODO this seems kinda hacky
    fruit.movePosition(0,0,0.05);
    detectCollisions();
}

void *timer(void *threadID){ //TODO make timer appear on screen //TODO move to util file
    float duration = 0;
    while(gameRunning){
        duration += tickSpeed;
        sleep(tickSpeed);
    }
    std::cout<<"Game ran for: " << duration <<" seconds\n";
    exit(0);

}

int main(int argc, char** argv){
    srand(time(NULL)); //Seeds the random number generator. Without it same numbers generated every time the program is run
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(screenWidth,screenHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("openGlStuff");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);

    //Creating our objects
    proj.movePosition(CREATE_RANDOM_CORD,CREATE_RANDOM_CORD,0.05);

    //Creating a new thread for the timer
    pthread_t timerThread; //Only 1 thread for now so no need to store it in an array.
    pthread_create(&timerThread,NULL,timer,(void *)1); //Has to pass a pointer to a function not a function by value.

    glutMainLoop();
    std::cout<<"Game over!\n";
    return 0;
}

void keyPressed(unsigned char key,int x,int y){
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

