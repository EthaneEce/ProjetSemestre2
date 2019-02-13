#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

/******************************************
************ Structures  ******************
*******************************************/
///structure regroupant les variables relative à un unique niveau de programation
//structure des variables destinée a la programmation de premier niveau
typedef struct prog_1
{
    BITMAP** images_prog1;
    char action; //enregistre l'action selectionné actuellement (avancer tourner sauté tirer)

} t_prog_1;

typedef struct cl
{
    char text[222];
    char lettre;
    char prec;
    int taille;
    char textaff[100];

}init_clavier;



/*******************************************
************* Magic Numbers  ***************
********************************************/

#define decalage_haut 130
#define decalage_gauche 50//icone de jeu
#define decalage_bas -20

#define dep_map_par_boucle 2 //deplacement de la map quand on se deplace sur celle ci avec les fleches directionnelles



#define nb_action_max 30

#define tour_seconde 40

/*******************************************
*************   prototypes *****************
********************************************/


///fonctionnement du jeu pour un niveau de programmation donnée et un niveau de jeu donnée
//en paramètre le niveau de programation et niveau de jeu   ______ on passe également les images annexes (images de fond)
int jeu(int level_prog,int level,t_graphismes* images_annexe);



#endif // JEU_H_INCLUDED
