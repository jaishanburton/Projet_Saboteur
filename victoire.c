#include"fichier.h"
#include"fichier.placercarte.h"
#include"sauvegarde.h"
#include"affichage.h"
#include"Initilisation.h"



///--------------------------------------ECRAN DE VICTOIRE SABOTEUR-------------------------------------------

void affichage_grotte()
{
    BITMAP *GROTTE;  // image de fond
    BITMAP *page;  // double buffer

    t_listeActeurs *acteurs;   // les pierres

    t_joueurs *saboteur;     //le saboteur

    t_ennemi *chercheur;  // le chercheur

    float x=0.0;
    SAMPLE*son=load_sample("victoire_saboteur.wav");

     play_sample(son,255,1,2000,1);

    srand(time(NULL));

    // Lancer allegro et le mode graphique
   // initialisationAllegro();

    page=create_bitmap(SCREEN_W,SCREEN_H);

    GROTTE=load_bitmap("images/grotte1.bmp",NULL);




    /// création du saboteur et chercheur
    saboteur=creerJoueur("images/saboteur3.bmp");
    chercheur=creerEnnemi("images/chercheur0.bmp");

     // préparer la liste des acteurs (100 maxi)
    // mais vide initialement
    acteurs=creerListeActeurs(100);


    while(!key[KEY_ESC])
    {
              if (!GROTTE)
    {
        allegro_message("pas pu trouver/charger grotte.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }


   if(key[KEY_RIGHT])
   {
    clear_bitmap(page);

         x=x-0.5;

            blit(GROTTE,page,0,0,x,0,SCREEN_W,SCREEN_H);

   }else
   if(key[KEY_LEFT])
   {
      clear_bitmap(page);
       x=x+0.5;




        // effacer buffer en appliquant décor  (pas de clear_bitmap)
           blit(GROTTE,page,0,0,x,0,SCREEN_W,SCREEN_H);

   }else
   {
       clear_bitmap(page);
       blit(GROTTE,page,0,0,0,0,SCREEN_W,SCREEN_H);
   }



         //bouger tout
         actualiserJoueur(saboteur,acteurs);
         actualiserEnnemi(chercheur);
         actualiserListeActeurs(acteurs);

         //gérer les collisions
         collisionListeActeurs(chercheur,acteurs);

         //afficher tout le monde
         dessinerJoueur(page,saboteur);
         dessinerEnnemi(page,chercheur);
         dessinerListeActeurs(page,acteurs);


        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H); // double buffer pour éviter les clignotements

        rest(10);//pause 10 ms

    }
    destroy_sample(son);
    destroy_bitmap(GROTTE);  // destrution de l'image pour éviter les chutes de mémoire
}




// Allouer et initialiser un acteur
t_acteur * creerActeur(int x,int y,int type){
    t_acteur *nouv;


    // Allouer
    nouv=(t_acteur *)malloc(1*sizeof(t_acteur));

    // Initialiser ...

    // ici ce qui est commun aux acteurs
    nouv->x=x;
    nouv->y=300;
    nouv->type=type;
    nouv->comportement=0;
    nouv->cptexplo=0; // pas encore explosé mais on initialise par sécurité
    nouv->vivant=1;


       if(key[KEY_RIGHT])
       {
            nouv->tx=40;
            nouv->ty=20;
            nouv->dx=2;
            // petite dispersion dans la trajectoire des jets de pierre:
            nouv->dy=0;//rand()%5-1;
            nouv->couleur=makecol(240,220,220);
       }else
       if(key[KEY_LEFT])
       {
           nouv->tx=-40;
            nouv->ty=-20;
            nouv->dx=-2;
            // petite dispersion dans la trajectoire des jets de pierre:
            nouv->dy=0;//rand()%5-1;
            nouv->couleur=makecol(240,220,220);
       }else
       {
           nouv->tx=40;
            nouv->ty=20;
            nouv->dx=2;
            // petite dispersion dans la trajectoire des jets de pierre :

            nouv->dy=0;//rand()%5-1;
            nouv->couleur=makecol(240,220,220);
       }

           // break;
   // }

    return nouv;
}




// Actualiser un acteur (bouger, sortie écran, fin explosion ...)
void actualiserActeur(t_acteur *acteur){

    float phase2=10;
    float radius=0.9;
    float radius1=17;
    float alpha=50*M_PI/120;
    phase2=phase2+M_PI/2;

    int i=0;

    // deplacement
    if(key[KEY_RIGHT])
    {
    for(i=0;i<3;i++)
    {
      acteur->x=acteur->x+acteur->dx;
    acteur->y=acteur->y+acteur->dy- radius*cos(phase2+alpha*i);
    }


    // type jets de pierres : accélère en dx mais pas au dela d'une limite
    if (acteur->type==1 && acteur->dx<14)
        acteur->dx++;

    // si dépasse le bord alors disparait
    if (acteur->x+acteur->tx<0 || acteur->x>SCREEN_W || acteur->y+acteur->ty<0 || acteur->y>SCREEN_H )
        acteur->vivant=0;

    // si en cours d'explosion incrémenter cptexplo
    // et si explose depuis trop longtemps alors disparait
    if (acteur->comportement==1)
    {
        acteur->cptexplo++;
        if (acteur->cptexplo > 7)
            acteur->vivant=0;
    }
    }

    else if(key[KEY_LEFT]){

    for(i=0;i<3;i++)
    {
    acteur->x=acteur->x+acteur->dx;
    acteur->y=acteur->y-acteur->dy- radius*cos(phase2+alpha*i);

    }
     // type jets de pierres : accélère en dx mais pas au dela d'une limite
    if (acteur->type==1 && acteur->dx<14)
        acteur->dx--;

    // si dépasse le bord alors disparait
    if (acteur->x-acteur->tx<0 || acteur->x>SCREEN_W || acteur->y-acteur->ty<0 || acteur->y>SCREEN_H )
        acteur->vivant=0;

    // si en cours d'explosion incrémenter cptexplo
    // et si explose depuis trop longtemps alors disparait
    if (acteur->comportement==1)
    {
        acteur->cptexplo++;
        if (acteur->cptexplo > 7)
            acteur->vivant=0;


    }

    }else
    {

    for(i=0;i<3;i++)
    {
        int y1=150;

   /* if(acteur->y>75)
    {


    acteur->x=acteur->x+acteur->dx/8;
    acteur->y=-3+acteur->y+radius*sin(alpha*i+M_PI/100);
    }
    else
        if(acteur->y<=75)
    {


    acteur->x=acteur->x+acteur->dx/8+125;
    acteur->y=(-3+acteur->y+600*cos(alpha*i+M_PI/100));

    }*/



    if(acteur->y>150)
    {
      acteur->x=1.5+acteur->x+radius*cos(alpha*i+M_PI/100);
    acteur->y=-5+acteur->y+radius*sin(alpha*i+M_PI/100);

    }

    else if(acteur->y<=y1)
    {

    acteur->x=1.5+acteur->x+radius*cos(alpha*i+M_PI/100)+125;
    acteur->y=5+acteur->y+radius1*sin(alpha*i+M_PI/100)+400;
    rest(30);

    }






   // y1=y1+75;

    }



    // jets de pierres : accélère en dx mais pas au dela d'une limite
    if (acteur->type==1 && acteur->dx<14)
        acteur->dx++;

    // si dépasse le bord alors disparait
    if (acteur->x+acteur->tx<0 || acteur->x>SCREEN_W || acteur->y+acteur->ty<0 || acteur->y>SCREEN_H )
        acteur->vivant=0;

    // si en cours d'explosion incrémenter cptexplo
    // et si explose depuis trop longtemps alors disparait
    if (acteur->comportement==1)
    {
        acteur->cptexplo++;
        if (acteur->cptexplo > 7)
            acteur->vivant=0;
    }
    }
}

// Dessiner un acteur sur la bitmap bmp
void dessinerActeur(BITMAP *bmp,t_acteur *acteur){


    // Si pas d'explosion
    if (acteur->comportement==0){
        switch(acteur->type)
        {
            case 0:
                if(key[KEY_RIGHT])
                {
                  rectfill(bmp,acteur->x,acteur->y,acteur->x+acteur->tx,acteur->y+acteur->ty,acteur->couleur);
                }else
                if(key[KEY_LEFT])
                {
                    rectfill(bmp,acteur->x,acteur->y,acteur->x-acteur->tx,acteur->y-acteur->ty,acteur->couleur);
                }else
                {
                    rectfill(bmp,acteur->x,acteur->y,acteur->x+acteur->tx,acteur->y+acteur->ty,acteur->couleur);
                }

                break;
            case 1:
                if(key[KEY_RIGHT])
                {
                   circlefill(bmp,acteur->x,acteur->y+acteur->ty/2,20,makecol(163,124,47));
                circlefill(bmp,acteur->x,acteur->y+acteur->ty/2,20,makecol(163,124,47));
                }else
                if(key[KEY_LEFT])
                {
                    circlefill(bmp,acteur->x,acteur->y-acteur->ty/2,20,makecol(163,124,47));
                circlefill(bmp,acteur->x,acteur->y-acteur->ty/2,20,makecol(163,124,47));
                }else
                {
                    circlefill(bmp,acteur->x,acteur->y+acteur->ty/2,20,makecol(163,124,47));
                circlefill(bmp,acteur->x,acteur->y+acteur->ty/2,20,makecol(163,124,47));
                }


                break;
        }
    }
    // sinon on dessine l'explosion

    else {
        switch(acteur->type)
        {
            case 0:
                  if(key[KEY_RIGHT])
                {
                circlefill(bmp,acteur->x+acteur->tx/2,acteur->y+acteur->ty/2,30-4*acteur->cptexplo,makecol(255,255-15*acteur->cptexplo,255-30*acteur->cptexplo));

                }else
                if(key[KEY_LEFT])
                {
                circlefill(bmp,acteur->x-acteur->tx/2,acteur->y-acteur->ty/2,30-4*acteur->cptexplo,makecol(255,255-15*acteur->cptexplo,255-30*acteur->cptexplo));

                }else
                {
                circlefill(bmp,acteur->x+acteur->tx/2,acteur->y+acteur->ty/2,30-4*acteur->cptexplo,makecol(255,255-15*acteur->cptexplo,255-30*acteur->cptexplo));

                }
                break;
            case 1:
                 if(key[KEY_RIGHT])
                {
                circlefill(bmp,acteur->x+acteur->tx/2,acteur->y+acteur->ty/2,60-6*acteur->cptexplo,makecol(255-15*acteur->cptexplo,128-15*acteur->cptexplo,0));

                }else
                if(key[KEY_LEFT])
                {
                circlefill(bmp,acteur->x-acteur->tx/2,acteur->y-acteur->ty/2,60-6*acteur->cptexplo,makecol(255-15*acteur->cptexplo,128-15*acteur->cptexplo,0));

                }else
                {
                circlefill(bmp,acteur->x+acteur->tx/2,acteur->y+acteur->ty/2,60-6*acteur->cptexplo,makecol(255-15*acteur->cptexplo,128-15*acteur->cptexplo,0));

                }
                break;
        }
    }
}

// Allouer et initialiser une liste (vide) de acteurs
t_listeActeurs * creerListeActeurs(int maxacteurs){
    t_listeActeurs *nouv;
    int i;

    nouv=(t_listeActeurs *)malloc(1*sizeof(t_listeActeurs));

    nouv->max=maxacteurs;
    nouv->n=0;
    nouv->tab=(t_acteur **)malloc(maxacteurs*sizeof(t_acteur*));

    for (i=0;i<maxacteurs;i++)
        nouv->tab[i]=NULL;

    return nouv;
}

// Retourne un booléen vrai si il reste de la place
// dans la liste, faux sinon
int libreListeActeurs(t_listeActeurs *la){
    return la->n < la->max;
}

// Allouer et ajouter un acteur à la liste
// et retourner l'adresse de ce nouveau acteur
// retourne NULL en cas de problème
// ( mais il vaut mieux d'abord vérifier qu'il
//   y a de la place disponible avant d'appeler )
t_acteur * ajouterActeur(t_listeActeurs *la,int x,int y,int type){
    int i;
    t_acteur *acteur;

    // Liste pleine, on alloue rien et on retourne NULL...
    if (la->n >= la->max)
        return NULL;

    // Allouer un acteur initialisé
    acteur=creerActeur(x,y,type);

    // Chercher un emplacement libre
    i=0;
    while (la->tab[i]!=NULL && i<la->max)
        i++;

    // Si on a trouvé ...
    // (normalement oui car on a vérifié n<max)
    if (i<la->max){
        // Accrocher le acteur à l'emplacement trouvé
           la->tab[i]=acteur;
        la->n++;

    }
    // Sinon c'est qu'il y a un problème de cohérence
    else
        allegro_message("Anomalie gestion ajouterActeur : liste corrompue");

    return acteur;
}

// Enlever et libèrer un acteur qui était dans la liste en indice i
void enleverActeur(t_listeActeurs *la,int i){

    // Vérifier qu'il y a bien un acteur accroché en indice i
    if (la->tab[i]!=NULL)
    {
        // libérer la mémoire du acteur
        free(la->tab[i]);

        // marquer l'emplacement comme libre
        la->tab[i]=NULL;
        la->n--;

    }
}

// Gérer l'évolution de l'ensemble des acteurs
void actualiserListeActeurs(t_listeActeurs *la){
    int i;

    // actualiser chaque acteur
    // si un acteur n'est plus vivant, l'enlever de la liste
    for (i=0;i<la->max;i++)
        if (la->tab[i]!=NULL){
            actualiserActeur(la->tab[i]);
            if (!la->tab[i]->vivant){
                enleverActeur(la,i);
            }
        }
}

// Dessiner sur une bitmap l'ensemble des acteurs
void dessinerListeActeurs(BITMAP *bmp,t_listeActeurs *la){
    int i;

    for (i=0;i<la->max;i++)
        if (la->tab[i]!=NULL)
            dessinerActeur(bmp,la->tab[i]);

}


// Un acteur a été touché ou a touché une cible : modifier son état
// ici on indique qu'il passe en comportement 1 (explosion)
// et le vecteur vitesse est divisé en norme (ralentissement)
void destinActeur(t_acteur *acteur){
    acteur->dx/=2;
    acteur->dy/=2;
    acteur->comportement=1;
    acteur->cptexplo=0;
}

// Gérer collision (éventuelle) entre un acteur (un tir) et un ennemi
void collisionActeur(t_ennemi *ennemi,t_acteur *acteur){
    int vx,vy,d2;

    // si il n'explose déjà pas !
    if ( acteur->comportement==0 )
    {
        // si il est dans la cible alors appeler destinActeur (explosion)

        // calcul du vecteur entre acteur et centre cible
        vx = acteur->x+acteur->tx/2 - (ennemi->x+ennemi->tx/2);
        vy = acteur->y+acteur->ty/2 - (ennemi->y+ennemi->ty/2);

        // calcul distance au carré au centre de la cible (Pythagore)
        // (on reste sur le carré pour éviter de calculer la racine)
        d2 = vx*vx + vy*vy;

        // si dans le disque alors destin...
        if ( d2 < ennemi->tx * ennemi->tx / 4 )
            destinActeur(acteur);
    }
}

// Gérer les collisions entre les acteurs (tous les tirs) et un ennemi
void collisionListeActeurs(t_ennemi *ennemi,t_listeActeurs *la){

    int i;

    // regarder pour chaque acteur...
    for (i=0;i<la->max;i++)
        if (la->tab[i]!=NULL)
            collisionActeur(ennemi,la->tab[i]);

}


// Allouer et initialiser un joueur
t_joueur * creerJoueur(char *nomimage){
    t_joueurs *nouv;

    // Allouer
    nouv = (t_joueurs *)malloc(1*sizeof(t_joueur));

    // Initialiser

    nouv->img=load_bitmap(nomimage,NULL);
    if (!nouv->img)
    {
        allegro_message("pas pu trouver %s",nomimage);
        exit(EXIT_FAILURE);
    }

    nouv->tx = nouv->img->w;
    nouv->ty = nouv->img->h;

    nouv->x = 100;
    nouv->y = 200;
    nouv->vit = 5;

    nouv->cpttir0 = 0;
    nouv->cpttir1 = 0;

    return nouv;
}

// Actualiser joueur (bouger interactivement et tirer...)
void actualiserJoueur(t_joueurs *joueur,t_listeActeurs *la){

    // Déplacements instantanés (pas d'inertie)
    // gestion d'un blocage dans une zone écran (moitié gauche)
    if (key[KEY_LEFT]){
        joueur->x -= joueur->vit;
        if (joueur->x<0)
            joueur->x=0;
    }

    if (key[KEY_RIGHT]){
        joueur->x += joueur->vit;
        if (joueur->x+joueur->tx > SCREEN_W)
            joueur->x=SCREEN_W-joueur->tx;
    }


    // Gestion du tir...

    // incrémenter la tempo des tirs
   // joueur->cpttir0++;
    joueur->cpttir1++;

    // si le joueur appui sur la gachette et arme ok...
    // espace = jets de pierre

    if (key[KEY_SPACE] && joueur->cpttir1>=10){
            if(key[KEY_RIGHT])
            {
             ajouterActeur(la,joueur->x+joueur->tx,200,1);//joueur->y+joueur->ty/2
            joueur->cpttir1 = 0;
            }else
            if(key[KEY_LEFT])
            {
            ajouterActeur(la,joueur->x-joueur->tx,-200,1);//joueur->y+joueur->ty/2
            joueur->cpttir1 = 0;
            }else
            {
                ajouterActeur(la,joueur->x+joueur->tx,200,1);//joueur->y+joueur->ty/2
            joueur->cpttir1 = 0;
            }

    }
}

// Dessiner joueur sur la bitmap bmp
void dessinerJoueur(BITMAP *bmp,t_joueurs *joueur){



    if(key[KEY_LEFT]||joueur->x<0)
    {

     draw_sprite(bmp,joueur->img,joueur->x,200);

    }else
    if(key[KEY_RIGHT]||joueur->x>SCREEN_W)
    {
     draw_sprite_h_flip(bmp,joueur->img,joueur->x,200);
    }else
    {
        draw_sprite_h_flip(bmp,joueur->img,joueur->x,200);
    }


}


// Allouer et initialiser ennemi
t_ennemi * creerEnnemi(char *nomimage){
    t_ennemi *nouv;

    // Allouer
    nouv = (t_ennemi *)malloc(1*sizeof(t_ennemi));

    // Initialiser

    nouv->img=load_bitmap(nomimage,NULL);
    if (!nouv->img)
    {
        allegro_message("pas pu trouver %s",nomimage);
        exit(EXIT_FAILURE);
    }

    nouv->tx =nouv->img->w;
    nouv->ty =nouv->img->h;

    nouv->x =900;
    nouv->y = 200;
    nouv->dx=rand()%11-5;
    nouv->dy=0;

    return nouv;
}

// Actualiser ennemi
// (bouger automatiquement au hasard dans la moitié droite...)
void actualiserEnnemi(t_ennemi *ennemi){

    // Il y aura un peu de hasard...
    srand(time(NULL));

    // proba de changement de déplacement : une chance sur 20
    if ( rand()%20==0 ){
        // Nouveau vecteur déplacement
        ennemi->dx = 8;//rand()%11-5;
        ennemi->dy = 0;
    }

    // contrôle des bords : ici on décide de rebondir sur les bords
    if  (  ( ennemi->x < 0 && ennemi->dx < 0 ) || ( ennemi->x + ennemi->tx > SCREEN_W && ennemi->dx > 0) )
       ennemi->dx =-ennemi->dx;


        if  (  ( ennemi->x > 0 && ennemi->dx > 0 ) ||( ennemi->x + ennemi->tx < SCREEN_W && ennemi->dx < 0) )
       ennemi->dx =+ennemi->dx;



    // calculer nouvelle position
    // nouvelle position = position actuelle + deplacement
    ennemi->x = ennemi->x + ennemi->dx;
    ennemi->y = 200;

}

// Dessiner ennemi sur la bitmap bmp
void dessinerEnnemi(BITMAP *bmp,t_ennemi *ennemi){
    if(ennemi->x>SCREEN_W/2)
    {
     draw_sprite(bmp,ennemi->img,ennemi->x,ennemi->y);
    }else
    if(ennemi->x<SCREEN_W/2)
    {
        draw_sprite_h_flip(bmp,ennemi->img,ennemi->x,ennemi->y);
    }

}





///--------------------------------------GAME OVER-------------------------------------------


void game_over()
{
    // déclaration de variables
    BITMAP *over;
    int ligne,colonne,couleurPixel,rouge;

    srand(time(NULL));

    //initialisationAllegro();

    //chargement de l'image
    over=load_bitmap("images/over.bmp",NULL);



    while(!key[KEY_ESC])
    {

           for(ligne=0;ligne<over->h;ligne++)
        {
            for(colonne=0;colonne<over->w;colonne++)
            {
                couleurPixel=getpixel(over,colonne,ligne);  // on récupère les pixels de l'image
               rouge=getr(couleurPixel);    // on récupère les pixels rouges


                    putpixel(over,colonne,ligne,makecol(rouge,0,0));  // on affichage l'image qu'avec les pixels rouges

            }
        }



blit(over,screen,0,0,0,0,over->w,over->h);


    }
   destroy_bitmap(over);
}




///--------------------------------------ECRAN DE VICTOIRE CHERCHEUR-------------------------------------------



void affiche_chercheur()
{

    // Buffer
    BITMAP *page;

    // Image de fond
    BITMAP *decor;

    // La collection des acteurs (les tirs)
    t_listeActeurss *acteurs;

    // Le vaisseau manipulé par le joueur
    t_joueurss *vaisseau;

    // La cible qui se déplace automatiquement
    t_ennemis *cible;

    // Il y aura du hasard
    srand(time(NULL));
      SAMPLE*son=load_sample("victoire_chercheur.wav");

     play_sample(son,255,1,2000,1);

   //initialisationAllegro();
    // buffer
    page=create_bitmap(SCREEN_W,SCREEN_H);

    // charger image de fond
    decor=load_bitmap("images/sortie_mine.bmp",NULL);//images/hotplanet
    if (!decor)
    {
        allegro_message("pas pu trouver images/sortie_mine.bmp");
        exit(EXIT_FAILURE);
    }

    // créer le vaisseau et la cible
    vaisseau=creerJoueurs("images/chercheur0(2).bmp");//images/spaceship
    cible=creerEnnemis("images/saboteur3.bmp");//images/deathstar

    // préparer la liste des acteurs (100 maxi)
    // mais vide initialement
    acteurs=creerListeActeurss(100);

    // BOUCLE DE JEU
    while (!key[KEY_ESC])
    {
        // effacer buffer en appliquant décor  (pas de clear_bitmap)
        blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);

        // bouger tout le monde
        actualiserJoueurss(vaisseau,acteurs);
        actualiserEnnemis(cible);
        actualiserListeActeurss(acteurs);

        // gérer les collisions
        collisionListeActeurss(cible,acteurs);

        // afficher tout le monde
        dessinerJoueurs(page,vaisseau);
        dessinerEnnemis(page,cible);
        dessinerListeActeurss(page,acteurs);

        // afficher tout ça à l'écran
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // petite temporisation
        rest(10);
    }
    destroy_bitmap(decor);
    destroy_sample(son);

}



