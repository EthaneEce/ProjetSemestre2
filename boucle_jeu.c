#include "biblio.h"


/******************************************************************************************/
///alloue et initialise les variable destinée aux differents niveau de programmation

// initialisation premier niveau icones
t_prog_1* init_prog_1()
{
    t_prog_1* prog1;
    prog1=(t_prog_1*)malloc(sizeof(t_prog_1));

    prog1->images_prog1=charger_images_prog1();
    if(prog1->images_prog1==NULL)
    {
        printf("chargement des images de direction du niveau 1 [ECHEC]\n");
        destroy_bitmap(Buffer);
        allegro_message("ECHEC rencontrer precedement    conseil : regarder l'affichage console     bye bye");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    else
        printf("chargement des images de direction du niveau 1 [SUCCES]\n");

    prog1->action=0;

    return prog1;
}


//initialisation de la commander clavier
init_clavier* init_prog_2()
{
    init_clavier* nouv;
    nouv=(init_clavier*)malloc(sizeof(init_clavier));

    strcpy(nouv->text,"");
    nouv->lettre='9';
    nouv->prec='!';
    nouv->taille=0;

    return nouv;
}

/*******************************************************************************************/
///ensemble de sous programmes incruster dans la boucle de jeu
///actualise le jeu en fonction du niveau de programmation

//niveau prog 1 -> icones
void commande_icone(t_prog_1* prog1,char actions[nb_action_max],short int* nb_act,short int* exe)
{
    ///declaration des ressources
    int j=0,k=0;
    int i;
    int nb_im;//numero de l'image a affiché en fonction de l'instruction

    ///affichage des 4 icones
    //avancer tourner droite gauche et sauter
    for(i=0; i<4; i++)
        masked_stretch_blit(prog1->images_prog1[i],Buffer,0,0,prog1->images_prog1[i]->w,prog1->images_prog1[i]->h,decalage_gauche+SCREEN_W/10+i*(SCREEN_H*1/10+20),SCREEN_H*9/10+decalage_bas,SCREEN_H*1/10,SCREEN_H*1/10);


    ///affichage du tableau d'instruction
    for(i=0; i<*nb_act; i++)
    {
        //on determine ou on affiche notre icone
        j++;
        if(j>((SCREEN_W<1100)?3:4))
        {
            k++;
            j=j-((SCREEN_W<1100)?3:4);
        }
        //on recherche l'image associé à cette action
        switch(actions[i])
        {
        case 'a':
            nb_im=0;
            break;
        case 'd':
            nb_im=1;
            break;
        case 'g':
            nb_im=2;
            break;
        case 's':
            nb_im=3;
            break;
        }
        masked_stretch_blit(prog1->images_prog1[nb_im],Buffer,0,0,prog1->images_prog1[nb_im]->w,prog1->images_prog1[nb_im]->h,SCREEN_W*2/3+20+(j-1)*(SCREEN_H/10+10),decalage_haut+10+k*(SCREEN_H/10+10),SCREEN_H*1/10,SCREEN_H*1/10);
    }




    //si on est pas en cours d'execution du programme utilisateur
    if(*exe==0)
    {
        ///suppresion d'un élément par le clique gauche
        if(mouse_b & 2)
        {
            if((mouse_x>SCREEN_W*2/3)&&(mouse_x<SCREEN_W-20)&&(mouse_y>decalage_haut)&&mouse_y<decalage_haut+(SCREEN_H)*2/3)
            {
                j=0;
                k=0;
                for(i=0; i<*nb_act; i++)
                {
                    j++;
                    if(j>((SCREEN_W<1100)?3:4))
                    {
                        k++;
                        j=j-((SCREEN_W<1100)?3:4);
                    }

                    if(mouse_x>SCREEN_W*2/3+20+(j-1)*(SCREEN_H/10+10)&&mouse_y>decalage_haut+10+k*(SCREEN_H/10+10)&&mouse_x<SCREEN_W*2/3+20+(j-1)*(SCREEN_H/10+10)+SCREEN_H/10&&mouse_y<decalage_haut+10+k*(SCREEN_H/10+10)+SCREEN_H/10)
                    {
                        //supression de l'instuction i
                        for(i=i; i<*nb_act; i++)
                            actions[i]=actions[i+1];
                        *nb_act-=1;
                        rest(300);
                        break;
                    }
                }
            }
        }


        ///ajout d'un élement
        //on le selectionne
        if(mouse_b && 1)
        {
            if(prog1->action==0)//on recupere l'action selectionné au clique
            {
                if(mouse_y>SCREEN_H*9/10+decalage_bas&& mouse_y<SCREEN_H+decalage_bas)
                {
                    if(mouse_x>decalage_gauche+SCREEN_W/10+0*(SCREEN_H*1/10+20) && mouse_x<decalage_gauche+SCREEN_W/10+0*(SCREEN_H*1/10+20)+SCREEN_H/10)
                        prog1->action='a';
                    if(mouse_x>decalage_gauche+SCREEN_W/10+1*(SCREEN_H*1/10+20) && mouse_x<decalage_gauche+SCREEN_W/10+1*(SCREEN_H*1/10+20)+SCREEN_H/10)
                        prog1->action='d';
                    if(mouse_x>decalage_gauche+SCREEN_W/10+2*(SCREEN_H*1/10+20) && mouse_x<decalage_gauche+SCREEN_W/10+2*(SCREEN_H*1/10+20)+SCREEN_H/10)
                        prog1->action='g';
                    if(mouse_x>decalage_gauche+SCREEN_W/10+3*(SCREEN_H*1/10+20) && mouse_x<decalage_gauche+SCREEN_W/10+3*(SCREEN_H*1/10+20)+SCREEN_H/10)
                        prog1->action='s';
                }
            }
        }
        //si on ne clique pas
        //on le depose dans le main
        else
        {
            // on ne clique plus ET on avait selectionné une action
            if(prog1->action!=0)
            {
                if((mouse_x>SCREEN_W*2/3)&&(mouse_x<SCREEN_W-20)&&(mouse_y>decalage_haut)&&(mouse_y<(SCREEN_H>700)?decalage_haut+(SCREEN_H)*2/3:decalage_haut+SCREEN_H*2/3-15))
                {
                    //on verifie qu'on peut encore ajouter des actions
                    if(*nb_act<nb_action_max)
                    {
                        actions[*nb_act]=prog1->action;
                        (*nb_act)++;
                    }
                }
            }
            prog1->action=0;
        }




        /// drag and drop
        //affichage de l'action selectionné au niveau de la souris
        if(prog1->action!=0)
        {
            //on recherche l'image associé à cette action
            switch(prog1->action)
            {
            case 'a':
                nb_im=0;
                break;
            case 'd':
                nb_im=1;
                break;
            case 'g':
                nb_im=2;
                break;
            case 's':
                nb_im=3;
                break;
            }
            //on affichhe cette image au niveau de la souris
            masked_stretch_blit(prog1->images_prog1[nb_im],Buffer,0,0,prog1->images_prog1[nb_im]->w,prog1->images_prog1[nb_im]->h,mouse_x-SCREEN_H/20,mouse_y-SCREEN_H/20,SCREEN_H*1/10,SCREEN_H*1/10);
        }
    }
}




//niveau prog 2 -> clavier
void commande_cl(init_clavier* nouv, char action[nb_action_max],short int nb_act,short int* exe)
{
    int i,rep,testt=1;
    char text1[222]="";
    if(*exe==0)
    {
        nouv->lettre=frappecl();    //on recupere une lettre en fonction de la frappe clavier qui sera rajoutee a la chaine de caractere
        nouv->taille=strlen(nouv->text);  //on mesure la taille de la chaine de caractere a chaque fois
        if (nouv->lettre!=nouv->prec&&nouv->lettre!='0'&&nouv->lettre!='+')
        {
            sprintf(nouv->text,"%s%c",nouv->text,nouv->lettre); //si la lettre tappee est differentee de la precedente, on ajoute la lettre a la chaine. etrangement, meme si la lettre est la meme que la precedente elle est quand meme rajoutee mais ce blindage permet de ne pas permettre l'appuie long
        }
        if (nouv->lettre!=nouv->prec&&nouv->lettre=='0')
        {
            nouv->text[nouv->taille-1]='\0'; //effacement d'une lettre a la fin de la chaine de caractere quand on appuie sur backspace
        }
        if(key[KEY_ENTER])  //quand on appuie sur entrer, on verifie si la chaine tappée est une commande
        {
            if(nouv->text[0]=='r'&&nouv->text[1]=='e'&&nouv->text[2]=='p'&&nouv->text[3]=='e'&&nouv->text[4]=='t'&&nouv->text[5]=='e'&&nouv->text[6]=='r'&&nouv->text[7]==' '&&nouv->text[8]>'1'&&nouv->text[8]<'9'&&nouv->text[9]==' ')
            {
                rep=nouv->text[8]-'0';
                for(i=10; i<strlen(nouv->text); i++)
                    sprintf(text1,"%s%c",text1,nouv->text[i]);
                for(i=0; i<rep; i++)
                    testt=test(text1,action);
                sprintf(text1,"");
                sprintf(nouv->text,"");
            }
            testt=test(nouv->text,action);
            if (testt==0)
                sprintf(nouv->text,"");
        }
        clear_keybuf();
        nouv->prec=nouv->lettre;
    }
    textout_ex(Buffer,font4,nouv->text,SCREEN_W*0.67,SCREEN_H*0.81,makecol(0,0,0),makecol(148,157,165));

    if(*exe==0)
    {
        if (action[0]=='@'||action[0]=='c')
        {
            for(i=0; i<nb_act; i++)
                action[i]=action[i+1];
            action[nb_act]='\0';
            rest(300);
        }
        ///suppresion d'un élément par le clique gauche
        if(mouse_b&2)
        {
            if(mouse_x>SCREEN_W*0.67&&mouse_x<SCREEN_W*0.75)
            {
                for(i=0; i<nb_act; i++)
                {
                    if(mouse_y>SCREEN_H*0.22+i*17&&mouse_y<SCREEN_H*0.22+(i+1)*17)
                    {
                        for(i=i; i<nb_act; i++)
                            action[i]=action[i+1];
                        action[nb_act]='\0';
                        rest(300);
                        break;
                    }
                }
            }
        }
    }
    ///affichage du tableau
    for(i=0; i<nb_act; i++)
    {
        if (action[i]=='a')
        {
            sprintf(nouv->textaff,"Avancer");
        }
        else if (action[i]=='g')
        {
            sprintf(nouv->textaff,"Gauche");
        }
        else if (action[i]=='d')
        {
            sprintf(nouv->textaff,"Droite");
        }
        else if (action[i]=='s')
        {
            sprintf(nouv->textaff,"Sauter");
        }
        else if (action[i]=='u')
        {
            sprintf(nouv->textaff,"Allie Avancer");
        }
        else if (action[i]=='l')
        {
            sprintf(nouv->textaff,"Allie Gauche");
        }
        else if (action[i]=='r')
        {
            sprintf(nouv->textaff,"Allie Droite");
        }
        else if (action[i]=='j')
        {
            sprintf(nouv->textaff,"Allie Sauter");
        }
        else
        {
            sprintf(nouv->textaff,"");
        }

        textout_ex(Buffer,font4,nouv->textaff,SCREEN_W*0.67,SCREEN_H*0.22+i*17,makecol(0,0,0),makecol(148,157,165));

    }
}

int test(char text[222], char action[nb_action_max])
{
    if(strcmp(text,"avancer")==0)
    {

        sprintf(action,"%s%c",action,'a');

        return 0;
    }
    if(strcmp(text,"gauche")==0)
    {

        sprintf(action,"%s%c",action,'g');

        return 0;
    }
    if(strcmp(text,"droite")==0)
    {

        sprintf(action,"%s%c",action,'d');

        return 0;
    }
    if(strcmp(text,"sauter")==0)
    {

        sprintf(action,"%s%c",action,'s');

        return 0;
    }

    if(strcmp(text,"allie avancer")==0)
    {

        sprintf(action,"%s%c",action,'u');

        return 0;
    }
    if(strcmp(text,"allie gauche")==0)
    {

        sprintf(action,"%s%c",action,'l');

        return 0;
    }
    if(strcmp(text,"allie droite")==0)
    {

        sprintf(action,"%s%c",action,'r');

        return 0;
    }
    if(strcmp(text,"allie sauter")==0)
    {

        sprintf(action,"%s%c",action,'j');

        return 0;
    }

}



/**********************************************************************************************/
//par defaut, allegro utilise un clavier qwerty, on est donc obliger de convertir le clavier ainsi
char frappecl()
{
    char let='+';
    if (key[KEY_Q])
        let= 'a';
    if (key[KEY_B])
        let= 'b';
    if (key[KEY_C])
        let= 'c';
    if (key[KEY_D])
        let= 'd';
    if (key[KEY_E])
        let= 'e';
    if (key[KEY_F])
        let= 'f';
    if (key[KEY_G])
        let= 'g';
    if (key[KEY_H])
        let= 'h';
    if (key[KEY_I])
        let= 'i';
    if (key[KEY_J])
        let= 'j';
    if (key[KEY_K])
        let= 'k';
    if (key[KEY_L])
        let= 'l';
    if (key[KEY_SEMICOLON])
        let= 'm';
    if (key[KEY_N])
        let= 'n';
    if (key[KEY_O])
        let= 'o';
    if (key[KEY_P])
        let= 'p';
    if (key[KEY_A])
        let= 'q';
    if (key[KEY_R])
        let= 'r';
    if (key[KEY_S])
        let= 's';
    if (key[KEY_T])
        let= 't';
    if (key[KEY_U])
        let= 'u';
    if (key[KEY_V])
        let= 'v';
    if (key[KEY_Z])
        let= 'w';
    if (key[KEY_X])
        let= 'x';
    if (key[KEY_Y])
        let= 'y';
    if (key[KEY_W])
        let= 'z';
    if (key[KEY_SPACE])
        let= ' ';
    if(key[KEY_BACKSPACE])
        let= '0';
    if (key[KEY_1])
        let= '1';
    if (key[KEY_2])
        let= '2';
    if (key[KEY_3])
        let= '3';
    if (key[KEY_4])
        let= '4';
    if (key[KEY_5])
        let= '5';
    if (key[KEY_6])
        let= '6';
    if (key[KEY_7])
        let= '7';
    if (key[KEY_8])
        let= '8';
    if (key[KEY_9])
        let= '9';
    return let;
}

void afficher_vie_gemme(int vie,int gemme, BITMAP*g,BITMAP*v)
{
    char vi,gemm;
    vi='0'+vie;
    gemm='0'+gemme;
    char text[10]="";
    sprintf(text,"= x%c",vi);

    masked_stretch_blit(g,Buffer,0,0,g->w,g->h,SCREEN_W*0.04,SCREEN_H*0.11,35,35);
    // draw_sprite(Buffer,g,SCREEN_W*0.06,SCREEN_H*0.14);
    textout_ex(Buffer,font3,text,SCREEN_W*0.09,SCREEN_H*0.12,makecol(0,0,0),makecol(148,157,165));

    sprintf(text,"= x%c",gemm);
    masked_stretch_blit(v,Buffer,0,0,v->w,v->h,SCREEN_W*0.21,SCREEN_H*0.10,80,80);
    //draw_sprite(Buffer,v,SCREEN_W*0.24,SCREEN_H*0.14);
    textout_ex(Buffer,font3,text,SCREEN_W*0.28,SCREEN_H*0.12,makecol(0,0,0),makecol(148,157,165));
}




