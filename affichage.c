#include"fichier.h"
#include"sauvegarde.h"
#include"affichage.h"
void AffichageJeu(t_joueur*joueurAction,BITMAP*doubleBuffer)
{
    int couleur=makecol(255,255,255);
    BITMAP*image;
    for(int i=0;i<6;i++)
        {
            if(joueurAction->jeu[i]!=-1)
            {
                image=ChargementCartes(joueurAction->jeu[i]);
                draw_sprite(doubleBuffer,image,1090,88+i*90);
            }
        }
    if(joueurAction->logo==1)
        image=load_bitmap("images/lion.bmp",NULL);
    else if(joueurAction->logo==2)
        image=load_bitmap("images/logo2.bmp",NULL);
    else if(joueurAction->logo==3)
        image=load_bitmap("images/logo3.bmp",NULL);
    else
        load_bitmap("images/logo4.bmp",NULL);
        /// Rectangle plein (couleur bleu fonce)
    rectfill(doubleBuffer,20,100,700,170,makecol(61,36,248));
    // texte dans le rectangle plein qui contient les infos sur les joueurs (nom, score, logo)
    textprintf_ex(doubleBuffer,font,50,110,couleur,-1,"Joueur : %s",joueurAction->name);
    textprintf_ex(doubleBuffer,font,200,110,couleur,-1,"Score : %d",joueurAction->score);
    textprintf_ex(doubleBuffer,font,440,110,couleur,-1,"Logo du Joueur : ");
    draw_sprite(doubleBuffer,image,570,100);
    textprintf_ex(doubleBuffer,font,50,130,couleur,-1,"Zone de déploiement de cartes du joueur en cours : ");
    textprintf_ex(doubleBuffer,font,80,145,couleur,-1,"-  Ligne 1 : ");
    textprintf_ex(doubleBuffer,font,80,160,couleur,-1,"-  Ligne 2 : ");
    destroy_bitmap(image);
}
void AffichagePlateau(t_carte*PlateauJeu[5][7],BITMAP*doubleBuffer,int nombre,t_joueur**listeJoueurs)
{
    BITMAP*image;
    // Déclaration du pointeur sur BITMAP devant recevoir l'image
    BITMAP *Image;
    BITMAP *image_entree;
    BITMAP *image_dos;
    BITMAP *image_pioche;


    int couleur;
    int black_color;


    ///---------------------------------------------------COORDONNEES DE LA SOURIS----------------------------------------------

    float zoom=1.0;
    ///////////////////////////////////////////////

     // Chargement de l'image (l'allocation a lieu en même temps)
    Image=load_bitmap("images/plateur_de_jeu.bmp",NULL);

    // Vérification que l'image est bien chargée (dans le cas contraire image vaut NULL)
    // TOUJOURS LE FAIRE CAR ON N'EST JAMAIS CERTAIN DE BIEN TROUVER L'IMAGE


    //image_zoom=load_bitmap("capture.bmp",NULL);

     // Chargement de l'image (l'allocation a lieu en même temps)
    image_entree=load_bitmap("images/entree_de_la_mine1.bmp",NULL);
    image_dos=load_bitmap("images/dos_de_carte_gold.bmp",NULL);    // le dos de la carte d'arrivée
    image_pioche=load_bitmap("images/dos_de_carte1.bmp",NULL);
    // Vérification que l'image est bien chargée (dans le cas contraire image vaut NULL)
    // TOUJOURS LE FAIRE CAR ON N'EST JAMAIS CERTAIN DE BIEN TROUVER L'IMAGE

         textprintf_ex(doubleBuffer,font, 850, 20,makecol(0,0,255),-1," Coordonnées de la souris:");

        if (!image_entree)
    {
        allegro_message("pas pu trouver/charger images/entree_dee_la_mine.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }


       if (!Image)
    {
        allegro_message("pas pu trouver/charger images/plateur_de_jeu.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

     if (!image_dos)
    {
        allegro_message("pas pu trouver/charger images/dos_de_carte_gold.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    if (!image_pioche)
    {
        allegro_message("pas pu trouver/charger images/dos_de_carte1.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }


      // Avoir une couleur (ici du blanc)
    couleur=makecol(255,255,255);
    //du noir
    black_color=makecol(0,0,0);
    // afficher du texte (couleur=blanc)
    textprintf_ex(doubleBuffer,font,250,50,couleur,-1,"Le Saboteur: Ecran du plateau de jeu, enjoy !!!");
    //coordonnees_souris();

    	//if ( x!= mouse_x || y!=mouse_y){
          		textprintf_ex(doubleBuffer,font, 1060, 20,makecol(0,0,0),-1, "  x: %d  y: %d", mouse_x,mouse_y);

           		textprintf_ex(doubleBuffer,font, 1060, 20,makecol(0,255,0),-1, "  x: %d  y: %d", mouse_x,mouse_y);
       	//	}

    // Rectangle contour (couleur=blanc)
    rect(doubleBuffer,10,90,1050,615,couleur);





   ///Rectangle rose (Panne des joueurs en attente)
    rectfill(doubleBuffer,20,171,1040,228,makecol(239,33,185));
    textprintf_ex(doubleBuffer,font,50,180,black_color,-1,"La Panne : ");



    /// la pioche (rectangle vert) et la defausse (rectangle vert clair)
    rectfill(doubleBuffer,705,100,870,170,makecol(32,218,32));
    rectfill(doubleBuffer,780,100,865,170,makecol(234,238,76));
    textprintf_ex(doubleBuffer,font,710,110,black_color,-1,"Pioche : ");
    blit(image_pioche,doubleBuffer,0,0, 800,100 , (image_pioche->w), (image_pioche->h)-12);   // dos de carte pour pioche

    rectfill(doubleBuffer,875,100,1040,170,makecol(101,248,86));
    textprintf_ex(doubleBuffer,font,880,110,black_color,-1,"Défausse : ");


    ///L'endroit où on a la pioche (les 6 cartes du joueur)

    rect(doubleBuffer,1090,90,1155,170,couleur);
    rect(doubleBuffer,1090,178,1155,258,couleur);
    rect(doubleBuffer,1090,268,1155,348,couleur);
    rect(doubleBuffer,1090,358,1155,438,couleur);
    rect(doubleBuffer,1090,448,1155,528,couleur);
    rect(doubleBuffer,1090,538,1155,618,couleur);




 //entrée du jeu
    rectfill(doubleBuffer,180,370,240,460,makecol(194,116,52));
    // Affichage de la carte entree de la mine
   /// blit(image_entree,screen,0,0,182,373 , image_entree->w, image_entree->h);
        blit(image_entree,doubleBuffer,0,0,182,373 , image_entree->w, image_entree->h);


    ///LES CASES D'ARRIVEES
    //rectangle bleu ciel du Joueur 1 ( logo + score )
    rectfill(doubleBuffer,960,230,1020,310,makecol(234,238,76));


   /// blit(image_dos,screen,0,0, 964,253 , image_dos->w, image_dos->h);   // dos de carte pour arrivee 1
        blit(image_dos,doubleBuffer,0,0, 964,230 , image_dos->w, image_dos->h);   // dos de carte pour arrivee 1

    //rectangle bleu ciel du Joueur 2 ( logo + score )
    rectfill(doubleBuffer,960,378,1020,458,makecol(234,238,76));


    /// blit(image_dos,screen,0,0, 964,383 , image_dos->w, image_dos->h);   // dos de carte pour arrivee 2
        blit(image_dos,doubleBuffer,0,0, 964,378 , image_dos->w, image_dos->h);   // dos de carte pour arrivee 2

      //rectangle bleu ciel du Joueur 3 ( logo + score )
    rectfill(doubleBuffer,960,526,1020,606,makecol(234,238,76));


    /// blit(image_dos,screen,0,0, 964,503 , image_dos->w, image_dos->h);   // dos de carte pour arrivee 3
        blit(image_dos,doubleBuffer,0,0, 964,526 , image_dos->w, image_dos->h);   // dos de carte pour arrivee 3

    /// Affichage de l'image sur l'écran au milieu bas

   /// blit(image,screen,0,0, (SCREEN_W-image->w)/2, (SCREEN_H-image->h), image->w, image->h);
        blit(Image,doubleBuffer,0,0, (SCREEN_W-Image->w)/2, (SCREEN_H-Image->h)/1.22, Image->w, Image->h);


    ///affichage du quadrillage sur le plateau de jeu
        hline(doubleBuffer,240,230,960,couleur);
        hline(doubleBuffer,240,304,960,couleur);
        hline(doubleBuffer,240,378,960,couleur);
        hline(doubleBuffer,240,452,960,couleur);
        hline(doubleBuffer,240,526,960,couleur);
        hline(doubleBuffer,240,600,960,couleur);

        vline(doubleBuffer,240,230,600,couleur);
        vline(doubleBuffer,343,230,600,couleur);
        vline(doubleBuffer,446,230,600,couleur);
        vline(doubleBuffer,549,230,600,couleur);
        vline(doubleBuffer,652,230,600,couleur);
        vline(doubleBuffer,755,230,600,couleur);
        vline(doubleBuffer,858,230,600,couleur);
        vline(doubleBuffer,960,230,600,couleur);


        //save_bitmap(doubleBuffer,screen,NULL);

    ///affichage zone des joueurs
    for(int i=0;i<nombre;i++)
    {
        rectfill(doubleBuffer,20,240+i*100,130,290+i*100,makecol(75,220,235));
        textprintf_ex(doubleBuffer,font,30,250+i*100,black_color,-1,"Joueur %d:",i+1);
        textprintf_ex(doubleBuffer,font,30,275+i*100,black_color,-1,"%s ",listeJoueurs[i]->name);
        textprintf_ex(doubleBuffer,font,50+i*250,210,black_color,-1,"%s : ",listeJoueurs[i]->name);
        if(listeJoueurs[i]->penalite!=-1)
        {
            image=ChargementCartes(listeJoueurs[i]->penalite);
            draw_sprite(doubleBuffer,image,150+i*250,170);
        }
    }


    for(int i=0;i<5;i++)
    {
        for(int j=0;j<7;j++)
        {
            /// pour chaque case on affiche et charge la carte correspondant
            if(PlateauJeu[i][j]->token==1)
            {
                image=load_bitmap("images/carrefour.bmp",NULL);
                if(PlateauJeu[i][j]->sens==1)
                    blit(image,doubleBuffer,0,0,240+j*103,230+i*74,image->w,image->h);
                else
                    rotate_sprite(doubleBuffer,image, 240+j*103,230+i*74,itofix(128));
            }
            else if(PlateauJeu[i][j]->token==2)
            {
                image=load_bitmap("images/chemin.bmp",NULL);
                if(PlateauJeu[i][j]->sens==1)
                    blit(image,doubleBuffer,0,0,240+j*103,230+i*74,image->w,image->h);
                else
                    rotate_sprite(doubleBuffer,image, 240+j*103,230+i*74,itofix(128));
            }
            else if(PlateauJeu[i][j]->token==3)
            {
                image=load_bitmap("images/croisementT1.bmp",NULL);
                if(PlateauJeu[i][j]->sens==1)
                    blit(image,doubleBuffer,0,0,240+j*103,230+i*74,image->w,image->h);
                else
                    rotate_sprite(doubleBuffer,image, 240+j*103,230+i*74,itofix(128));
            }
            else if(PlateauJeu[i][j]->token==4)
            {
                image=load_bitmap("images/croisementT2.bmp",NULL);
                if(PlateauJeu[i][j]->sens==1)
                    blit(image,doubleBuffer,0,0,240+j*103,230+i*74,image->w,image->h);
                else
                    rotate_sprite(doubleBuffer,image, 240+j*103,230+i*74,itofix(128));
            }
            else if(PlateauJeu[i][j]->token==5)
            {
                image=load_bitmap("images/impasse.bmp",NULL);
                if(PlateauJeu[i][j]->sens==1)
                    blit(image,doubleBuffer,0,0,240+j*103,230+i*74,image->w,image->h);
                else
                    rotate_sprite(doubleBuffer,image, 240+j*103,230+i*74,itofix(128));

            }
            else if(PlateauJeu[i][j]->token==10)
            {
                image=load_bitmap("images/eboulement.bmp",NULL);
                blit(image,doubleBuffer,0,0,240+j*103,230+i*74,image->w,image->h);
            }
        }
    }

       if(key[KEY_W])  ///touche pour zoomer
    {
        zoom=zoom+0.01;
     //blit(imageChargee,page,0,0, (SCREEN_W-imageChargee->w)/2, (SCREEN_H-imageChargee->h)/2, imageChargee->w, imageChargee->h);
    masked_stretch_blit(doubleBuffer,screen,0,0,doubleBuffer->w,doubleBuffer->h,0,0,doubleBuffer->w*zoom,doubleBuffer->h*zoom);
    rectfill(doubleBuffer,doubleBuffer->w*zoom,0,doubleBuffer->w,doubleBuffer->h,makecol(0,0,0));   /// effacement de tout ce qu'il y avait precedemment à l'écran
  rectfill(doubleBuffer,0,doubleBuffer->h*zoom,doubleBuffer->w,doubleBuffer->h,makecol(0,0,0));
    rest(15);
  blit(doubleBuffer,screen,0,0,1200,650,doubleBuffer->w*zoom,doubleBuffer->h*zoom); //affichage du double Buffer

    }
    else if(key[KEY_A])  ///touche pour dézoomer
    {
          zoom=zoom-0.01;

    masked_stretch_blit(doubleBuffer,screen,0,0,doubleBuffer->w,doubleBuffer->h,0,0,doubleBuffer->w*zoom,doubleBuffer->h*zoom);
   rectfill(doubleBuffer,doubleBuffer->w*zoom,0,doubleBuffer->w,doubleBuffer->h,makecol(0,0,0));   /// effacement de tout ce qu'il y avait precedemment à l'écran
  rectfill(doubleBuffer,0,doubleBuffer->h*zoom,doubleBuffer->w,doubleBuffer->h,makecol(0,0,0));
    rest(15);
   blit(doubleBuffer,screen,0,0,1200,650,doubleBuffer->w*zoom,doubleBuffer->h*zoom); //affichage du double Buffer
    }
    else if(key[KEY_N])   ///touche pour retour à la normale
    {

          zoom=1;
     //blit(imageChargee,page,0,0, (SCREEN_W-imageChargee->w)/2, (SCREEN_H-imageChargee->h)/2, imageChargee->w, imageChargee->h);
    masked_stretch_blit(doubleBuffer,screen,0,0,doubleBuffer->w,doubleBuffer->h,0,0,doubleBuffer->w*zoom,doubleBuffer->h*zoom);
   rectfill(doubleBuffer,doubleBuffer->w*zoom,0,doubleBuffer->w,doubleBuffer->h,makecol(0,0,0));   /// effacement de tout ce qu'il y avait precedemment à l'écran
  rectfill(doubleBuffer,0,doubleBuffer->h*zoom,doubleBuffer->w,doubleBuffer->h,makecol(0,0,0));
   rest(15);
   blit(doubleBuffer,screen,0,0,1200,650,doubleBuffer->w*zoom,doubleBuffer->h*zoom);//affichage du double Buffer

    }

    destroy_bitmap(Image);
    destroy_bitmap(image_entree);
    destroy_bitmap(image_dos);
    destroy_bitmap(image_pioche);

}
BITMAP*ChargementCartes(int token)
{
    BITMAP*image=NULL;
    /// chargement de l'image de la carte
    if(token==1)
        image=load_bitmap("images/carrefour.bmp",NULL);
    else if(token==2)
        image=load_bitmap("images/chemin.bmp",NULL);
    else if(token==3)
        image=load_bitmap("images/croisementT1.bmp",NULL);
    else if(token==4)
        image=load_bitmap("images/croisementT2.bmp",NULL);
    else if(token==5)
        image=load_bitmap("images/impasse.bmp",NULL);
    else if(token==6)
        image=load_bitmap("images/chariot_et_pioche_repares.bmp",NULL);
    else if(token==7)
        image=load_bitmap("images/lanterne_et_chariot_repares.bmp",NULL);
    else if(token==8)
        image=load_bitmap("images/lanterne_et_pioche_reparees.bmp",NULL);
    else if(token==9)
        image=load_bitmap("images/outils_casses.bmp",NULL);
    else if(token==10)
        image=load_bitmap("images/eboulement.bmp",NULL);
    else if(token==11)
        image=load_bitmap("images/map.bmp",NULL);
    else if(token==12)
        image=load_bitmap("images/lanterne_cassee.bmp",NULL);
    else if(token==13)
        image=load_bitmap("images/lanterne_reparee.bmp",NULL);
    else if(token==14)
        image=load_bitmap("images/pioche_cassee.bmp",NULL);
    else if(token==15)
        image=load_bitmap("images/pioche_reparee.bmp",NULL);
    else if(token==16)
        image=load_bitmap("images/chariot_casse.bmp",NULL);
    else if(token==17)
        image=load_bitmap("images/chariot_repare.bmp",NULL);

    return image;
}
void Pause(t_pile*Tour,t_carte*PlateauJeu[5][7],t_joueur**listeJoueurs,int nombre,int joueurAction)
{
    char chaine[25];
    int pointeur,couleur1,couleur2,couleur3;
    BITMAP*doubleBuffer;
    doubleBuffer=create_bitmap(SCREEN_W/4,SCREEN_H/4);
    while(pointeur!=3||(!mouse_b&1))
    {
        couleur1=0;
        couleur2=0;
        couleur3=0;
        pointeur=0;
        clear_bitmap(doubleBuffer);
        rectfill(doubleBuffer,0,0,SCREEN_W/2,SCREEN_H/2,makecol(0,0,255));
        textprintf_ex(doubleBuffer,font,SCREEN_W/8-20,SCREEN_H/8-50,makecol(255,255,255),-1,"PAUSE");
        if(mouse_x>528&&mouse_x<560&&mouse_y>359&&mouse_y<368)
            pointeur=1;
        else if(mouse_x>532&&mouse_x<606&&mouse_y>381&&mouse_y<389)
            pointeur=2;
        else if(mouse_x>526&&mouse_x<581&&mouse_y>400&&mouse_y<409)
            pointeur=3;
        if(pointeur==1)
            couleur1=makecol(255,0,0);
        else if(pointeur==2)
            couleur2=makecol(255,0,0);
        else if(pointeur==3)
            couleur3=makecol(255,0,0);
        if(pointeur==1&&mouse_b&1)
        {
            rest(500);
            aide(); //appel du sous programme aide()
        }
        else if(pointeur==2&&mouse_b&1)
        {
            printf("Nom de la sauvegarde: " );
            scanf("%s",chaine);
            sauvegarde(chaine,Tour,PlateauJeu,listeJoueurs,nombre);
        }

        textprintf_ex(doubleBuffer,font,SCREEN_W/8-30,SCREEN_H/8-20,couleur1,-1,"*Aide");
        textprintf_ex(doubleBuffer,font,SCREEN_W/8-30,SCREEN_H/8,couleur2,-1,"*Sauvegarde");
        textprintf_ex(doubleBuffer,font,SCREEN_W/8-30,SCREEN_H/8+20,couleur3,-1,"*Quitter");
        blit(doubleBuffer,screen,0,0,400,300,SCREEN_W,SCREEN_H);
    }
    clear_bitmap(doubleBuffer);
    destroy_bitmap(doubleBuffer);
}
void aide() //mise en place du sous programme aide
{
     // Déclaration des différents pointeurs afin de recevoir des images
    BITMAP *idee_du_jeu;
    BITMAP *preparation;
    BITMAP *deroulement;
    BITMAP *deroulement2;
    BITMAP *deroulement3;
    BITMAP *fin;
    //Déclaration du pointeur doubleBuffer
    BITMAP *doubleBuffer;

    int noir;
//Chargement des images "idee","preparation","deroulement","deroulement2","deroulement3" et "fin"
      idee_du_jeu=load_bitmap("images/idee.bmp",NULL);
      preparation=load_bitmap("images/preparation.bmp",NULL);
      deroulement=load_bitmap("images/deroulement.bmp",NULL);
      deroulement2=load_bitmap("images/deroulement2.bmp",NULL);
      deroulement3=load_bitmap("images/deroulement3.bmp",NULL);
      fin=load_bitmap("images/fin.bmp",NULL);

    //Creation du double buffer
    doubleBuffer=create_bitmap(SCREEN_W,SCREEN_H);
    //affectation de la couleur noire à la variable noir pour faciliter le code
    noir=makecol(0,0,0);

    while(!key[KEY_SPACE])
    {
        // mise en place de plusieurs rectangles jaunes constituant le menu d'aide
        rectfill(doubleBuffer,400,190,790,217,makecol(255,255,100));
        rectfill(doubleBuffer,400,240,790,267,makecol(255,255,100));
        rectfill(doubleBuffer,400,290,790,317,makecol(255,255,100));
        rectfill(doubleBuffer,400,340,790,367,makecol(255,255,100));
        //textes contenus dans les rectangles pleins crees precedemment
        textprintf_ex(doubleBuffer,font,559,200,makecol(200,0,0),-1,"Idee du jeu");
        textprintf_ex(doubleBuffer,font,529,250,makecol(200,0,0),-1,"Preparation du jeu");
        textprintf_ex(doubleBuffer,font,528,300,makecol(200,0,0),-1,"Deroulement du jeu");
        textprintf_ex(doubleBuffer,font,558,350,makecol(200,0,0),-1,"Fin du jeu");
        textprintf_ex(doubleBuffer,font,30,570,makecol(255,128,0),-1,"Appuyez SPACE pour quitter");

        //condition permettant de selectionner l'option "idee de jeu"
        if (mouse_b&1 && ((mouse_x>400)&&(mouse_x<790)) && ((mouse_y>190)&&(mouse_y<217)))
        {
        //mise en plage de plusieurs rectangles pleins noirs pour "effacer" l'écran précédent
        rectfill(screen,400,190,790,217,noir);
        rectfill(screen,400,240,790,267,noir);
        rectfill(screen,400,290,790,317,noir);
        rectfill(screen,400,340,790,367,noir);
        rectfill(screen,30,50,565,585,noir);

            while(!key[KEY_ESC])
        {
            //effacage du bitmat
            clear_bitmap(doubleBuffer);
            //ajout de textes pour guider l'utilisateur
            textprintf_ex(screen,font,510,50,makecol(200,0,0),-1,"Voici l'idee du jeu");
            textprintf_ex(screen,font,30,570,makecol(255,128,0),-1,"Appuyez ECHAP pour quitter");
            //affichage de l'image idee de jeu
            blit(idee_du_jeu,screen,0,0, (SCREEN_W-idee_du_jeu->w)/2, (SCREEN_H-idee_du_jeu->h)/4, idee_du_jeu->w, idee_du_jeu->h);
        }
        }else

        //condition permettant de selectionner l'option "preparation du jeu"
        if (mouse_b&1 && ((mouse_x>400)&&(mouse_x<790)) && ((mouse_y>240)&&(mouse_y<267)))
        {
        //mise en plage de plusieurs rectangles pleins noirs pour "effacer" l'écran précédent
        rectfill(screen,400,190,790,217,noir);
        rectfill(screen,400,240,790,267,noir);
        rectfill(screen,400,290,790,317,noir);
        rectfill(screen,400,340,790,367,noir);
        rectfill(screen,30,50,565,585,noir);

              while(!key[KEY_ESC])
        {
            //ajout de textes pour guider l'utilisateur
            textprintf_ex(screen,font,500,50,makecol(200,0,0),-1,"Voici la preparation du jeu");
            textprintf_ex(screen,font,30,570,makecol(255,128,0),-1,"Appuyez ECHAP pour quitter");
            //affichage de l'image preparation
            blit(preparation,screen,0,0, (SCREEN_W-preparation->w)/2, (SCREEN_H-preparation->h)/2, preparation->w, preparation->h);
        }
        }else

        //condition permettant de selectionner l'option "deroulement du jeu"
        if (mouse_b&1 && ((mouse_x>400)&&(mouse_x<790)) && ((mouse_y>290)&&(mouse_y<317)))
        {
        //mise en plage de plusieurs rectangles pleins noirs pour "effacer" l'écran précédent
        rectfill(screen,400,190,790,217,noir);
        rectfill(screen,400,240,790,267,noir);
        rectfill(screen,400,290,790,317,noir);
        rectfill(screen,400,340,790,367,noir);
        rectfill(screen,30,50,565,585,noir);

        while(!key[KEY_ESC])
            {
            textprintf_ex(screen,font,510,50,makecol(200,0,0),-1,"Voici le deroulement du jeu"); //texte pour guider l'utilisateur
            textprintf_ex(screen,font,30,570,makecol(255,128,0),-1,"Appuyez ECHAP pour quitter");
            blit(deroulement,screen,0,0, (SCREEN_W-deroulement->w)/2, (SCREEN_H-deroulement->h)/2, deroulement->w, deroulement->h); //affichage de l'image deroulement
            /*rest(10000); //delai de 10 secondes avant de passer à l'image suivante
            rectfill(screen,0,0,1200,600,makecol(0,0,0)); //effacage de l'ecran
            textprintf_ex(screen,font,510,50,makecol(200,0,0),-1,"Voici le deroulement du jeu");
            textprintf_ex(screen,font,310,85,makecol(200,200,0),-1,"Patientez encore 20 secondes pour bien comprendre le deroulement du jeu");
            blit(deroulement2,screen,0,0, (SCREEN_W-deroulement2->w)/2, (SCREEN_H-deroulement2->h)/2, deroulement2->w, deroulement2->h); //affichage de l'image deroulement2
            rest(10000);
            rectfill(screen,0,0,1200,600,makecol(0,0,0)); //effacage de l'ecran
           textprintf_ex(screen,font,510,50,makecol(200,0,0),-1,"Voici le deroulement du jeu");
            textprintf_ex(screen,font,310,85,makecol(200,200,0),-1,"Patientez encore 10 secondes pour bien comprendre le deroulement du jeu");
            blit(deroulement3,screen,0,0, (SCREEN_W-deroulement3->w)/2, (SCREEN_H-deroulement3->h)/2, deroulement3->w, deroulement3->h); //affichage de l'image deroulement3
            rest(10000);
           */
            }

        }else

        //condition permettant de selectionner l'option "fin du jeu"
        if (mouse_b&1 && ((mouse_x>400)&&(mouse_x<790)) && ((mouse_y>340)&&(mouse_y<367)))
        {
        //mise en plage de plusieurs rectangles pleins noirs pour "effacer" l'écran précédent
        rectfill(screen,400,190,790,217,noir);
        rectfill(screen,400,240,790,267,noir);
        rectfill(screen,400,290,790,317,noir);
        rectfill(screen,400,340,790,367,noir);
        rectfill(screen,30,50,565,585,noir);

              while(!key[KEY_ESC])
        {

            //texte pour guider l'utilisateur
            textprintf_ex(screen,font,510,50,makecol(200,0,0),-1,"Voici la fin du jeu");
            textprintf_ex(screen,font,30,570,makecol(255,128,0),-1,"Appuyez ECHAP pour quitter");
            //affichage de l'image fin
            blit(fin,screen,0,0, (SCREEN_W-fin->w)/2, (SCREEN_H-fin->h)/2, fin->w, fin->h);
        }
        }else

        blit(doubleBuffer,screen,0,0,0,0,SCREEN_W, SCREEN_H); //affichage du double Buffer
    }
    //destruction de chaque image
    destroy_bitmap(idee_du_jeu);
    destroy_bitmap(preparation);
    destroy_bitmap(deroulement);
    destroy_bitmap(deroulement2);
    destroy_bitmap(deroulement3);
    destroy_bitmap(fin);
    destroy_bitmap(doubleBuffer);
    clear_bitmap(screen);
}


