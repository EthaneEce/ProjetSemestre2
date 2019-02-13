#include "biblio.h"


/**************************************************************************************************************/
///variables globales
//permet de gerer les polices de texte en affichage graphique
FONT* font3;
FONT* font4;


/*

//permet de determiner en pourcentage le lieu d'un pixel sur l'écran
if(mouse_b&1)
    printf("x : %d , y :%d \ n",mouse_x*100/SCREEN_W, mouse_y*100/SCREEN_H);

*/

/***************************************************************************************************************/

///permet l'affichage du image_annexe->menu et permet l'interaction avec l'utilisateur
//il renvoie une valeur correspondant au choix de l'utilisateur :
//      -> 0 pour quitter, 5 pour l'aide, 1 pour clic, 2 pour clavier, 3 pour scratch
int menu(t_graphismes* image_annexe)
{
    ///declaration des ressouces
    //resources necessaire au pigeon


    int x=0;                // emplacement en x des pigeons
    int y=rand()%SCREEN_H;  // enplacement en y du pigeon 1
    int y2=rand()%SCREEN_H; // enplacement en y du pigeon 2
    int compt=0;            // reference l'image du pigeon à afficher

    //resources necessaire aux boutons
    bool bquitter,baide,bselec,bclic,bclavier,bscratch;             //action du bouton actuelle
    bool Pquitter=0,Paide=0,Pselec=0,Pclic=0,Pclavier=0,Pscratch=0; //action du bouton précedent

    int lvl;
    int* lvlunlock;

    lvlunlock=recup_fichier_unlock();

    ///chargement des polices
    // !!! variables globales
    //FONT*font1=load_font("font/font1.pcx",NULL,NULL);
    //FONT*font2=load_font("font/font2.pcx",NULL,NULL);
    font3=load_font("font/font3.pcx",NULL,NULL);
    font4=load_font("font/code.pcx",NULL,NULL);

    for(;;)//boucle infini on sort de cette boucle grace au return
    {


        //afichage du fond et des pigeons
        draw_sprite(Buffer,image_annexe->fondmenu,0,0);
        draw_sprite(Buffer,image_annexe->pigeon[compt],x/3,y);
        draw_sprite_h_flip(Buffer,image_annexe->pigeon[compt],SCREEN_W-x/3,y2);
        draw_sprite(Buffer,image_annexe->menu,SCREEN_W/2-167,SCREEN_H*0.04);

        //affichage des boutons
        /*ces tests permettent un affichage des boutons en fonction de la taille de l'ecran pour que le texte ne sortent pas de cette zone
         ces test ne sont pas idéals le mieux serait de creer un tableau constant référencant les differentes variations */
        if(SCREEN_W<1000)
        {
            bselec=draw_bouton(SCREEN_W*0.31,SCREEN_H*0.52,SCREEN_W*0.69,SCREEN_H*0.59,makecol(0,192,232),makecol(168,222,240),3,"SELECTION DU NIVEAU",font3);
            baide=draw_bouton(SCREEN_W*0.44,SCREEN_H*0.66,SCREEN_W*0.56,SCREEN_H*0.73,makecol(34,177,76),makecol(181,230,29),3,"AIDE",font3);
            bquitter=draw_bouton(SCREEN_W*0.43,SCREEN_H*0.80,SCREEN_W*0.57,SCREEN_H*0.87,makecol(228,22,84),makecol(239,99,141),3,"QUITTER",font3);
        }
        if(SCREEN_W>1000&&SCREEN_W<1050)
        {
            bselec=draw_bouton(SCREEN_W*0.35,SCREEN_H*0.52,SCREEN_W*0.65,SCREEN_H*0.59,makecol(0,192,232),makecol(168,222,240),3,"SELECTION DU NIVEAU",font3);
            baide=draw_bouton(SCREEN_W*0.44,SCREEN_H*0.66,SCREEN_W*0.56,SCREEN_H*0.73,makecol(34,177,76),makecol(181,230,29),3,"AIDE",font3);
            bquitter=draw_bouton(SCREEN_W*0.43,SCREEN_H*0.80,SCREEN_W*0.57,SCREEN_H*0.87,makecol(228,22,84),makecol(239,99,141),3,"QUITTER",font3);
        }

        if (SCREEN_W>1100&&SCREEN_W<1180)
        {
            bselec=draw_bouton(SCREEN_W*0.37,SCREEN_H*0.52,SCREEN_W*0.63,SCREEN_H*0.59,makecol(0,192,232),makecol(168,222,240),3,"SELECTION DU NIVEAU",font3);
            baide=draw_bouton(SCREEN_W*0.44,SCREEN_H*0.66,SCREEN_W*0.56,SCREEN_H*0.73,makecol(34,177,76),makecol(181,230,29),3,"AIDE",font3);
            bquitter=draw_bouton(SCREEN_W*0.43,SCREEN_H*0.80,SCREEN_W*0.57,SCREEN_H*0.87,makecol(228,22,84),makecol(239,99,141),3,"QUITTER",font3);
        }

        if(SCREEN_W>1200)
        {
            bselec=draw_bouton(SCREEN_W*0.37,SCREEN_H*0.52,SCREEN_W*0.63,SCREEN_H*0.59,makecol(0,192,232),makecol(168,222,240),3,"SELECTION DU NIVEAU",font3);
            baide=draw_bouton(SCREEN_W*0.44,SCREEN_H*0.66,SCREEN_W*0.56,SCREEN_H*0.73,makecol(34,177,76),makecol(181,230,29),3,"AIDE",font3);
            bquitter=draw_bouton(SCREEN_W*0.43,SCREEN_H*0.80,SCREEN_W*0.57,SCREEN_H*0.87,makecol(228,22,84),makecol(239,99,141),3,"QUITTER",font3);
        }


        //gestion du pigeon
        x++;
        if(x%vitesse_pi==0)//on change l'image si besoin du pigeon pour l'animation
            compt++;
        if(compt>8)
            compt=0;

        if(x>SCREEN_W*3)
        {
            x=0;
            y=rand()%(SCREEN_H-50);
            y2=rand()%(SCREEN_H-50);
        }

        //on affiche le buffer à l'écran
        draw_sprite(screen, Buffer, 0,0);



        //si on a appuié  sur le bouton de selection du niveau et que l'on relache
        if(bselec==0&&Pselec==1&&(!mouse_b&1))
        {
            charger_histoire();
            do
            {
                //affichage du fond
                draw_sprite(Buffer,image_annexe->fondmenu,0,0);

                //affichage des boutons
                /*ces tests permettent un affichage des boutons en fonction de la taille de l'ecran pour que le texte ne sortent pas de cette zone
                ces test ne sont pas idéals le mieux serait de creer un tableau constant référencant les differentes variations */

                if(SCREEN_W<1000&&SCREEN_W>600)
                {
                    bclic=draw_bouton(SCREEN_W*0.34,SCREEN_H*0.52,SCREEN_W*0.66,SCREEN_H*0.59,makecol(0,192,232),makecol(168,222,240),3,"JOUER AUX CLICS",font3);
                    bclavier=draw_bouton(SCREEN_W*0.16,SCREEN_H*0.66,SCREEN_W*0.84,SCREEN_H*0.73,makecol(34,177,76),makecol(181,230,29),3,"JOUER AVEC LES COMMANDES CLAVIER",font3);
                    bscratch=draw_bouton(SCREEN_W*0.30,SCREEN_H*0.80,SCREEN_W*0.70,SCREEN_H*0.87,makecol(228,22,84),makecol(239,99,141),3,"JOUER AVEC SCRATCH",font3);
                }
                if(SCREEN_W>1000&&SCREEN_W<1050)
                {
                    bclic=draw_bouton(SCREEN_W*0.38,SCREEN_H*0.52,SCREEN_W*0.62,SCREEN_H*0.59,makecol(0,192,232),makecol(168,222,240),3,"JOUER AUX CLICS",font3);
                    bclavier=draw_bouton(SCREEN_W*0.25,SCREEN_H*0.66,SCREEN_W*0.75,SCREEN_H*0.73,makecol(34,177,76),makecol(181,230,29),3,"JOUER AVEC LES COMMANDES CLAVIER",font3);
                    bscratch=draw_bouton(SCREEN_W*0.34,SCREEN_H*0.80,SCREEN_W*0.66,SCREEN_H*0.87,makecol(228,22,84),makecol(239,99,141),3,"JOUER AVEC SCRATCH",font3);
                }
                if (SCREEN_W>1100&&SCREEN_W<1180)
                {
                    bclic=draw_bouton(SCREEN_W*0.38,SCREEN_H*0.52,SCREEN_W*0.62,SCREEN_H*0.59,makecol(0,192,232),makecol(168,222,240),3,"JOUER AUX CLICS",font3);
                    bclavier=draw_bouton(SCREEN_W*0.27,SCREEN_H*0.66,SCREEN_W*0.73,SCREEN_H*0.73,makecol(34,177,76),makecol(181,230,29),3,"JOUER AVEC LES COMMANDES CLAVIER",font3);
                    bscratch=draw_bouton(SCREEN_W*0.36,SCREEN_H*0.80,SCREEN_W*0.64,SCREEN_H*0.87,makecol(228,22,84),makecol(239,99,141),3,"JOUER AVEC SCRATCH",font3);
                }
                if(SCREEN_W>1200)
                {
                    bclic=draw_bouton(SCREEN_W*0.38,SCREEN_H*0.52,SCREEN_W*0.62,SCREEN_H*0.59,makecol(0,192,232),makecol(168,222,240),3,"JOUER AUX CLICS",font3);
                    bclavier=draw_bouton(SCREEN_W*0.27,SCREEN_H*0.66,SCREEN_W*0.73,SCREEN_H*0.73,makecol(34,177,76),makecol(181,230,29),3,"JOUER AVEC LES COMMANDES CLAVIER",font3);
                    bscratch=draw_bouton(SCREEN_W*0.36,SCREEN_H*0.80,SCREEN_W*0.64,SCREEN_H*0.87,makecol(228,22,84),makecol(239,99,141),3,"JOUER AVEC SCRATCH",font3);
                }

                draw_sprite(screen, Buffer, 0,0);

                if (bclic==0&&Pclic==1&&(!mouse_b&1))
                {
                    aide(1);
                    lvl=seleclvl(10,lvlunlock);
                    return lvl;
                }


                if (bclavier==0&&Pclavier==1&&(!mouse_b&1))
                {
                    ///aide(2);
                    lvl=seleclvl(20,lvlunlock);
                    return lvl;
                }


                if (bscratch==0&&Pscratch==1&&(!mouse_b&1))
                {
                    lvl=seleclvl(30,lvlunlock);
                    return lvl;
                }


                //gestion du bouton clique pour savoir quand est ce qu'on relache le bouton
                Pclic=0;
                Pclavier=0;
                Pscratch=0;

                Pclic=bclic;
                Pclavier=bclavier;
                Pscratch=bscratch;
            }
            while(!key[KEY_ESC]);
            bselec=0;
        }

        // bouton quitter
        if(bquitter==0&&Pquitter==1&&(!mouse_b&1))
        {
            return 0;
        }

        //bouton aide
        if(baide==0&&Paide==1&&(!mouse_b&1))
        {
            aide(3);
            return 2;
        }

        //gestion du bouton clique pour savoir quand est ce qu'on relache le bouton
        Pselec=0;
        Paide=0;
        Pquitter=0;

        Pselec=bselec;
        Pquitter=bquitter;
        Paide=baide;
    }
}


