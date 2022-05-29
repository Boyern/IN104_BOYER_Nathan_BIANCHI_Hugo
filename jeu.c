#include <stdio.h>
#include "pacman.c"
#include "sudoku.c"


int main(){
    int i=0;
    int a;
    do{
        printf("Choisissez le jeu auquel vous voulez jouer : \n 1 : Pacman 2 : Sudoku\n");
        scanf("%d",&i);
        } while(i!=1 && i!= 2 && i!= 3);


    if(i==1){
        a=jeu_pacman();

    }

    if(i==2){
        a=jeu_sudoku();
    }


    return a;
}