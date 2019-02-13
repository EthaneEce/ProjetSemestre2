#include "biblio.h"

/***********************************************************************************************
********** ensemble de sous programme permettant la liberation de l'espace m�moire  ************
************************************************************************************************/


///sous prog permettant la liberation d'espace m�moire � la fin d'un niveau
void liberation_memoire(int level_prog,t_niveau* info,unsigned char*** tab,BITMAP* mape,t_image_level* Im_level)
{
    /*****   4 liberation m�moire *******/

    printf("\n");
    free_tab_map(tab,info);
    //confirmation de la liberation par �crit dans le sous programme
    //free_imageS(tab_images,nb_image_cube,"cube_isometrique");
    //confirmation de la liberation par �crit dans le sous programme
    free(info);
    printf("liberation memoire des donnees du niveau [SUCCES]\n");
    destroy_bitmap(mape);
    printf("liberation memoire de l'image map [SUCCES]\n");


}

///libere un tableau a 3 dimensions
//on recoit en param�tre l'adresse du tableau et la taille de celui ci dans la structure info
void free_tab_map(unsigned char*** tab, t_niveau* info)
{
    int y,z;

    for(z=0; z<info->map_z; z++)
        for(y=0; y<info->map_y; y++)
            free(tab[z][y]);

    for(z=0; z<info->map_z; z++)
        free(tab[z]);
    free(tab);
    printf("liberation memoire du tableau de donnee map [SUCCES]\n");
}

///libere un tableau d'image � n nombre d'images
// en param�tre l'adresse du tableau d'image  || le nombre d'image du tableau || le nom du tableau
void free_imageS(BITMAP** tableau,int nombre,char* chaine)
{
    int i;
    for(i=0; i<nombre; i++)
        destroy_bitmap(tableau[i]);
    free(tableau);
    printf("liberation memoire du tableau d'images (%s)de %d images [SUCCES]\n",chaine,nombre);
}
///libere l'espace memoire d'une tructure d'image
//en parametre l'adresse de la structure d'image
void free_images_annex(t_graphismes*images_annexe)
{
    destroy_bitmap(images_annexe->fond_jeu);
    destroy_bitmap(images_annexe->space);
    destroy_bitmap(images_annexe->cerveau);
    destroy_bitmap(images_annexe->fondmenu);
    destroy_bitmap(images_annexe->menu);

    free(images_annexe);
    printf("liberation memoire du tableau d'images (annexe+pigeon)de 5 images [SUCCES]\n");

}

///liberation de l'espace m�moire allou� pour un niveau de programation niveau 1 (icone)
void liberation_memoire_prog1(t_prog_1* prog1)
{
    free_imageS(prog1->images_prog1,nb_image_prog1,"image_prog1->fleche");
    free(prog1);
    printf("liberation memoire des donnees relative au niveau de programmation 1 [SUCCES]\n");

}
