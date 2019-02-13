#include "biblio.h"
/********************************************************************************************************************
********     ensemble des sous programme permettant la modélisation et affichage 3D du jeu       ********************
*********************************************************************************************************************/


///affiche la map 3D sur une BITMAP 2D avec une image de fond
void actualise_map_2D(BITMAP* mappe,unsigned char*** tab,t_niveau* info,t_image_level* level,t_graphismes* images_annexe,t_personnage* perso)
{
    //declaration variables

    int x,y,z;//position de la map
    int xe,ye;//position à l'écran
    int value;
    int n_im_mvt;
    int num_allie=0;

    //initialisation du fond d'écran
    //blit(images_annexe->space,mappe,0,0,0,0,images_annexe->space->w,images_annexe->space->h);
    stretch_sprite(mappe,images_annexe->space,0,0,mappe->w,mappe->h);

    //affichage des infos sur une bitmap
    for (x=0; x<info->map_x; x++)
        for (y=0; y<info->map_y; y++)
            for (z=0; z<info->map_z; z++)
            {
                value=tab[z][y][x];
                if(value!=0 && value<4)//les cubes
                {
                    projection(&xe, &ye, x, y, z,info);
                    masked_blit(level->cube[value-1],mappe,0,0, xe, ye,level->cube[value-1]->w,level->cube[value-1]->h);
                }
                if(value==9)//la cles
                {
                    projection(&xe, &ye, x, y, z,info);
                    masked_blit(level->cle,mappe,0,0, xe, ye,level->cle->w,level->cle->h);
                }

                if(value==4)//le perso principal
                {
                    projection(&xe,&ye,perso->old_x+(perso->x-perso->old_x)*perso->trans,perso->old_y+(perso->y-perso->old_y)*perso->trans,perso->old_z+(perso->z-perso->old_z)*perso->trans,info);
                    if((perso->old_x!=perso->x||perso->old_y!=perso->y)&&!(perso->old_z<perso->z))
                        n_im_mvt=perso->trans*6;
                    else
                        n_im_mvt=0;

                    while(n_im_mvt>2)n_im_mvt-=3;

                    masked_blit(level->personnage[0][perso->orientation][n_im_mvt],mappe,0,0,5+xe,ye,level->personnage[0][perso->orientation][n_im_mvt]->w,level->personnage[0][perso->orientation][n_im_mvt]->h);
                }
                if(value>5&&value!=9)
                {

                    num_allie=value-6;

                    projection(&xe,&ye,info->allie[num_allie].old_x+(info->allie[num_allie].x-info->allie[num_allie].old_x)*info->allie[num_allie].trans,info->allie[num_allie].old_y+(info->allie[num_allie].y-info->allie[num_allie].old_y)*info->allie[num_allie].trans,info->allie[num_allie].old_z+(info->allie[num_allie].z-info->allie[num_allie].old_z)*info->allie[num_allie].trans,info);

                    if((info->allie[num_allie].old_x!=info->allie[num_allie].x||info->allie[num_allie].old_y!=info->allie[num_allie].y)&&!(info->allie[num_allie].old_z<info->allie[num_allie].z))
                        n_im_mvt=info->allie[num_allie].trans*6;
                    else
                        n_im_mvt=0;

                    while(n_im_mvt>2)n_im_mvt-=3;

                    masked_blit(level->personnage[1][info->allie[num_allie].orientation][n_im_mvt],mappe,0,0,xe,15+ye,level->personnage[1][info->allie[num_allie].orientation][n_im_mvt]->w,level->personnage[1][info->allie[num_allie].orientation][n_im_mvt]->h);

                }
            }
}


/*----------- source : M. FERCOC COURS 0  -------------------------*/
/// Fonction de projection 3D -> 2D pour un element
void projection(int *pxe, int *pye, float x, float y, float z,t_niveau* info)
{
    *pxe = 2*16*( 2*x - 2*y) +info->ecran_w-info->decalage_w;//
    *pye = 2*16*(x + y - 2*z) +info->decalage_h;//
}

