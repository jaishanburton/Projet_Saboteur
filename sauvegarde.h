#ifndef SAUVEGARDE_H_INCLUDED
#define SAUVEGARDE_H_INCLUDED
#endif // SAUVEGARDE_H_INCLUDED

/// Sauvegarde partie
void sauvegarde(char nomFichier[25],t_pile*Tour,t_carte*PlateauJeu[5][7],t_joueur**listeJoueurs,int nombre);

/// Sauvegarde la pioche
void sauvegardePioche(char nomFichier[25],t_pile*Tour);

///Sauvegarde le plateau de jeu
void sauvegardePlateau(char nomFichier[25],t_carte*PlateauJeu[5][7]);

/// sauvegarde le tableau de joueur
void sauvegardeJoueur(char nomFichier[25],t_joueur**listeJoueurs,int nombre);

/// Chargement de la partie
void ChargementPartie();

/// Chargement de la pioche
void chargementPioche(char nomFichier[50],t_pile*Tour);

/// Chargement du plateau de jeu
void chargementPlateau(char nomFichier[25],t_carte*PlateauJeu[5][7]);

/// Chargement du tableau de joueur
t_joueur** chargementJoueur(char nomFichier[25],int*nombre);

/// sauvegardePartie
int sauvegardePartie();
