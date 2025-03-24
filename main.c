#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main() {

    Reseau *reseau = malloc(sizeof(Reseau));
    reseau->nb_utilisateurs = 0;
    reseau->utilisateurs = malloc(sizeof(Utilisateur*));
    if (reseau->utilisateurs == NULL) {
        printf("Erreur allocation liste utilisateurs\n");
        return 0;
    }

    for (int i = 0; i < 5; i++) {
        Utilisateur *user = creerUtilisateur(i, "root");
        ajouterUtilisteur(user, reseau);
    }

    Utilisateur *user_tmp;
    for (int i = 0; i < reseau->nb_utilisateurs; i++) {
        user_tmp = reseau->utilisateurs[i];
        printf("USER : id=%d, pseudo=%s\n", user_tmp->id, user_tmp->pseudo);
    }

    return 0;
}