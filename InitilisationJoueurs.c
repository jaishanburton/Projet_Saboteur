#include"fichier.h"
#include"Initilisation.h"
t_carte*InitilisationPlateau()
{
    t_carte*nouveau=NULL;/// pointeur de structure t_carte
    nouveau=(t_carte*)malloc(sizeof(t_carte));/// allocation dynamique du pointeur
    if(nouveau==NULL)
    {
        printf("ERREUR allocation T_carte nouveau");
    }
    else
    {
        nouveau->token=-1;/// l'identifiant de la case prend -1 (aucune carte);
    }
    return nouveau;/// retourne nouveau à l'appelant
}
void initilisationAllegro()
{
   allegro_init();
   install_mouse();
   install_keyboard();
   set_uformat(U_ASCII);

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1200,650,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);
    install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);
}
t_carte* InitilisationCarte(int carte)
{
    t_carte*nouveau;/// pointeur structure t_carte
    nouveau=(t_carte*)malloc(sizeof(t_carte));/// allocation dynamique du pointeur

    if(nouveau==NULL)
    {
        printf("ERREUR allocation\n");
    }
    else
    {
        nouveau->token=carte;
        nouveau->sens=1;
        if(nouveau->token==1||nouveau->token==3||nouveau->token==4)/// carte avec chemin vers le haut
        {
            nouveau->haut=1;
        }
        else
        {
            nouveau->haut=0;
        }
        if(nouveau->token==1||nouveau->token==2||nouveau->token==3||nouveau->token==4)/// carte avec chemin vers la droite
        {
            nouveau->droite=1;
        }
        else
        {
            nouveau->droite=0;
        }
        if(nouveau->token==1||nouveau->token==4)/// carte avec chemin vers le bas
        {
            nouveau->bas=1;
        }
        else
        {
            nouveau->bas=0;
        }
        if(nouveau->token==1||nouveau->token==2||nouveau->token==3||nouveau->token==5)/// carte avec chemin vers la gauche
        {
            nouveau->gauche=1;
        }
        else
        {
            nouveau->gauche=0;
        }
        nouveau->sens=1;
    }
    return nouveau;///rendre le pointeur à l'appelant
}
void CreationJoueurs(t_joueur**listeJoueurs,int nombre,t_pile*Tour)
{
    int saboteur=0; /// compteur du nombre de saboteur(maximum 1 saboteur à chaque manche)
    for(int i=0;i<nombre;i++)
    {
        printf("Joueurs %d\n",i+1);
        allegro_message("Joueur %d",i+1);/// Fenêtre POP UP pour avertir quels joueurs est ce le tour
        listeJoueurs[i]=creation(&saboteur,Tour);/// Appelle programme création d'un joueur
    }
}
t_joueur*creation(int *saboteur,t_pile*Tour)
{
    BITMAP*image;/// Pointeur d'image
    t_joueur*nouveau;/// Pointeur de structure t_joueur
    nouveau=(t_joueur*)malloc(sizeof(t_joueur));/// Allocation dynamique du pointeur nouveau
    char chaine[15];
    BITMAP *logo; ///Pointeur d'image


    nouveau->logo=rand()%(4-1+1)+1; /// Affectation d'un nombre aléatoire entre 1 et 4

    if(nouveau==NULL)
    {
        printf("ERREUR allocation\n");
    }
    else
    {
        printf("Saisir Nom : \n");
        gets(chaine);/// saisie de la chaine
        nouveau->name=ChaineDyn(chaine);/// Saisie du nom du joueur
        nouveau->score=0;/// Initilisation des points
        for(int i=0;i<6;i++)
        {
            nouveau->jeu[i]=Tour->Element[Tour->Hauteur];
            Tour->Hauteur++;
        }
        //nouveau=InitilisationPioche(nouveau);
        nouveau->penalite=-1;
        /// Création du rôle
        if(rand()%(2)==1&&(*saboteur)==0)/// Saboteur
        {
            nouveau->role=22;/// 22 = saboteur
            image=load_bitmap("images/saboteur_carte.bmp",NULL);/// Chargement de la carte correspondant au role
            (*saboteur)=1;
            textprintf_ex(screen,font,555,200,makecol(255,255,255),-1,"SABOTEUR");/// Affichage du rôle
        if(nouveau->logo==1) ///1=logo lion
            {
                logo=load_bitmap("images/lion.bmp",NULL); ///chargement logo lion
                textprintf_ex(screen,font,360,400,makecol(200,170,0),-1,"Votre logo sera le lion. Il vous representera fierement !"); ///petit commentaire sous le logo lion

            }
            else if(nouveau->logo==2) /// 2=logo assassin
            {
                logo=load_bitmap("images/logo2.bmp",NULL); ///chargement logo assassin
                textprintf_ex(screen,font,360,400,makecol(200,0,10),-1,"Votre logo sera l'assassin. Vous serez chirurgical !"); ///petit commentaire sous le logo assassin

            }
            else if(nouveau->logo==3) /// 3=logo espion
            {
                logo=load_bitmap("images/logo3.bmp",NULL); ///chargement logo assassin
                textprintf_ex(screen,font,380,400,makecol(50,200,200),-1,"Votre logo sera l'espion. Personne verra vos coups !"); ///petit commentaire sous le logo espion

            }
            else /// logo ours
            {
                logo=load_bitmap("images/logo4.bmp",NULL); ///chargement logo ours
                textprintf_ex(screen,font,350,400,makecol(150,100,150),-1,"Votre logo sera l'ours. Son instinct vous guidera a la victoire !"); ///petit commentaire sous le logo ours

            }

        }
        else/// Chercheur
        {
            nouveau->role=21;/// 21 = chercheur
            image=load_bitmap("images/chercheur.bmp",NULL);/// Chargement de la carte correspondant au role
            textprintf_ex(screen,font,555,200,makecol(255,255,255),-1,"CHERCHEUR");/// Affichage du rôle
        if(nouveau->logo==1)/// 1=logo lion
            {

                logo=load_bitmap("images/lion.bmp",NULL); ///chargement logo lion
                textprintf_ex(screen,font,360,400,makecol(200,170,0),-1,"Votre logo sera le lion. Il vous representera fierement !"); ///petit commentaire sous le logo lion

            }
            else if(nouveau->logo==2) /// 2=logo assassin
            {
                logo=load_bitmap("images/logo2.bmp",NULL); ///chargement logo assassin
                textprintf_ex(screen,font,360,400,makecol(200,0,10),-1,"Votre logo sera l'assassin. Vous serez chirurgical !"); ///petit commentaire sous le logo assassin

            }
            else if(nouveau->logo==3) /// 3=logo espion
            {

                logo=load_bitmap("images/logo3.bmp",NULL); ///chargement logo assassin
                textprintf_ex(screen,font,380,400,makecol(50,200,200),-1,"Votre logo sera l'espion. Personne verra vos coups !"); ///petit commentaire sous le logo espion

            }
            else/// logo ours
            {

                logo=load_bitmap("images/logo4.bmp",NULL); ///chargement logo ours
                textprintf_ex(screen,font,350,400,makecol(150,100,150),-1,"Votre logo sera l'ours. Son instinct vous guidera a la victoire !"); ///petit commentaire sous le logo ours

            }
        }
        textprintf_ex(screen,font,550,10,makecol(255,255,255),-1,"Role de %s",nouveau->name);/// Affichage du nom
        blit(image,screen,0,0,555,50,image->w,image->h);/// Affichage de la carte correspondant au role
        blit(logo,screen,0,0,555,300,SCREEN_W,SCREEN_H); /// Affichage du logo correspondant
        rest(4000); /// délai de 4 secondes
        clear_bitmap(screen);
    }
    return nouveau;
    //free(nouveau);
    //destroy_bitmap(image);
}
char*ChaineDyn(char chaine[15])
{
    char*info=NULL;
    info=(char*)malloc((strlen(chaine)+1)*sizeof(char));/// alloue l'espace mémoire nécessaire à la chaine de caractère
    if(info!=NULL)
    {
        strcpy(info,chaine);/// Copie la chaine de caractere dans la chaine dynamique
    }
    return info;/// Retourne la chaine dynamique
    //free(info);
}