// Allouer et initialiser un acteur
t_acteurs * creerActeurs(int x,int y,int type){
    t_acteurs *nouv;

    // Allouer
    nouv=(t_acteurs *)malloc(1*sizeof(t_acteurs));

    // Initialiser ...

    // ici ce qui est commun aux acteurs
    nouv->x=x;
    nouv->y=300;
    nouv->type=type;
    nouv->comportement=0;
    nouv->cptexplo=0; // pas encore explosé mais on initialise par sécurité
    nouv->vivant=1;

    // ici ce qui est spécifique aux types


        // missile
            nouv->tx=40;
            nouv->ty=20;
            nouv->dx=2;
            // petite dispersion dans la trajectoire des missiles :
            nouv->dy=4;//rand()%5-2;
            nouv->couleur=makecol(240,220,220);



    return nouv;
}

// Actualiser un acteur (écran, fin explosion ...)
void actualiserActeurs(t_acteurs *acteur){

    // deplacement immobile
    acteur->x=acteur->x+acteur->dx;
    acteur->y=acteur->y+acteur->dy;

    // type jets de pierres : accélère en dx mais pas au dela d'une limite
    if (acteur->type==1 && acteur->dx<14)
        acteur->dx++;

    // si dépasse le bord alors disparait
    if (acteur->x+acteur->tx<0 || acteur->x>SCREEN_W || acteur->y+acteur->ty<0 || acteur->y>SCREEN_H )
        acteur->vivant=0;

    // si en cours d'explosion incrémenter cptexplo
    // et si explose depuis trop longtemps alors disparait
    if (acteur->comportement==1)
    {
        acteur->cptexplo++;
        if (acteur->cptexplo > 7)
            acteur->vivant=0;
    }
}

