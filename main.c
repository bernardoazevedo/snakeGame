/* 
                                                PROGRESS

___SOLVED:
-> WHEN YOU COME BACK AT CODING THIS, TRY WITH ONLY ONE POINT OF BODY FIRST, WILL BE EASIER TO UNDERSTAND THE LOGIC. 
WHEN IT WORKS WITH ONE, YOU CAN ADD MORE.

___TO DO:
-> FIX THE LOOP TO PLAY AGAIN: NEEDS TO CLEAN THE INFORMATIONS OF END GAME BEFORE START AGAIN
-> STORE THE RECORD IN MEMORY
-> STORE THE PLAYER NAME AND RECORD WITH DATA PERSISTENCY
-> ORGANIZE THE CODE


___TIPS:
-> Study the Ninvaders and Bastet Github page can help a lot.
*/

#include "structures.h"


int main(){
    char getOut;
    int score=0, record=0;

    do{
        initGraphics();
        score = drawGame(record);

        printf("\nWould you like to play again?\n");
        printf("[Y]/[N]: ");
        scanf("%c", &getOut);

        if(score>record){
            record = score;
        }
    }while(getOut=='y');

    return 0;
}