/// menu secondaire de selection de niveau
int seleclvl(int lvlprog,int lvlunlock[3])
{
    int i;
    char text[222];
    BITMAP*fond,*selection,*cadenas;
    BITMAP*lvl[4];
    fond=chargerImage("IMAGES/annexe/fondmenu.bmp");
    selection=chargerImage("IMAGES/annexe/selction/selection.bmp");
    cadenas=chargerImage("IMAGES/annexe/selction/cadenas.bmp");

    for(i=0; i<4; i++)
    {
        sprintf(text,"IMAGES/annexe/selction/selection%c.bmp",i+'1');
        lvl[i]=chargerImage(text);
    }
    while(!key[KEY_ESC])
    {
        draw_sprite(Buffer,fond,0,0);
        masked_stretch_blit(selection,Buffer,0,0,193,43,SCREEN_W/2-SCREEN_W/6,SCREEN_H/25,SCREEN_W/3,SCREEN_H/9);
        stretch_blit(lvl[0],Buffer,0,0,800,450,SCREEN_W*0.08,SCREEN_H*0.20,SCREEN_W*0.37,SCREEN_H*0.34);
        stretch_blit(lvl[1],Buffer,0,0,800,450,SCREEN_W*0.55,SCREEN_H*0.20,SCREEN_W*0.37,SCREEN_H*0.34);
        stretch_blit(lvl[2],Buffer,0,0,800,450,SCREEN_W*0.08,SCREEN_H*0.60,SCREEN_W*0.37,SCREEN_H*0.34);
        stretch_blit(lvl[3],Buffer,0,0,800,450,SCREEN_W*0.55,SCREEN_H*0.60,SCREEN_W*0.37,SCREEN_H*0.34);

        if (lvlunlock[lvlprog/10-1]<4)
        {
            masked_stretch_blit(cadenas,Buffer,0,0,246,238,SCREEN_W*0.55,SCREEN_H*0.60,SCREEN_W*0.37,SCREEN_H*0.34);
            if (lvlunlock[lvlprog/10-1]<3)
            {
                masked_stretch_blit(cadenas,Buffer,0,0,246,238,SCREEN_W*0.08,SCREEN_H*0.60,SCREEN_W*0.37,SCREEN_H*0.34);
                if (lvlunlock[lvlprog/10-1]<2)
                {
                    masked_stretch_blit(cadenas,Buffer,0,0,246,238,SCREEN_W*0.55,SCREEN_H*0.20,SCREEN_W*0.37,SCREEN_H*0.34);
                }
            }
        }
        else if (lvlunlock[lvlprog/10-1]==4)
        {
            if(mouse_b&1)
            {
                if ((mouse_x>SCREEN_W*0.08&&mouse_x<SCREEN_W*0.08+SCREEN_W*0.37)&&(mouse_y>SCREEN_H*0.20&&mouse_y<SCREEN_H*0.20+SCREEN_H*0.34))
                    return lvlprog+1;
                if ((mouse_x>SCREEN_W*0.55&&mouse_x<SCREEN_W*0.55+SCREEN_W*0.37)&&(mouse_y>SCREEN_H*0.20&&mouse_y<SCREEN_H*0.20+SCREEN_H*0.34))
                    return lvlprog+2;
                if ((mouse_x>SCREEN_W*0.08&&mouse_x<SCREEN_W*0.08+SCREEN_W*0.37)&&(mouse_y>SCREEN_H*0.60&&mouse_y<SCREEN_H*0.60+SCREEN_H*0.34))
                    return lvlprog+3;
                if ((mouse_x>SCREEN_W*0.55&&mouse_x<SCREEN_W*0.55+SCREEN_W*0.37)&&(mouse_y>SCREEN_H*0.60&&mouse_y<SCREEN_H*0.60+SCREEN_H*0.34))
                    return lvlprog+4;
            }
        }
        if (lvlunlock[lvlprog/10-1]==3)
        {
            if(mouse_b&1)
            {
                if ((mouse_x>SCREEN_W*0.08&&mouse_x<SCREEN_W*0.08+SCREEN_W*0.37)&&(mouse_y>SCREEN_H*0.20&&mouse_y<SCREEN_H*0.20+SCREEN_H*0.34))
                    return lvlprog+1;
                if ((mouse_x>SCREEN_W*0.55&&mouse_x<SCREEN_W*0.55+SCREEN_W*0.37)&&(mouse_y>SCREEN_H*0.20&&mouse_y<SCREEN_H*0.20+SCREEN_H*0.34))
                    return lvlprog+2;
                if ((mouse_x>SCREEN_W*0.08&&mouse_x<SCREEN_W*0.08+SCREEN_W*0.37)&&(mouse_y>SCREEN_H*0.60&&mouse_y<SCREEN_H*0.60+SCREEN_H*0.34))
                    return lvlprog+3;
            }
        }
        if (lvlunlock[lvlprog/10-1]==2)
        {
            if(mouse_b&1)
            {
                if ((mouse_x>SCREEN_W*0.08&&mouse_x<SCREEN_W*0.08+SCREEN_W*0.37)&&(mouse_y>SCREEN_H*0.20&&mouse_y<SCREEN_H*0.20+SCREEN_H*0.34))
                    return lvlprog+1;
                if ((mouse_x>SCREEN_W*0.55&&mouse_x<SCREEN_W*0.55+SCREEN_W*0.37)&&(mouse_y>SCREEN_H*0.20&&mouse_y<SCREEN_H*0.20+SCREEN_H*0.34))
                    return lvlprog+2;
            }
        }
        if (lvlunlock[lvlprog/10-1]==1)
        {
            if(mouse_b&1)
            {
                if ((mouse_x>SCREEN_W*0.08&&mouse_x<SCREEN_W*0.08+SCREEN_W*0.37)&&(mouse_y>SCREEN_H*0.20&&mouse_y<SCREEN_H*0.20+SCREEN_H*0.34))
                    return lvlprog+1;
            }
        }


        draw_sprite(screen,Buffer,0,0);
    }
    return 0;
}



