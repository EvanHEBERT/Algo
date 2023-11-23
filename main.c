
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
//variables globales
#define colonnes 20
#define lignes 10
//structure niveau
struct niveau {
    char matrix[lignes][colonnes];
};
struct Joueur{
    char nom[40];
    int score;
};
//ss programme affichage du niveau
void displayLevel(struct niveau *niveau) {
    for (int i = 0; i < lignes; i++) {
        //lignes
        for (int j = 0; j < colonnes; j++) {
            printf("+---");//separation des cases
        }
        printf("+\n");

        for (int j = 0; j < colonnes; j++) {
            printf("| %c ", niveau-> matrix[i][j]);
        }
        printf("|\n");
    }

    for (int j = 0; j < colonnes; j++) {
        printf("+---");
    }
    printf("+\n");
}
// Fonction pour déplacer Snoopy vers le haut
void bougerhaut(struct niveau *niveau, int *snoopyX, int *snoopyY) {
    if (*snoopyY > 0 && niveau->matrix[*snoopyY - 1][*snoopyX] != 'obstacle') {
        // Le déplacement vers le haut est possible
        niveau->matrix[*snoopyY][*snoopyX] = ' '; // Efface la position actuelle de Snoopy
        *snoopyY -= 1; // Déplace Snoopy vers le haut
        niveau->matrix[*snoopyY][*snoopyX] = 'S'; // Met à jour la nouvelle position de Snoopy
    } else {
        // Le déplacement vers le haut n'est pas possible, affichez un message ou ne faites rien
        printf("Déplacement vers le haut impossible.\n");
    }
}

// Fonction pour déplacer Snoopy vers le bas (similaire aux autres fonctions de déplacement)
void bougerbas(struct niveau *niveau, int *snoopyX, int *snoopyY) {
    if (*snoopyY < lignes - 1 && niveau->matrix[*snoopyY + 1][*snoopyX] != 'obstacle') {
        niveau->matrix[*snoopyY][*snoopyX] = ' ';
        *snoopyY += 1;
        niveau->matrix[*snoopyY][*snoopyX] = 'S';
    } else {
        printf("Déplacement vers le bas impossible.\n");
    }
}

// Fonction pour déplacer Snoopy vers la gauche (similaire aux autres fonctions de déplacement)
void bougergauche(struct niveau *niveau, int *snoopyX, int *snoopyY) {
    if (*snoopyX > 0 && niveau->matrix[*snoopyY][*snoopyX - 1] != 'obstacle') {
        niveau->matrix[*snoopyY][*snoopyX] = ' ';
        *snoopyX -= 1;
        niveau->matrix[*snoopyY][*snoopyX] = 'S';
    } else {
        printf("Déplacement vers la gauche impossible.\n");
    }
}

// Fonction pour déplacer Snoopy vers la droite (similaire aux autres fonctions de déplacement)
void bougerdroite(struct niveau *niveau, int *snoopyX, int *snoopyY) {
    if (*snoopyX < colonnes - 1 && niveau->matrix[*snoopyY][*snoopyX + 1] != 'obstacle') {
        niveau->matrix[*snoopyY][*snoopyX] = ' ';
        *snoopyX += 1;
        niveau->matrix[*snoopyY][*snoopyX] = 'S';
    } else {
        printf("Déplacement vers la droite impossible.\n");
    }
}

int main (){
    //Temps initial
    time_t debut= time(NULL);
    //duree de la partie en secondes
    int duree=120; //2min
    // Déclaration et initialisation d'un joueur
    struct Joueur joueur;
    strcpy(joueur.nom, "Joueur1");  // Nom du joueur
    joueur.score = 0;  // Score initial

    printf("Niveau 2\n");
    // Position initiale de Snoopy
    int snoopyX = 10;
    int snoopyY = 5;

    while(1){
    //MESURE DU TEMPS ECOULE
    time_t tempsinstant= time(NULL);
    double tempsecoule= difftime(tempsinstant,debut);
    //verifier si le temps est ecoulé
        if (tempsecoule >= duree) {
            printf("Le temps est écoulé. Fin du jeu!\n");
            break;
        }
        else{
            printf("Nom du joueur: %s\n Score: %d\n", joueur.nom, joueur.score);

            struct niveau niveau2 = {
                    {
                            {'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'C', ' ', ' ', ' ', 'O'},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'S', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'D', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', 'D', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'C', ' ', ' ', ' ', ' ', 'O'},
                    }
            };
            // Affichage du niveau
            displayLevel(&niveau2);

            sleep(1);


        } return 0;
    }
}






