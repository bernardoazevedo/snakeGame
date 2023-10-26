#include <ncursesw/ncurses.h> /* ncurses.h includes stdio.h */
#include <string.h>
#include <unistd.h>

typedef struct bodyPart{
    int posX;
    int posY;
}typeBodyPart;

typedef struct body{
    typeBodyPart bodyPart[100];
    int qntParts;
}typeBody;

typedef struct snake{
    char headDraw;
    char bodyDraw;
    typeBodyPart head;
    typeBody body;
}typeSnake;


void initGraphics();
void drawGame();