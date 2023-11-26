//bibliotheques utiles
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define colonnes 20//nombre de colonnes
#define lignes 10//nombre de lignes

struct niveau {
    char matrix[lignes][colonnes];
    int snoopyX;//coordonnee en abscisse
    int snoopyY;//coordonnee en ordonnee
    int blocPousse;  //  variable pour indiquer si le bloc a été poussé
    int oiseauxRecuperes;//variables nombres d oiseaux recuperés
};


struct Joueur {//structure joueur
    char nom[40];
    int score;//score joueur
    int vies;//nombre de vie joueur
};
//declaration de la position et vitesse balle
struct Balle {
    int x;// coordonnee en abscisse balle
    int y;//coordonnee en ordonee balle
    int vx;//vitesse horizontale balle
    int vy;//vitesse verticale de la balle
};

// Fonction pour afficher le niveau
void displayLevel(struct niveau *niveau, struct Balle *balle) {
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            printf("+---");// delimiter les cases
        }
        printf("+\n");

        for (int j = 0; j < colonnes; j++) {
            if (i == balle->y && j == balle->x) {// afficher la balle
                printf("| B ");
            } else {
                printf("| %c ", niveau->matrix[i][j]);
            }
        }
        printf("|\n");
    }

    for (int j = 0; j < colonnes; j++) {
        printf("+---");// delimite cases
    }
    printf("+\n");
}

// Fonction pour déplacer la balle
void moveBall(struct Balle *balle, struct niveau *niveau, struct Joueur *joueur) {
    niveau->matrix[balle->y][balle->x] = ' ';  // Efface l'emplacement précédent de la balle

    int nextX = balle->x + balle->vx;
    int nextY = balle->y + balle->vy;

    // Vérifie si la prochaine position de la balle touche un bloc '<' ou '>'
    if ((nextX > 0 && nextX < colonnes - 1) &&
        (niveau->matrix[nextY][nextX] == '<' || niveau->matrix[nextY][nextX] == '>')) {
        // Détermine la direction du bloc
        int blocDirection = (niveau->matrix[nextY][nextX] == '<') ? -1 : 1;

        // Inverse la direction horizontale
        balle->vx = blocDirection * abs(balle->vx);
    }

    // Vérifie si la balle atteint les limites du niveau en horizontal
    if (nextX < 0 || nextX >= colonnes) {
        balle->vx = -balle->vx;  // Inverse la direction horizontale
    }

    // Vérifie si la balle atteint les limites du niveau en vertical
    if (nextY < 0 || nextY >= lignes) {
        balle->vy = -balle->vy;  // Inverse la direction verticale
    }

    // Vérifie si la balle touche Snoopy
    if (nextX == niveau->snoopyX && nextY == niveau->snoopyY) {
        joueur->vies--;

        if (joueur->vies <= 0) {
            printf("Snoopy a épuisé toutes ses vies. Fin du jeu!\n");
            exit(0);
        }

        // Réinitialise la position de Snoopy après avoir été touché
        niveau->snoopyX = 1;
        niveau->snoopyY = 1;
    }

    // Vérifie si la balle touche un bloc 'C'
    if (niveau->matrix[nextY][nextX] == 'C') {
        balle->vx = -balle->vx;  // Inverse la direction horizontale
        balle->vy = -balle->vy;  // Inverse la direction verticale
    }

    // Applique le déplacement de la balle
    balle->x += balle->vx;
    balle->y += balle->vy;

    // Réinitialise la position de la balle si elle atteint les limites du niveau
    if (balle->x < 0) {
        balle->x = 0;
        balle->vx = -balle->vx;  // Inverse la direction horizontale
    } else if (balle->x >= colonnes) {
        balle->x = colonnes - 1;
        balle->vx = -balle->vx;  // Inverse la direction horizontale
    }

    if (balle->y < 0) {
        balle->y = 0;
        balle->vy = -balle->vy;  // Inverse la direction verticale
    } else if (balle->y >= lignes) {
        balle->y = lignes - 1;
        balle->vy = -balle->vy;  // Inverse la direction verticale
    }

    niveau->matrix[balle->y][balle->x] = 'B';  // Met à jour la position actuelle de la balle
}










