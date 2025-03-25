#ifndef AMI_H
#define AMI_H

#define DEBUG 0

typedef struct Post {
    int id;
    char contenu[500];
    struct Post *suivant;
} Post;

typedef struct Utilisateur {
    int id;
    char pseudo[20];
    int nb_amis;
    struct Utilisateur **amis;
    struct Post *post;
} Utilisateur;

typedef struct Reseau {
    Utilisateur **utilisateurs;
    int nb_utilisateurs;
} Reseau;

void clear();

Reseau *initReseau();

void ajouterUtilisteur(Utilisateur *user, Reseau *reseau);
Utilisateur *creerUtilisateur(int id, char *pseudo);
void nouveauUtilisateur(Reseau *reseau, int compteur_user);

void afficherUtilisateur(Utilisateur *user);
int afficherListeUtilisateurs(Reseau *reseau);

void menuUtilisateur(Reseau *reseau);

void afficherAmis(Utilisateur *user);
void afficherPost(Utilisateur *user);

void ajouterAmi(Utilisateur *user, Reseau *reseau);
void publierPost(Utilisateur *user);

void detruirePost(Utilisateur *user);

void libUtilisateur(Utilisateur *user);
void libReseau(Reseau *reseau);
void libPost(Post *post);

void tempo();

#endif