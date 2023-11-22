#include <stdio.h>
#include <ctype.h>
void afficherReglesjeu(){ //ss programme regles du jeu
    printf("Voici les règles du jeu\n""Règles du jeu:\n"
           "Vous devez récupérer les 4 oiseaux dissimulés dans toute la carte pendant un temps imparti de 2 minutes.\n"
           "\n"
           "Les 4 niveaux sont de difficultés croissante. De nouveaux obstacles sont ajoutés au fur et à mesure des niveaux.\n"
           "\n"
           "Une horloge : objet pour figer le temps \n"
           "• Des objets symbolisant l'invincibilité\n"
           "• Des blocs qu'on peut pousser d'une case à chaque fois\n"
           "• Des blocs qu'on peut casser\n"
           "• Des blocs qui disparaissent et réapparaissent à intervalle de temps régulier\n"
           "• Des flèches \"bloc mobile\" qu'on pousse une fois et qui se déplacent dans le sens de la flèche\n"
           "jusqu'à un obstacle quelconque");

}
void NouvellePartie(){ // sous programme lancement nvlle partie
    printf("Lancement d'une nouvelle partie...\n");
}
void ChargerPartie(){// sp Charger partie
    printf("Chargement d'une partie existante...\n");
}
void lancerNiveauAvecMotDePasse() {// mdp pour acces niveau
    printf("Entrez le mot de passe du niveau : \n");
    char motDePasse[50];
    scanf("%s", motDePasse);
    printf("Niveau lancé avec le mot de passe : %s\n", motDePasse);
}
void score (){//score joueur
    printf("Votre score est de: %f\n ",score);
}
int main() {//programme principal
    int choix;
    do {//affichage du menu
        printf("1. Règles du jeu\n");
        printf("2. Lancer un nouveau Jeu à partir du niveau 1\n");
        printf("3. Charger une partie\n");
        printf("4. Lancer directement un niveau via son Mot de passe\n");
        printf("5. Score\n");
        printf("6. Quitter\n");
        printf("Veuillez choisir une option.");
        scanf("%d", &choix);

        switch (choix) {// choix de l'option du menu
            case 1:
                afficherReglesjeu();
                break;
            case 2:
                NouvellePartie();
                break;
            case 3:
                ChargerPartie();
                break;
            case 4:
                lancerNiveauAvecMotDePasse();
                break;
            case 5:
                score();
                break;
            case 6:
                printf("Fermeture du jeu...\n");
                break;
            default:
                if (!isalpha(choix)) {
                    printf("Saisie incorrecte, veuillez réessayer. \n");
                }
                else {
                    printf("Saisie incorrecte, veuillez entrer un entier. \n");
                }
                while (getchar() != '\n');

        }
    }

    while(choix!=6);


    return 0;
}

