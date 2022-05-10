#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void afficher_tableau(int** T){
    for (int i=0; i<=8; i++){
        for (int j=0; j<=8; j++){
            printf("%d ", T[i][j]);
        }
        printf("\n");
    }
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

void remplir_autre (int** T){

    int x[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int i = 0;
    int j = 3;

    
    int k = 0;

    while (k<9)
    {
        int l =0;
        while( (k<9) && ( (x[l] != 0) && (valide(T, i + k/3, i + k mod 3, x[l])) ) )
        {
            if ( (x[l] != 0) && (valide(T, i + k/3, i + k mod 3, x[l])) )
            {
                

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
        return 1; // cas d'échec
    }

    k = 0;

    while ((k<9) && (T[k][j] != x))
    {
        k++; 
    }

    if (k != 9)
    {
        return 1; //cas d'échec
    }

    return 0;
}



int main () {

    srand(time(NULL));

    int** tab;
    tab = calloc(9, sizeof(int*));
    for(int i = 0;i<9;i++) {
        tab[i] = calloc(9, sizeof(int));
    }

    remplir_diag(tab);


    afficher_tableau(tab);




    

    
    
    
    
    
    free(tab);
}
