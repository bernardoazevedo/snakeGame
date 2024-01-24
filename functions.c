#include "structures.h"


char mesg[]="Snake Game"; //message to be appeared on the screen
int row,col; //to store the number of rows and the number of colums of the screen
char input, option;


void initGraphics(){
    initscr(); //start the curses mode
    //raw();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    //keypad(stdscr, TRUE);
    getmaxyx(stdscr, row, col); //get the number of rows and columns
}

typeSnake snakeSetup(){
    int i=0;
    typeSnake snake;

    //setting positions to 0
    snake.head.posX = 0;
    snake.head.posY = 0;
    snake.body.qntParts = 0;
    for(i=0; i<1000; i++){
        snake.body.bodyPart[i].posX = 0;
        snake.body.bodyPart[i].posY = 0;
    }

    //set the chars that represents each snake part 
    snake.headDraw = '@';
    snake.bodyDraw = 'o';
    //set the initial positions
    snake.head.posX = 0;
    snake.head.posY = 0;
    snake.body.qntParts = 0;

    return snake;
}

typeFood foodSetup(){
    typeFood food;

    //setting positions to 0
    food.position.posX = 0;
    food.position.posY = 0;

    //the char that represents the food
    food.foodDraw = '*';

    food.position.posX = col-(col/2); // since x position runs from 2 to 2, the food posX can't be odd
    if((food.position.posX % 2) != 0){
        food.position.posX--;
    }
    
    food.position.posY = row-(row/2);

    return food;
}

void gameSetup(){
    input=' ';
    option=' ';
}


void drawGameInfos(typeSnake snake, typeFood food, int highScore){ //write the informations on screen
    mvprintw(row-2,0,"Score: %d\n", snake.body.qntParts); //for testing, can be the score! -yes, the score!
    mvprintw(row-1,0,"highScore: %d\n", highScore); //the best
}

void drawSnake(typeSnake snake){
    // draw the snake head
    int i;

    mvprintw(snake.head.posY, snake.head.posX, "%c", snake.headDraw);

    // draw the snake body
    if(snake.body.qntParts > 0){
        for(i=0; i<snake.body.qntParts; i++){
            mvprintw(snake.body.bodyPart[i].posY, snake.body.bodyPart[i].posX, "%c", snake.bodyDraw);
        }
    }
}

void drawFood(typeFood food){
    mvprintw(food.position.posY, food.position.posX, "%c", food.foodDraw);
    mvprintw(row-1, col-1, " "); // only for move the cursor to the end of the screen
}

void writeScreen(typeSnake snake, typeFood food, int highScore){ // write the game
    drawGameInfos(snake, food, highScore);
    drawSnake(snake);
    drawFood(food);
}

void cleanSnakeOldPositions(typeSnake snake){ // cleaning the snake old positions
    // clean the body
    int i;

    for(i=0; i<snake.body.qntParts; i++){
        mvprintw(snake.body.bodyPart[i].posY, snake.body.bodyPart[i].posX, " ");
    }

    // clean the head
    if(option=='w' || option=='s' || option=='a' || option=='d'){
        mvprintw(snake.head.posY, snake.head.posX, " ");
    }
}

void cleanFoodPosition(typeFood food){ // clean the food position
    mvprintw(food.position.posY, food.position.posX, " ");
}

void foodMovement(typeFood *food, typeSnake *snake){ // do the moviment logic of food
    srand(time(NULL));
    bool correct;
    int i;

    do{
        //this loop provides a random position for the food and assure that the position is valid  
        correct=true;

        // give a random x and y position for the food
        food->position.posX = rand() % col;
        food->position.posY = rand() % row;

        // checks if the position x is pair, because x moves from 2 to 2 positions
        if(food->position.posX % 2 != 0){
            correct=false;
        }

        // checks if the given random position is the same of head
        if(food->position.posX == snake->head.posX){
            if(food->position.posY == snake->head.posY){
                correct=false;
            }
        }

        // checks if the given random position is the same of any part of snake body
        for(i=0; i<snake->body.qntParts; i++){
            if(food->position.posX == snake->body.bodyPart[i].posX){
                if(food->position.posY == snake->body.bodyPart[i].posY){
                    correct=false;
                }
            }
        }

    }while(!correct);
}

int movement(typeSnake *snake, typeFood *food){ // movement of snake head, snake body and food
    int i;
    
    //check if head will hit the body
    for(i=snake->body.qntParts-1; i>=0; i--){
        if(snake->head.posX == snake->body.bodyPart[i].posX){
            if(snake->head.posY == snake->body.bodyPart[i].posY){
                return 1;
            }
        }
    }

    //if the snake eat the food, food movements
    if((snake->head.posX == food->position.posX) && (snake->head.posY == food->position.posY)){
        foodMovement(food, snake);
        if(snake->body.qntParts<1000){
            snake->body.qntParts++;
        }
    }

    //body movement
    for(i=snake->body.qntParts-1; i>0; i--){
        snake->body.bodyPart[i] = snake->body.bodyPart[i-1];
    }
    snake->body.bodyPart[0] = snake->head;

    //head movement
    switch(option){
        case 'w': //up
            snake->head.posY--;
            break;
        case 's': //down
            snake->head.posY++;
            break;
        case 'a': //left
            snake->head.posX = snake->head.posX-2;
            break;
        case 'd': //right
            snake->head.posX = snake->head.posX+2;
            break;
    }

    /*
    //reset positions if get out of window
    if(snake->head.posX > col-2){
        snake->head.posX = 0;
    }
    else if(snake->head.posX < 0){
        snake->head.posX = col-2;
    }
    if(snake->head.posY > row-1){
        snake->head.posY = 0;
    }
    else if(snake->head.posY < 0){
        snake->head.posY = row-1;
    }
    */

    //if you get out of window, Game Over 
    if((snake->head.posX > col-2) || (snake->head.posX < 0) || (snake->head.posY > row-1) || (snake->head.posY < 0)){
        return 1;
    }

    return 0;
}

void catchInput(){
    //catch the input from keyboard
    //if the input is one of the options, it passes to 'option', which will movement the positions
    input = getch();
    if(input=='w' || input=='s' || input=='a' || input=='d'){
        //this don't allow the snake to turn 180º at once time
        if(!(option=='w' && input=='s') && !(option=='s' && input=='w') && !(option=='a' && input=='d') && !(option=='d' && input=='a')){
            option = input;
        }
    }
}

int drawGame(int highScore){
    typeSnake snake;
    typeFood food;

    gameSetup();
    snake = snakeSetup();
    food = foodSetup();

    while(input!='q'){
        //write the changes on screen
        writeScreen(snake, food, highScore);
        refresh();
        usleep(100000);

        catchInput();

        cleanSnakeOldPositions(snake);

        //if the head collides with the body or wall, the game will end and the food position will be cleaned
        if(movement(&snake, &food) == 1){ 
            input = 'q';
            cleanFoodPosition(food); 
        }
    }

    refresh();
    usleep(1000000);

    endwin(); //end curses mode
    return snake.body.qntParts;
}