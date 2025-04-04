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
        reseau->utilisateurs = malloc(sizeof(Utilisateur*));
        if (reseau->utilisateurs == NULL) printf("Erreur allocation liste utilisateurs\n");
    }
    return reseau;
}


void ajouterUtilisteur(Utilisateur *user, Reseau *reseau) {
    if (user == NULL) {
        if (DEBUG) printf("Erreur a l'ajout de user : user = NULL\n");
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
        user->post = NULL;
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
    tempo();
}


void afficherUtilisateur(Utilisateur *user) {
    if(user == NULL){
        printf("Utilisateur inexistant\n");
        tempo();
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
        if (choix < 0 || choix > reseau->nb_utilisateurs) printf("Choix '%d' incorrect\n", choix);
    } while (choix < 0 || choix > reseau->nb_utilisateurs);
    
    return choix;
}


void menuUtilisateur(Reseau *reseau) {
    int id_user = afficherListeUtilisateurs(reseau);
    if (id_user == 0) return;
    Utilisateur *user = reseau->utilisateurs[id_user-1];
    int run = 1;
    int choix_user;
    do {
        clear();
        printf("---< %s >---\n", user->pseudo);
        do {
            printf("0. Quitter\n");
            printf("1. Ajouter ami\n");
            printf("2. Publier Post\n");
            printf("3. Afficher amis\n");
            printf("4. Afficher post\n");
            printf("5. Supprimer le dernier post\n");
            printf("Choix : ");
            scanf("%d", &choix_user);
            if (choix_user < 0 || choix_user > 5) printf("Choix '%d' est incorrect\n", choix_user);
            printf("----------------\n");
        } while (choix_user < 0 || choix_user > 5);
        switch (choix_user) {
            case 0: run = 0; break;
            case 1: clear(); ajouterAmi(user, reseau); break;
            case 2: clear(); publierPost(user); break;
            case 3: clear(); afficherAmis(user); break;
            case 4: clear(); afficherPost(user); break;
            case 5: clear(); detruirePost(user); break; 
        }
    } while (run);
}


void afficherAmis(Utilisateur *user) {
    if(user == NULL){
        printf("Utilisateur inexistant\n");
        tempo();
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
    tempo();
}


void afficherPost(Utilisateur *user) {
    if(user == NULL){
        printf("Utilisateur inexistant\n");
        tempo();
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
    tempo();
}


void ajouterAmi(Utilisateur *user, Reseau *reseau) {
    if(user == NULL){
        printf("Utilisateur inexistant\n");
        tempo();
        return;
    }
    if (user->amis != NULL) {
        user->amis = realloc(user->amis, (user->nb_amis+1) * sizeof(Utilisateur *));
        Utilisateur *ami;
        do {
            int id_ami = afficherListeUtilisateurs(reseau);
            ami = reseau->utilisateurs[id_ami-1];
        } while (user == ami);
        user->amis[user->nb_amis] = ami;
        user->nb_amis++;
        printf("%s est desormais votre ami, vous avez maintenant %d amis\n",ami->pseudo, user->nb_amis);
        tempo();
        return;
    }
    printf("Erreur ajout amis pour %s\n", user->pseudo);
    tempo();
}


void publierPost(Utilisateur *user) {
    if(user == NULL) {
        printf("Utilisateur inexistant\n");
        tempo();
        return;
    } else {
        if (user->post == NULL) {
            user->post = malloc(sizeof(Post));
            if (user->post != NULL) {
                printf("Contenu :\n");
                getchar();
                fgets(user->post->contenu, 500, stdin);
                user->post->id = 0;
                user->post->suivant = NULL;
            }
        } else {
            Post *post = malloc(sizeof(Post));
            if (post != NULL) {
                printf("Contenu :\n");
                getchar();
                fgets(post->contenu, 500, stdin);
                post->id = user->post->id+1;
                post->suivant = user->post;
                user->post = post;
            }
        }
    }
}


void detruirePost(Utilisateur *user) {
    if(user == NULL) {
        printf("Utilisateur inexistant\n");
        tempo();
        return;
    }
    if(user->post == NULL) {
        printf("Aucun post a supprimer\n");
        tempo();
        return;
    }
    Post *tmp= user->post;
    user->post=user->post->suivant;
    libPost(tmp);
    printf("Dernier post supprime\n");
    tempo();
    return;
}


void libPost(Post *post) {
    if (post == NULL) return;
    Post *post_tmp = post->suivant;
    free(post);
    post = NULL;
    libPost(post_tmp);
}


void libUtilisateur(Utilisateur *user) {
    free(user->amis);
    user->amis = NULL;
    libPost(user->post);
    free(user);
    user = NULL;
}


void libReseau(Reseau *reseau) {
    for (int i = 0; i < reseau->nb_utilisateurs; i++) {
        free(reseau->utilisateurs[i]);
        reseau->utilisateurs[i] = NULL;
    }
    free(reseau);
    reseau = NULL;
}


void tempo(){
    int choix = 1;
    do {
        printf("Entrez '0' pour quitter : ");
        scanf("%d", &choix);
    } while (choix);
}