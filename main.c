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
    // Restaurer la case où se trouvait la balle
    niveau->matrix[balle->y][balle->x] = ' ';

    // Déplacer la balle
    balle->x += balle->vx;
    balle->y += balle->vy;

    // Vérifier les limites du niveau
    if (balle->x < 0 || balle->x >= colonnes || balle->y < 0 || balle->y >= lignes) {
        // La balle est sortie du niveau, réinitialiser sa position
        balle->x = 1;
        balle->y = 1;
    }
}

// Fonction pour déplacer Snoopy vers le haut
void bougerhaut(struct niveau *niveau, struct Joueur *joueur, int distance) {
    for (int i = 0; i < distance; i++) {
        if (niveau->snoopyY > 0 && niveau->matrix[niveau->snoopyY - 1][niveau->snoopyX] == 'C') {
            // Casser le bloc 'C' en déplaçant Snoopy vers le haut
            niveau->matrix[niveau->snoopyY - 1][niveau->snoopyX] = ' ';
            joueur->score += 10; // Augmenter le score lorsque le bloc est cassé
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
            // Casser le bloc 'C' en déplaçant Snoopy vers le bas
            niveau->matrix[niveau->snoopyY + 1][niveau->snoopyX] = ' ';
            joueur->score += 10; // Augmenter le score lorsque le bloc est cassé
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
            // Casser le bloc 'C' en déplaçant Snoopy vers la gauche
            niveau->matrix[niveau->snoopyY][niveau->snoopyX - 1] = ' ';
            joueur->score += 10; // Augmenter le score lorsque le bloc est cassé
        } else if (niveau->snoopyX > 0 && niveau->matrix[niveau->snoopyY][niveau->snoopyX - 1] == ' ') {
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
            niveau->snoopyX -= 1;
            if (niveau->matrix[niveau->snoopyY][niveau->snoopyX] != 'C') {
                niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'S';
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
            // Casser le bloc 'C' en déplaçant Snoopy vers la droite
            niveau->matrix[niveau->snoopyY][niveau->snoopyX + 1] = ' ';
            joueur->score += 10; // Augmenter le score lorsque le bloc est cassé
        } else if (niveau->snoopyX < colonnes - 1 && niveau->matrix[niveau->snoopyY][niveau->snoopyX + 1] == ' ') {
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
            niveau->snoopyX += 1;
            if (niveau->matrix[niveau->snoopyY][niveau->snoopyX] != 'C') {
                niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'S';
            }
        } else {
            printf("Déplacement vers la droite impossible.\n");
            break;
        }
    }
}

// Fonction pour casser le bloc 'C' en étant à côté
void casserBlocC(struct niveau *niveau, struct Joueur *joueur) {
    if (niveau->matrix[niveau->snoopyY][niveau->snoopyX] == 'C') {
        niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
        joueur->score += 10; // Augmenter le score lorsque le bloc est cassé
    } else if (niveau->snoopyX > 0 && niveau->matrix[niveau->snoopyY][niveau->snoopyX - 1] == 'C') {
        niveau->matrix[niveau->snoopyY][niveau->snoopyX - 1] = ' ';
        joueur->score += 10; // Augmenter le score lorsque le bloc est cassé
    } else if (niveau->snoopyX < colonnes - 1 && niveau->matrix[niveau->snoopyY][niveau->snoopyX + 1] == 'C') {
        niveau->matrix[niveau->snoopyY][niveau->snoopyX + 1] = ' ';
        joueur->score += 10; // Augmenter le score lorsque le bloc est cassé
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

    int distanceDeplacement = 1; // Distance de déplacement par défaut

    while (1) {
        time_t tempsinstant = time(NULL);
        double tempsecoule = difftime(tempsinstant, debut);

        if (tempsecoule >= duree) {
            printf("Le temps est écoulé. Fin du jeu!\n");
            break;
        } else {
            // Affichage du décompte
            int temps_restant = duree - (int)tempsecoule;
            printf("Temps restant : %d secondes\n", temps_restant);

            printf("Nom du joueur: %s\n Score: %d\n", joueur.nom, joueur.score);

            // Affichage du niveau
            displayLevel(&niveau2);

            // Affichage de la balle
            niveau2.matrix[balle.y][balle.x] = 'B';

            // Mouvement de la balle
            moveBall(&balle, &niveau2);

            // Déplacement du personnage avec la touche 'C'
            char direction;
            printf("Appuyez sur H,B,G,D (Haut, Bas , Gauche , Droite ) pour bouger et sur  'C' pour casser : ");
            direction = getchar();
            while (getchar() != '\n'); // Pour consommer les caractères restants dans le buffer

            // Gestion du déplacement en fonction de la distanceDeplacement
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
                    // Casser le bloc 'C' si Snoopy est devant ou à côté
                    casserBlocC(&niveau2, &joueur);
                    break;
                default:
                    printf("Commande non reconnue.\n");
            }

            sleep(1);
        }
    }

    return 0;
}
