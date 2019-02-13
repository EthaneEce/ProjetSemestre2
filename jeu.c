#include "biblio.h"


///fonctionnement du jeu pour un niveau de programmation donnée et un niveau de jeu donnée
//en paramètre le niveau de programation et niveau de jeu   ______ on passe également les images annexes (images de fond)
int jeu(int level_prog,int level,t_graphismes* images_annexe)
{

    ///declaration des ressources

    //declaration propre au jeu

    t_niveau* info;//regroupe les information relative à UN niveau
    BITMAP* map;   // map non visible de l'ensemble de la carte
    t_image_level* Im_level; //ensemble des images du niveau (cube personnage etc)
    t_personnage* perso;
    unsigned char*** tab;    //permet de referencer la map 3D


    char actions[nb_action_max];//tableau enregistrant les actions à réaliser
    short int nb_act=0;     //nombre d'action choisi
    short int num_action=0;


    //declaration pour affichage de la map
    int ex,ey;//position haut gauche de l'affichage de la map
    float taille_map=0.7;//facteur d'agrandissement de la map

    int nb_cle;
    int vie=3;
    bool tombe=0;
    int i;

    //gestion des boutons
    bool bretour=0,pretour=0;
    short int exit=0;
    bool baide=0,paide=0;
    bool bexe=0,pexe=0;
    short int exe=0;
    bool ppause=0,bpause=0;
    short int pause=0;


    int compteur=0;

    bool action_realisee;//l'action à t'elle pu etre réalisé ou non ??

    SAMPLE*tomber;
    tomber=logg_load("snd/tomber.ogg");
    SAMPLE*aie;
    aie=logg_load("snd/ayeeeuuu.ogg");


    ///declaration et initialisation en fonction du niveau de prog
    t_prog_1* prog1;
    init_clavier* prog2;
    switch(level_prog)
    {
    case 1:
        prog1=init_prog_1();
        break;
    case 2:
        prog2=init_prog_2();
        break;
    }


    ///chargement de l'ensemble des informations d'un niveau avec  test de succes
    chargement(level_prog,level,&info,&perso,&tab,&Im_level);

    //creation de la bitmap de la map
    map=create_bitmap(info->ecran_w,info->ecran_h);

    //on determine la position de l'écran initial
    projection(&ex,&ey,perso->x,perso->y,perso->z,info);
    ex-=(SCREEN_W-80)*taille_map*1/2;
    ey-=SCREEN_H*taille_map*1/2;
    if(ey<0)
        ey=0;
    if(ex<0)
        ex=0;


    //on positionne notre personnage à son emplacement
    tab[perso->z][perso->y][perso->x]=4;

    for(i=0; i<info->nb_cle; i++)
    {
        tab[info->emplacement_gemmes[i][2]][info->emplacement_gemmes[i][1]][info->emplacement_gemmes[i][0]]=9;
    }
    nb_cle=info->nb_cle;

    for(i=0; i<info->n_allie; i++)
    {

        tab[info->allie[i].z][info->allie[i].y][info->allie[i].x]=0;
        info->allie[i].x=info->allie[i].ini_x;
        info->allie[i].y=info->allie[i].ini_y;
        info->allie[i].z=info->allie[i].ini_z;
        info->allie[i].old_x=info->allie[i].ini_x;
        info->allie[i].old_y=info->allie[i].ini_y;
        info->allie[i].old_z=info->allie[i].ini_z;
        info->allie[i].orientation=info->allie[i].ini_orien;
        info->allie[i].trans=0;
        tab[info->allie[i].z][info->allie[i].y][info->allie[i].x]=6+i;

    }


    do
    {
        //permet de determiner en pourcentage le lieu d'un pixel sur l'écran

        ///affichage général à l'ensemble des niveau de programmation
        //affichage du fond
        stretch_sprite(Buffer,images_annexe->fond_jeu,0,0,SCREEN_W,SCREEN_H);
        //affichage du fond cerveau
        stretch_sprite(Buffer,images_annexe->cerveau,SCREEN_W*2/3,decalage_haut,SCREEN_W*1/3-20,(SCREEN_H>700)?(SCREEN_H)*2/3:SCREEN_H*2/3-15);

        //modelisation de la map 3D sur une map 2D avec fond space
        actualise_map_2D(map,tab, info,Im_level,images_annexe,perso);
        stretch_blit(map,Buffer,ex,ey,(SCREEN_W-80)*taille_map,(SCREEN_H>700)?(SCREEN_H)*taille_map:taille_map*(SCREEN_H-22),30,decalage_haut,(SCREEN_W-80)*2/3,(SCREEN_H>700)?(SCREEN_H)*2/3:SCREEN_H*2/3-15);



        ///affichage et gestion des boutons
        //affichage du logo aide
        masked_stretch_blit(images_annexe->bouton[0],Buffer,0,0,images_annexe->bouton[0]->w,images_annexe->bouton[0]->h,SCREEN_W*8.8/10,SCREEN_H*9/10+decalage_bas,SCREEN_H*1/10,SCREEN_H*1/10);
        //affichage du logo play
        masked_stretch_blit(images_annexe->bouton[1],Buffer,0,0,images_annexe->bouton[1]->w,images_annexe->bouton[1]->h,SCREEN_W*7.3/10,SCREEN_H*9/10+decalage_bas,SCREEN_H*1/10,SCREEN_H*1/10);

        afficher_vie_gemme(vie,nb_cle,Im_level->coeur,Im_level->cle);

        //gestion du bouton retour
        pretour=bretour;
        bretour=draw_bouton((SCREEN_W<1000)?SCREEN_W*0.85:SCREEN_W*0.88,SCREEN_H*0.06,SCREEN_W*0.98,SCREEN_H*0.15,makecol(228,22,84),makecol(239,99,141),3,"RETOUR",font3);
        if(pretour==1&&bretour==0&&!(mouse_b&1))
            exit=1;

        paide=baide;
        if((mouse_b & 1)&&(mouse_x>SCREEN_W*8.8/10.) &&(mouse_x<SCREEN_W*8.8/10.+SCREEN_H*0.1)&&(mouse_y>SCREEN_H*9/10+decalage_bas)&& (mouse_y<SCREEN_H+decalage_bas))
            baide=1;
        else
            baide=0;
        if(paide==1&&baide==0&&!(mouse_b&1))
            aide(level_prog);

        if(pexe==1&&bexe==0&&!(mouse_b&1))
        {
            exe=(exe+1)%2;

            //reinitialisation des valeurur et du tableau
            tab[perso->z][perso->y][perso->x]=0;
            perso->x=perso->ini_x;
            perso->y=perso->ini_y;
            perso->z=perso->ini_z;
            perso->old_x=perso->ini_x;
            perso->old_y=perso->ini_y;
            perso->old_z=perso->ini_z;
            perso->orientation=perso->ini_orien;
            perso->trans=0;
            tab[perso->z][perso->y][perso->x]=4;
            //les gemmes
            nb_cle=info->nb_cle;

            for(i=0; i<info->nb_cle; i++)
            {
                tab[info->emplacement_gemmes[i][2]][info->emplacement_gemmes[i][1]][info->emplacement_gemmes[i][0]]=9;
            }
            for(i=0; i<info->n_allie; i++)
            {

                tab[info->allie[i].z][info->allie[i].y][info->allie[i].x]=0;
                info->allie[i].x=info->allie[i].ini_x;
                info->allie[i].y=info->allie[i].ini_y;
                info->allie[i].z=info->allie[i].ini_z;
                info->allie[i].old_x=info->allie[i].ini_x;
                info->allie[i].old_y=info->allie[i].ini_y;
                info->allie[i].old_z=info->allie[i].ini_z;
                info->allie[i].orientation=info->allie[i].ini_orien;
                info->allie[i].trans=0;
                tab[info->allie[i].z][info->allie[i].y][info->allie[i].x]=6+i;

            }


            compteur=0;
            num_action=0;
            pause=0;
        }
        //gestion du bouton play et arret
        pexe=bexe;
        if((mouse_b & 1)&&(mouse_x>SCREEN_W*7.3/10.) &&(mouse_x<SCREEN_W*7.3/10.+SCREEN_H*0.1)&&(mouse_y>SCREEN_H*9/10+decalage_bas)&& (mouse_y<SCREEN_H+decalage_bas))
            bexe=1;
        else
            bexe=0;



        ///en fonction du style de jeu
        switch(level_prog)
        {
        case 1: //icones
            commande_icone(prog1,actions,&nb_act,&exe);
            break;

        case 2://clavier
            nb_act=strlen(actions);

            commande_cl(prog2,actions,nb_act,&exe);
            break;
        case 3:
            break;
        }


        //deplacement de la map
        if(key[KEY_DOWN]&&ey<map->h-(SCREEN_H)*taille_map)
            ey+=dep_map_par_boucle;
        if(key[KEY_UP]&&ey>0)
            ey-=dep_map_par_boucle;
        if(key[KEY_LEFT]&&ex>0)
            ex-=dep_map_par_boucle;
        if(key[KEY_RIGHT]&&ex<map->w-(SCREEN_W-80)*taille_map)
            ex+=dep_map_par_boucle;

        //agrandissement ou retrecissement de la map
        if(key[KEY_RIGHT]&&key[KEY_LEFT]&&taille_map<2)
            taille_map=taille_map+0.001;
        if(key[KEY_DOWN]&&key[KEY_UP]&&taille_map>0.35)
            taille_map=taille_map-0.001;


        ///si le programmme utilisateur ne compile pas
        if(exe==0)
        {
        }
        ///si on execute le programme utilisateur
        else
        {
            ///gestion de nouveau bouton
            //affichage du logo arret
            /*ce bouton sera gerer en même temps que le bouton play initialement (play/arret)*/
            masked_stretch_blit(images_annexe->bouton[3],Buffer,0,0,images_annexe->bouton[3]->w,images_annexe->bouton[3]->h,SCREEN_W*7.3/10,SCREEN_H*9/10+decalage_bas,SCREEN_H*1/10,SCREEN_H*1/10);

            /*nouveau bouton*/
            //affichage du logo pause
            masked_stretch_blit(images_annexe->bouton[2],Buffer,0,0,images_annexe->bouton[2]->w,images_annexe->bouton[2]->h,SCREEN_W*8/10,SCREEN_H*9/10+decalage_bas,SCREEN_H*1/10,SCREEN_H*1/10);
            //bouton pause et play
            ppause=bpause;
            if((mouse_b & 1)&&(mouse_x>SCREEN_W*8/10.) &&(mouse_x<SCREEN_W*8/10.+SCREEN_H*0.1)&&(mouse_y>SCREEN_H*9/10+decalage_bas)&& (mouse_y<SCREEN_H+decalage_bas))
                bpause=1;
            else
                bpause=0;
            if(ppause==1&&bpause==0&&!(mouse_b&1))
            {
                pause=(pause+1)%2;
            }


            ///fonctionnement du programme utilisateur

            if(pause==0)//il n'y a pas de pause
            {
                ///deplacement
                if(num_action<nb_act||perso->trans<1)
                {
                    compteur++;

                    //si une action n'est pas encore fini
                    if(compteur%(tour_seconde*2/24)==0&&perso->trans<1)
                    {
                        perso->trans=perso->trans+1./24.;
                        for(i=0;i<info->n_allie;i++)
                            info->allie[i].trans=info->allie[i].trans+1./24.;
                    }
                    else
                    {
                        //on réalise l'action suivante
                        if(perso->trans>=1)
                        {

                        }
                        if(compteur%(tour_seconde*2)==0)
                        {
                            perso->old_x=perso->x;
                            perso->old_y=perso->y;
                            perso->old_z=perso->z;

                            for(i=0;i<info->n_allie;i++)
                            {
                                info->allie[i].old_x=info->allie[i].x;
                                info->allie[i].old_y=info->allie[i].y;
                                info->allie[i].old_z=info->allie[i].z;
                            }





                            switch(actions[num_action])
                            {
                            case 'a': //avancer

                            tab[perso->z][perso->y][perso->x]=0;
                                switch(perso->orientation)
                                {
                                case 0:
                                    if(tab[perso->z][perso->y-1][perso->x]==0||tab[perso->z][perso->y-1][perso->x]==9)
                                    {
                                        (perso->y)=perso->y-1;
                                        action_realisee=1;
                                    }
                                    else
                                        action_realisee=0;
                                    break;
                                case 1:
                                    if(tab[perso->z][perso->y][perso->x+1]==0||tab[perso->z][perso->y][perso->x+1]==9)
                                    {
                                        (perso->x)=perso->x+1;
                                        action_realisee=1;
                                    }
                                    else
                                        action_realisee=0;
                                    break;
                                case 2:
                                    if(tab[perso->z][perso->y+1][perso->x]==0||tab[perso->z][perso->y+1][perso->x]==9)
                                    {
                                        (perso->y)=perso->y+1;
                                        action_realisee=1;
                                    }
                                    else
                                        action_realisee=0;
                                    break;
                                case 3:
                                    if(tab[perso->z][perso->y][perso->x-1]==0||tab[perso->z][perso->y][perso->x-1]==9)
                                    {
                                        (perso->x)=perso->x-1;
                                        action_realisee=1;
                                    }
                                    else
                                    {
                                        action_realisee=0;
                                    }
                                    break;
                                }
                                break;

                            case 'd'://tourner a droite
                                tab[perso->z][perso->y][perso->x]=0;
                                perso->orientation++;
                                perso->orientation=perso->orientation%4;
                                action_realisee=1;
                                break;

                            case 'g'://tourner a gauche
                                tab[perso->z][perso->y][perso->x]=0;
                                perso->orientation--;
                                if(perso->orientation<0)
                                    perso->orientation+=4;
                                action_realisee=1;
                                break;

                            case 's'://sauter
                                tab[perso->z][perso->y][perso->x]=0;
                                switch(perso->orientation)
                                {
                                case 0:
                                    if(((tab[perso->z+1][perso->y][perso->x]==0)&&(tab[perso->z+1][perso->y-1][perso->x]==0))||(tab[perso->z+1][perso->y-1][perso->x]==9))
                                    {
                                        perso->y--;
                                        perso->z++;
                                        action_realisee=1;
                                    }
                                    else
                                        action_realisee=0;
                                    break;
                                case 1:
                                    if(((tab[perso->z+1][perso->y][perso->x]==0)&&(tab[perso->z+1][perso->y][perso->x+1]==0))||(tab[perso->z+1][perso->y][perso->x+1]==9))
                                    {
                                        perso->x++;
                                        perso->z++;
                                        action_realisee=1;
                                    }
                                    else
                                        action_realisee=0;
                                    break;
                                case 2:
                                    if(((tab[perso->z+1][perso->y][perso->x]==0)&&(tab[perso->z+1][perso->y+1][perso->x]==0))||(tab[perso->z+1][perso->y+1][perso->x]==9))
                                    {
                                        perso->y++;
                                        perso->z++;
                                        action_realisee=1;
                                    }
                                    else
                                        action_realisee=0;
                                    break;
                                case 3:
                                    if((tab[perso->z+1][perso->y][perso->x]==0&&tab[perso->z+1][perso->y][perso->x-1]==0)||tab[perso->z+1][perso->y][perso->x-1]==9)
                                    {
                                        perso->x--;
                                        perso->z++;
                                        action_realisee=1;
                                    }
                                    else
                                        action_realisee=0;
                                    break;
                                }
                                break;


                            case 'u': //avancer allié
                                for(i=0; i<info->n_allie; i++)
                                tab[info->allie[i].z][info->allie[i].y][info->allie[i].x]=0;
                                action_realisee=1;
                                for(i=0; i<info->n_allie; i++)
                                {

                                    switch(info->allie[i].orientation)
                                    {
                                    case 0:
                                        if(tab[info->allie[i].z][info->allie[i].y-1][info->allie[i].x]==0||tab[info->allie[i].z][info->allie[i].y-1][info->allie[i].x]==9)
                                        {
                                            (info->allie[i].y)=info->allie[i].y-1;
                                        }
                                        else
                                            action_realisee=0;
                                        break;
                                    case 1:
                                        if(tab[info->allie[i].z][info->allie[i].y][info->allie[i].x+1]==0||tab[info->allie[i].z][info->allie[i].y][info->allie[i].x+1]==9)
                                        {
                                            (info->allie[i].x)=info->allie[i].x+1;
                                        }
                                        else
                                            action_realisee=0;
                                        break;
                                    case 2:
                                        if(tab[info->allie[i].z][info->allie[i].y+1][info->allie[i].x]==0||tab[info->allie[i].z][info->allie[i].y+1][info->allie[i].x]==9)
                                        {
                                            (info->allie[i].y)=info->allie[i].y+1;
                                        }
                                        else
                                            action_realisee=0;
                                        break;
                                    case 3:
                                        if(tab[info->allie[i].z][info->allie[i].y][info->allie[i].x-1]==0||tab[info->allie[i].z][info->allie[i].y][info->allie[i].x-1]==9)
                                        {
                                            (info->allie[i].x)=info->allie[i].x-1;
                                        }
                                        else
                                            action_realisee=0;
                                        break;
                                    }
                                }
                                break;


                            case 'r'://tourner a droite allié
                                for(i=0; i<info->n_allie; i++)
                                tab[info->allie[i].z][info->allie[i].y][info->allie[i].x]=0;
                                for(i=0; i<info->n_allie; i++)
                                {
                                    info->allie[i].orientation++;
                                    info->allie[i].orientation=info->allie[i].orientation%4;

                                }
                                action_realisee=1;

                                break;

                            case 'l'://tourner a gauche allié
                                for(i=0; i<info->n_allie; i++)
                                tab[info->allie[i].z][info->allie[i].y][info->allie[i].x]=0;
                                for(i=0; i<info->n_allie; i++)
                                {
                                    info->allie[i].orientation--;
                                    if(info->allie[i].orientation<0)
                                        info->allie[i].orientation+=4;
                                }
                                action_realisee=1;
                                break;


                            case 'j'://sauter
                                for(i=0; i<info->n_allie; i++)
                                tab[info->allie[i].z][info->allie[i].y][info->allie[i].x]=0;
                                action_realisee=1;
                                for(i=0; i<info->n_allie; i++)
                                {
                                    switch(info->allie[i].orientation)
                                    {
                                    case 0:
                                        if(((tab[info->allie[i].z+1][info->allie[i].y][info->allie[i].x]==0)&&(tab[info->allie[i].z+1][info->allie[i].y-1][info->allie[i].x]==0))||(tab[info->allie[i].z+1][info->allie[i].y-1][info->allie[i].x]==9))
                                        {
                                            info->allie[i].y--;
                                            info->allie[i].z++;

                                        }
                                        else
                                            action_realisee=0;
                                        break;
                                    case 1:
                                        if(((tab[info->allie[i].z+1][info->allie[i].y][info->allie[i].x]==0)&&(tab[info->allie[i].z+1][info->allie[i].y][info->allie[i].x+1]==0))||(tab[info->allie[i].z+1][info->allie[i].y][info->allie[i].x+1]==9))
                                        {
                                            info->allie[i].x++;
                                            info->allie[i].z++;

                                        }
                                        else
                                            action_realisee=0;
                                        break;
                                    case 2:
                                        if(((tab[info->allie[i].z+1][info->allie[i].y][info->allie[i].x]==0)&&(tab[info->allie[i].z+1][info->allie[i].y+1][info->allie[i].x]==0))||(tab[info->allie[i].z+1][info->allie[i].y+1][info->allie[i].x]==9))
                                        {
                                            info->allie[i].y++;
                                            info->allie[i].z++;

                                        }
                                        else
                                            action_realisee=0;
                                        break;
                                    case 3:
                                        if((tab[info->allie[i].z+1][info->allie[i].y][info->allie[i].x]==0&&tab[info->allie[i].z+1][info->allie[i].y][info->allie[i].x-1]==0)||tab[info->allie[i].z+1][info->allie[i].y][info->allie[i].x-1]==9)
                                        {
                                            info->allie[i].x--;
                                            info->allie[i].z++;

                                        }
                                        else
                                            action_realisee=0;
                                        break;
                                    }
                                }

                                break;

                            }

                            //on verifier qu'il est bien sur plateforme
                            while(perso->z>0&&tab[perso->z-1][perso->y][perso->x]==0)
                            {
                                perso->z-=1;
                                tombe=1;
                            }
                            for(i=0; i<info->n_allie; i++)
                            {
                                while(info->allie[i].z>0&&tab[info->allie[i].z-1][info->allie[i].y][info->allie[i].x]==0)
                                {
                                    info->allie[i].z-=1;
                                    tombe=1;
                                }
                            }

                            if(tombe==1)
                                play_sample(tomber,255,128,1000,0);///SON TOMBER
                            tombe=0;

                            if(action_realisee==0)//echec
                            {
                                vie-=1;
                                play_sample(aie,255,128,1000,0);                                      ///SON ayeeeeuuuuu.ogg
                                rest(1000);
                                ///image
                                stretch_blit(images_annexe->lose,screen,0,0,images_annexe->lose->w,images_annexe->lose->h,SCREEN_W*0.15,SCREEN_H*0.40,SCREEN_W*0.65,SCREEN_H*0.2);
                                rest(2500);
                                pexe=1;
                                bexe=0;

                            }

                            if(tab[perso->z][perso->y][perso->x]==9)
                                nb_cle-=1;
                            for(i=0; i<info->n_allie; i++)
                            {
                                if(tab[info->allie[i].z][info->allie[i].y][info->allie[i].x]==9)
                                    nb_cle-=1;
                                tab[info->allie[i].z][info->allie[i].y][info->allie[i].x]=6+i;
                            }

                            tab[perso->z][perso->y][perso->x]=4;

                            for(i=0;i<info->n_allie;i++)
                                info->allie[i].trans=0;
                            perso->trans=0;
                            num_action++;
                            compteur=0;

                        }
                    }


                }
                else
                {
                    vie-=1;
                    ///image
                    stretch_blit(images_annexe->lose,screen,0,0,images_annexe->lose->w,images_annexe->lose->h,SCREEN_W*0.15,SCREEN_H*0.40,SCREEN_W*0.65,SCREEN_H*0.2);
                    rest(4000);
                    pexe=1;
                    bexe=0;

                }

            }
            else//il y a pause
            {

                //affichage du logo play au lieu du logo pause
                /*ce bouton est toujours gerer par le bouton pause*/
                masked_stretch_blit(images_annexe->bouton[1],Buffer,0,0,images_annexe->bouton[1]->w,images_annexe->bouton[1]->h,SCREEN_W*8/10,SCREEN_H*9/10+decalage_bas,SCREEN_H*1/10,SCREEN_H*1/10);
                /* tous les autres boutons sont toujours accesible*/
            }
        }

        //affichage du Buffer à l'écran peut importe la situation
        blit(Buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        if(nb_cle==0)
            exit=nb_act;
        if(vie<1)
            exit=2;
    }
    while(!(key[KEY_ESC])&&exit==0);
    // exit = 0 -> on ne quitte pas
    // exit = 1 -> on quitte le programme PAS de victoire, PAS de reusssite
    // exit = 2 -> on quitte le programme AVEC DEFAITE
    // exit > 2 -> on quitte le programme AVEC VICTOIRE


    /***************     important !!!!!!!!   ************/
    /*

    à chaque fin de lecture du programme utilisateur il reussi ou perd une de ces 3 vies


    En fonction du nombre de coup qu'il a fait pour reussir le niveau il aura 1, 2, ou 3 étoiles


    */




    ///liberation de la mémoire alloué dans ce sous programme
    liberation_memoire(level_prog,info,tab,map,Im_level);
    switch(level_prog)
    {
    case 1:
        liberation_memoire_prog1(prog1);
        break;
    case 2:
        break;
    }


    return exit;

}










