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


int remplir_autres(int** grid, int row, int col)
{
    int N = 9;

    if (row == N - 1 && col == N)
        return 1;
 
    if (col == N)
    {
        row++;
        col = 0;
    }
   
    if (grid[row][col] > 0)
    {
        return remplir_autres(grid, row, col + 1);
    }


    for (int num = 1; num <= N; num++)
    {
        if (valide(grid, row, col, num)==1)
        {
            grid[row][col] = num;
           
            if (remplir_autres(grid, row, col + 1)==1)
                return 1;
        }
        grid[row][col] = 0;
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


    remplir_autres(tab, 0, 0);


    afficher_tableau(tab);


    


    

    
    
    
    
    
    free(tab);
}
