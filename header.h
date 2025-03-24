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
    int nb_amis;
    struct Utilisateur **ami;
    struct Post *post;
} Utilisateur;

typedef struct Reseau{
    Utilisateur **utilisateurs;
    int nb_utilisateurs;
} Reseau;

void ajouterUtilisteur(Utilisateur *user, Reseau *reseau);
Utilisateur *creerUtilisateur(int id, char *pseudo);

void afficherUtilisateur(Utilisateur *user);
void afficherAmis(Utilisateur *user);
void afficherPost(Utilisateur *user);

void ajouterAmi(Utilisateur *user, Utilisateur *ami, Reseau *reseau);
void puiblierPost(Utilisateur *user, char *contenu);

void detruireUtilisateur(Utilisateur *user);
void detruireAmis(Utilisateur *user);
void detruirePost(Post *post);


#endif