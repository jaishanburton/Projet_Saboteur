#include"fichier.h"
#include"fichier.placercarte.h"
#include"sauvegarde.h"
#include"affichage.h"
#include"Initilisation.h"




void choix()
{

   //  BITMAP *image;
     BITMAP *image2;

     //BITMAP *doubleBuffer;



  SAMPLE*son=load_sample("menu.wav");

     play_sample(son,255,1,2000,1);


      //creation du double buffer
    //doubleBuffer=create_bitmap(SCREEN_W,SCREEN_H);

   image2=load_bitmap("images/saboteur2.bmp",NULL);    ///image de chargement du jeu
   // image=load_bitmap("saboteur.bmp",NULL);     ///image du jeu


     if (!image2)
    {
        allegro_message("pas pu trouver/charger images/saboteur2.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }


     blit(image2,screen,0,0,(SCREEN_W-image2->w)/2, (SCREEN_H-image2->h)/2, image2->w, image2->h);
    rest(5000); /// chargement 5 secondes
    destroy_bitmap(image2);
    rectfill(screen,0,0,1200,600,makecol(0,0,0));
    textprintf_ex(screen,font,900,600,makecol(255,255,255),-1,"Chargement du jeu. ");
    rest(1000);
    textprintf_ex(screen,font,900,600,makecol(255,255,255),-1,"Chargement du jeu.. ");
    rest(1000);
    textprintf_ex(screen,font,900,600,makecol(255,255,255),-1,"Chargement du jeu... ");
    rest(1000);
    textprintf_ex(screen,font,900,600,makecol(255,255,255),-1,"Chargement du jeu.... ");
    rest(1000);
    textprintf_ex(screen,font,900,600,makecol(255,255,255),-1,"Chargement du jeu..... ");
    rest(1000);
     textprintf_ex(screen,font,900,600,makecol(0,0,0),-1,"Chargement du jeu..... ");
    rest(1000);
    destroy_sample(son);

   new_menu();

}




void new_menu()
{

     BITMAP *image;

     BITMAP *doubleBuffer;

    int white_color,blue_color;
    //int key;
    float zoom=1.0;
    int free;
    //creation du double buffer
    doubleBuffer=create_bitmap(SCREEN_W,SCREEN_H);
    white_color=makecol(255,255,255);
    blue_color=makecol(0,0,255);
    image=load_bitmap("images/saboteur.bmp",NULL);     ///image du jeu

    while(free!=1)
    {
        clear_bitmap(doubleBuffer);
        if (!image)
        {
            allegro_message("pas pu trouver/charger images/saboteur.bmp");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
        blit(image,doubleBuffer,0,0, (SCREEN_W-image->w)/2, (SCREEN_H-image->h)/2, image->w, image->h);
        if((mouse_x>800)&&(mouse_x<950)&&(mouse_y>230)&&(mouse_y<270))
        {
          rectfill(doubleBuffer,795,230,950,270,blue_color);
          rectfill(doubleBuffer,795,280,950,320,makecol(0,0,0));
          rectfill(doubleBuffer,795,330,950,375,makecol(0,0,0));
          rectfill(doubleBuffer,795,380,950,420,makecol(0,0,0));
          rectfill(doubleBuffer,795,430,950,470,makecol(0,0,0));
        }
        else if((mouse_x>795)&&(mouse_x<950)&&(mouse_y>280)&&(mouse_y<320))
         {
            rectfill(doubleBuffer,795,230,950,270,makecol(0,0,0));
            rectfill(doubleBuffer,795,280,950,320,blue_color);
            rectfill(doubleBuffer,795,330,950,375,makecol(0,0,0));
            rectfill(doubleBuffer,795,380,950,420,makecol(0,0,0));
            rectfill(doubleBuffer,795,430,950,470,makecol(0,0,0));
         }
         else if((mouse_x>795)&&(mouse_x<950)&&(mouse_y>330)&&(mouse_y<375))
         {
            rectfill(doubleBuffer,795,230,950,270,makecol(0,0,0));
            rectfill(doubleBuffer,795,280,950,320,makecol(0,0,0));
            rectfill(doubleBuffer,795,330,950,375,blue_color);
            rectfill(doubleBuffer,795,380,950,420,makecol(0,0,0));
            rectfill(doubleBuffer,795,430,950,470,makecol(0,0,0));
         }
         else if((mouse_x>795)&&(mouse_x<950)&&(mouse_y>380)&&(mouse_y<420))
         {
            rectfill(doubleBuffer,795,230,950,270,makecol(0,0,0));
            rectfill(doubleBuffer,795,280,950,320,makecol(0,0,0));
            rectfill(doubleBuffer,795,330,950,375,makecol(0,0,0));
            rectfill(doubleBuffer,795,380,950,420,blue_color);
            rectfill(doubleBuffer,795,430,950,470,makecol(0,0,0));
         }
         else if((mouse_x>795)&&(mouse_x<950)&&(mouse_y>430)&&(mouse_y<470))
         {
             rectfill(doubleBuffer,795,230,950,270,makecol(0,0,0));
             rectfill(doubleBuffer,795,280,950,320,makecol(0,0,0));
             rectfill(doubleBuffer,795,330,950,375,makecol(0,0,0));
             rectfill(doubleBuffer,795,380,950,420,makecol(0,0,0));
             rectfill(doubleBuffer,795,430,950,470,blue_color);
         }
         else
         {
             rectfill(doubleBuffer,795,230,950,270,makecol(0,0,0));
             rectfill(doubleBuffer,795,280,950,320,makecol(0,0,0));
             rectfill(doubleBuffer,795,330,950,375,makecol(0,0,0));
             rectfill(doubleBuffer,795,380,950,420,makecol(0,0,0));
             rectfill(doubleBuffer,795,430,950,470,makecol(0,0,0));
         }
        textprintf_ex(doubleBuffer,font,200,60,white_color,-1,"Mes cher(e)s ami(e)s, Bienvenue sur le Saboteur, un jeu de societé à partager entre amis et famille !!! ");
        textprintf_ex(doubleBuffer,font,670,250,white_color,-1,"                  NOUVELLE PARTIE ");
        textprintf_ex(doubleBuffer,font,670,300,white_color,-1,"                 PARTIE PRECEDENTE ");
        textprintf_ex(doubleBuffer,font,670,350,white_color,-1,"                        AIDE ");
        textprintf_ex(doubleBuffer,font,670,400,white_color,-1,"                       SCORE ");
        textprintf_ex(doubleBuffer,font,670,450,white_color,-1,"                      QUITTER ");




         if(key[KEY_W])  ///touche pour zoomer
    {
        zoom=zoom+0.01;
     //blit(imageChargee,page,0,0, (SCREEN_W-imageChargee->w)/2, (SCREEN_H-imageChargee->h)/2, imageChargee->w, imageChargee->h);
    masked_stretch_blit(doubleBuffer,screen,0,0,doubleBuffer->w,doubleBuffer->h,0,0,doubleBuffer->w*zoom,doubleBuffer->h*zoom);
    rectfill(doubleBuffer,doubleBuffer->w*zoom,0,doubleBuffer->w,doubleBuffer->h,makecol(0,0,0));   /// effacement de tout ce qu'il y avait precedemment à l'écran
  rectfill(doubleBuffer,0,doubleBuffer->h*zoom,doubleBuffer->w,doubleBuffer->h,makecol(0,0,0));
    rest(15);
  //blit(doubleBuffer,screen,0,0,1200,650,doubleBuffer->w*zoom,doubleBuffer->h*zoom); //affichage du double Buffer

    }
    else if(key[KEY_A])  ///touche pour dézoomer
    {
          zoom=zoom-0.01;

    masked_stretch_blit(doubleBuffer,screen,0,0,doubleBuffer->w,doubleBuffer->h,0,0,doubleBuffer->w*zoom,doubleBuffer->h*zoom);
   rectfill(doubleBuffer,doubleBuffer->w*zoom,0,doubleBuffer->w,doubleBuffer->h,makecol(0,0,0));   /// effacement de tout ce qu'il y avait precedemment à l'écran
  rectfill(doubleBuffer,0,doubleBuffer->h*zoom,doubleBuffer->w,doubleBuffer->h,makecol(0,0,0));
    rest(15);
  // blit(doubleBuffer,screen,0,0,1200,650,doubleBuffer->w*zoom,doubleBuffer->h*zoom); //affichage du double Buffer
    }
    else if(key[KEY_N])   ///touche pour retour à la normale
    {

          zoom=1;
     //blit(imageChargee,page,0,0, (SCREEN_W-imageChargee->w)/2, (SCREEN_H-imageChargee->h)/2, imageChargee->w, imageChargee->h);
    masked_stretch_blit(screen,doubleBuffer,0,0,doubleBuffer->w,doubleBuffer->h,0,0,doubleBuffer->w*zoom,doubleBuffer->h*zoom);
   rectfill(doubleBuffer,doubleBuffer->w*zoom,0,doubleBuffer->w,doubleBuffer->h,makecol(0,0,0));   /// effacement de tout ce qu'il y avait precedemment à l'écran
  rectfill(doubleBuffer,0,doubleBuffer->h*zoom,doubleBuffer->w,doubleBuffer->h,makecol(0,0,0));
   rest(15);
  // blit(doubleBuffer,screen,0,0,1200,650,doubleBuffer->w*zoom,doubleBuffer->h*zoom);//affichage du double Buffer

    }
        blit(doubleBuffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);///affichage du double Buffer

        if(mouse_b&1)
        {
            if((mouse_x>800)&&(mouse_x<950)&&(mouse_y>230)&&(mouse_y<270))
                DebutPartie();
            else if((mouse_x>795)&&(mouse_x<950)&&(mouse_y>280)&&(mouse_y<320))
                ChargementPartie();
            else if((mouse_x>795)&&(mouse_x<950)&&(mouse_y>330)&&(mouse_y<375))
                aide();
            else if((mouse_x>795)&&(mouse_x<950)&&(mouse_y>380)&&(mouse_y<420))
                affichageScore();
            else if((mouse_x>795)&&(mouse_x<950)&&(mouse_y>430)&&(mouse_y<470))
                free=1;
        }
    }
    destroy_bitmap(image);
    destroy_bitmap(doubleBuffer);
}
