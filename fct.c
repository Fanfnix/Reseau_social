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


void menuUtilisateur(Reseau *reseau) {
    int id_user = afficherListeUtilisateurs(reseau);
    Utilisateur *user = reseau->utilisateurs[id_user];
    int run = 1;
    int choix_user;
    do {
        clear();
        printf("---< RESEAU >---\n");
        do {
            printf("0. Quitter\n");
            printf("1. Ajouter ami\n");
            printf("2. Publier Post\n");
            printf("3. Afficher amis\n");
            printf("4. Afficher post\n");
            printf("Choix : ");
            scanf("%d", &choix_user);
            if (choix_user < 0 || choix_user > 4) printf("Choix '%d' est incorrect\n", choix_user);
            printf("----------------\n");
        } while (choix_user < 0 || choix_user > 4);
        switch (choix_user) {
            case 0: run = 0; break;
            case 1: clear(); ajouterAmi(user, ami, reseau); break; // On demandera ami dans la fonction ajouterAmi
            case 2: clear(); publierPost(user); break;
            case 3: clear(); afficherAmis(user); break;
            case 4: clear(); afficherPost(user); break;
        }
    } while (run);
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
    int choix = 1;
    do {
        printf("Entrez '0' pour quitter : ");
        scanf("%d", &choix);
    } while (choix);
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
    int choix;
    do {
        printf("Entrez '0' pour quitter : ");
        scanf("%d", &choix);
    } while (choix);
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

void publierPost(Utilisateur *user) {
    if(user == NULL) {
        printf("Utilisateur inexistant\n");
        return;
    } else {
        if (user->post != NULL) {
            Post *post = malloc(sizeof(Post));
            if (post != NULL) {
                printf("Contenu :\n");
                scanf("%s", &post->contenu);
                post->suivant = user->post;
                user->post = post;
            }
        }
    }
}