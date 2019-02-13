#ifndef JEU_MODELISATION_3D_H_INCLUDED
#define JEU_MODELISATION_3D_H_INCLUDED



/*******************************************
*************   prototypes *****************
********************************************/

///affiche la map 3D sur une BITMAP 2D avec une image de fond
void actualise_map_2D(BITMAP* mappe,unsigned char*** tab,t_niveau* info,t_image_level*,t_graphismes* images_annexe,t_personnage* perso);

/*----------- source : M. FERCOC COURS 0  -------------------------*/
/// Fonction de projection 3D -> 2D pour un element
void projection(int *pxe, int *pye, float x, float y, float z,t_niveau* info);


#endif // JEU_MODELISATION_3D_H_INCLUDED
