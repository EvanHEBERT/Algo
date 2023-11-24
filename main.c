#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define colonnes 20
#define lignes 10

struct niveau {
    char matrix[lignes][colonnes];
    int snoopyX;
    int snoopyY;
    int blocPousse;  // Nouvelle variable pour indiquer si le bloc a été poussé
    int oiseauxRecuperes;
};


struct Joueur {
    char nom[40];
    int score;
    int vies;
};

struct Balle {
    int x;
    int y;
    int vx;
    int vy;
};

// Fonction pour afficher le niveau
void displayLevel(struct niveau *niveau, struct Balle *balle) {
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            printf("+---");
        }
        printf("+\n");

        for (int j = 0; j < colonnes; j++) {
            if (i == balle->y && j == balle->x) {
                printf("| B ");
            } else {
                printf("| %c ", niveau->matrix[i][j]);
            }
        }
        printf("|\n");
    }

    for (int j = 0; j < colonnes; j++) {
        printf("+---");
    }
    printf("+\n");
}

// Fonction pour déplacer la balle
void moveBall(struct Balle *balle, struct niveau *niveau, struct Joueur *joueur) {
    niveau->matrix[balle->y][balle->x] = ' ';

    balle->x += balle->vx;
    balle->y += balle->vy;

    if (balle->x < 0 || balle->x >= colonnes || balle->y < 0 || balle->y >= lignes) {
        balle->x = 1;
        balle->y = 1;

        joueur->vies--;

        if (joueur->vies <= 0) {
            printf("Snoopy a épuisé toutes ses vies. Fin du jeu!\n");
            exit(0);
        }
    }
}

/// Fonction pour récupérer un oiseau si Snoopy est sur une case avec un oiseau
void recupererOiseau(struct niveau *niveau, struct Joueur *joueur, int temps_restant) {
    if (niveau->matrix[niveau->snoopyY][niveau->snoopyX] == 'O') {
        // Vérifier si l'oiseau n'a pas déjà été récupéré
        if (niveau->matrix[niveau->snoopyY][niveau->snoopyX] != 'X') {
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'X'; // Marquer l'oiseau comme récupéré
            niveau->oiseauxRecuperes++;  // Incrémenter le compteur d'oiseaux récupérés

            if (niveau->oiseauxRecuperes == 4) {
                joueur->score += (temps_restant * 100); // Score basé sur le temps restant après avoir récupéré les 4 oiseaux
                niveau->oiseauxRecuperes = 0;  // Réinitialiser le compteur d'oiseaux récupérés
            }
        }
    }
}



// Fonction pour déplacer Snoopy vers le haut
void bougerhaut(struct niveau *niveau, struct Joueur *joueur, int distance) {
    for (int i = 0; i < distance; i++) {
        if (niveau->snoopyY > 0 && niveau->matrix[niveau->snoopyY - 1][niveau->snoopyX] == 'C') {
            niveau->matrix[niveau->snoopyY - 1][niveau->snoopyX] = ' ';
            joueur->score += 10;
        } else if (niveau->snoopyY > 0 && niveau->matrix[niveau->snoopyY - 1][niveau->snoopyX] == 'O') {
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
            niveau->snoopyY -= 1;
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'S';
        } else if (niveau->snoopyY > 0 && niveau->matrix[niveau->snoopyY - 1][niveau->snoopyX] == ' ') {
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
            niveau->snoopyY -= 1;
            if (niveau->matrix[niveau->snoopyY][niveau->snoopyX] != 'C') {
                niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'S';
            }
        } else {
            printf("Déplacement vers le haut impossible.\n");
            break;
        }
    }
}

// Fonction pour déplacer Snoopy vers le bas
void bougerbas(struct niveau *niveau, struct Joueur *joueur, int distance) {
    for (int i = 0; i < distance; i++) {
        if (niveau->snoopyY < lignes - 1 && niveau->matrix[niveau->snoopyY + 1][niveau->snoopyX] == 'C') {
            niveau->matrix[niveau->snoopyY + 1][niveau->snoopyX] = ' ';
            joueur->score += 10;
        } else if (niveau->snoopyY < lignes - 1 && niveau->matrix[niveau->snoopyY + 1][niveau->snoopyX] == 'O') {
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
            niveau->snoopyY += 1;
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'S';
        } else if (niveau->snoopyY < lignes - 1 && niveau->matrix[niveau->snoopyY + 1][niveau->snoopyX] == ' ') {
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
            niveau->snoopyY += 1;
            if (niveau->matrix[niveau->snoopyY][niveau->snoopyX] != 'C') {
                niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'S';
            }
        } else {
            printf("Déplacement vers le bas impossible.\n");
            break;
        }
    }
}


// Fonction pour déplacer Snoopy vers la gauche
void bougergauche(struct niveau *niveau, struct Joueur *joueur, int distance) {
    for (int i = 0; i < distance; i++) {
        if (niveau->snoopyX > 0 && niveau->matrix[niveau->snoopyY][niveau->snoopyX - 1] == 'C') {
            niveau->matrix[niveau->snoopyY][niveau->snoopyX - 1] = ' ';
            joueur->score += 10;
        } else if (niveau->snoopyX > 0 && niveau->matrix[niveau->snoopyY][niveau->snoopyX - 1] == 'O') {
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
            niveau->snoopyX -= 1;
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'S';
        } else if (niveau->snoopyX > 0 && niveau->matrix[niveau->snoopyY][niveau->snoopyX - 1] == ' ') {
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
            niveau->snoopyX -= 1;
            if (niveau->matrix[niveau->snoopyY][niveau->snoopyX] != 'C') {
                niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'S';
            }
        } else if (niveau->snoopyX > 1 && niveau->matrix[niveau->snoopyY][niveau->snoopyX - 1] == '<') {
            if (niveau->blocPousse == 0) {
                niveau->matrix[niveau->snoopyY][niveau->snoopyX - 1] = ' ';
                niveau->matrix[niveau->snoopyY][niveau->snoopyX - 2] = '<';
                joueur->score += 5;
                niveau->blocPousse = 1;  // Marquer le bloc comme poussé
            } else {
                printf("Le bloc a déjà été poussé.\n");
                break;
            }
        } else {
            printf("Déplacement vers la gauche impossible.\n");
            break;
        }
    }
}