// Dessiner un acteur sur la bitmap bmp
void dessinerActeurs(BITMAP *bmp,t_acteurs *acteur){
    // Si pas d'explosion
    if (acteur->comportement==0){
        switch(acteur->type)
        {
            case 0:
                rectfill(bmp,acteur->x,acteur->y,acteur->x+acteur->tx,acteur->y+acteur->ty,acteur->couleur);
                break;
            case 1:
               circlefill(bmp,acteur->x,acteur->y+acteur->ty/2,20,makecol(163,124,47));//2*acteur->tx/3,acteur->ty/2
                circlefill(bmp,acteur->x,acteur->y+acteur->ty/2,20,makecol(163,124,47));//acteur->tx/3,acteur->ty/3
                break;
        }
    }
    // sinon on dessine l'explosion
    // d'un diamètre décroissant et d'une couleur rougissante
    else {
        switch(acteur->type)
        {
            case 0:
                circlefill(bmp,acteur->x+acteur->tx/2,acteur->y+acteur->ty/2,30-4*acteur->cptexplo,makecol(255,255-15*acteur->cptexplo,255-30*acteur->cptexplo));
                break;
            case 1:
                circlefill(bmp,acteur->x+acteur->tx/2,acteur->y+acteur->ty/2,60-6*acteur->cptexplo,makecol(255-15*acteur->cptexplo,128-15*acteur->cptexplo,0));
                break;
        }
    }
}

