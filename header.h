#ifndef AMI_H
#define AMI_H

typedef struct Post{
    int id;
    char contenu[100];
    struct Post *suivant;
}Post;

typedef struct Utilisateur{
    int id;
    char pseudo[20];
    struct Utilisateur **ami;
    struct Post *post;
} Utilisateur;

typedef struct Reseau{
    Utilisateur **utilisateurs;
    int nb_utilisateurs;
} Reseau;

Utilisateur *creerUtilisateur(int id, char *pseudo, Reseau *reseau);

void afficherUtilisateur(Utilisateur *user);
void afficherAmis(Utilisateur *user);
void afficherPost(Utilisateur *user);

void ajouterAmi(Utilisateur *user, Utilisateur *ami);
void puiblierPost(Utilisateur *user, char *contenu);


#endif