#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define H 30
#define W 60
#define Nb_fantasmi 4



struct coord {
    int x;
    int y;
};

struct PacMan {
    struct coord c;
    int nx;
    int ny;
    int vite;
    int food;
};

struct fantasma {
    struct coord c;
    int nx;
    int ny;
};

struct fantasma tuttifantasmi [Nb_fantasmi];

void init_pacman(struct PacMan* pc){
	struct coord co = {1,1};
    pc->c = co;
    pc->nx = 0;
    pc->ny = 0;
    pc->vite = 1;
    pc->food = 0;      
}

char area [H][W] = {
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

void init_fantasmi (char T [H][W], struct fantasma l [Nb_fantasmi]){

    for (int i=0; i<Nb_fantasmi; i++){
        int b = 0;
        while (b == 0){
            int l  = rand()%30;
            int c = rand()%60;
            if (T[l][c] == ' ' && ((l != 1) || (c != 1))){
                struct coord co = {l,c};
                l[i]->coord = co;
                T[l][c] = 'G';
                b = 1;
            }
        }

    }
}


int main (){

    srand(time(NULL));

    return 0;
}