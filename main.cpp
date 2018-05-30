#include "main.h"


/*
 Tutorials used.
 https://www.badprog.com/c-opengl-hello-world
 https://www.youtube.com/watch?v=7k8RCVfTS7w
 http://www.swiftless.com/tutorials/opengl/keyboard.html
 https://stackoverflow.com/questions/44828434/how-do-i-draw-a-shape-on-key-press-using-glut
*/






/*
 This function is called whilst the system is idle in the glutMainLoop
*/
void display(void){
    glClear(GL_COLOR_BUFFER_BIT); //Creates a black background to the window

    if (lIsPressed && direction !=9 ) direction=3;
    if (jIsPressed && direction !=12) direction=6;
    if (hIsPressed && direction !=3 ) direction=9;
    if (kIsPressed && direction !=6 ) direction=12;


    //Forcing shapes to draw every frame. TODO remove this hack
    snake.movePosition(0,0);
    fruit.movePosition(0,0);

    snake.detectFruitCollision(fruit,&score,&length);
    snake.detectSnakeCollision(&gameRunning,&length);
    snake.setLength(length);
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


    //Creating a 3 long snake with it's head at (0,0)
    snake.movePosition(0,-0.1);
    snake.movePosition(0,0.05);
    snake.addSnakePart(snake.getX(),snake.getY());
    snake.movePosition(0,0.05);
    snake.addSnakePart(snake.getX(),snake.getY());


    //Move the fruit to it's random starting point onscreen
    fruit.moveToRandomPosition();

    //Creating a new thread for the timer
    pthread_t timerThread;
    pthread_create(&timerThread,NULL,timer,(void *)1); //Has to pass a pointer to a function not a function by value.

    glutMainLoop();
    return 0;
}

void keyPressed(unsigned char key,int x,int y){ //x and y are the position of the mouse when the key is pressed
    switch(key){
        case 27:
            gameRunning = false;
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
    }
    glutPostRedisplay();
    // glutPostRedisplay merely sets a flag for the main loop to call the display function if no further events are pending, so timing a frame redraw through that is not very accurate.https://stackoverflow.com/questions/30381064/how-to-reduce-opengl-cpu-usage-and-or-how-to-use-opengl-properly
}

void keyUp(unsigned char key,int x,int y){
    switch (key){
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
            break;
    }
    glutPostRedisplay();
}