// Allouer et initialiser une liste (vide) de acteurs
t_listeActeurss * creerListeActeurss(int maxacteurs){
    t_listeActeurss *nouv;
    int i;

    nouv=(t_listeActeurss *)malloc(1*sizeof(t_listeActeurss));

    nouv->max=maxacteurs;
    nouv->n=0;
    nouv->tab=(t_acteurs **)malloc(maxacteurs*sizeof(t_acteurs*));

    for (i=0;i<maxacteurs;i++)
        nouv->tab[i]=NULL;

    return nouv;
}

// Retourne un booléen vrai si il reste de la place
// dans la liste, faux sinon
int libreListeActeurss(t_listeActeurss *la){
    return la->n < la->max;
}

// Allouer et ajouter un acteur à la liste
// et retourner l'adresse de ce nouveau acteur
// retourne NULL en cas de problème
// ( mais il vaut mieux d'abord vérifier qu'il
//   y a de la place disponible avant d'appeler )
t_acteurs * ajouterActeurs(t_listeActeurss *la,int x,int y,int type){
    int i;
    t_acteurs *acteur;

    // Liste pleine, on alloue rien et on retourne NULL...
    if (la->n >= la->max)
        return NULL;

    // Allouer un acteur initialisé
    acteur=creerActeurs(x,y,type);

    // Chercher un emplacement libre
    i=0;
    while (la->tab[i]!=NULL && i<la->max)
        i++;

    // Si on a trouvé ...
    // (normalement oui car on a vérifié n<max)
    if (i<la->max){
        // Accrocher le acteur à l'emplacement trouvé
        la->tab[i]=acteur;
        la->n++;
    }
    // Sinon c'est qu'il y a un problème de cohérence
    else
        allegro_message("Anomalie gestion ajouterActeur : liste corrompue");

    return acteur;
}

