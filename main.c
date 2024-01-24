#include "structures.h"


int main(){
    char getOut;
    int score=0, highScore=0;

    do{
        initGraphics();
        score = drawGame(highScore);

        system("clear");

        printf("\nGame Over!\n");

        if(score>highScore){
            printf("\nYou did the highest score!\n");

            printf("\nOld high score: %d\n", highScore);
            printf("Your score: %d\n", score);
            
            highScore = score;
        }
        else{
            printf("\nYour score: %d\n", score);
            printf("High score: %d\n", highScore);
        }


        printf("\nWould you like to play again?\n");
        printf("[Y]/[N]: ");
        getch();
        scanf(" %c", &getOut);

        if(score>highScore){
            highScore = score;
        }
    }while(getOut=='y');

    return 0;
}