#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


 #define H (30)
 #define W (60)
 #define Nb_fantasmi (5)

struct coord
{
	int x;
	int y;
};

struct PacMan
{
	struct coord* co;
	int nx;
	int ny;
	int vite;
	int food;
};

struct fantasma
{
	struct coord* co;
	int nx;
	int ny;
};




struct fantasma* tutti_fantasmi[Nb_fantasmi];
struct coord depart_PacMan={1,1};
struct PacMan Pm={&depart_PacMan,0,0,3,0};



char area [H] [W]={
   { "############################################################" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#        # # # # #          #             # # # # # #      #" },
   { "#        #       #         # #            #                #" },
   { "#        #       #        #   #           #                #" },
   { "#        # # # # #       #     #          #                #" },
   { "#        #              # # # # #         #                #" },
   { "#        #             #         #        #                #" },
   { "#        #            #           #       #                #" },
   { "#        #           #             #      #                #" },
   { "#        #          #               #     # # # # # #      #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#        ##        ##           #          ##        #     #" },
   { "#        # #      # #          # #         # #       #     #" },
   { "#        #  #    #  #         #   #        #  #      #     #" },
   { "#        #    # #   #        #     #       #   #     #     #" },
   { "#        #     #    #       # # # # #      #    #    #     #" },
   { "#        #          #      #         #     #     #   #     #" },
   { "#        #          #     #           #    #      #  #     #" },
   { "#        #          #    #             #   #       # #     #" },
   { "#        #          #   #               #  #        ##     #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "#                                                          #" },
   { "############################################################" }
};

void initialize (struct fantasma** tutti_fantasmi, char area[H][W]){

   srand(time(NULL));

   for (int i=0;i<Nb_fantasmi;i+=1){

      struct fantasma* G=malloc (sizeof (struct fantasma));
      int x0=rand()%(H+1);
      int y0=rand()%(W+1);

      while((y0==1 && x0==1) || area[x0][y0]=='#'){
         x0=rand()%(H+1);
         y0=rand()%(W+1);
      }

      struct coord* c=malloc(sizeof(struct fantasma));
      c->x=x0;
      c->y=y0;
      G->co=c;
      G->nx=0;
      G->ny=0;
      
      tutti_fantasmi[i]=G;
      area[x0][y0]='G';
   }
}

void move_Pac_Man(struct PacMan* PacMan, char area[H][W]){

   struct coord* c=PacMan->co;

   if (area[c->x+PacMan->nx][c->y+PacMan->ny]!='#' && area[c->x+PacMan->nx][c->y+PacMan->ny]!='G'){

      area[c->x][c->y]=' ';
      c->x+=PacMan->nx;
      c->y+=PacMan->ny;
      if (area[c->x][c->y]=='.'){
        PacMan->food+=1;
      }
      area[c->x][c->y]='P';
   }

   else{
      PacMan->vite-=1;

      area[c->x][c->y]=' ';
      c->x=1;
      c->y=1;
      area[c->x][c->y]='P';
   }
}

void move_fantasmas(struct fantasma** tutti_fantasmi, char area[H][W]){

   for (int k=0;k<Nb_fantasmi;k+=1){ 
      struct coord* c=tutti_fantasmi[k]->co;
      int nx=tutti_fantasmi[k]->nx;
      int ny=tutti_fantasmi[k]->ny;

      if (area[c->x+nx][c->y+ny]!='#'){
         c->x=c->x+nx;
         c->y+=ny;

         if (area[c->x][c->y]=='.'){
            area[c->x-nx][c->y-ny]='.';
         }

         if (area[c->x][c->y]==' '){
            area[c->x-nx][c->y-ny]=' ';
         }

         area[c->x][c->y]='G';
      }

      else{
         c->x-=nx;
         c->y-=ny;

         if (area[c->x][c->y]=='.'){
            area[c->x+nx][c->y+ny]='.';
         }

         if (area[c->x][c->y]==' '){
            area[c->x-nx][c->y-ny]=' ';
         }

         area[c->x][c->y]='G';
      }
   }
}


void afficher_area(char area[H][W]){

   for (int l=0;l<H;l+=1){

         for (int c=0;c<W;c+=1){

            printf("%c",area[l][c]);
         }
         printf("\n");
      }
}


void clavier(struct PacMan* P, struct fantasma** tutti_fantasmi){

   srand(time(NULL));
   char direction;
   scanf(" %c",&direction);

   if (direction == 'z'){
      P->nx =-1;
      P->ny = 0;
   }

   else if (direction == 's'){
      P->nx = 1;
      P->ny = 0;
   }

   else if (direction == 'q'){
      P->ny = -1;
      P->nx = 0;  
   }

   else if (direction == 'd'){
      P->ny = 1;
      P->nx = 0;
   }

   for  (int k=0;k<Nb_fantasmi;k++){

      int c = rand()%2;

      if (c==1){
         tutti_fantasmi[k]->nx = 0;
         int d = rand()%2;

         if (d==1){
            tutti_fantasmi[k]->ny = -1;
         }

         else{
            tutti_fantasmi[k]->ny = 1;
         }
      }

      else{
         tutti_fantasmi[k]->ny = 0;
         int d = rand()%2;

         if (d==1){
            tutti_fantasmi[k]->nx = -1;
         }

         else{
            tutti_fantasmi[k]->nx = 1;
         }
      }
   }
}

void check_life(struct PacMan* PacMan){

   if(PacMan->vite>=0){
      afficher_area(area);
   }

   else{
      printf("La partie est terminée.\nVotre score est de %d points.\n",PacMan->food);
   }
}


int jeu_pacman(){

   for (int l=0;l<H;l+=1){

         for (int c=0;c<W;c+=1){

            if (area[l][c]==' '){

               area[l][c]='.';
            }
         }
      }


   area[depart_PacMan.x][depart_PacMan.y]='P';
   initialize(tutti_fantasmi,area);

   while (Pm.vite>=0){

      if (Pm.vite>=0){

         printf("Life : %d\nFood : %d\n",Pm.vite,Pm.food);
      }

      afficher_area(area);
      clavier(&Pm, tutti_fantasmi);
      move_fantasmas(tutti_fantasmi,area);
      move_Pac_Man(&Pm, area);
      check_life(&Pm);
   }
}
