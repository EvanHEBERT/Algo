#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define colonnes 20
#define lignes 10

struct niveau {
    char matrix[lignes][colonnes];
    int snoopyX;
    int snoopyY;
};

struct Joueur {
    char nom[40];
    int score;
};

struct Balle {
    int x;
    int y;
    int vx; // Vitesse horizontale
    int vy; // Vitesse verticale
};

void displayLevel(struct niveau *niveau) {
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            printf("+---");
        }
        printf("+\n");

        for (int j = 0; j < colonnes; j++) {
            printf("| %c ", niveau->matrix[i][j]);
        }
        printf("|\n");
    }

    for (int j = 0; j < colonnes; j++) {
        printf("+---");
    }
    printf("+\n");
}

void moveBall(struct Balle *balle, struct niveau *niveau) {
    niveau->matrix[balle->y][balle->x] = ' ';  // Efface la position actuelle de la balle

    balle->x += balle->vx;
    balle->y += balle->vy;

    // Vérifie les limites du niveau
    if (balle->x < 0 || balle->x >= colonnes || balle->y < 0 || balle->y >= lignes) {
        // Réinitialise la position de la balle si elle est sortie du niveau
        balle->x = 1;
        balle->y = 1;
    }

    // Affiche la balle à sa nouvelle position
    niveau->matrix[balle->y][balle->x] = 'B';
}

// Fonction pour déplacer Snoopy vers le haut
void bougerhaut(struct niveau *niveau, struct Joueur *joueur) {
    if (niveau->snoopyY > 0) {
        if (niveau->matrix[niveau->snoopyY - 1][niveau->snoopyX] == ' ') {
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
            niveau->snoopyY -= 1;
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'S';
        } else if (niveau->matrix[niveau->snoopyY - 1][niveau->snoopyX] == 'O') {
            joueur->score += 10;
            printf("Oiseau collecté! Score: %d\n", joueur->score);
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' '; // Mettez à jour la case actuelle avec un espace
            niveau->snoopyY -= 1;
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'S';
        } else {
            printf("Déplacement vers le haut impossible.\n");
        }
    } else {
        printf("Déplacement vers le haut impossible.\n");
    }
}

// Fonction pour déplacer Snoopy vers le bas
void bougerbas(struct niveau *niveau, struct Joueur *joueur) {
    if (niveau->snoopyY < lignes - 1) {
        if (niveau->matrix[niveau->snoopyY + 1][niveau->snoopyX] == ' ') {
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
            niveau->snoopyY += 1;
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'S';
        } else if (niveau->matrix[niveau->snoopyY + 1][niveau->snoopyX] == 'O') {
            joueur->score += 10;
            printf("Oiseau collecté! Score: %d\n", joueur->score);
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' '; // Mettez à jour la case actuelle avec un espace
            niveau->snoopyY += 1;
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'S';
        } else {
            printf("Déplacement vers le bas impossible.\n");
        }
    } else {
        printf("Déplacement vers le bas impossible.\n");
    }
}

// Fonction pour déplacer Snoopy vers la gauche
void bougergauche(struct niveau *niveau, struct Joueur *joueur) {
    if (niveau->snoopyX > 0) {
        if (niveau->matrix[niveau->snoopyY][niveau->snoopyX - 1] == ' ') {
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
            niveau->snoopyX -= 1;
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'S';
        } else if (niveau->matrix[niveau->snoopyY][niveau->snoopyX - 1] == 'O') {
            joueur->score += 10;
            printf("Oiseau collecté! Score: %d\n", joueur->score);
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' '; // Mettez à jour la case actuelle avec un espace
            niveau->snoopyX -= 1;
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'S';
        } else {
            printf("Déplacement vers la gauche impossible.\n");
        }
    } else {
        printf("Déplacement vers la gauche impossible.\n");
    }
}

// Fonction pour déplacer Snoopy vers la droite
void bougerdroite(struct niveau *niveau, struct Joueur *joueur) {
    if (niveau->snoopyX < colonnes - 1) {
        if (niveau->matrix[niveau->snoopyY][niveau->snoopyX + 1] == ' ') {
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
            niveau->snoopyX += 1;
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'S';
        } else if (niveau->matrix[niveau->snoopyY][niveau->snoopyX + 1] == 'O') {
            joueur->score += 10;
            printf("Oiseau collecté! Score: %d\n", joueur->score);
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' '; // Mettez à jour la case actuelle avec un espace
            niveau->snoopyX += 1;
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'S';
        } else {
            printf("Déplacement vers la droite impossible.\n");
        }
    } else {
        printf("Déplacement vers la droite impossible.\n");
    }
}





int main() {
    time_t debut = time(NULL);
    int duree = 120;
    struct Joueur joueur;
    strcpy(joueur.nom, "Joueur1");
    joueur.score = 0;

    printf("Niveau 2\n");
    struct niveau niveau2 = {
            {{'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'C', ' ', ' ', ' ', 'O'},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'D', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', 'D', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'C', ' ', ' ', ' ', ' ', 'O'}},
            10,
            5};

    struct Balle balle = {1, 1, 1, 1}; // Position et vitesse initiales de la balle

    while (1) {
        time_t tempsinstant = time(NULL);
        double tempsecoule = difftime(tempsinstant, debut);

        if (tempsecoule >= duree) {
            printf("Le temps est écoulé. Fin du jeu!\n");
            break;
        } else {
            printf("Nom du joueur: %s\n Score: %d\n", joueur.nom, joueur.score);

            // Affichage du niveau
            displayLevel(&niveau2);

            // Affichage de la balle
            moveBall(&balle, &niveau2);

            // Déplacement du personnage avec les flèches
            char direction;
            printf("Déplacez Snoopy avec h,b,g,d (haut, bas, gauche, droite), ou 'q' pour quitter : ");
            direction = getchar();
            while (getchar() != '\n');  // Pour consommer les caractères restants dans le buffer

            switch (direction) {
                case 'q':
                    printf("Fin du jeu.\n");
                    return 0;
                case 'h':
                    bougerhaut(&niveau2, &joueur);
                    break;
                case 'b':
                    bougerbas(&niveau2, &joueur);
                    break;
                case 'g':
                    bougergauche(&niveau2, &joueur);
                    break;
                case 'd':
                    bougerdroite(&niveau2, &joueur);
                    break;
                default:
                    printf("Commande non reconnue.\n");
            }

            sleep(1);
        }
    }

    return 0;
}
