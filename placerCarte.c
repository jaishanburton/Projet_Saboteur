#include"fichier.h"
#include"fichier.placercarte.h"
#include"sauvegarde.h"
#include"affichage.h"
#include"Initilisation.h"

void TourJeu(t_joueur**listeJoueurs,int joueurAction,t_carte*PlateauJeu[5][7],int nombre,t_pile*Tour)
{
    ///double buffer
    BITMAP*doubleBuffer;
    doubleBuffer=create_bitmap(SCREEN_W,SCREEN_H);
    t_carte*nouveau;/// pointeur de structure carte
    int carte=1,saisit=0,numero,sortie=0,valide;
    float zoom=1.0;
    while(sortie!=3)
    {
        clear_bitmap(doubleBuffer);/// effacer écran
        if(sortie!=0)
              textprintf(doubleBuffer,font,455,70,makecol(255,255,255),"Vous devez défausser %d carte(s)",3-sortie);
          else
              textprintf(doubleBuffer,font,455,70,makecol(255,255,255),"Défaussez %d carte(s) ou poser 1 carte",3-sortie);
        if(mouse_b&1)
        {
            if(mouse_x>1090&&mouse_x<1155)
            {
                if(mouse_y>90&&mouse_y<170)
                {
                    saisit=1;
                    numero=0;
                }
                else if(mouse_y>178&&mouse_y<258)
                {
                    saisit=1;
                    numero=1;
                }
                else if(mouse_y>268&&mouse_y<348)
                {
                    saisit=1;
                    numero=2;
                }
                else if(mouse_y>358&&mouse_y<438)
                {
                    saisit=1;
                    numero=3;
                }
                else if(mouse_y>448&&mouse_y<528)
                {
                    saisit=1;
                    numero=4;
                }
                else if(mouse_y>538&&mouse_y<618)
                {
                    saisit=1;
                    numero=5;
                }
                if(saisit==1)
                {
                    carte=listeJoueurs[joueurAction]->jeu[numero];
                    listeJoueurs[joueurAction]->jeu[numero]=-1;
                    nouveau=InitilisationCarte(carte);/// Initilisation de la nouvelle carte à placer
                    valide=PlacerCarte(PlateauJeu,nouveau,listeJoueurs,sortie,nombre,joueurAction);
                    sortie=valide+sortie;
                    if(valide<1)/// Place la carte sur le plateau
                        listeJoueurs[joueurAction]->jeu[numero]=carte;
                }
            }
        }
        if(key[KEY_P])
        {
            Pause(Tour,PlateauJeu,listeJoueurs,nombre,joueurAction);
        }
        AffichageJeu(listeJoueurs[joueurAction],doubleBuffer);
        /// affichage du plateau de jeu
        AffichagePlateau(PlateauJeu,doubleBuffer,nombre,listeJoueurs);
        blit(doubleBuffer,screen,0,0,0,0,SCREEN_W, SCREEN_H);

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
 //  blit(doubleBuffer,screen,0,0,1200,650,doubleBuffer->w*zoom,doubleBuffer->h*zoom); //affichage du double Buffer
    }
    else if(key[KEY_N])   ///touche pour retour à la normale
    {

          zoom=1;
     //blit(imageChargee,page,0,0, (SCREEN_W-imageChargee->w)/2, (SCREEN_H-imageChargee->h)/2, imageChargee->w, imageChargee->h);
    masked_stretch_blit(doubleBuffer,screen,0,0,doubleBuffer->w,doubleBuffer->h,0,0,doubleBuffer->w*zoom,doubleBuffer->h*zoom);
   rectfill(doubleBuffer,doubleBuffer->w*zoom,0,doubleBuffer->w,doubleBuffer->h,makecol(0,0,0));   /// effacement de tout ce qu'il y avait precedemment à l'écran
  rectfill(doubleBuffer,0,doubleBuffer->h*zoom,doubleBuffer->w,doubleBuffer->h,makecol(0,0,0));
   rest(15);
  //  blit(doubleBuffer,screen,0,0,1200,650,doubleBuffer->w*zoom,doubleBuffer->h*zoom);//affichage du double Buffer

    }

    }
    //free(nouveau);
    destroy_bitmap(doubleBuffer);
}
int PlacerCarte(t_carte*PlateauJeu[5][7],t_carte*nouveau,t_joueur**listeJoueurs,int sortie,int nombre,int joueurAction)
{
    BITMAP*image;/// pointeur image
    int ligne,colonne,valide=0;

    ///double buffer
    BITMAP*doubleBuffer;
    doubleBuffer=create_bitmap(SCREEN_W,SCREEN_H);

    while(mouse_b&1)/// drag and drop
    {
        clear_bitmap(doubleBuffer);/// effacer écran
        textprintf_ex(doubleBuffer,font,60,200,makecol(255,255,255),makecol(0,0,0),"Appuyer sur ESPACE pour tourner la carte");

        image=ChargementCartes(nouveau->token);
        /// affichage du plateau de jeu
        AffichagePlateau(PlateauJeu,doubleBuffer,nombre,listeJoueurs);
        /// affichage jeu du joueur
        AffichageJeu(listeJoueurs[joueurAction],doubleBuffer);

        /// tourner la carte
        if(key[KEY_SPACE])
        {
            if(nouveau->sens==1)
                nouveau->sens=0;
            else
                nouveau->sens=1;
            rest(500);
        }
        if(nouveau->sens==1)
            draw_sprite(doubleBuffer,image,mouse_x-30,mouse_y-30);
        else
            rotate_sprite(doubleBuffer,image, mouse_x-30,mouse_y-30,itofix(128));/// tourne la carte

        if(sortie!=0)
              textprintf(doubleBuffer,font,455,70,makecol(255,255,255),"Vous devez défausser %d carte(s)",3-sortie);
          else
              textprintf(doubleBuffer,font,455,70,makecol(255,255,255),"Défaussez %d carte(s) ou poser 1 carte",3-sortie);

          blit(doubleBuffer,screen,0,0,0,0,SCREEN_W, SCREEN_H);
          ligne=PositionY();/// ligne du tableau correpondant à la case sélectionner
          colonne=PositionX();/// colonne du tableau correpondant à la case sélectionner
      }
      /// carte chemin
      if(mouse_x>240&&mouse_x<960&&mouse_y>230&&mouse_y<600&&sortie==0&&(nouveau->token<=6||nouveau->token==10)&&listeJoueurs[joueurAction]->penalite==-1)
      {
        valide=Validation(nouveau,PlateauJeu,ligne,colonne,nouveau->sens);/// Blindage placement de la carte
        if(valide==1)/// Placement valide
        {
            PlateauJeu[ligne][colonne]=nouveau;/// la case de plateau de jeu recoit les informations de la carte
            valide=3;
        }
      }
      else if(mouse_x>875&&mouse_x<1040&&mouse_y>100&&mouse_y<170)/// Défausse
          valide=1;
      else if(mouse_x>20&&mouse_x<130&&((nouveau->token>5&&nouveau->token<9)||(nouveau->token>10&&nouveau->token<18)))/// carte action
          valide=BlindageAction(listeJoueurs,nombre,nouveau->token);

      destroy_bitmap(image);
      destroy_bitmap(doubleBuffer);
      return valide;
}
int BlindageAction(t_joueur**listeJoueurs,int nombre,int token)
{
    int valide=0;
    for(int i=0;i<nombre;i++)
          {
              if(mouse_y>240+i*100&&mouse_y<290+i*100)
              {
                  printf("%d/%d\n",listeJoueurs[i]->penalite,token);
                  if(listeJoueurs[i]->penalite==-1&&(token==12||token==14||token==16))
                  {
                      listeJoueurs[i]->penalite=token;
                      valide=3;
                  }
                  else if(listeJoueurs[i]->penalite==12&&(token==13||token==8||token==7))
                  {
                      listeJoueurs[i]->penalite=-1;
                      valide=3;
                  }
                  else if(listeJoueurs[i]->penalite==14&&(token==15||token==6||token==8))
                  {
                      listeJoueurs[i]->penalite=-1;
                      valide=3;
                  }
                  else if(listeJoueurs[i]->penalite==16&&(token==17||token==6||token==7))
                  {
                      listeJoueurs[i]->penalite=-1;
                      valide=3;
                  }
              }
          }
    return valide;
}
int PositionY()
{
    int Y,compteurY=0;
    Y=mouse_y;/// recoit la position en Y de la souris
    while(Y>230)/// 230 car position en Y de l'origine du tableau
    {
        Y-=74;/// 74 car taille en Y des case
        compteurY++;
    }
    return compteurY-1;/// car la première case du tableau est la case [0]
}
int PositionX()
{
    int X,compteurX=0;
    X=mouse_x;/// recoit la position en X de la souris
    while(X>240)/// 230 car position en X de l'origine du tableau
    {
        X-=103;/// 103 car taille en X des case
        compteurX++;
    }
    return compteurX-1;/// car la première case du tableau est la case [0]
}
int Validation(t_carte* nouveau,t_carte*PlateauJeu[5][7], int ligne,int colonne,int sens)
{
    int valide=1,contact=0;/// Valide->chemin, contact->touche au moins une carte
    int stockage;
    if(sens==0)
    {
        stockage=nouveau->droite;
        nouveau->droite=nouveau->gauche;
        nouveau->gauche=stockage;

        stockage=nouveau->haut;
        nouveau->haut=nouveau->bas;
        nouveau->bas=stockage;
    }
    if(ligne==0)/// première ligne du tableau
    {
        if(nouveau->haut==1)/// carte à un chemin vers le haut->invalide
            valide=0;
    }
    else
    {   /// cas général (3 cas de validation) pour chemin du haut de la carte à poser
        ///1 les cartes adjacentes on les chemins qui corresponde
        ///2 les cartes non pas de chemin l'une à l'autre
        ///3 pas de carte adjacente
        if((nouveau->haut==1&&PlateauJeu[ligne-1][colonne]->bas==1)||(nouveau->haut==0&&PlateauJeu[ligne-1][colonne]->bas==0)||(PlateauJeu[ligne-1][colonne]->token==-1))
        {
            /// chemin corresponde -> carte en contact
            if(nouveau->haut==1&&PlateauJeu[ligne-1][colonne]->bas==1)
            {
                contact=1;
            }
        }
        else
            valide=0;
    }

    if(colonne==6)/// dernière colonne du tableau
    {
        if(nouveau->droite==1&&ligne!=0&&ligne!=4&&ligne!=2)/// chemin vers la droite->invalide sauf si pépite
            valide=0;
    }
    else
    {   /// cas général (3 cas de validation) pour chemin de droite de la carte à poser
        if((nouveau->droite==1&&PlateauJeu[ligne][colonne+1]->gauche==1)||(nouveau->haut==0&&PlateauJeu[ligne][colonne+1]->gauche==0)||(PlateauJeu[ligne][colonne+1]->token==-1))
        {
            /// chemin corresponde -> carte en contact
            if(nouveau->droite==1&&PlateauJeu[ligne][colonne+1]->gauche==1)
            {
                contact=1;
            }
        }
        else
            valide=0;
    }
    if(ligne==4)/// dernière colonne du tableau
    {
        if(nouveau->bas==1)/// chemin vers le bas->invalide
            valide=0;
    }
    else
    {   /// cas général (3 cas de validation) pour chemin du bas de la carte à poser
        if((nouveau->bas==1&&PlateauJeu[ligne+1][colonne]->haut==1)||(nouveau->bas==0&&PlateauJeu[ligne+1][colonne]->haut==0)||(PlateauJeu[ligne+1][colonne]->token==-1))
        {
            /// chemin corresponde -> carte en contact
            if(nouveau->bas==1&&PlateauJeu[ligne+1][colonne]->haut==1)
            {
                contact=1;
            }
        }
    else
        valide=0;
    }
    if(colonne==0)/// première colonne du tableau
    {
        if(nouveau->gauche==1)/// chemin vers la gauche->invalide
            valide=0;
    }
    else
    {  /// cas général (3 cas de validation) pour chemin de gauche de la carte à poser
       if((nouveau->gauche==1&&PlateauJeu[ligne][colonne-1]->droite==1)||(nouveau->gauche==0&&PlateauJeu[ligne][colonne-1]->droite==0)||(PlateauJeu[ligne][colonne-1]->token==-1))
        {
            /// chemin corresponde -> carte en contact
            if(nouveau->gauche==1&&PlateauJeu[ligne][colonne-1]->droite==1)
            {
                contact=1;
            }
        }
        else
            valide=0;
    }
    ///carte de départ
    if(ligne==2&&colonne==0&&nouveau->gauche==1)/// carte doit au moins avoir un chemin vers la gauche
    {
        contact=1;
        valide=1;
    }
    /// On ne peut pas placer une carte par dessus une autre sauf carte éboulement
    if(PlateauJeu[ligne][colonne]->token!=-1&&PlateauJeu[ligne][colonne]->token!=10)
    {
        valide=0;
    }
    if(contact==1&&valide==1)/// carte valide plus au moins 1 contact
    {
        valide=1;
    }
    else
        valide=0;

    if(nouveau->token==10&&PlateauJeu[ligne][colonne]->token!=-1)
        valide=1;

    return valide;/// retourne valide à l'appelant
}
t_joueur*Piochage(int nouveau,t_carte*PlateauJeu[5][7],int nombre,t_joueur**listeJoueurs,t_pile*Tour)
{
    BITMAP*image;
    ///double buffer
    BITMAP*doubleBuffer;
    doubleBuffer=create_bitmap(SCREEN_W,SCREEN_H);

    for(int i=0;i<6;i++)
    {
        while(listeJoueurs[nouveau]->jeu[i]==-1)
        {
            clear_bitmap(doubleBuffer);/// effacer écran
            AffichageJeu(listeJoueurs[nouveau],doubleBuffer);
            AffichagePlateau(PlateauJeu,doubleBuffer,nombre,listeJoueurs);
            textprintf(doubleBuffer,font,455,70,makecol(255,255,255),"Piocher une carte");
            if(mouse_b&1&&mouse_x>780&&mouse_x<865&&mouse_y>100&&mouse_y<170)
            {
               listeJoueurs[nouveau]->jeu[i]=Tour->Element[Tour->Hauteur];
               Tour->Hauteur++;
               image=ChargementCartes(listeJoueurs[nouveau]->jeu[i]);
               draw_sprite(doubleBuffer,image,780,100);
            }
            blit(doubleBuffer,screen,0,0,0,0,SCREEN_W, SCREEN_H);
        }
        rest(500);
    }
    destroy_bitmap(doubleBuffer);
    return listeJoueurs[nouveau];
}
void Partie(t_carte*PlateauJeu[5][7],t_joueur**listeJoueurs,int nombre,t_pile*Tour)
{
    char nomFichier[25];
    int joueurAction=0,victoire=0,gagnant;
    ///double buffer
    BITMAP*doubleBuffer;
    doubleBuffer=create_bitmap(SCREEN_W,SCREEN_H);
    sprintf(nomFichier,"sauvegardeRapide");
    while(victoire<1&&Tour->Hauteur!=Tour->Place)// utilisé pour test début du tour de jeu à retirer pour la suite
    {
        if(joueurAction>=nombre)
            joueurAction=0;
        allegro_message("Au tour de %s",listeJoueurs[joueurAction]->name);
        TourJeu(listeJoueurs,joueurAction,PlateauJeu,nombre,Tour);
        victoire=ConditionVictoire(PlateauJeu,2,0,0,victoire);
        if(victoire==0)
        {
            for(int i=0;i<6;i++)
            {
                if(listeJoueurs[joueurAction]->jeu[i]==-1)
                {
                    listeJoueurs[joueurAction]=Piochage(joueurAction,PlateauJeu,nombre,listeJoueurs,Tour);
                }
            }
        }
        clear_bitmap(doubleBuffer);
        /// affichage du plateau de jeu
        AffichagePlateau(PlateauJeu,doubleBuffer,nombre,listeJoueurs);
        blit(doubleBuffer,screen,0,0,0,0,SCREEN_W, SCREEN_H);
        joueurAction++;
        if(joueurAction==nombre)
            sauvegarde(nomFichier,Tour,PlateauJeu,listeJoueurs,nombre);
    }
    if(victoire>=1)
    {
        if(listeJoueurs[joueurAction-1]->role==21)
        {
            gagnant=1;
            affiche_chercheur(); ///écran de victoire des chercheurs

        }
        else
        {
            gagnant=0;
            affichage_grotte();///écran de victoire pour les saboteurs

        }
        clear_bitmap(screen);
        Score(listeJoueurs,gagnant,nombre);/// Affiche les scores à chaque manche
    }

    else
    {
        game_over(); /// game over
    }
    if(sauvegardePartie()==1)
    {
        printf("Nom de la sauvegarde: " );
        scanf("%s",nomFichier);
        sauvegarde(nomFichier,Tour,PlateauJeu,listeJoueurs,nombre);

    }
     rest(5000);
    destroy_bitmap(doubleBuffer);
    clear_bitmap(screen);
    //A mettre à la fin

}