// Enlever et libèrer un acteur qui était dans la liste en indice i
void enleverActeurs(t_listeActeurss *la,int i){

    // Vérifier qu'il y a bien un acteur accroché en indice i
    if (la->tab[i]!=NULL)
    {
        // libérer la mémoire du acteur
        free(la->tab[i]);

        // marquer l'emplacement comme libre
        la->tab[i]=NULL;
        la->n--;

    }
}

// Gérer l'évolution de l'ensemble des acteurs
void actualiserListeActeurss(t_listeActeurss *la){
    int i;

    // actualiser chaque acteur
    // si un acteur n'est plus vivant, l'enlever de la liste
    for (i=0;i<la->max;i++)
        if (la->tab[i]!=NULL){
            actualiserActeurs(la->tab[i]);
            if (!la->tab[i]->vivant){
                enleverActeurs(la,i);
            }
        }
}

// Dessiner sur une bitmap l'ensemble des acteurs
void dessinerListeActeurss(BITMAP *bmp,t_listeActeurss *la){
    int i;

    for (i=0;i<la->max;i++)
        if (la->tab[i]!=NULL)
            dessinerActeurs(bmp,la->tab[i]);

}


// Un acteur a été touché ou a touché une cible : modifier son état
// ici on indique qu'il passe en comportement 1 (explosion)
// et le vecteur vitesse est divisé en norme (ralentissement)
void destinActeurs(t_acteurs *acteur){
    acteur->dx/=2;
    acteur->dy/=2;
    acteur->comportement=1;
    acteur->cptexplo=0;
}

