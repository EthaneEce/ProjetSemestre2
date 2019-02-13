#include "biblio.h"

//declaration de variable globales
BITMAP* Buffer;

int main()
{

    //declaration des ressources
    t_graphismes* images_annexe=NULL;
    int fin=0;
    int dim;

    int screen_hauteur;
    int screen_largeur;
    int choix;
    int retour_jeu;

    int niv_suiv=0;
    bool babla=0;


    SAMPLE*victoire;

    victoire=logg_load("snd/victoire.ogg");


    do
    {
        printf("\n\n\tVeuillez choisir les dimension d'affichage de l'ecran :\n\t\t1) 1280/720\n\t\t2) 1156/650 \n\t\t3) 1024/768\n\t\t4) 800/600\n\n \tchoix:  ");
        scanf("%d",&dim);

        switch(dim)
        {
        case 1:
            screen_largeur=1280;
            screen_hauteur=720;
            break;
        case 2:
            screen_largeur=1156;
            screen_hauteur=650;
            break;
        case 3:
            screen_largeur=1024;
            screen_hauteur=768;
            break;
        case 4:
            screen_largeur=800;
            screen_hauteur=600;
            break;
        default:
            printf("erreur de saisie ");
        }
    }
    while(dim<1||dim>4);



    //initialisation d'allegro
    lancerToutAllegro(screen_largeur,screen_hauteur);
    Buffer=create_bitmap(SCREEN_W,SCREEN_H);


    //chargement des images neccessaire au jeu en dehors des differents niveaux
    images_annexe=charger_images_annexe();
    printf("\nchargement des images annexes ");
    if(images_annexe==NULL)
    {
        printf("[ECHEC]\n");
        destroy_bitmap(Buffer);
        allegro_message("ECHEC rencontrer precedement    conseil : regarder l'affichage console     bye bye");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    else
        printf("[SUCCES]\n");






    do
    {
        if(niv_suiv==0)
            choix=menu(images_annexe);
        niv_suiv=0;
        switch(choix/10)
        {
        case 0: //Quitter
            switch(choix%10)
            {
            case 0:
                fin=1;
                break;

            case 2:

                break;

            default:
                printf("erreur de saisie2\n");

            }
            break;

        case 1: //image
        case 2: //clique
            retour_jeu=jeu(choix/10,choix%10,images_annexe);
            if(retour_jeu==2)//echec
            {
                do
                {
                    stretch_blit(images_annexe->game_over,Buffer,0,0,images_annexe->game_over->w,images_annexe->game_over->h,0,0,SCREEN_W,SCREEN_H);
                    if(SCREEN_W>805)
                    {
                        babla=draw_bouton(SCREEN_W*0.24,SCREEN_H*0.78,SCREEN_W*0.42,SCREEN_H*0.88,makecol(228,22,84),makecol(239,99,141),3,"RETOUR MENU",font3);
                    niv_suiv=draw_bouton(SCREEN_W*0.60,SCREEN_H*0.78,SCREEN_W*0.83,SCREEN_H*0.88,makecol(34,177,76),makecol(181,230,29),3,"RECOMMENCER",font3);

                    }
                    else
                    {
                        babla=draw_bouton(SCREEN_W*0.24,SCREEN_H*0.78,SCREEN_W*0.47,SCREEN_H*0.88,makecol(228,22,84),makecol(239,99,141),3,"RETOUR MENU",font3);
                    niv_suiv=draw_bouton(SCREEN_W*0.60,SCREEN_H*0.78,SCREEN_W*0.87,SCREEN_H*0.88,makecol(34,177,76),makecol(181,230,29),3,"RECOMMENCER",font3);

                    }

                    //affichage du Buffer à l'écran peut importe la situation
                    blit(Buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);

                }
                while(niv_suiv!=1&&babla!=1);
                babla=0;


            }
            if(retour_jeu>2)///reussite
            {
                save(choix/10,choix%10);
                play_sample(victoire,255,128,1000,0);                                                 ///SON
                do
                {
                    stretch_blit(images_annexe->win,Buffer,0,0,images_annexe->win->w,images_annexe->win->h,0,0,SCREEN_W,SCREEN_H);

                    if(SCREEN_W>805)
                    {babla=draw_bouton(SCREEN_W*0.24,SCREEN_H*0.78,SCREEN_W*0.42,SCREEN_H*0.88,makecol(228,22,84),makecol(239,99,141),3,"RETOUR MENU",font3);
                    if (choix%10<4)
                        niv_suiv=draw_bouton(SCREEN_W*0.60,SCREEN_H*0.78,SCREEN_W*0.83,SCREEN_H*0.88,makecol(34,177,76),makecol(181,230,29),3,"NIVEAU SUIVANT",font3);
                    }
                    else{
                            babla=draw_bouton(SCREEN_W*0.24,SCREEN_H*0.78,SCREEN_W*0.47,SCREEN_H*0.88,makecol(228,22,84),makecol(239,99,141),3,"RETOUR MENU",font3);
                    niv_suiv=draw_bouton(SCREEN_W*0.60,SCREEN_H*0.78,SCREEN_W*0.88,SCREEN_H*0.88,makecol(34,177,76),makecol(181,230,29),3,"NIVEAU SUIVANT",font3);


                    }
                    //affichage du Buffer à l'écran peut importe la situation
                    blit(Buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);


                }
                while(niv_suiv!=1&&babla!=1);
                choix+=1;
                babla=0;

            }
            break;
        default:
            printf("erreur de saisie1\n");
        }
    }
    while(fin==0);


    ///destruction de la memoire alloué
    free_images_annex(images_annexe);

    ///detruire les bitmaps utilisées et les espaces mémoire alloué
    destroy_bitmap(Buffer);

    //confirmation de la fin de programme
    printf("\nLe programme vient de quitter \n bye bye\n");


    return 0;
}
END_OF_MAIN();


