#ifndef BOUCLE_JEU_H_INCLUDED
#define BOUCLE_JEU_H_INCLUDED



/*******************************************
*************   prototypes *****************
********************************************/

///alloue et initialise les variable destinée aux differents niveau de programmation

// premier niveau icones
t_prog_1* init_prog_1();

//initialisation de la commander clavier
init_clavier* init_prog_2();



/******************************************/
///ensemble de sous programmes incruster dans la boucle de jeu
///actualise le jeu en fonction du niveau de programmation

//niveau prog 1 -> icones
void commande_icone(t_prog_1* prog1,char actions[20],short int* nb_act,short int* exe);


//niveau prog 2 -> clavier
void commande_cl(init_clavier* nouv, char action[20],short int nb_act,short int* exe);

/*******************************************/

//par defaut, allegro utilise un clavier qwerty, on est donc obliger de convertir le clavier ainsi
char frappecl();


void afficher_vie_gemme(int vie,int gemme, BITMAP*g,BITMAP*v);

#endif // BOUCLE_JEU_H_INCLUDED




















