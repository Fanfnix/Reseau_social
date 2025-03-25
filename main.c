#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main() {

    Reseau *reseau = initReseau();
    if (reseau == NULL) {
        printf("Erreur création reseau\n");
        return 0;
    }

    int compteur_user = 1;
    for (compteur_user; compteur_user < 5; compteur_user++) {
        char pseudo[20]; sprintf(pseudo, "Michel%d", compteur_user);
        Utilisateur *user = creerUtilisateur(compteur_user, pseudo);
        ajouterUtilisteur(user, reseau);
    }

    int run = 1;
    int choix_principale;
    do {
        clear();
        printf("---< RESEAU >---\n");
        do {
            printf("0. Quitter\n");
            printf("1. Creer Utilisateur\n");
            printf("2. Afficher liste utilisateur\n");
            printf("3. Aller sur un utilisateur\n");
            printf("Choix : ");
            scanf("%d", &choix_principale);
            if (choix_principale < 0 || choix_principale > 3) printf("Choix '%d' est incorrect\n", choix_principale);
            printf("----------------\n");
        } while (choix_principale < 0 || choix_principale > 3);
        switch (choix_principale) {
            case 0: run = 0; break;
            case 1: clear(); nouveauUtilisateur(reseau, compteur_user); compteur_user++; break;
            case 2: clear(); afficherListeUtilisateurs(reseau); break;
            case 3: clear(); menuUtilisateur(reseau); break;
        }
    } while (run);

    libReseau(reseau);

    return 0;
}