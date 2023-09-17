#include"fichier.h"
#include"sauvegarde.h"
int ConditionVictoire(t_carte*PlateauJeu[5][7],int ligne,int colonne,int interdit,int victoire)
{
    if(PlateauJeu[ligne][colonne]->token!=-1)
    {
        if(PlateauJeu[ligne][colonne]->droite==1&&colonne==6)
        {
            if(ligne==0)
                victoire=1;
            if(ligne==2)
            {
                victoire=2;
                printf("victoire = %d\n",victoire);
            }
            if(ligne==4)
            {
                victoire=3;
                printf("victoire = %d\n",victoire);
            }
        }
        else
        {
            if(PlateauJeu[ligne][colonne]->haut==1&&interdit!=1)
               victoire=ConditionVictoire(PlateauJeu,ligne-1,colonne,3,victoire);
            if(PlateauJeu[ligne][colonne]->bas==1&&interdit!=3)
                victoire=ConditionVictoire(PlateauJeu,ligne+1,colonne,1,victoire);
            if(PlateauJeu[ligne][colonne]->droite==1&&interdit!=2)
                victoire=ConditionVictoire(PlateauJeu,ligne,colonne+1,0,victoire);
            if(PlateauJeu[ligne][colonne]->gauche==1&&interdit!=0)
                victoire=ConditionVictoire(PlateauJeu,ligne,colonne-1,2,victoire);
        }
    }
    return victoire;
}
void Score(t_joueur**listeJoueurs,int gagnant,int nombre)
{
    int resultat;///
    BITMAP*image;

    for(int i=0;i<nombre;i++)/// Affichage du rôle de chaque personne
    {
        textprintf_ex(screen,font,(i+1)*100,10,makecol(255,255,255),-1,"%s",listeJoueurs[i]->name);
        if(listeJoueurs[i]->role==21)
        {
            image=load_bitmap("images/chercheur.bmp",NULL);
            blit(image,screen,0,0,(i+1)*100,50,image->w,image->h);
            textprintf_ex(screen,font,(i+1)*100,200,makecol(255,255,255),-1,"CHERCHEUR");
        }
        else
        {
            image=load_bitmap("images/saboteur_carte.bmp",NULL);
            blit(image,screen,0,0,(i+1)*100,50,image->w,image->h);
            textprintf_ex(screen,font,(i+1)*100,200,makecol(255,255,255),-1,"SABOTEUR");
        }
        rest(2000);
    }
    /// Affichage des gagnants
    if(gagnant==1) /// Gagnant = 1 : Les chercheurs ont gagné
    {
        textprintf_ex(screen,font,200,400,makecol(255,255,255),-1,"LES CHERCHEURS ONT GAGNE");
    }
    else/// Gagnant = 0 : Les saboteur ont gagné
    {
        textprintf_ex(screen,font,200,400,makecol(255,255,255),-1,"LE SABOTEUR A GAGNE");
    }
    rest(5000);
    clear_bitmap(screen);
    /// Affectation des récompenses au(x) gagnant(s)
    for(int i=0;i<nombre;i++)
    {
        /// Verification des conditions de victoire
        if((gagnant==1&&listeJoueurs[i]->role==21)||(gagnant==0&&listeJoueurs[i]->role==22))
        {
            resultat=rand()%(3)+1;/// génération aléatoire d'une carte de victoire
            allegro_message("%s",listeJoueurs[i]->name);
            /// Affichage de la carte correspondante
            if(resultat==1)/// 1 pépite
            {
                image=load_bitmap("images/1pepite.bmp",NULL);
                blit(image,screen,0,0,300,50,image->w,image->h);
                textprintf_ex(screen,font,300,10,makecol(255,255,255),-1,"%s",listeJoueurs[i]->name);
                listeJoueurs[i]->score=listeJoueurs[i]->score+1;
            }
            else if(resultat==2)/// 2 pépites
            {
                image=load_bitmap("images/2pepites.bmp",NULL);
                blit(image,screen,0,0,300,50,image->w,image->h);
                textprintf_ex(screen,font,300,10,makecol(255,255,255),-1,"%s",listeJoueurs[i]->name);
                listeJoueurs[i]->score=listeJoueurs[i]->score+2;
            }
            else if(resultat==3)/// 3 pépites
            {
                image=load_bitmap("images/3pepites.bmp",NULL);
                blit(image,screen,0,0,300,50,image->w,image->h);
                textprintf_ex(screen,font,300,10,makecol(255,255,255),-1,"%s",listeJoueurs[i]->name);
                listeJoueurs[i]->score=listeJoueurs[i]->score+3;
            }
            textprintf_ex(screen,font,300,200,makecol(255,255,255),-1,"tu as gagné %d pépite(s)",resultat);
        }
        rest(2000);
        clear_bitmap(screen);
    }
    destroy_bitmap(image);
}
void affichageScore()
{
    BITMAP*image;
    BITMAP*doubleBuffer;
    char nomFichier[25];
    printf("Les scores de quelle partie voulez vous charger : ");
    scanf("%s",nomFichier);
    t_pile Tour;
    int nombre;
    t_carte*PlateauJeu[5][7];
    t_joueur**listeJoueurs=NULL;
    chargementPioche(nomFichier,&Tour);
    chargementPlateau(nomFichier,PlateauJeu);
    listeJoueurs=chargementJoueur(nomFichier,&nombre);
    doubleBuffer=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(screen);
    printf("score\n");
    while(!key[KEY_ESC])
    {
        clear_bitmap(doubleBuffer);
        textprintf(doubleBuffer,font,200,10,makecol(255,255,255),"Score de la partie : %s",nomFichier);
        for(int i=0;i<nombre;i++)
        {
            textprintf(doubleBuffer,font,200,100+i*100,makecol(255,255,255),"Joueur : %s",listeJoueurs[i]->name);
            textprintf(doubleBuffer,font,600,100+i*100,makecol(255,255,255),"Score : %d",listeJoueurs[i]->score);
            if(listeJoueurs[i]->logo==1)
                image=load_bitmap("images/lion.bmp",NULL);
            else if(listeJoueurs[i]->logo==2)
                image=load_bitmap("images/logo2.bmp",NULL);
            else if(listeJoueurs[i]->logo==3)
                image=load_bitmap("images/logo3.bmp",NULL);
            else
                image=load_bitmap("images/logo4.bmp",NULL);
            draw_sprite(doubleBuffer,image,350,100+i*100);

        }
        blit(doubleBuffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
    destroy_bitmap(doubleBuffer);
    destroy_bitmap(image);
    free(listeJoueurs);
}
int sauvegardePartie()
{
    BITMAP *doubleBuffer;
    int white_color,blue_color;
    int free=0,sauvegarde=0;
    doubleBuffer=create_bitmap(SCREEN_W,SCREEN_H);
    white_color=makecol(255,255,255);
    blue_color=makecol(0,0,255);
    while(free!=1)
    {
        clear_bitmap(doubleBuffer);
        if((mouse_x>800)&&(mouse_x<950)&&(mouse_y>230)&&(mouse_y<270))
        {
          rectfill(doubleBuffer,795,230,950,270,blue_color);
          rectfill(doubleBuffer,795,280,950,320,makecol(0,0,0));
        }
        else if((mouse_x>795)&&(mouse_x<950)&&(mouse_y>280)&&(mouse_y<320))
         {
            rectfill(doubleBuffer,795,230,950,270,makecol(0,0,0));
            rectfill(doubleBuffer,795,280,950,320,blue_color);
         }
         else
         {
             rectfill(doubleBuffer,795,230,950,270,makecol(0,0,0));
             rectfill(doubleBuffer,795,280,950,320,makecol(0,0,0));
         }
         textprintf_ex(doubleBuffer,font,400,60,white_color,-1,"Voulez vous sauvegarder la partie ?");
        textprintf_ex(doubleBuffer,font,670,250,white_color,-1,"                 OUI ");
        textprintf_ex(doubleBuffer,font,670,300,white_color,-1,"                 NON ");
        blit(doubleBuffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);///affichage du double Buffer
        if(mouse_b&1)
        {
            if((mouse_x>800)&&(mouse_x<950)&&(mouse_y>230)&&(mouse_y<270))
            {
                free=1;
                sauvegarde=1;
            }
            else if((mouse_x>795)&&(mouse_x<950)&&(mouse_y>280)&&(mouse_y<320))
                free=1;
        }
    }
    destroy_bitmap(doubleBuffer);
    return sauvegarde;
}
