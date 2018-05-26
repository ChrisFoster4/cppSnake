#include "main.h"


/*
 Tutorials used.
 https://www.badprog.com/c-opengl-hello-world
 https://www.youtube.com/watch?v=7k8RCVfTS7w
 http://www.swiftless.com/tutorials/opengl/keyboard.html
 https://stackoverflow.com/questions/44828434/how-do-i-draw-a-shape-on-key-press-using-glut
*/


Projectile snake; //TODO find a better way to make this accesible to display func than global variable
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

    snake.movePosition(0,0); //Forcing to draw the shapes every frame. TODO this seems kinda hacky
    fruit.movePosition(0,0);
    snake.detectFruitCollision(fruit,&score);
    snake.detectSnakeCollision(&gameRunning,&score);
        snake.setLength(score);
}

void glutCallbackTimer(int extra){ //Forces the redisplay function to be called after a set amount of time
    glutPostRedisplay();
    glutTimerFunc(30, glutCallbackTimer, 0);
}

void *timer(void *threadID){ //TODO make timer appear on screen //TODO move to util file
    float duration = 0;
    while(gameRunning){
        duration += TICK_DELAY;
        switch (direction){ //TODO Move snake functionality should be moved to it's own thread
            case 3:
                snake.movePosition(0.05,0);
                snake.addSnakePart(snake.getX(),snake.getY());
                glutPostRedisplay();
                break;
            case 6:
                snake.movePosition(0,-0.05);
                snake.addSnakePart(snake.getX(),snake.getY());
                glutPostRedisplay();
                break;
            case 9:
                snake.movePosition(-0.05,0);
                snake.addSnakePart(snake.getX(),snake.getY());
                glutPostRedisplay();
                break;
            case 12:
                snake.movePosition(0,0.05);
                snake.addSnakePart(snake.getX(),snake.getY());
                glutPostRedisplay();
                break;
        }
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
    glutCreateWindow("c++ Snake");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
    glutTimerFunc(0, glutCallbackTimer, 0);

    snake.movePosition(CREATE_RANDOM_CORD,CREATE_RANDOM_CORD);

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