// Fonction pour récupérer un oiseau si Snoopy est sur une case avec un oiseau
void recupererOiseau(struct niveau *niveau, struct Joueur *joueur, int temps_restant) {
    int oiseauxRecuperes;
    // Vérifie si la case actuelle de Snoopy contient un oiseau ('O')
    if (niveau->matrix[niveau->snoopyY][niveau->snoopyX] == 'O' && niveau->matrix[niveau->snoopyY][niveau->snoopyX] != 'X') {
        // Marque l'oiseau comme récupéré en mettant 'X' dans la matrice du niveau
        niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'X';
        oiseauxRecuperes=oiseauxRecuperes +1;




        // Vérifie si tous les oiseaux ont été récupérés (compteur à 4)
        if (oiseauxRecuperes == 4) {
            // Ajoute des points au score du joueur basés sur le temps restant
            joueur->score += (temps_restant * 100);
        }
    }
}





// Fonction pour déplacer Snoopy vers le haut
void bougerhaut(struct niveau *niveau, struct Joueur *joueur, int distance) {
    // Boucle pour effectuer le déplacement en fonction de la distance spécifiée
    for (int i = 0; i < distance; i++) {
        // Vérifie si Snoopy peut se déplacer vers le haut et s'il y a un bloc 'C'
        if (niveau->snoopyY > 0 && niveau->matrix[niveau->snoopyY - 1][niveau->snoopyX] == 'C') {
            // Retire le bloc 'C' de la position actuelle
            niveau->matrix[niveau->snoopyY - 1][niveau->snoopyX] = ' ';
            // Ajoute des points au score du joueur
            joueur->score += 10;
        }
            // Vérifie si Snoopy peut se déplacer vers le haut et s'il y a un oiseau 'O'
        else if (niveau->snoopyY > 0 && niveau->matrix[niveau->snoopyY - 1][niveau->snoopyX] == 'O') {
            // Retire l'oiseau 'O' de la position actuelle
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
            // Met à jour la position de Snoopy
            niveau->snoopyY -= 1;
            // Place Snoopy sur la nouvelle position
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'S';
        }
            // Vérifie si Snoopy peut se déplacer vers le haut et s'il y a une case vide
        else if (niveau->snoopyY > 0 && niveau->matrix[niveau->snoopyY - 1][niveau->snoopyX] == ' ') {
            // Retire Snoopy de la position actuelle
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
            // Met à jour la position de Snoopy
            niveau->snoopyY -= 1;
            // Vérifie si la nouvelle position ne contient pas un bloc 'C'
            if (niveau->matrix[niveau->snoopyY][niveau->snoopyX] != 'C') {
                // Place Snoopy sur la nouvelle position
                niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'S';
            }
        }
            // Si aucun des cas précédents n'est satisfait, le déplacement vers le haut est impossible
        else {
            printf("Déplacement vers le haut impossible.\n");
            break;
        }
    }
}


// Fonction pour déplacer Snoopy vers le bas ( chaque etape est identique au sp precedent )
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


// Fonction pour déplacer Snoopy vers la gauche ( chaque etape est identique au sp precedent )
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

// Fonction pour déplacer Snoopy vers la droite ( chaque etape est identique au sp precedent )
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






// Fonction pour casser un bloc 'C' à côté de Snoopy
void casserBlocC(struct niveau *niveau, struct Joueur *joueur) {
    // Vérifie si la position actuelle de Snoopy contient un bloc 'C'
    if (niveau->matrix[niveau->snoopyY][niveau->snoopyX] == 'C') {
        // Retire le bloc 'C' de la position actuelle
        niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
        // Ajoute des points au score du joueur
        joueur->score += 10;
    }
        // Vérifie si la position à gauche de Snoopy contient un bloc 'C' et Snoopy n'est pas sur la bordure gauche
    else if (niveau->snoopyX > 0 && niveau->matrix[niveau->snoopyY][niveau->snoopyX - 1] == 'C') {
        // Retire le bloc 'C' de la position à gauche
        niveau->matrix[niveau->snoopyY][niveau->snoopyX - 1] = ' ';
        // Ajoute des points au score du joueur
        joueur->score += 10;
    }
        // Vérifie si la position à droite de Snoopy contient un bloc 'C' et Snoopy n'est pas sur la bordure droite
    else if (niveau->snoopyX < colonnes - 1 && niveau->matrix[niveau->snoopyY][niveau->snoopyX + 1] == 'C') {
        // Retire le bloc 'C' de la position à droite
        niveau->matrix[niveau->snoopyY][niveau->snoopyX + 1] = ' ';
        // Ajoute des points au score du joueur
        joueur->score += 10;
    }
        // Si aucun des cas précédents n'est satisfait, aucun bloc 'C' à casser à côté de Snoopy
    else {
        printf("Aucun bloc 'C' à casser à côté de Snoopy.\n");
    }
}

