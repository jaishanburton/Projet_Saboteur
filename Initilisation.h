#ifndef INITILISATION_H_INCLUDED
#define INITILISATION_H_INCLUDED
#endif // INITILISATION_H_INCLUDED

/// Initilisation allegro
void initilisationAllegro();

/// Initilisation de la carte � placer
t_carte*InitilisationCarte(int carte);

/// Initilisation des cartes du plateau de jeu
t_carte*InitilisationPlateau();

/// Ajoute une carte au jeu des joueurs lorqu'il en manque
t_joueur*InitilisationPioche(t_joueur*nouveau);

/// Initilisation de la pioche
int Empiler(t_pile*Tour);

/// Cr�e un joueur
t_joueur *creation(int *saboteur,t_pile*Tour);

/// saisit et retourne une cha�ne dynamique
char*ChaineDyn(char chaine[15]);

/// D�but de partie(S�lection du nombre de joueurs)
void DebutPartie();

/// Menu de cr�ation
void CreationJoueurs(t_joueur**listeJoueurs,int nombre,t_pile*Tour);

void new_menu();
void choix();

