#include <allegro.h>

typedef struct carte
{
    int token; /// Identifiant de la carte
    int haut;  /// 1: chemin vers le haut 0: pas de chemin vers le haut
    int bas; //
    int droite;//
    int gauche;//
    int sens;/// sens de la carte (2 sens possible)
}t_carte;

typedef struct joueur
{
    char*name;
    int score;
    int jeu[6];
    int role;
    int penalite;
    int logo;
}t_joueur;

typedef struct pile
{
    int Element[69];
    int Hauteur;
    int Place;
}t_pile;




// chaque acteur qui se d�place
typedef struct acteur
{
    // position du coin sup. gauche
    float x,y;
    // vecteur deplacement
    float dx,dy;
    // largeur hauteur
    int tx,ty;
    // couleur (ne sera plus pertinent avec des sprites import�s...)
    int couleur;
    //jet de pierres
    int type;
    int comportement;
    int cptexplo; // temps depuis l'explosion
    // vivant :
    //   0 mort (doit disparaitre de la liste)
    //   1 vivant
    int vivant;

} t_acteur;

// Une collection de acteurs
typedef struct listeActeurs
{   // nombre maxi d'�l�ments
    // =taille du tableau de pointeurs
    int max;
    // nombre effectif de pointeurs utilis�s
    // (les autres sont � NULL)
    int n;
    // le tableau de pointeurs (allou� dynamiquement)
    t_acteur **tab;

} t_listeActeurs;


// Un �l�ment � d�placement interactif // SABOTEUR
typedef struct joueurs{
    int x,y;     // position
    int tx,ty;   // taille
    int vit;     // vitesse des d�placements (nombre de pixels)
    int cpttir0; // tempo armement 0
    int cpttir1; // tempo armement 1
    BITMAP *img; // sprite (image charg�e)
} t_joueurs;

// Un �l�ment � d�placement automatique al�atoire  //CHERCHEUR
typedef struct ennemi{
    int x,y;     // position
    int dx,dy;   // vecteur d�placement
    int tx,ty;   // taille
    BITMAP *img; // sprite (image charg�e)
} t_ennemi;





// chaque acteur qui se d�place
typedef struct acteurs
{
    // position du coin sup. gauche
    float x,y;
    // vecteur deplacement
    float dx,dy;
    // largeur hauteur
    int tx,ty;
    // couleur (ne sera plus pertinent avec des sprites import�s...)
    int couleur;
    //jet de pierres
    int type;
    int comportement;
    int cptexplo; // temps depuis l'explosion
    // vivant :
    //   0 mort (doit disparaitre de la liste)
    //   1 vivant
    int vivant;

} t_acteurs;

// Une collection de acteurs
typedef struct listeActeurss
{   // nombre maxi d'�l�ments
    // =taille du tableau de pointeurs
    int max;
    // nombre effectif de pointeurs utilis�s
    // (les autres sont � NULL)
    int n;
    // le tableau de pointeurs (allou� dynamiquement)
    t_acteur **tab;

} t_listeActeurss;


// Un �l�ment � d�placement interactif // SABOTEUR
typedef struct joueurss{
    int x,y;     // position
    int tx,ty;   // taille
    int vit;     // vitesse des d�placements (nombre de pixels)
    int cpttir0; // tempo armement 0
    int cpttir1; // tempo armement 1
    BITMAP *img; // sprite (image charg�e)
} t_joueurss;

// Un �l�ment � d�placement automatique al�atoire  //CHERCHEUR
typedef struct ennemis{
    int x,y;     // position
    int dx,dy;   // vecteur d�placement
    int tx,ty;   // taille
    BITMAP *img; // sprite (image charg�e)
} t_ennemis;