// Gérer collision (éventuelle) entre un acteur (un tir) et un ennemi
void collisionActeurs(t_ennemis *ennemi,t_acteurs *acteur){
    int vx,vy,d2;

    // si il n'explose déjà pas !
    if ( acteur->comportement==0 )
    {
        // si il est dans la cible alors appeler destinActeur (explosion)

        // calcul du vecteur entre acteur et centre cible
        vx = acteur->x+acteur->tx/2 - (ennemi->x+ennemi->tx/2);
        vy = acteur->y+acteur->ty/2 - (ennemi->y+ennemi->ty/2);

        // calcul distance au carré au centre de la cible (Pythagore)
        // (on reste sur le carré pour éviter de calculer la racine)
        d2 = vx*vx + vy*vy;

        // si dans le disque alors destin...
        if ( d2 < ennemi->tx * ennemi->tx / 4 )
            destinActeurs(acteur);
    }
}

// Gérer les collisions entre les acteurs (tous les tirs) et un ennemi
void collisionListeActeurss(t_ennemis *ennemi,t_listeActeurss *la){

    int i;

    // regarder pour chaque acteur...
    for (i=0;i<la->max;i++)
        if (la->tab[i]!=NULL)
            collisionActeurs(ennemi,la->tab[i]);

}


// Allouer et initialiser un joueur
t_joueurss * creerJoueurs(char *nomimage){
    t_joueurss *nouv;

    // Allouer
    nouv = (t_joueurss *)malloc(1*sizeof(t_joueurss));

    // Initialiser

    nouv->img=load_bitmap(nomimage,NULL);
    if (!nouv->img)
    {
        allegro_message("pas pu trouver %s",nomimage);
        exit(EXIT_FAILURE);
    }

    nouv->tx = nouv->img->w;
    nouv->ty = nouv->img->h;

    nouv->x = 200;
    nouv->y = 20;
    nouv->vit = 5;

    nouv->cpttir0 = 0;
    nouv->cpttir1 = 0;

    return nouv;
}

