#include"fichier.h"
#include"fichier.placercarte.h"
#include"sauvegarde.h"
#include"Initilisation.h"
void DebutPartie()
{
    t_pile Tour;
    int nombre,fin=0; /// nombre = nombre de joueurs fin = booléen
    t_joueur**listeJoueurs=NULL; /// Tableau dynamique de structure t_joueurs
     t_carte*PlateauJeu[5][7];/// Tableau stockant les cartes poser sur le plateau de jeu
    /// Affichage du menu tant qu'il n'y a pas une sélection d'un nombre de joueurs
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<7;j++)
        {
            PlateauJeu[i][j]=InitilisationPlateau();
        }
    }
    while(!fin)
    {
        textprintf_ex(screen,font,100,210,makecol(255,255,255),-1,"Sélectionner le nombre de joueurs");
        /// Mise en rouge des infos sur lesquels se trouvent la souris
        if(mouse_x>401&&mouse_x<471&&mouse_y>230&&mouse_y<237)
        {
            textprintf_ex(screen,font,400,230,makecol(255,0,0),-1,"2 joueurs");
            textprintf_ex(screen,font,400,240,makecol(255,255,255),-1,"3 joueurs");
            textprintf_ex(screen,font,400,250,makecol(255,255,255),-1,"4 joueurs");
        }
        else if(mouse_x>401&&mouse_x<471&&mouse_y>242&&mouse_y<247)
        {
            textprintf_ex(screen,font,400,230,makecol(255,255,255),-1,"2 joueurs");
            textprintf_ex(screen,font,400,240,makecol(255,0,0),-1,"3 joueurs");
            textprintf_ex(screen,font,400,250,makecol(255,255,255),-1,"4 joueurs");
        }
        else if(mouse_x>401&&mouse_x<471&&mouse_y>251&&mouse_y<257)
        {
            textprintf_ex(screen,font,400,230,makecol(255,255,255),-1,"2 joueurs");
            textprintf_ex(screen,font,400,240,makecol(255,255,255),-1,"3 joueurs");
            textprintf_ex(screen,font,400,250,makecol(255,0,0),-1,"4 joueurs");
        }
        else
        {
            textprintf_ex(screen,font,400,230,makecol(255,255,255),-1,"2 joueurs");
            textprintf_ex(screen,font,400,240,makecol(255,255,255),-1,"3 joueurs");
            textprintf_ex(screen,font,400,250,makecol(255,255,255),-1,"4 joueurs");
        }

        if(mouse_b&1&&mouse_x>401&&mouse_x<471&&mouse_y>230&&mouse_y<237)/// Clique gauche sur 2 joueurs
        {
            nombre = 2;
            fin=1;
        }
        else if(mouse_b&1&&mouse_x>401&&mouse_x<471&&mouse_y>242&&mouse_y<247)/// Clique gauche sur 3 joueurs
        {
            nombre = 3;
            fin=1;
        }
        else if(mouse_b&1&&mouse_x>401&&mouse_x<471&&mouse_y>251&&mouse_y<257)/// Clique gauche sur 4 joueurs
        {
            nombre = 4;
            fin=1;
        }

    }
    clear_bitmap(screen);/// Efface entièrement l'écran
    textprintf_ex(screen,font,200,300,makecol(255,255,255),-1,"Chargement de la partie pour %d joueurs",nombre);
    rest(2000);/// Temporise 2s
    clear_bitmap(screen);
    Tour.Hauteur=0;
    Tour.Place=69;
    Empiler(&Tour);
    listeJoueurs=(t_joueur**)malloc(nombre*sizeof(t_joueur*));/// Allocation dynamique du tableau de liste de joueurs
    for(int i=0;i<nombre;i++)
        listeJoueurs[i]=(t_joueur*)malloc(sizeof(t_joueur));
    CreationJoueurs(listeJoueurs,nombre,&Tour);/// Appelle du menu de création des joueurs
    Partie(PlateauJeu,listeJoueurs,nombre,&Tour);
   // free(listeJoueurs);
    clear_bitmap(screen);
}
void ChargementPartie()
{
    char nomFichier[25];
    printf("Quelle partie voulez vous charger : ");
    scanf("%s",nomFichier);
    t_pile Tour;
    int nombre;
    t_carte*PlateauJeu[5][7];
    t_joueur**listeJoueurs=NULL;
    chargementPioche(nomFichier,&Tour);
    chargementPlateau(nomFichier,PlateauJeu);
    listeJoueurs=chargementJoueur(nomFichier,&nombre);
    Partie(PlateauJeu,listeJoueurs,nombre,&Tour);
    free(listeJoueurs);
}
t_joueur** chargementJoueur(char nomFichier[25],int*nombre)
{
    t_joueur**listeJoueurs=NULL;
    FILE*fichier=NULL;
    char dossier[50];
    char chaine[15];
    sprintf(dossier,"Sauvegarde/");
    strcat(dossier,nomFichier);
    strcat(dossier,"Joueur.txt");
    fichier=fopen(dossier,"r");
    if(fichier==NULL)
        printf("ERREUR d'ouverture de %s\n",dossier);
    else
    {
        fscanf(fichier,"%d\n",nombre);
        listeJoueurs=(t_joueur**)malloc((*nombre)*sizeof(t_joueur*));/// Allocation dynamique du tableau de liste de joueurs
        for(int i=0;i<(*nombre);i++)
        {
            listeJoueurs[i]=(t_joueur*)malloc(sizeof(t_joueur));
            fscanf(fichier,"%s\n",chaine);
            listeJoueurs[i]->name=ChaineDyn(chaine);
            fscanf(fichier,"%d\n",&listeJoueurs[i]->score);
            fscanf(fichier,"%d\n",&listeJoueurs[i]->penalite);
            fscanf(fichier,"%d\n",&listeJoueurs[i]->role);
            fscanf(fichier,"%d\n",&listeJoueurs[i]->logo);
            for(int j=0;j<6;j++)
                    fscanf(fichier,"%d\n",&listeJoueurs[i]->jeu[j]);

        }
        fclose(fichier);
    }
    return listeJoueurs;
}
void chargementPlateau(char nomFichier[25],t_carte*PlateauJeu[5][7])
{
    FILE*fichier=NULL;
    char dossier[50];
    sprintf(dossier,"Sauvegarde/");
    strcat(dossier,nomFichier);
    strcat(dossier,"Plateau.txt");
    fichier=fopen(dossier,"r");
    if(fichier==NULL)
        printf("ERREUR d'ouverture de %s\n",dossier);
    else
    {
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<7;j++)
            {
                PlateauJeu[i][j]=(t_carte*)malloc(sizeof(t_carte));
                fscanf(fichier,"%d\n",&PlateauJeu[i][j]->token);
                if(PlateauJeu[i][j]->token!=-1)
                {
                    fscanf(fichier,"%d\n",&PlateauJeu[i][j]->haut);
                    fscanf(fichier,"%d\n",&PlateauJeu[i][j]->bas);
                    fscanf(fichier,"%d\n",&PlateauJeu[i][j]->droite);
                    fscanf(fichier,"%d\n",&PlateauJeu[i][j]->gauche);
                    fscanf(fichier,"%d\n",&PlateauJeu[i][j]->sens);
                }
            }
        }
        fclose(fichier);
    }
}
void chargementPioche(char nomFichier[50],t_pile*Tour)
{
    FILE*fichier=NULL;
    char dossier[50];
    sprintf(dossier,"Sauvegarde/");
    strcat(dossier,nomFichier);
    strcat(dossier,"Pioche.txt");
    fichier=fopen(dossier,"r");
    if(fichier==NULL)
        printf("ERREUR d'ouverture de %s\n",dossier);
    else
    {
        fscanf(fichier,"%d\n",&Tour->Hauteur);
        fscanf(fichier,"%d\n",&Tour->Place);
        for(int i=0;i<69;i++)
            fscanf(fichier,"%d\n",&Tour->Element[i]);
        fclose(fichier);
    }
}
int Empiler(t_pile*Tour)
{
    int Tab[17][2];
    int nombre;
    for(int i=0;i<17;i++)
        Tab[i][0]=i+1;
    for(int i=0;i<5;i++)
        Tab[i][1]=9;
    for(int i=5;i<17;i++)
        Tab[i][1]=2;
    for(int i=0;i<69;i++)
    {
        do
        {
            nombre=rand()%(17);
        }while(Tab[nombre][1]<0);
        Tab[nombre][1]--;
        Tour->Element[i]=Tab[nombre][0];
    }
    return 0;
}
