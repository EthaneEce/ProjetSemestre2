#ifndef CHARGEMENT_DE_DONNEES_H_INCLUDED
#define CHARGEMENT_DE_DONNEES_H_INCLUDED

/*******************************************
************* Magic Numbers  ***************
********************************************/

//initialisation constante
#define nb_image_prog1 4

#define nb_image_cube 3
#define nb_personnage 2
#define nb_direction 4
#define nb_mvt 3


#define nb_pi 9
#define nb_bouton 4


/******************************************
************ Structures  ******************
*******************************************/

typedef struct graphismes
{

    BITMAP* fond_jeu;
    BITMAP* cerveau;
    BITMAP* fondmenu;
    BITMAP* menu;
    BITMAP* space;

    BITMAP** pigeon;

    BITMAP** bouton;

    BITMAP* lose;
    BITMAP* win;
    BITMAP* game_over;

} t_graphismes;

typedef struct image_level
{
    BITMAP** cube;
    BITMAP**** personnage;
    BITMAP* cle;
    BITMAP*coeur;

} t_image_level;

/*******************************************
*************   prototypes *****************
********************************************/

///chargement de l'ensemble des informations d'un niveau avec  test de succes
//fait appel à tout les programmes situé dessous
void chargement(int level_prog, int level,t_niveau**info,t_personnage** perso,unsigned char**** tab,t_image_level** Im_level);

/***************************************************************/


///recupere les données d'un niveau passée en parametre et les enregistrent dans une structure
//les parametres: les niveaux de level de jeu et de programmation
t_niveau* recup_fichier_info(int level_prog,int level);

///recupere un tableau a 3 dimensions representant la map
unsigned char*** recup_fichier_map(int level_prog,int level,t_niveau* info);


///recupere les données des personnages pour un niveau donnée passée en parametere
//en parametre entrant : le niveau de programation ET de jeu
//en sortant revoie unpointeur sur cette structure
t_personnage* recup_fichier_perso(int level_prog,int level);


///alloue dynamiquement un tableau avec verification et liberation mémoire si echec
unsigned char*** allocation_dynamique(int hauteur, int longueur, int largeur);

/*************************************************************************/

///chargement des images
BITMAP** charger_images_prog1();

///recupere les images neccessaire au fonctionnement général du jeu
t_graphismes* charger_images_annexe();

///recupere l'ensemble des images pour un niveau de jeu donné et retourne un tableau d'image
t_image_level* charger_images_level(int level_prog,int level);


/**************************************************************/

/*----- source : M. FERCOC COURS 0  -------------*/
///permet de charger une image avec verification d'echec à partir d'une chaine passée en paramètre
BITMAP* chargerImage(char * );

int* recup_fichier_unlock();

void save(int level_prog,int level);


#endif // CHARGEMENT_DE_DONNEES_INCLUDED