// Fonction pour déplacer Snoopy vers la droite
void bougerdroite(struct niveau *niveau, struct Joueur *joueur, int distance) {
    for (int i = 0; i < distance; i++) {
        if (niveau->snoopyX < colonnes - 1 && niveau->matrix[niveau->snoopyY][niveau->snoopyX + 1] == 'C') {
            niveau->matrix[niveau->snoopyY][niveau->snoopyX + 1] = ' ';
            joueur->score += 10;
        } else if (niveau->snoopyX < colonnes - 1 && niveau->matrix[niveau->snoopyY][niveau->snoopyX + 1] == 'O') {
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
            niveau->snoopyX += 1;
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'S';
        } else if (niveau->snoopyX < colonnes - 1 && niveau->matrix[niveau->snoopyY][niveau->snoopyX + 1] == ' ') {
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
            niveau->snoopyX += 1;
            if (niveau->matrix[niveau->snoopyY][niveau->snoopyX] != 'C') {
                niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'S';
            }
        } else if (niveau->snoopyX < colonnes - 2 && niveau->matrix[niveau->snoopyY][niveau->snoopyX + 1] == '>') {
            if (niveau->blocPousse == 0) {
                niveau->matrix[niveau->snoopyY][niveau->snoopyX + 1] = ' ';
                niveau->matrix[niveau->snoopyY][niveau->snoopyX + 2] = '>';
                joueur->score += 5;
                niveau->blocPousse = 1;  // Marquer le bloc comme poussé
            } else {
                printf("Le bloc a déjà été poussé.\n");
                break;
            }
        } else {
            printf("Déplacement vers la droite impossible.\n");
            break;
        }
    }
}






void casserBlocC(struct niveau *niveau, struct Joueur *joueur) {
    if (niveau->matrix[niveau->snoopyY][niveau->snoopyX] == 'C') {
        niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
        joueur->score += 10;
    } else if (niveau->snoopyX > 0 && niveau->matrix[niveau->snoopyY][niveau->snoopyX - 1] == 'C') {
        niveau->matrix[niveau->snoopyY][niveau->snoopyX - 1] = ' ';
        joueur->score += 10;
    } else if (niveau->snoopyX < colonnes - 1 && niveau->matrix[niveau->snoopyY][niveau->snoopyX + 1] == 'C') {
        niveau->matrix[niveau->snoopyY][niveau->snoopyX + 1] = ' ';
        joueur->score += 10;
    } else {
        printf("Aucun bloc 'C' à casser à côté de Snoopy.\n");
  }
}



int main() {
    time_t debut = time(NULL);
    int duree = 120;
    struct Joueur joueur;
    strcpy(joueur.nom, "Joueur1");
    joueur.score = 0;
    joueur.vies = 3;

    printf("Niveau 2\n");
    struct niveau niveau2 = {
            {{'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'C', ' ', ' ', ' ', 'O'},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '>', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', '<', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'C', ' ', ' ', ' ', ' ', 'O'}},
            10,
            5,
             0,
             0}; // Initialisation de la variable blocPousse


    struct Balle balle = {1, 1, 1, 1};

    int distanceDeplacement = 1;

    while (1) {
        time_t tempsinstant = time(NULL);
        double tempsecoule = difftime(tempsinstant, debut);

        if (tempsecoule >= duree) {
            printf("Le temps est écoulé. Fin du jeu!\n");
            break;
        } else {
            int temps_restant = duree - (int)tempsecoule;
            printf("Temps restant : %d secondes\n", temps_restant);

            printf("Nom du joueur: %s\n Score: %d\n Vies: %d\n", joueur.nom, joueur.score, joueur.vies);

            displayLevel(&niveau2, &balle);

            moveBall(&balle, &niveau2, &joueur);

            char direction;
            printf("Appuyez sur H,B,G,D (Haut, Bas , Gauche , Droite ) pour bouger et sur  'C' pour casser : ");
            direction = getchar();
            while (getchar() != '\n');

            switch (direction) {
                case 'q':
                    printf("Fin du jeu.\n");
                    return 0;
                case 'h':
                    bougerhaut(&niveau2, &joueur, distanceDeplacement);
                    break;
                case 'b':
                    bougerbas(&niveau2, &joueur, distanceDeplacement);
                    break;
                case 'g':
                    bougergauche(&niveau2, &joueur, distanceDeplacement);
                    break;
                case 'd':
                    bougerdroite(&niveau2, &joueur, distanceDeplacement);
                    break;
                case 'c':
                    casserBlocC(&niveau2, &joueur);
                    break;
                default:
                    printf("Commande non reconnue.\n");
            }

            recupererOiseau(&niveau2, &joueur,temps_restant); // Récupérer un oiseau après le déplacement de Snoopy

            sleep(1);
        }
    }

    return 0;
}

