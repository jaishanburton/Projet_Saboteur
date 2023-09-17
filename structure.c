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




// chaque acteur qui se déplace
typedef struct acteur
{
    // position du coin sup. gauche
    float x,y;
    // vecteur deplacement
    float dx,dy;
    // largeur hauteur
    int tx,ty;
    // couleur (ne sera plus pertinent avec des sprites importés...)
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
{   // nombre maxi d'éléments
    // =taille du tableau de pointeurs
    int max;
    // nombre effectif de pointeurs utilisés
    // (les autres sont à NULL)
    int n;
    // le tableau de pointeurs (alloué dynamiquement)
    t_acteur **tab;

} t_listeActeurs;


// Un élément à déplacement interactif // SABOTEUR
typedef struct joueurs{
    int x,y;     // position
    int tx,ty;   // taille
    int vit;     // vitesse des déplacements (nombre de pixels)
    int cpttir0; // tempo armement 0
    int cpttir1; // tempo armement 1
    BITMAP *img; // sprite (image chargée)
} t_joueurs;

// Un élément à déplacement automatique aléatoire  //CHERCHEUR
typedef struct ennemi{
    int x,y;     // position
    int dx,dy;   // vecteur déplacement
    int tx,ty;   // taille
    BITMAP *img; // sprite (image chargée)
} t_ennemi;





// chaque acteur qui se déplace
typedef struct acteurs
{
    // position du coin sup. gauche
    float x,y;
    // vecteur deplacement
    float dx,dy;
    // largeur hauteur
    int tx,ty;
    // couleur (ne sera plus pertinent avec des sprites importés...)
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
{   // nombre maxi d'éléments
    // =taille du tableau de pointeurs
    int max;
    // nombre effectif de pointeurs utilisés
    // (les autres sont à NULL)
    int n;
    // le tableau de pointeurs (alloué dynamiquement)
    t_acteur **tab;

} t_listeActeurss;


// Un élément à déplacement interactif // SABOTEUR
typedef struct joueurss{
    int x,y;     // position
    int tx,ty;   // taille
    int vit;     // vitesse des déplacements (nombre de pixels)
    int cpttir0; // tempo armement 0
    int cpttir1; // tempo armement 1
    BITMAP *img; // sprite (image chargée)
} t_joueurss;

// Un élément à déplacement automatique aléatoire  //CHERCHEUR
typedef struct ennemis{
    int x,y;     // position
    int dx,dy;   // vecteur déplacement
    int tx,ty;   // taille
    BITMAP *img; // sprite (image chargée)
} t_ennemis;