/* ****************************************************************************************************
*                    SOURCE :                                                                        *
* https://codes-sources.commentcamarche.net/source/31767-dessin-d-un-bouton-a-enfoncer-en-allegro-c  *
*                                                                                                    *
******************************************************************************************************/

///fonction affichant un bouton texte et renvoie si on clique dessus
// -> permet l'affichage d'un bouton avec effet d'enfoncement du clique
// -> il retourne 1 si on clique et 0 si on ne clique pas
int draw_bouton(int posx, int posy, int pos2x, int pos2y, int color1, int color2, int profondeur, char* texte,FONT*font1)
{
    int pos_mouse=1; // Pour savoir si la souris est sur le bouton
    int color; // Pour definir la couleur du bouton
    int c_hg; // Couleur du coin haut gauche
    int c_bd; // Couleur du coin bas droite
    int texte_x; // Position du texte en x
    int texte_y; // Position du texte en y
    int retour=0; // Renvoi
    int i;


    if(profondeur >5)
        profondeur=5;
    if(profondeur <=0)
        profondeur=1;

    // Si la souris est sur le bouton on modifie la valeur de pos_mouse
    if(mouse_x>=posx && mouse_x<=pos2x && mouse_y>=posy && mouse_y<=pos2y)
    {
        pos_mouse=2;
        // Si l'utilisateur clique sur le bouton
        if(mouse_b & 1)
        {
            pos_mouse=3;
            // On renvoie un 1 si le bouton est enfoncé
            retour=1;
        }
    }
    else
        pos_mouse=1;


    // Changement des couleurs pour les effets de perspective et pour savoir si la souris est sur le bouton
    switch(pos_mouse)
    {
    case 1:
        c_hg=couleur_max;
        c_bd=0;
        color=color1;
        texte_x=(posx+pos2x)/2;
        texte_y=(posy+pos2y)/2;
        break;
    case 2:
        c_hg=couleur_max;
        c_bd=0;
        color=color2;
        texte_x=(posx+pos2x)/2;
        texte_y=(posy+pos2y)/2;
        break;
    case 3:
        c_hg=0;
        c_bd=couleur_max;
        color=color2;
        texte_x=((posx+pos2x)/2)+profondeur;
        texte_y=((posy+pos2y)/2)+profondeur;
        break;
    }


    // Dessin de lignes blanches et noires pour la perspective
    for(i=0; i!=profondeur; i++)
    {
        hline(Buffer,posx,posy+i,pos2x-i,makecol(c_hg,c_hg,c_hg));
        vline(Buffer,posx+i,posy,pos2y-i,makecol(c_hg,c_hg,c_hg));
        hline(Buffer,posx+i,pos2y-i,pos2x,makecol(c_bd,c_bd,c_bd));
        vline(Buffer,pos2x-i,posy+i,pos2y,makecol(c_bd,c_bd,c_bd));
    }

    // Remplissage du bouton
    rectfill(Buffer,posx+profondeur,posy+profondeur,pos2x-profondeur,pos2y-profondeur,color);
    // Ecriture du texte


    //textprintf_centre(buffer,font1,texte_x,texte_y,makecol(255,255,255),"%s",texte);

    textout_centre_ex(Buffer,font1,texte,texte_x,texte_y-13,makecol(couleur_max,couleur_max,couleur_max),color);

    ///textout(buffer,font,texte,texte_x,texte_y,makecol(255,255,255));

    // Renvoi : 1 si le bouton a été cliqué, 0 sinon
    return retour;
}


/**************************************************************************************************************************/

///permet d'initialiser la fenetre d'allegro a la bonne dimension avec verification
/* ********************************************
*****    source : TD de Mme PALASI       *****
**********************************************/
void lancerToutAllegro(int largeur, int hauteur)
{
    /// initialisation générale
    allegro_init();
    install_keyboard();
    install_mouse();

    /// initialisation du MODE GRAPHIQUE
    //on fixe le mode couleur (8, 16, 24 ou 32 bits)
    set_color_depth(desktop_color_depth());

    // on essaie d’ouvrir une fenêtre de largeur*hauteur pixels
    // si l’ouverture échoue on quitte
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,largeur,hauteur,0,0)!=0)
    {
        allegro_message("probleme mode graphique : %s", allegro_error);
        allegro_exit();
        exit(EXIT_FAILURE);
    }


    if(install_sound(DIGI_AUTODETECT,MIDI_NONE,0)!=0)
    {
        allegro_message("probleme installation sonore : %s", allegro_error);
        allegro_exit();
        exit(EXIT_FAILURE);

    }
    install_timer();

    /// si on veut afficher le pointeur de souris
    show_mouse(screen);
}

