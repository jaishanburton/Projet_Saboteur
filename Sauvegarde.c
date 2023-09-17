#include"fichier.h"
#include"sauvegarde.h"
void sauvegarde(char nomFichier[25],t_pile*Tour,t_carte*PlateauJeu[5][7],t_joueur**listeJoueurs,int nombre)
{
    sauvegardePioche(nomFichier,Tour);
    sauvegardePlateau(nomFichier,PlateauJeu);
    sauvegardeJoueur(nomFichier,listeJoueurs,nombre);
    printf("Partie Sauvegarder\n");
}
void sauvegardePioche(char nomFichier[25],t_pile*Tour)
{
    FILE*fichier=NULL;
    char dossier[50];
    sprintf(dossier,"Sauvegarde/");
    strcat(dossier,nomFichier);
    strcat(dossier,"Pioche.txt");
    fichier=fopen(dossier,"w");
    if(fichier==NULL)
        printf("ERREUR d'ouverture de %s\n",dossier);
    else
    {
        fprintf(fichier,"%d\n",Tour->Hauteur);
        fprintf(fichier,"%d\n",Tour->Place);
        for(int i=0;i<69;i++)
            fprintf(fichier,"%d\n",Tour->Element[i]);
        fclose(fichier);
    }
}
void sauvegardePlateau(char nomFichier[25],t_carte*PlateauJeu[5][7])
{
    FILE*fichier=NULL;
    char dossier[50];
    sprintf(dossier,"Sauvegarde/");
    strcat(dossier,nomFichier);
    strcat(dossier,"Plateau.txt");
    fichier=fopen(dossier,"w");

    if(fichier==NULL)
        printf("ERREUR d'ouverture de %s\n",dossier);
    else
    {
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<7;j++)
            {
                fprintf(fichier,"%d\n",PlateauJeu[i][j]->token);
                if(PlateauJeu[i][j]->token!=-1)
                {
                    fprintf(fichier,"%d\n",PlateauJeu[i][j]->haut);
                    fprintf(fichier,"%d\n",PlateauJeu[i][j]->bas);
                    fprintf(fichier,"%d\n",PlateauJeu[i][j]->droite);
                    fprintf(fichier,"%d\n",PlateauJeu[i][j]->gauche);
                    fprintf(fichier,"%d\n",PlateauJeu[i][j]->sens);
                }
            }
        }
      fclose(fichier);
    }
}
void sauvegardeJoueur(char nomFichier[25],t_joueur**listeJoueurs,int nombre)
{
    FILE*fichier=NULL;
    char dossier[50];
    sprintf(dossier,"Sauvegarde/");
    strcat(dossier,nomFichier);
    strcat(dossier,"Joueur.txt");
    fichier=fopen(dossier,"w");
    if(fichier==NULL)
        printf("ERREUR d'ouverture de %s\n",dossier);
    else
    {
        fprintf(fichier,"%d\n",nombre);
        for(int i=0;i<nombre;i++)
        {
            fprintf(fichier,"%s\n",listeJoueurs[i]->name);
            fprintf(fichier,"%d\n",listeJoueurs[i]->score);
            fprintf(fichier,"%d\n",listeJoueurs[i]->penalite);
            fprintf(fichier,"%d\n",listeJoueurs[i]->role);
            fprintf(fichier,"%d\n",listeJoueurs[i]->logo);
            for(int j=0;j<6;j++)
                fprintf(fichier,"%d\n",listeJoueurs[i]->jeu[j]);
        }
        fclose(fichier);
    }
}
