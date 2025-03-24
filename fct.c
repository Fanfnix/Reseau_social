#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void ajouterUtilisteur(Utilisateur *user, Reseau *reseau) {
    if (user == NULL) {
        printf("Erreur a l'ajout de user-%d : user = NULL\n", user->id);
        return;
    }
    reseau->utilisateurs = realloc(reseau->utilisateurs, (reseau->nb_utilisateurs+1) * sizeof(Utilisateur*));
    reseau->utilisateurs[(int)reseau->nb_utilisateurs] = user;
    reseau->nb_utilisateurs++;
    printf("Ajout user-%d avec succes : nb_user = %d\n", reseau->utilisateurs[reseau->nb_utilisateurs-1]->id, reseau->nb_utilisateurs-1);
    return;
}

Utilisateur *creerUtilisateur(int id, char *pseudo) {
    Utilisateur *user = malloc(sizeof(Utilisateur));
    if (user != NULL) {
        user->id = id;
        strcpy(user->pseudo, pseudo);
        printf("user-%d cree avec succes\n", user->id);
    }
    return user;
}

void afficherUtilisateur(Utilisateur *user){
    
    if(user == NULL){
        printf("Utilisateur inexistant\n");
        return;
    }

    printf("--------------------\n");
    printf("Pseudo : %s\nId : %d", user->pseudo, user->id);
    printf("--------------------\n");
}

void afficherAmis(Utilisateur *user){
    
    if(user == NULL){
        printf("Utilisateur inexistant\n");
        return;
    }
    printf("--------------------\n");
    printf("Amis de %s : \n", user->pseudo);
    for(int i = 0; i < user->nb_amis; i++){
        if(user->ami[i] != NULL){
            afficherUtilisateur(user->ami[i]);
            printf("\n--------------------\n");
        }
    }
}

void afficherPost(Utilisateur *user){
    
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
    if(user->nb_amis == 0){
        user->ami = malloc(sizeof(Utilisateur *));
    }else{
        user->ami = realloc(user->ami, (user->nb_amis +1) * sizeof(Utilisateur *));
    }
    for (int i = 1; i <= reseau->nb_utilisateurs; i++)
    {
        afficherUtilisateur(reseau->utilisateurs[i]);
    }
    printf("Choisissez un ami a ajouter avec son id : \n");
    int id = scanf("%d", &id);
    for (int i = 0; i < reseau->nb_utilisateurs; i++)
    {
        if (id == reseau->utilisateurs[i]->id)
        {
            user->ami = reseau->utilisateurs[i];
            user->nb_amis++;
        }
        else
        {
            printf("Id inexistant\n");
        }
    }
    printf("%s est desormais votre ami, vous avez maintenant %d amis\n",reseau->utilisateurs[*ami->pseudo], user->nb_amis);
}

void publierPost(Utilisateur *user, char *contenu){
    
    if(user == NULL){
        printf("Utilisateur inexistant\n");
        return;
    }
    if(user->post == NULL){
        user->post = malloc(sizeof(Post));
    }
    else{
        user->post = realloc(user->post+1, sizeof(Post));
    }

    
}