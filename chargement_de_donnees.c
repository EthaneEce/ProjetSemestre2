#include "biblio.h"

/*****************************************************************************************************************************
*** ensemble de sous programmes permettant le chargement d'information enregistrer sous forme d'image ou de fichier texte  ***
******************************************************************************************************************************/

///chargement de l'ensemble des informations d'un niveau avec test de succes ou liberation m�moire et sortie de programme
//toutes les donn�es allou� doivent etre pass�
void chargement(int level_prog, int level,t_niveau** info,t_personnage** perso,unsigned char **** tab,t_image_level** Im_level)
{
    ///recup info level
    *info=recup_fichier_info(level_prog,level);
    printf("\nchargement des informations du niveau");
    if(*info==NULL)
    {

        printf("[ECHEC]\n");
        destroy_bitmap(Buffer);
        allegro_message("ECHEC rencontrer precedement    conseil : regarder l'affichage console     bye bye");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    else
        printf(" [SUCCES]\n");



    ///recuperation informations de la map
    *tab=recup_fichier_map(level_prog,level,*info);
    //test afin de verifier si l'allocation et l'initialisation c'est r�aliser correctement
    printf("chargement de la map du niveau");
    if(*tab==NULL)
    {
        //si echec alors on libere ce qui a �t� allou� pr�cedement
        printf("[ECHEC]\n");
        destroy_bitmap(Buffer);
        free(*info);
        allegro_message("ECHEC rencontrer precedement    conseil : regarder l'affichage console     bye bye");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    else
        printf(" [SUCCES]\n\n");



    ///recuperation des information du personnage
    *perso=recup_fichier_perso(level_prog,level);
    //test afin de verifier si l'allocation et l'initialisation c'est r�aliser correctement
    printf("chargement des donnees du personnage");
    if(*perso==NULL)
    {
        //si echec alors on libere ce qui a �t� allou� pr�cedement
        printf("[ECHEC]\n");
        destroy_bitmap(Buffer);
        free_tab_map(*tab,*info);
        free(*info);
        allegro_message("ECHEC rencontrer precedement    conseil : regarder l'affichage console     bye bye");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    else
        printf(" [SUCCES]\n\n");


    ///recuperation des images
    *Im_level=charger_images_level(level_prog,level);
    //test afin de verifier si l'allocation et l'initialisation c'est r�aliser correctement
    printf("chargement des images du niveau");
    if(*Im_level==NULL)
    {
        //si echec alors on libere ce qui a �t� allou� pr�cedement
        printf(" [ECHEC]\n");
        destroy_bitmap(Buffer);
        free_tab_map(*tab,*info);
        free(*perso);
        free(*info);
        allegro_message("ECHEC rencontrer precedement    conseil : regarder l'affichage console     bye bye");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    else
        printf(" [SUCCES]\n");
}

/*************************************************************************************************************************
**************************************************************************************************************************
**************************************************************************************************************************/

int* recup_fichier_unlock()
{
    int* lvlunlock;
    lvlunlock=(int*)malloc(sizeof(int)*3);

    FILE* pointeur;
    pointeur=fopen(".\\DATA\\unlock.txt","r");

    fscanf(pointeur,"%d",&lvlunlock[0]);
    fscanf(pointeur,"%d",&lvlunlock[1]);
    fscanf(pointeur,"%d",&lvlunlock[2]);

    fclose(pointeur);

    return lvlunlock;

}

void save(int level_prog,int level)
{
    FILE* pointeur;
    pointeur=fopen(".\\DATA\\unlock.txt","r");

    int lvlunlock[3];

    fscanf(pointeur,"%d",&lvlunlock[0]);
    fscanf(pointeur,"%d",&lvlunlock[1]);
    fscanf(pointeur,"%d",&lvlunlock[2]);

    fclose(pointeur);

    if (lvlunlock[level_prog-1]<level+1)
        lvlunlock[level_prog-1]=level+1;

    pointeur=fopen(".\\DATA\\unlock.txt","w");

    fprintf(pointeur,"%d ",lvlunlock[0]);
    fprintf(pointeur,"%d ",lvlunlock[1]);
    fprintf(pointeur,"%d ",lvlunlock[2]);

    fclose(pointeur);

}
/*************************************************************************************************************************
**************************************************************************************************************************
**************************************************************************************************************************/

///recupere les donn�es des personnages pour un niveau donn�e pass�e en parametere
//en parametre entrant : le niveau de programation ET de jeu
//en sortant revoie unpointeur sur cette structure
t_personnage* recup_fichier_perso(int level_prog,int level)
{
    t_personnage* perso=NULL;
    FILE* pointeur=NULL;
    char chaine[]=".\\DATA\\prog_X\\level_X\\personnage.txt";
    chaine[12]=level_prog+'0';
    chaine[20]=level+'0';


    pointeur=fopen(chaine,"r");
    if(pointeur==NULL)
    {
        printf("\nerreur d'ouverture du fichier texte contenant les donnees personnages\n");
        return NULL;
    }

    perso=(t_personnage*)malloc(sizeof(t_personnage));
    if(perso==NULL)
    {
        printf("\nerreur d'allocation dynamique des donnees du personnage\n");
        fclose(pointeur);
        return NULL;
    }

    fscanf(pointeur,"%d",&perso->x);
    fscanf(pointeur,"%d",&perso->y);
    fscanf(pointeur,"%d",&perso->z);

    fscanf(pointeur,"%d",&perso->orientation);

    perso->old_x=perso->x;
    perso->old_y=perso->y;
    perso->old_z=perso->z;
    perso->trans=1;

    perso->ini_x=perso->x;
    perso->ini_y=perso->y;
    perso->ini_z=perso->z;
    perso->ini_orien=perso->orientation;

    fclose(pointeur);

    return perso;
}

///recupere les donn�es d'un niveau pass�e en parametre et les enregistrent dans une structure
/*les parametres: les niveaux de level de jeu et de programmation */
t_niveau* recup_fichier_info(int level_prog,int level)
{
    t_niveau* info=NULL;

    int i;
    FILE* pointeur=NULL;
    char chaine[]=".\\DATA\\prog_X\\level_X\\donnees.txt";
    chaine[12]=level_prog+'0';
    chaine[20]=level+'0';

    pointeur=fopen(chaine,"r");


    if(pointeur==NULL)
    {
        printf("\nerreur d'ouverture du fichier texte contenant les donnees\n");
        return NULL;
    }

    info=(t_niveau*)malloc(sizeof(t_niveau));

    if(info==NULL)
    {
        printf("\nerreur d'allocation dynamique des donnees sur level\n");
        fclose(pointeur);
        return NULL;
    }
    fscanf(pointeur,"%d",&info->map_x);
    fscanf(pointeur,"%d",&info->map_y);
    fscanf(pointeur,"%d",&info->map_z);
    fscanf(pointeur,"%d",&info->ecran_w);
    fscanf(pointeur,"%d",&info->ecran_h);
    fscanf(pointeur,"%d",&info->decalage_w);
    fscanf(pointeur,"%d",&info->decalage_h);
    fscanf(pointeur,"%d",&info->n_allie);

    if(info->n_allie>0)
    {
        info->allie=(t_personnage*)malloc(sizeof(t_personnage)*info->n_allie);

        for(i=0; i<info->n_allie; i++)
        {
            fscanf(pointeur,"%d",&info->allie[i].x);
            fscanf(pointeur,"%d",&info->allie[i].y);
            fscanf(pointeur,"%d",&info->allie[i].z);

            fscanf(pointeur,"%d",&info->allie[i].orientation);
            info->allie[i].old_x=info->allie[i].x;
            info->allie[i].old_y=info->allie[i].y;
            info->allie[i].old_z=info->allie[i].z;
            info->allie[i].trans=1;

            info->allie[i].ini_x=info->allie[i].x;
            info->allie[i].ini_y=info->allie[i].y;
            info->allie[i].ini_z=info->allie[i].z;
            info->allie[i].ini_orien=info->allie[i].orientation;
        }
    }


    fscanf(pointeur,"%d",&info->coup_1);
    fscanf(pointeur,"%d",&info->coup_2);

    fscanf(pointeur,"%d",&info->nb_cle);

    info->emplacement_gemmes=(int**)malloc(sizeof(int*)*info->nb_cle);
    for(i=0; i<info->nb_cle; i++)
        info->emplacement_gemmes[i]=(int*)malloc(sizeof(int)*3);

    for(i=0; i<info->nb_cle; i++)
    {
        fscanf(pointeur,"%d",&info->emplacement_gemmes[i][0]);
        fscanf(pointeur,"%d",&info->emplacement_gemmes[i][1]);
        fscanf(pointeur,"%d",&info->emplacement_gemmes[i][2]);
    }
    fclose(pointeur);

    return info;
}


///recupere un tableau a 3 dimensions representant la map
unsigned char*** recup_fichier_map(int level_prog,int level,t_niveau* info)
{
    unsigned char*** tab=NULL;

    int x,y,z;

    char chaine[]=".\\DATA\\prog_X\\level_X\\map.txt";
    chaine[12]=level_prog+'0';
    chaine[20]=level+'0';

    FILE* pointeur=NULL;
    pointeur=fopen(chaine,"r");

    if(pointeur==NULL)
    {
        printf("erreur d'ouverture du fichier texte contenant la map\n");
        return NULL;
    }

    tab=allocation_dynamique(info->map_z,info->map_y,info->map_x);
    if(tab==NULL)
    {
        fclose(pointeur);
        return NULL;
    }

    for(z=0; z<info->map_z; z++)
    {
        for(y=0; y<info->map_y; y++)
            for(x=0; x<info->map_x; x++)
                fscanf(pointeur,"%d",&(tab[z][y][x]));
        fscanf(pointeur,"/n/n");
    }

    fclose(pointeur);

    return tab;
}




/***************************************************************************************************************************************************************/

///chargement des images du programme 1 fleches etc
BITMAP** charger_images_prog1()
{
    BITMAP** images_prog1=NULL;

    int i;
    bool test=0;

    images_prog1=(BITMAP**)malloc(nb_image_prog1*sizeof(BITMAP*));

    //test pour savoir si l'allocation � bien marcher
    if(images_prog1==NULL)
        return NULL;

    images_prog1[0]=chargerImage(".\\IMAGES\\annexe\\prog1\\AVANCER.bmp");
    images_prog1[1]=chargerImage(".\\IMAGES\\annexe\\prog1\\DROITE.bmp");
    images_prog1[2]=chargerImage(".\\IMAGES\\annexe\\prog1\\GAUCHE.bmp");
    images_prog1[3]=chargerImage(".\\IMAGES\\annexe\\prog1\\SAUTER.bmp");




    //test pour savoir si tous les fichier images ont �t� trouv�
    for(i=0; i<nb_image_prog1; i++)
        if(images_prog1[i]==NULL)
            test=1;

    //si echec alors on d�ssaloue
    if(test==1)
    {

        for(i=0; i<nb_image_prog1; i++)
            if(images_prog1[i]!=NULL)
                destroy_bitmap(images_prog1[i]);
        free(images_prog1);
        return NULL;
    }
    return images_prog1;
}

///recupere les images neccessaire au fonctionnement g�n�ral du jeu
t_graphismes* charger_images_annexe()
{
    //declaration des ressources
    t_graphismes* images_annexe=NULL;

    bool test=0;
    int i;

    //allocation
    images_annexe=(t_graphismes*)malloc(sizeof(t_graphismes));

    //test pour savoir si l'allocation � bien marcher
    if(images_annexe==NULL)
        return NULL;
    //alloc
    images_annexe->pigeon=(BITMAP**)malloc(nb_pi*sizeof(BITMAP*));
    if(images_annexe->pigeon==NULL)
    {
        free(images_annexe);
        return NULL;
    }
    images_annexe->bouton=(BITMAP**)malloc(nb_bouton*sizeof(BITMAP*));
    if(images_annexe->bouton==NULL)
    {
        for(i=0; i<nb_pi; i++)
            destroy_bitmap(images_annexe->pigeon[i]);
        free(images_annexe);
        return NULL;
    }

    images_annexe->fond_jeu=chargerImage(".\\IMAGES\\annexe\\fond_jeu.bmp");
    images_annexe->space=chargerImage(".\\IMAGES\\annexe\\background-space.bmp");
    images_annexe->cerveau=chargerImage(".\\IMAGES\\annexe\\cerveau.bmp");
    images_annexe->fondmenu=chargerImage(".\\IMAGES\\annexe\\fondmenu.bmp");
    images_annexe->menu=chargerImage(".\\IMAGES\\annexe\\menu.bmp");

    images_annexe->pigeon[0]=chargerImage(".\\IMAGES\\annexe\\pigeon\\pigeon0.bmp");
    images_annexe->pigeon[1]=chargerImage(".\\IMAGES\\annexe\\pigeon\\pigeon1.bmp");
    images_annexe->pigeon[2]=chargerImage(".\\IMAGES\\annexe\\pigeon\\pigeon2.bmp");
    images_annexe->pigeon[3]=chargerImage(".\\IMAGES\\annexe\\pigeon\\pigeon3.bmp");
    images_annexe->pigeon[4]=chargerImage(".\\IMAGES\\annexe\\pigeon\\pigeon4.bmp");
    images_annexe->pigeon[5]=chargerImage(".\\IMAGES\\annexe\\pigeon\\pigeon5.bmp");
    images_annexe->pigeon[6]=chargerImage(".\\IMAGES\\annexe\\pigeon\\pigeon6.bmp");
    images_annexe->pigeon[7]=chargerImage(".\\IMAGES\\annexe\\pigeon\\pigeon7.bmp");
    images_annexe->pigeon[8]=chargerImage(".\\IMAGES\\annexe\\pigeon\\pigeon8.bmp");



    images_annexe->bouton[0]=chargerImage(".\\IMAGES\\annexe\\bouton\\bouton-aide.bmp");
    images_annexe->bouton[1]=chargerImage(".\\IMAGES\\annexe\\bouton\\bouton-play.bmp");
    images_annexe->bouton[2]=chargerImage(".\\IMAGES\\annexe\\bouton\\bouton-pause.bmp");
    images_annexe->bouton[3]=chargerImage(".\\IMAGES\\annexe\\bouton\\bouton-arret.bmp");


    images_annexe->lose=chargerImage(".\\IMAGES\\annexe\\win\\lose.bmp");
    images_annexe->win=chargerImage(".\\IMAGES\\annexe\\win\\win.bmp");
    images_annexe->game_over=chargerImage(".\\IMAGES\\annexe\\win\\gameover.bmp");

    //test pour savoir si tous les fichier images ont �t� trouv�
    if(images_annexe->cerveau==NULL)
        test=1;
    if(images_annexe->fond_jeu==NULL)
        test=1;
    if(images_annexe->space==NULL)
        test=1;
    if(images_annexe->fondmenu==NULL)
        test=1;
    if(images_annexe->menu==NULL)
        test=1;

    //test pour savoir si tous les fichier images des boutons ont �t� trouv�
    for(i=0; i<nb_bouton; i++)
        if(images_annexe->bouton[i]==NULL)
            test=1;

    //test pour savoir si tous les fichier images du pigeon ont �t� trouv�
    for(i=0; i<nb_pi; i++)
        if(images_annexe->pigeon[i]==NULL)
            test=1;

    //si echec alors on d�ssaloue
    if(test>0)
    {
        if(images_annexe->cerveau!=NULL)
            destroy_bitmap(images_annexe->cerveau);
        if(images_annexe->fond_jeu!=NULL)
            destroy_bitmap(images_annexe->fond_jeu);
        if(images_annexe->space!=NULL)
            destroy_bitmap(images_annexe->space);
        if(images_annexe->fondmenu!=NULL)
            destroy_bitmap(images_annexe->fondmenu);
        if(images_annexe->menu!=NULL)
            destroy_bitmap(images_annexe->menu);

        for(i=0; i<nb_pi; i++)
            if(images_annexe->pigeon[i]!=NULL)
                destroy_bitmap(images_annexe->pigeon[i]);

        free(images_annexe->pigeon);

        free(images_annexe);
        return NULL;
    }

    return images_annexe;
}


///recupere l'ensemble des images pour un niveau de jeu donn� et retourne un tableau d'image
t_image_level* charger_images_level(int level_prog,int level)
{
    t_image_level* Im_level;
    bool test=0;
    int i,j;

    char lieu[]=".\\IMAGES\\saisonX\\";
    lieu[15]=level+'0';

    char chaine[40];


    Im_level=(t_image_level*)malloc(sizeof(t_image_level));
    if(Im_level==NULL)
        return NULL;
    Im_level->cube=(BITMAP**)malloc(sizeof(BITMAP*)*(nb_image_cube));

    //test pour savoir si l'allocation � bien marcher
    if(Im_level->cube==NULL)
    {
        free(Im_level);
        return NULL;
    }
    Im_level->personnage=(BITMAP****)malloc(sizeof(BITMAP***)*nb_personnage);

    for(i=0; i<nb_personnage; i++)
        Im_level->personnage[i]=(BITMAP***)malloc(sizeof(BITMAP**)*nb_direction);
    for(i=0; i<nb_personnage; i++)
        for(j=0; j<nb_direction; j++)
            Im_level->personnage[i][j]=(BITMAP**)malloc(sizeof(BITMAP*)*nb_mvt);



    strcpy(chaine,lieu);
    strcat(chaine,"iso_cube1.bmp");
    Im_level->cube[0]=chargerImage(chaine);

    strcpy(chaine,lieu);
    strcat(chaine,"iso_cube2.bmp");
    Im_level->cube[1]=chargerImage(chaine);

    strcpy(chaine,lieu);
    strcat(chaine,"iso_cube3.bmp");
    Im_level->cube[2]=chargerImage(chaine);

    strcpy(chaine,lieu);
    strcat(chaine,"cles.bmp");
    Im_level->cle=chargerImage(chaine);


    Im_level->coeur=chargerImage(".\\IMAGES\\annexe\\coeur.bmp");

    //perso principal
    Im_level->personnage[0][0][0]=chargerImage(".\\IMAGES\\personnage\\00.bmp");
    Im_level->personnage[0][0][1]=chargerImage(".\\IMAGES\\personnage\\01.bmp");
    Im_level->personnage[0][0][2]=chargerImage(".\\IMAGES\\personnage\\02.bmp");

    Im_level->personnage[0][1][0]=chargerImage(".\\IMAGES\\personnage\\10.bmp");
    Im_level->personnage[0][1][1]=chargerImage(".\\IMAGES\\personnage\\11.bmp");
    Im_level->personnage[0][1][2]=chargerImage(".\\IMAGES\\personnage\\12.bmp");

    Im_level->personnage[0][2][0]=chargerImage(".\\IMAGES\\personnage\\20.bmp");
    Im_level->personnage[0][2][1]=chargerImage(".\\IMAGES\\personnage\\21.bmp");
    Im_level->personnage[0][2][2]=chargerImage(".\\IMAGES\\personnage\\22.bmp");

    Im_level->personnage[0][3][0]=chargerImage(".\\IMAGES\\personnage\\30.bmp");
    Im_level->personnage[0][3][1]=chargerImage(".\\IMAGES\\personnage\\31.bmp");
    Im_level->personnage[0][3][2]=chargerImage(".\\IMAGES\\personnage\\32.bmp");

    //alli�
    Im_level->personnage[1][0][0]=chargerImage(".\\IMAGES\\allie\\da.bmp");
    Im_level->personnage[1][0][1]=chargerImage(".\\IMAGES\\allie\\db.bmp");
    Im_level->personnage[1][0][2]=chargerImage(".\\IMAGES\\allie\\dc.bmp");

    Im_level->personnage[1][1][0]=chargerImage(".\\IMAGES\\allie\\ca.bmp");
    Im_level->personnage[1][1][1]=chargerImage(".\\IMAGES\\allie\\cb.bmp");
    Im_level->personnage[1][1][2]=chargerImage(".\\IMAGES\\allie\\cc.bmp");


    Im_level->personnage[1][2][0]=chargerImage(".\\IMAGES\\allie\\aa.bmp");
    Im_level->personnage[1][2][1]=chargerImage(".\\IMAGES\\allie\\ab.bmp");
    Im_level->personnage[1][2][2]=chargerImage(".\\IMAGES\\allie\\ac.bmp");

    Im_level->personnage[1][3][0]=chargerImage(".\\IMAGES\\allie\\ba.bmp");
    Im_level->personnage[1][3][1]=chargerImage(".\\IMAGES\\allie\\bb.bmp");
    Im_level->personnage[1][3][2]=chargerImage(".\\IMAGES\\allie\\bc.bmp");



    //test pour savoir si tous les fichier images ont �t� trouv�
    for(i=0; i<nb_image_cube; i++)
        if(Im_level->cube[i]==NULL)
            test=1;


    //si echec alors on d�ssaloue
    if(test==1)
    {
        for(i=0; i<nb_image_cube; i++)
            if(Im_level->cube[i]!=NULL)
                destroy_bitmap(Im_level->cube[i]);
        free(Im_level);
        return NULL;
    }

    return Im_level;
}

/**************************************************************************************************/

///alloue dynamiquement un tableau avec verification et liberation m�moire si echec
unsigned char*** allocation_dynamique(int hauteur, int longueur, int largeur)
{
    unsigned char*** tab;
    int i, j,k;
    int test=0;


    //allocation 1 dimension
    tab=(unsigned char***)malloc(sizeof(unsigned char**)*hauteur);
    //test d'alloc
    if(tab==NULL)
    {
        printf("erreur de chargement de la map->allocation espace memoire 1\n");
        return NULL;
    }

    //alloc 2 dimensions
    for(i=0; i<hauteur&&test==0; i++)
    {
        tab[i]=(unsigned char**)malloc(sizeof(unsigned char*)*longueur);
        //test
        if(tab[i]==NULL) test=1;
    }
    //desallocation
    if(test==1)
    {
        printf("erreur de chargement de la map->allocation espace memoire 2\n");
        for(i=i-1; i>=0; i--)
            free(tab[i]);
        free(tab);
        return NULL;
    }

    //allocation 3 dimensions
    for(i=0; i<hauteur&&test==0; i++)
        for(j=0; j<longueur&&test==0; j++) //&&(j==0||tab[i][j-1]!=NULL)
        {
            tab[i][j]=(unsigned char*)malloc(sizeof(unsigned char)*largeur);
            //test
            if(tab[i][j]==NULL) test=1;
        }
    //desallocation
    if(test==1)
    {
        printf("erreur de chargement de la map->allocation espace memoire 3\n");
        do
        {
            do free(tab[i][j-1]);
            while(j>0);
            i--;
            j=longueur-1;
        }
        while(i>0);

        for(i=0; i<hauteur; i++)
            free(tab[i]);
        free(tab);
        return NULL;
    }

    //initialisation par default
    for(i=0; i<hauteur; i++)
        for(j=0; j<longueur; j++)
            for(k=0; k<largeur; k++)
                tab[i][j][k]=0;
    return tab;
}

/**************************************
  source : M. FERCOC COURS 0
**************************************/
///permet de charger une image avec verification d'echec � partir d'une chaine pass�e en param�tre
BITMAP *chargerImage(char *nomFichierImage)
{
    BITMAP *bmp;
    bmp=load_bitmap(nomFichierImage,NULL);
    if (bmp==NULL)
    {
        printf("    Image NON charg\202e : %s\n", nomFichierImage);
        return NULL;
    }
    printf("    Image charg\202e : %s\n", nomFichierImage);
    return bmp;
}
