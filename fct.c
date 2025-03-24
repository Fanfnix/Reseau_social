#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


void clear() {
    #if __linux__
    system("clear");
    #elif _WIN32
    system("cls");
    #endif
}


Reseau *initReseau() {
    Reseau *reseau = malloc(sizeof(Reseau));
    if (reseau != NULL) {
        reseau->nb_utilisateurs = 0;
        reseau->size = 1;
        reseau->utilisateurs = malloc(sizeof(Utilisateur*));
        if (reseau->utilisateurs == NULL) printf("Erreur allocation liste utilisateurs\n");
    }
    return reseau;
}


void ajouterUtilisteur(Utilisateur *user, Reseau *reseau) {
    if (user == NULL) {
        if (DEBUG) printf("Erreur a l'ajout de %s : user = NULL\n", user->pseudo);
        return;
    }
    reseau->utilisateurs = realloc(reseau->utilisateurs, (reseau->nb_utilisateurs+1) * sizeof(Utilisateur*));
    reseau->utilisateurs[(int)reseau->nb_utilisateurs] = user;
    reseau->nb_utilisateurs++;
    if (DEBUG) printf("Ajout %s avec succes : nb_user = %d\n", reseau->utilisateurs[reseau->nb_utilisateurs-1]->pseudo, reseau->nb_utilisateurs-1);
    return;
}

Utilisateur *creerUtilisateur(int id, char *pseudo) {
    Utilisateur *user = malloc(sizeof(Utilisateur));
    if (user != NULL) {
        user->id = id;
        strcpy(user->pseudo, pseudo);
        user->nb_amis = 0;
        user->amis = malloc(sizeof(Utilisateur*));
        user->post = malloc(sizeof(Post));
        if (DEBUG) printf("%s cree avec succes\n", user->pseudo);
    }
    return user;
}

void nouveauUtilisateur(Reseau *reseau, int compteur_user) {
    char pseudo[20];
    printf("Pseudo pour user-%d : ", compteur_user);
    scanf("%s", &pseudo);
    Utilisateur *user = creerUtilisateur(compteur_user, pseudo);
    ajouterUtilisteur(user, reseau);
}


void afficherUtilisateur(Utilisateur *user) {
    if(user == NULL){
        printf("Utilisateur inexistant\n");
        return;
    }
    printf("+-------------------------------+\n");
    printf("| user-%d : %s", user->id, user->pseudo);
    for (int i = 0; i < (21-strlen(user->pseudo)); i++) printf(" ");
    printf("|\n");
    printf("+-------------------------------+\n");
}

int afficherListeUtilisateurs(Reseau *reseau) {
    for (int i = 0; i < reseau->nb_utilisateurs; i++) afficherUtilisateur(reseau->utilisateurs[i]);
    int choix = 0;
    do {
        printf("Entrez id Utilisateur ou '0' pour quitter : ");
        scanf("%d", &choix);
        if (choix < 0 || choix > reseau->nb_utilisateurs-1) printf("Choix '%d' incorrect\n", choix);
    } while (choix < 0 || choix > reseau->nb_utilisateurs-1);
    
    return choix;
}


void afficherAmis(Utilisateur *user) {
    if(user == NULL){
        printf("Utilisateur inexistant\n");
        return;
    }
    printf("--------------------\n");
    printf("Amis de %s : \n", user->pseudo);
    for(int i = 0; i < user->nb_amis; i++){
        if(user->amis[i] != NULL){
            afficherUtilisateur(user->amis[i]);
            printf("\n--------------------\n");
        }
    }
}

void afficherPost(Utilisateur *user) {
    if(user == NULL){
        printf("Utilisateur inexistant\n");
        return;
    }
    printf("--------------------\n");
    printf("Voici les posts de %s: \n", user->pseudo);
    Post *post = user->post;
    while(post != NULL){
        printf("--------------------\n");
        printf("Post %d : %s\n", post->id, post->contenu);
        post = post->suivant;
        printf("--------------------\n");
    }
}


void ajouterAmi(Utilisateur *user, Utilisateur *ami, Reseau *reseau){
    if(user == NULL || ami == NULL){
        printf("Utilisateur inexistant\n");
        return;
    }
    if (user->amis != NULL) {
        user->amis = realloc(user->amis, (user->nb_amis +1) * sizeof(Utilisateur *));
        for (int i = 1; i <= reseau->nb_utilisateurs; i++) afficherUtilisateur(reseau->utilisateurs[i]);
        printf("Choisissez un ami a ajouter avec son id : \n");
        int id = scanf("%d", &id);
        for (int i = 0; i < reseau->nb_utilisateurs; i++)
        {
            if (id == reseau->utilisateurs[i]->id)
            {
                user->amis[user->nb_amis] = reseau->utilisateurs[i];
                user->nb_amis++;
            }
            else
            {
                printf("Id inexistant\n");
            }
        }
        printf("%s est desormais votre ami, vous avez maintenant %d amis\n",reseau->utilisateurs[*ami->pseudo], user->nb_amis);
        return;
    }
    printf("Erreur ajout amis pour user-%d\n", user->id);
}

void publierPost(Utilisateur *user, char *contenu){
    if(user == NULL){
        printf("Utilisateur inexistant\n");
        return;
    } else {
        if (user->post != NULL) {
            // suite
        }
    }
}