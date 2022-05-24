#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int** copie_tableau(int **T){
    
    int** tab;
    tab = calloc(9, sizeof(int*));
    for(int i = 0;i<9;i++) {
        tab[i] = calloc(9, sizeof(int));
    }
    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            tab[i][j] = T[i][j];
        }
    }
    return tab;
}


void afficher_tableau(int** T){
    printf("\n");
    for (int i=0; i<=8; i++){
        for (int j=0; j<=8; j++){
            printf("%d ", T[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void remplir_diag (int** T){

    for (int k=0; k<3; ++k)
	{
        int x[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};

        for (int i = 0; i < 9-1; ++i)
        {
            int j = rand() % (9-i) + i;
            int temp = x[i];
            x[i] = x[j];
            x[j] = temp;
        }
        for (int n = 0; n <= 2; ++n)
        {
            for (int p = 0; p <= 2; ++p)
            {
                T[3*k+n][3*k+p] = x[3*n+p];
            }
        }
	}
}


int valide(int** T, int i, int j, int x){
    
    int k = 0;

    while ((k<9) && (T[i][k] != x))
    {
        k++;
    }

    if (k != 9)
    {
        return 0; // cas d'échec
    }

    k = 0;

    while ((k<9) && (T[k][j] != x))
    {
        k++; 
    }

    if (k != 9)
    {
        return 0; //cas d'échec
    }

    k = 0;

    int i0 = i/3;
    int j0 = j/3;

    while ((k<9) && (T[3*i0 + k/3][3*j0 + k%3] != x))
    {   
        k++; 
    }

    if (k != 9)
    {
        return 0; //cas d'échec
    }

    return 1;
}


int valide_tableau(int** T, int** T_eff, int* x0, int* y0){

    int c;
    int v;

    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            if (T_eff[i][j]==0){
                c = T[i][j];
                T[i][j] = 0;
                v = valide(T,i,j,c);
                T[i][j] = c;
                if (v==0){
                    *x0 = i;
                    *y0 = j;
                    return 0;
                }
            }
        }
    }
    return 1;
}


int remplir_autres(int** T, int lig, int col)
{
    int N = 9;

    if (lig == N - 1 && col == N)
        return 1;
 
    if (col == N)
    {
        lig++;
        col = 0;
    }
   
    if (T[lig][col] > 0)
    {
        return remplir_autres(T, lig, col + 1);
    }


    for (int num = 1; num <= N; num++)
    {
        if (valide(T, lig, col, num)==1)
        {
            T[lig][col] = num;
           
            if (remplir_autres(T, lig, col + 1)==1)
                return 1;
        }
        T[lig][col] = 0;
    }

    return 0;
}


void efface(int** T, int K){
    
    int k = 0;

    while (k<K){

        int i = rand()%9;
        int j = rand()%9;

        if (T[i][j]>0){
            T[i][j] = 0;
            k++;
        }
    }
}



int main () {

    srand(time(NULL));


    int** tab;

    tab = calloc(9, sizeof(int*));
    for(int i = 0;i<9;i++) {
        tab[i] = calloc(9, sizeof(int));
    }


    remplir_diag(tab);
    remplir_autres(tab, 0, 0);

    int K = 54;

    efface(tab,K);

    afficher_tableau(tab);

    int** tab_efface = copie_tableau(tab);


    //afficher_tableau(tab_efface);


    
    int x;
    int y;
    int v;

    int k=0;

    while(k<K){

        printf("Entrez les coordonnées et la valeur à ajouter: ligne,colonne,valeur\n");
        scanf("%d,%d,%d", &x , &y, &v);

        if ( (v<=0) || (v>9) || (tab_efface[x][y]!=0) ){
            printf("Saisie invalide\n\n");
        }
        else{

            if (tab[x][y]!=0){
                tab[x][y] = v;
                afficher_tableau(tab);
            }
            else{
                tab[x][y] = v;
                afficher_tableau(tab);
                k++;
            }

        }
    }

    int valide = 0;
    
    while (valide==0){
        
        int verif;
        printf("Voulez-vous vérifier si le sudoku est valide ? \n\n1 pour Oui \n0 pour Non \n\n");
        scanf("%d", &verif);

        if (verif==1){
            int x0;
            int y0;
            valide = valide_tableau(tab,tab_efface,&x0,&y0);

            if (valide==0){
                printf("Le sudoku n'est pas valide, la case (%d,%d) n'est pas correcte.\n", x0, y0);
            }
        }

        else{
            printf("Entrez les coordonnées et la valeur à modifier: ligne,colonne,valeur\n");
            scanf("%d,%d,%d", &x , &y, &v);

            if ( (v<=0) || (v>9) || (tab_efface[x][y]!=0) ){
                printf("Saisie invalide\n\n");
            }
            else{
                tab[x][y] = v;
                afficher_tableau(tab);
            }
        }
    }

    printf("Bravo, vous avez terminé le sudoku.\n");

    free(tab);
    free(tab_efface);
}
