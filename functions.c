#include "structures.h"


//
char mesg[]="Snake Game"; //message to be appeared on the screen
int row,col; //to store the number of rows and the number of colums of the screen
char input=' ', option;



void initGraphics(){
    initscr(); //start the curses mode
    //raw();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    //keypad(stdscr, TRUE);
    getmaxyx(stdscr,row,col); //get the number of rows and columns
}

void setup(typeSnake *snake){
    snake->headDraw = '@';
    snake->bodyDraw = '*';

    snake->head.posX = 0;
    snake->head.posY = 0;

    snake->body.qntParts = 0;
}

void drawGame(){
    int i=0;

    typeSnake snake;
    setup(&snake);


    while(input!='q'){
        // @************** draw the snake on screen **************@
        //draw the snake head
        mvprintw(snake.head.posY, snake.head.posX, "%c", snake.headDraw);
        //draw the snake body
        if(snake.body.qntParts > 0){
            for(i=0; i<snake.body.qntParts; i++){
                mvprintw(snake.body.bodyPart[i].posY, snake.body.bodyPart[i].posX, "%c", snake.bodyDraw);
            }
            //mvprintw(snake.body.bodyPart[snake.body.qntParts-1].posY, snake.body.bodyPart[snake.body.qntParts-1].posX, "%c", snake.bodyDraw);
        }



        // @************** write the informations on screen **************@
        mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg); //print the message at the center of the screen */
        mvprintw(row-2,0,"This screen has %d rows and %d columns\n", row,col);
        mvprintw(row-2,col-14,"BodyParts: %d\n", snake.body.qntParts);



        //@************** write the changes on screen **************@
        refresh();
        usleep(100000);



        //@************** catch the input from keyboard **************@
        //if the input is one of the options, it passes to 'option', which will movement the positions
        input = getch();
        if(input=='w' || input=='s' || input=='a' || input=='d'){
            option = input;
        }
        else if(input=='h'){ //only for testing, remember to change later
            snake.body.qntParts++;
        }



        //@************** Clean the old positions
        for(i=0; i<snake.body.qntParts; i++){
            mvprintw(snake.body.bodyPart[i].posY, snake.body.bodyPart[i].posX, " ");
        }
        if(option=='w' || option=='s' || option=='a' || option=='d'){
            mvprintw(snake.head.posY, snake.head.posX, " ");
        }



        //@************** Movement
        //body movement
        for(i=snake.body.qntParts; i>0; i--){
            snake.body.bodyPart[i] = snake.body.bodyPart[i-1];
        }
        snake.body.bodyPart[0] = snake.head;
        //head movement
        switch(option){
            case 'w': //up
                snake.head.posY--;
                break;
            case 's': //down
                snake.head.posY++;
                break;
            case 'a': //left
                snake.head.posX = snake.head.posX-2;
                break;
            case 'd': //right
                snake.head.posX = snake.head.posX+2;
                break;
        }
        //reset positions if get out of window
        if(snake.head.posX > col){
            snake.head.posX = 0;
        }
        else if(snake.head.posX < 0){
            snake.head.posX = col;
        }
        if(snake.head.posY > row){
            snake.head.posY = 0;
        }
        else if(snake.head.posY < 0){
            snake.head.posY = row;
        }


    }
    
    endwin(); //end curses mode
}