// Fonction pour afficher le score et terminer le jeu
void afficherScoreEtTerminer(struct Joueur *joueur) {
    printf("Félicitations! Vous avez récupéré tous les oiseaux!\n");
    printf("Score final : %d\n", joueur->score);
    exit(0);
}





// Programme principal
int main() {
    time_t debut = time(NULL); // Initialisation du timer
    int duree = 120; // Durée du niveau
    struct Joueur joueur;
    strcpy(joueur.nom, "Joueur1");
    joueur.score = 0; // Score du joueur dans ce niveau
    joueur.vies = 3; // Nombre de vies du joueur

    printf("Niveau 2\n"); // Interface du niveau
    struct niveau niveau2 = {
            {{'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'C', ' ', ' ', ' ', 'O'},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '>', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', '<', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'C', ' ', ' ', ' ', ' ', 'O'}},
            10,
            5,
            0,
            0}; // Initialisation de la variable blocPousse

    // Initialisation de la balle
    struct Balle balle = {1, 1, 1, 1};

    // Distance de déplacement pour Snoopy
    int distanceDeplacement = 1;

    // Variable pour suivre si tous les oiseaux ont été récupérés
    bool oiseauxRecuperes = false;

    // Boucle principale du jeu
    while (1) {
        // Obtient le temps actuel
        time_t tempsinstant = time(NULL);
        // Calcule le temps écoulé depuis le début du niveau
        double tempsecoule = difftime(tempsinstant, debut);

        // Vérifie si le temps écoulé est supérieur ou égal à la durée du niveau
        if (tempsecoule >= duree) {
            // Affiche un message de fin de jeu si le temps est écoulé
            printf("Le temps est écoulé. Fin du jeu!\n");
            break;
        } else {
            // Calcule le temps restant avant la fin du niveau
            int temps_restant = duree - (int)tempsecoule;
            // Affiche le temps restant
            printf("Temps restant : %d secondes\n", temps_restant);

            // Affiche les informations du joueur (nom, score, vies)
            printf("Nom du joueur: %s\n Score: %d\n Vies: %d\n", joueur.nom, joueur.score, joueur.vies);

            // Affiche le niveau avec la position actuelle de la balle
            displayLevel(&niveau2, &balle);

            // Déplace la balle en fonction de sa vitesse
            moveBall(&balle, &niveau2, &joueur);

            char direction;
            // Demande à l'utilisateur d'entrer une commande
            printf("Appuyez sur h, b, g, d (Haut, Bas , Gauche , Droite ) pour bouger et sur  'c' pour casser : ");
            direction = getchar();
            while (getchar() != '\n'); // Vide le tampon d'entrée

            // Interprète la commande de l'utilisateur
            switch (direction) {
                case 'q': // Quitte le niveau
                    printf("Fin du jeu.\n");
                    return 0;
                case 'h': // Déplace Snoopy vers le haut
                    bougerhaut(&niveau2, &joueur, distanceDeplacement);
                    break;
                case 'b': // Déplace Snoopy vers le bas
                    bougerbas(&niveau2, &joueur, distanceDeplacement);
                    break;
                case 'g': // Déplace Snoopy vers la gauche
                    bougergauche(&niveau2, &joueur, distanceDeplacement);
                    break;
                case 'd': // Déplace Snoopy vers la droite
                    bougerdroite(&niveau2, &joueur, distanceDeplacement);
                    break;
                case 'c': // Casse un bloc 'C'
                    casserBlocC(&niveau2, &joueur);
                    break;
                default:
                    printf("Commande non reconnue.\n");
            }

            // Récupère un oiseau après le déplacement de Snoopy
            recupererOiseau(&niveau2, &joueur, temps_restant);

            // Vérifie si tous les oiseaux ont été récupérés
            if (niveau2.oiseauxRecuperes == 4) {
                afficherScoreEtTerminer(&joueur);
                break;
            }

        }
    }
    return 0;
}
