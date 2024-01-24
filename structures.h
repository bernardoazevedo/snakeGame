#include <ncursesw/ncurses.h> /* ncurses.h includes stdio.h */
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


typedef struct position{
    int posX;
    int posY;
}typePosition;

typedef struct body{
    typePosition bodyPart[1000];
    int qntParts;
}typeBody;

typedef struct snake{
    char headDraw;
    char bodyDraw;
    typePosition head;
    typeBody body;
}typeSnake;

typedef struct food{
    char foodDraw;
    typePosition position;
}typeFood;


void initGraphics();
void gameSetup();
typeSnake snakeSetup();
typeFood foodSetup();

void drawGameInfos(typeSnake snake, typeFood food, int highscore);
void drawSnake(typeSnake snake);
void drawFood(typeFood food);
void writeScreen(typeSnake snake, typeFood food, int highscore);

void cleanSnakeOldPositions(typeSnake snake);
void cleanFoodPosition(typeFood food);

void catchInput();

void foodMovement(typeFood *food, typeSnake *snake);
int movement(typeSnake *snake, typeFood *food);

int drawGame(int highScore;);