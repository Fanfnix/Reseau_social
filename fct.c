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