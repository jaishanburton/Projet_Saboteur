#ifndef FICHIER_PLACERCARTE_H_INCLUDED
#define FICHIER_PLACERCARTE_H_INCLUDED
#endif // FICHIER_PLACERCARTE_H_INCLUDED

/// Place une sur le plateau de jeu
int PlacerCarte(t_carte*PlateauJeu[5][7],t_carte*nouveau,t_joueur**listeJoueurs,int sortie,int nombre,int joueurAction);

/// convertion position Y de la souris en ligne du tableau
int PositionY();
/// convertion position X de la souris en colonne du tableau
int PositionX();

/// Blindage pose de la carte
int Validation(t_carte* nouveau,t_carte*PlateauJeu[5][7], int ligne,int colonne,int sens);

/// 1 tour de jeu( 1 carte poser)
void TourJeu(t_joueur**listeJoueurs,int joueurAction,t_carte*PlateauJeu[5][7],int nombre,t_pile*Tour);

/// D�roulement de la partie avec les diff�rents tour de jeu
void Partie(t_carte*PlateauJeu[5][7],t_joueur**listeJoueurs,int nombre,t_pile*Tour);

/// Blindage carte action
int BlindageAction(t_joueur**listeJoueurs,int nombre,int token);

/// Permet au joueur de piocher une carte
t_joueur*Piochage(int nouveau,t_carte*PlateauJeu[5][7],int nombre,t_joueur**listeJoueurs,t_pile*Tour);

/// Victoire des chercheurs
int ConditionVictoire(t_carte*PlateauJeu[5][7],int ligne,int colonne,int interdit,int victoire);


void affichage_grotte();


// Allouer et initialiser un acteur
// pour ce projet il faut x y de d�part et type
//   ( � adapter selon besoins )
t_acteur * creerActeur(int x,int y,int type);

// Allouer et initialiser une liste (vide) de acteurs
t_listeActeurs * creerListeActeurs(int maxacteurs);

// Retourne un bool�en vrai si il reste de la place
// dans la liste, faux sinon
int libreListeActeurs(t_listeActeurs *la);

// Allouer et ajouter un acteur � la liste
// et retourner l'adresse de ce nouveau acteur
// retourne NULL en cas de probl�me
// pour ce projet il faut x y de d�part et type
//   ( � adapter selon besoins )
t_acteur * ajouterActeur(t_listeActeurs *la,int x,int y,int type);

// Enlever et lib�rer un acteur qui �tait dans la liste en indice i
void enleverActeur(t_listeActeurs *la,int i);



// Actualiser un acteur (bouger ...)
void actualiserActeur(t_acteur *acteur);

// G�rer l'�volution de l'ensemble des acteurs
void actualiserListeActeurs(t_listeActeurs *la);


// Dessiner un acteur sur la bitmap bmp
void dessinerActeur(BITMAP *bmp,t_acteur *acteur);

// Dessiner sur une bitmap l'ensemble des acteurs
void dessinerListeActeurs(BITMAP *bmp,t_listeActeurs *la);


// Un acteur a �t� touch� ou a touch� une cible : modifier son �tat
// ici on indique qu'il passe en comportement 1 (explosion)
// et le vecteur vitesse est divis� en norme (ralentissement)
void destinActeur(t_acteur *acteur);

// G�rer collision (�ventuelle) entre un acteur (un tir) et un ennemi
void collisionActeur(t_ennemi *ennemi,t_acteur *acteur);

// G�rer les collisions entre les acteurs (tous les tirs) et un ennemi
void collisionListeActeurs(t_ennemi *ennemi,t_listeActeurs *la);


// Sp�cifique � cet exemple : g�rer le vaisseau et la cible

// Allouer et initialiser joueur
t_joueur * creerJoueur(char *nomimage);

// Actualiser joueur (bouger interactivement et tirer...)
void actualiserJoueur(t_joueurs *joueur,t_listeActeurs *la);

// Dessiner joueur sur la bitmap bmp
void dessinerJoueur(BITMAP *bmp,t_joueurs *joueur);


// Allouer et initialiser ennemi
t_ennemi * creerEnnemi(char *nomimage);

// Actualiser ennemi (bouger automatiquement au hasard...)
void actualiserEnnemi(t_ennemi *ennemi);

// Dessiner ennemi sur la bitmap bmp
void dessinerEnnemi(BITMAP *bmp,t_ennemi *ennemi);



void game_over(); // �cran de game over





/// M�me principe que pour l'�cran de victoire du saboteur sauf que maintenant c'est pour les chercheurs

void affiche_chercheur();

// Allouer et initialiser un acteur
t_acteurs * creerActeurs(int x,int y,int type);

// Actualiser un acteur (�cran, fin explosion ...)
void actualiserActeurs(t_acteurs *acteur);

// Dessiner un acteur sur la bitmap bmp
void dessinerActeurs(BITMAP *bmp,t_acteurs *acteur);

// Allouer et initialiser une liste (vide) de acteurs
t_listeActeurss * creerListeActeurss(int maxacteurs);

// Retourne un bool�en vrai si il reste de la place
// dans la liste, faux sinon
int libreListeActeurss(t_listeActeurss *la);

// Allouer et ajouter un acteur � la liste
// et retourner l'adresse de ce nouveau acteur
// retourne NULL en cas de probl�me
// ( mais il vaut mieux d'abord v�rifier qu'il
//   y a de la place disponible avant d'appeler )
t_acteurs * ajouterActeurs(t_listeActeurss *la,int x,int y,int type);

// Enlever et lib�rer un acteur qui �tait dans la liste en indice i
void enleverActeurs(t_listeActeurss *la,int i);

// G�rer l'�volution de l'ensemble des acteurs
void actualiserListeActeurss(t_listeActeurss *la);


// Dessiner sur une bitmap l'ensemble des acteurs
void dessinerListeActeurss(BITMAP *bmp,t_listeActeurss *la);


// Un acteur a �t� touch� ou a touch� une cible : modifier son �tat
// ici on indique qu'il passe en comportement 1 (explosion)
// et le vecteur vitesse est divis� en norme (ralentissement)
void destinActeurs(t_acteurs *acteur);

// G�rer collision (�ventuelle) entre un acteur (un tir) et un ennemi
void collisionActeurs(t_ennemis *ennemi,t_acteurs *acteur);

// G�rer les collisions entre les acteurs (tous les tirs) et un ennemi
void collisionListeActeurss(t_ennemis *ennemi,t_listeActeurss *la);

// Allouer et initialiser un joueur
t_joueurss * creerJoueurs(char *nomimage);

// Actualiser joueur (position immobile du chercheur et tirer...)
void actualiserJoueurss(t_joueurss *joueur,t_listeActeurss *la);

// Dessiner joueur sur la bitmap bmp
void dessinerJoueurs(BITMAP *bmp,t_joueurss *joueur);

// Allouer et initialiser ennemi
t_ennemis * creerEnnemis(char *nomimage);

void actualiserEnnemis(t_ennemis *ennemi);

// Dessiner ennemi sur la bitmap bmp
void dessinerEnnemis(BITMAP *bmp,t_ennemis *ennemi);
