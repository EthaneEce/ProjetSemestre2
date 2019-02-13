#include "biblio.h"

/* sous programme qui charge et affiche l'histoire du jeu*/
void charger_histoire()
{
    BITMAP* histoire1;
    BITMAP* histoire2;
    BITMAP* histoire3;

    int suite=0; //variable indiquant si passage a image suivante ou non
    int coef;
    int exit=0;

    coef=(SCREEN_W<900)?6:4;

    histoire1=chargerImage(".\\IMAGES\\annexe\\histoireaides\\histoire1.bmp"); //chargements différentes bmp histoire
    histoire2=chargerImage(".\\IMAGES\\annexe\\histoireaides\\histoire2.bmp");
    histoire3=chargerImage(".\\IMAGES\\annexe\\histoireaides\\histoire3.bmp");

    mouse_x=0;
    mouse_y=0;

    rectprogressif(histoire1->w, histoire1->h, coef, 2);
    do
    {

        if(mouse_b&1)
        {
            if(mouse_x>=SCREEN_W/coef+516 && mouse_x<=SCREEN_W/coef+565 && mouse_y>=SCREEN_H/2+211 && mouse_y<=SCREEN_H/2+246)
            {
                suite=1;

            }
        }
        blit(histoire1,Buffer,0,0,SCREEN_W/coef, SCREEN_H/2, histoire1->w, histoire1->h);
        blit(Buffer,screen, 0,0,0,0,SCREEN_W,SCREEN_H);

        if(suite==1&&!(mouse_b&1))
            exit=1;



    }
    while(exit!=1);

    mouse_x=0;
    mouse_y=0;

    rectprogressif(histoire2->w, histoire2->h, coef, 2);

    do
    {
        if(mouse_b&1)
        {
            if(mouse_x>=SCREEN_W/coef+520 && mouse_x<=SCREEN_W/coef+561 && mouse_y>=SCREEN_H/2+173 && mouse_y<=SCREEN_H/2+206)
            {
                suite=2;
            }
        }
        blit(histoire2,Buffer,0,0,SCREEN_W/coef, SCREEN_H/2, histoire2->w, histoire2->h);
        blit(Buffer,screen, 0,0,0,0,SCREEN_W,SCREEN_H);

        if(suite==2&&!(mouse_b&1))
            exit=2;

    }
    while(exit!=2);

    mouse_x=0;
    mouse_y=0;

    rectprogressif(histoire3->w, histoire3->h, coef, 2);

    do
    {
        if(mouse_b&1)
        {
            if(mouse_x>=SCREEN_W/coef+526 && mouse_x<=SCREEN_W/coef+564 && mouse_y>=SCREEN_H/2+179 && mouse_y<=SCREEN_H/2+207)
            {
                suite=3;
            }
        }
        blit(histoire3,Buffer,0,0,SCREEN_W/coef, SCREEN_H/2, histoire3->w, histoire3->h);
        blit(Buffer,screen, 0,0,0,0,SCREEN_W,SCREEN_H);

        if(suite==3&&!(mouse_b&1))
            exit=3;

    }
    while(exit!=3);


}

void rectprogressif(int Wbmp, int Hbmp, int divW, int divH)
{
    int i;

    for(i=10; i<=Wbmp; i+=20)
    {
        rectfill(screen, SCREEN_W/divW, SCREEN_H/divH, SCREEN_W/divW+i, SCREEN_H/divH+Hbmp, makecol(255,255,255));
        rest(2);
    }
}


void aide(int niveaudeprog)
{
    /*
    niveaudeprog=1 CLIC
    niveaudeprog=2 CLAVIER
    niveaudeprog=3 SCRATCH
    */

    BITMAP* aiden1;
    BITMAP* aiden2;
    BITMAP* aidegen;

    int fermer=0;
    int coef;
    int exit=0;

    coef=(SCREEN_W<900)?6:5;

    aiden1=chargerImage(".\\IMAGES\\annexe\\histoireaides\\aideniveau1.bmp"); //chargements différentes bmp aides
    aiden2=chargerImage(".\\IMAGES\\annexe\\histoireaides\\aideniveau2.bmp");
    aidegen=chargerImage(".\\IMAGES\\annexe\\histoireaides\\aidegeneral.bmp");

    if(niveaudeprog==1)//aide clic niveau 1
    {
        rectprogressif(aiden1->w, aiden1->h, coef, 3);

        mouse_x=0;
        mouse_y=0;

        do
        {
            if(mouse_b&1)
            {
                if(mouse_x>=SCREEN_W/coef+530 && mouse_x<=SCREEN_W/coef+578 && mouse_y>=SCREEN_H/3+19 && mouse_y<=SCREEN_H/3+65)
                {
                    fermer=1;
                }
            }
            blit(aiden1, Buffer, 0, 0, SCREEN_W/coef, SCREEN_H/3, aiden1->w, aiden1->h);
            blit(Buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);


            if(fermer==1&&!(mouse_b&1))
                exit=1;

        }
        while(exit!=1);
    }
    if(niveaudeprog==2)//aide clavier niveau 2
    {
        rectprogressif(aiden2->w, aiden2->h, coef, 3);

        mouse_x=0;
        mouse_y=0;

        do
        {
            if(mouse_b&1)
            {
                if(mouse_x>=SCREEN_W/coef+536 && mouse_x<=SCREEN_W/coef+588 && mouse_y>=SCREEN_H/3+13 && mouse_y<=SCREEN_H/3+60)
                {
                    fermer=1;
                }
            }
            blit(aiden2, Buffer, 0, 0, SCREEN_W/coef, SCREEN_H/3, aiden2->w, aiden2->h);
            blit(Buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);


            if(fermer==1&&!(mouse_b&1))
                exit=1;
        }
        while(exit!=1);
    }

    if(niveaudeprog==3)//aide generale
    {
        rectprogressif(aidegen->w, aidegen->h, coef, 3);

        mouse_x=0;
        mouse_y=0;

        do
        {
            if(mouse_b&1)
            {
                if(mouse_x>=SCREEN_W/coef+541 && mouse_x<=SCREEN_W/coef+585 && mouse_y>=SCREEN_H/3+12 && mouse_y<=SCREEN_H/3+57)
                {
                    fermer=1;
                }
            }
            blit(aidegen, Buffer, 0, 0, SCREEN_W/coef, SCREEN_H/3, aidegen->w, aidegen->h);
            blit(Buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);


            if(fermer==1&&!(mouse_b&1))
                exit=1;
        }
        while(exit!=1);
    }


}