// Actualiser joueur (position immobile du chercheur et tirer...)
void actualiserJoueurss(t_joueurss *joueur,t_listeActeurss *la){

    joueur->x=200;
    joueur->y=20;
    // Gestion du tir...

    // incrémenter la tempo des tirs
   joueur->cpttir1++;


    // entrée = missile
    if ( joueur->cpttir1>=10){//key[KEY_SPACE] &&
        ajouterActeurs(la,joueur->x+joueur->tx,joueur->y+joueur->ty/2,1);
        joueur->cpttir1 = 0;
    }
}

// Dessiner joueur sur la bitmap bmp
void dessinerJoueurs(BITMAP *bmp,t_joueurss *joueur){
    draw_sprite(bmp,joueur->img,joueur->x,joueur->y);
}


// Allouer et initialiser ennemi
t_ennemis * creerEnnemis(char *nomimage){
    t_ennemi *nouv;

    // Allouer
    nouv = (t_ennemis *)malloc(1*sizeof(t_ennemis));

    // Initialiser

    nouv->img=load_bitmap(nomimage,NULL);
    if (!nouv->img)
    {
        allegro_message("pas pu trouver %s",nomimage);
        exit(EXIT_FAILURE);
    }

    nouv->tx = nouv->img->w;
    nouv->ty = nouv->img->h;

    nouv->x = 800;
    nouv->y = 250;
    nouv->dx=0;
    nouv->dy=0;

    return nouv;
}


void actualiserEnnemis(t_ennemis *ennemi){

        ennemi->dx = 0;
        ennemi->dy = 0;

    ennemi->x=800;
    ennemi->y=250;


}

// Dessiner ennemi sur la bitmap bmp
void dessinerEnnemis(BITMAP *bmp,t_ennemis *ennemi){
    draw_sprite(bmp,ennemi->img,ennemi->x,ennemi->y);
}



