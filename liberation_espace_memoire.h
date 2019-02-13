#ifndef LIBERATION_ESPACE_MEMOIRE_H_INCLUDED
#define LIBERATION_ESPACE_MEMOIRE_H_INCLUDED


/*******************************************
*************   prototypes *****************
********************************************/

///sous prog permettant la liberation d'espace mémoire à la fin d'un niveau
void liberation_memoire(int level_prog,t_niveau* info,unsigned char*** tab,BITMAP* mape,t_image_level*);

///libere un tableau a 3 dimensions
//on recoit en paramètre l'adresse du tableau et la taille de celui ci dans la structure info
void free_tab_map(unsigned char*** tab, t_niveau* info);

///libere un tableau d'image à n nombre d'images
void free_imageS(BITMAP** tableau,int nombre,char* chaine);


///libere l'espace memoire d'une tructure d'image
//en parametre l'adresse de la structure d'image
void free_images_annex(t_graphismes* images_annexe);

///liberation de l'espace mémoire alloué pour un niveau de programation niveau 1 (icone)
void liberation_memoire_prog1(t_prog_1* prog1);

#endif // LIBERATION_ESPACE_MEMOIRE_H_INCLUDED
