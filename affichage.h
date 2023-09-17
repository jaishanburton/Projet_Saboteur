#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED
#endif // AFFICHAGE_H_INCLUDED
/// Affiche le plateau et la page de jeu
void AffichagePlateau(t_carte*PlateauJeu[5][7],BITMAP*doubleBuffer,int nombre,t_joueur**listeJoueurs);

///Charge la carte correspondant
BITMAP*ChargementCartes(int token);

/// Affiche le jeu du joueur
void AffichageJeu(t_joueur*joueurAction,BITMAP*doubleBuffer);

/// Calcule les scores à la fin de la partie
void Score(t_joueur**listeJoueurs,int gagnant,int nombre);

/// aide aux joueurs
void aide();

/// Menu pause
void Pause(t_pile*Tour,t_carte*PlateauJeu[5][7],t_joueur**listeJoueurs,int nombre,int joueurAction);

/// affichageScore
void affichageScore();
