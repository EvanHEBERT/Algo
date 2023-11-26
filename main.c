#include <stdio.h>
#include <ctype.h>//bibliotheques utiles
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>


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
    int oiseauxrecuperes;
};
//declaration de la position et vitesse balle
struct Balle {
    int x;// coordonnee en abscisse balle
    int y;//coordonnee en ordonee balle
    int vx;//vitesse horizontale balle
    int vy;//vitesse verticale de la balle
};
//pareil pour la balle 2
struct Balle2{
    int x2;
    int y2;
    int vx2;
    int vy2;
};

// Fonction pour afficher le niveau
void afficherniveau(struct niveau *niveau, struct Balle *balle) {
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

void afficherniveau3(struct niveau *niveau, struct Balle *balle, struct Balle2 *balle2) {
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            printf("+---");// delimiter les cases
        }
        printf("+\n");

        for (int j = 0; j < colonnes; j++) {
            if (i == balle->y && j == balle->x) {// afficher la balle
                printf("| %c ",0xB);}
            else if(i ==balle2->y2 && j == balle2->x2){
                printf("| %c ",0xB);
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
    if (niveau->matrix[nextY][nextX] == 1) {
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


void moveBall2(struct Balle2 *balle2, struct niveau *niveau, struct Joueur *joueur) {//pareil que pour la première balle
    niveau->matrix[balle2->y2][balle2->x2] = ' ';

    int nextX = balle2->x2 + balle2->vx2;
    int nextY = balle2->y2 + balle2->vy2;


    if ((nextX > 0 && nextX < colonnes - 1) &&
        (niveau->matrix[nextY][nextX] == '<' || niveau->matrix[nextY][nextX] == '>')) {
        int blocDirection = (niveau->matrix[nextY][nextX] == '<') ? -1 : 1;
        balle2->vx2 = blocDirection * abs(balle2->vx2);
    }

    if (nextX < 0 || nextX >= colonnes) {
        balle2->vx2 = -balle2->vx2;
    }
    if (nextY < 0 || nextY >= lignes) {
        balle2->vy2 = -balle2->vy2;
    }
    if (nextX == niveau->snoopyX && nextY == niveau->snoopyY) {
        joueur->vies--;

        if (joueur->vies <= 0) {
            printf("Snoopy a épuisé toutes ses vies. Fin du jeu!\n");
            exit(0);
        }
        niveau->snoopyX = 1;
        niveau->snoopyY = 1;
    }

    if (niveau->matrix[nextY][nextX] == 5) {
        balle2->vx2 = -balle2->vx2;  // Inverse la direction horizontale
        balle2->vy2 = -balle2->vy2;  // Inverse la direction verticale
    }

    balle2->x2 += balle2->vx2;
    balle2->y2 += balle2->vy2;

    if (balle2->x2 < 0) {
        balle2->x2 = 0;
        balle2->vx2 = -balle2->vx2;
    } else if (balle2->x2 >= colonnes) {
        balle2->x2 = colonnes - 1;
        balle2->vx2 = -balle2->vx2;
    }

    if (balle2->y2 < 0) {
        balle2->y2 = 0;
        balle2->vy2 = -balle2->vy2;
    } else if (balle2->y2 >= lignes) {
        balle2->y2 = lignes - 1;
        balle2->vy2 = -balle2->vy2;
    }

    niveau->matrix[balle2->y2][balle2->x2] = 'B';
}








// Fonction pour récupérer un oiseau si Snoopy est sur une case avec un oiseau
void recupererOiseau(struct niveau *niveau, struct Joueur *joueur, int temps_restant) {
    int oiseauxRecuperes;
    // Vérifie si la case actuelle de Snoopy contient un oiseau ('O')
    if (niveau->matrix[niveau->snoopyY][niveau->snoopyX] == 'O' && niveau->matrix[niveau->snoopyY][niveau->snoopyX] != 'X') {
        // Marque l'oiseau comme récupéré en mettant 'X' dans la matrice du niveau
        niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 'X';
        oiseauxRecuperes=oiseauxRecuperes +1;






    }
}
// Fonction pour vérifier si les coins du niveau sont occupés par des espaces
bool verifierCoins(struct niveau *niveau) {
    // Vérifie les quatre coins du niveau
    if (niveau->matrix[0][0] == ' ' && niveau->matrix[0][colonnes - 1] == ' ' &&
        niveau->matrix[lignes - 1][0] == ' ' && niveau->matrix[lignes - 1][colonnes - 1] == ' ') {
        return true;  // Les quatre coins sont occupés par des espaces
    } else {
        return false; // Au moins un coin n'est pas occupé par un espace
    }
}

struct EtatJeu {
    struct niveau niveau2;
    struct Balle balle;
    struct Joueur joueur;
    int estEnPause;
};





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
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 1;
        }
            // Vérifie si Snoopy peut se déplacer vers le haut et s'il y a une case vide
        else if (niveau->snoopyY > 0 && niveau->matrix[niveau->snoopyY - 1][niveau->snoopyX] == ' ') {
            // Retire Snoopy de la position actuelle
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
            // Met à jour la position de Snoopy
            niveau->snoopyY -= 1;
            // Vérifie si la nouvelle position ne contient pas un bloc 'C'
            if (niveau->matrix[niveau->snoopyY][niveau->snoopyX] != 5) {
                // Place Snoopy sur la nouvelle position
                niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 1;
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
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 1;
        } else if (niveau->snoopyY < lignes - 1 && niveau->matrix[niveau->snoopyY + 1][niveau->snoopyX] == ' ') {
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
            niveau->snoopyY += 1;
            if (niveau->matrix[niveau->snoopyY][niveau->snoopyX] != 5) {
                niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 1;
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
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 1;
        } else if (niveau->snoopyX > 0 && niveau->matrix[niveau->snoopyY][niveau->snoopyX - 1] == ' ') {
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
            niveau->snoopyX -= 1;
            if (niveau->matrix[niveau->snoopyY][niveau->snoopyX] != 5) {
                niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 1;
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
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 1;
        } else if (niveau->snoopyX < colonnes - 1 && niveau->matrix[niveau->snoopyY][niveau->snoopyX + 1] == ' ') {
            niveau->matrix[niveau->snoopyY][niveau->snoopyX] = ' ';
            niveau->snoopyX += 1;
            if (niveau->matrix[niveau->snoopyY][niveau->snoopyX] != 5) {
                niveau->matrix[niveau->snoopyY][niveau->snoopyX] = 1;
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



// sp niveau 3
void niveau3() {
    char matrix[lignes][colonnes];
    time_t debut = time(NULL); // Initialisation du timer
    int duree = 120; // Durée du niveau
    struct Joueur joueur;
    strcpy(joueur.nom, "Joueur1");
    joueur.score = 0; // Score du joueur dans ce niveau
    joueur.vies = 3; // Nombre de vies du joueur

    printf("Niveau 2\n"); // Interface du niveau
    struct niveau niveau3 = {
            {{'O', ' ', ' ', ' ', 0xF, 0xF, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 5, ' ', ' ', ' ', 'O'},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', 5, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 0xF, 0xF, ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '>', ' ', 0xF, ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', 0xF, 0xF, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', 5, ' ', ' ', ' ', ' ', ' ', ' ', 0xF, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', '<', ' ', ' ', ' ', 0xF, ' ', ' ', ' ', '>', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 0xF, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 5, ' ', ' ', ' ', ' ', 'O'}},
            10,
            5,
            0,
            0}; // Initialisation de la variable blocPousse

    // Initialisation de la balle
    struct Balle balle = {1, 1, 1, 1};
    struct Balle2 balle2 = {9, 6, -1, -1};



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
            int temps_restant = duree - (int) tempsecoule;
            // Affiche le temps restant
            printf("Temps restant : %d secondes\n", temps_restant);

            // Affiche les informations du joueur (nom, score, vies)
            printf("Nom du joueur: %s\n Score: %d\n Vies: %d\n", joueur.nom, joueur.score, joueur.vies);

            // Affiche le niveau avec la position actuelle de la balle
            afficherniveau3(&niveau3, &balle, &balle2);


            // Déplace la balle en fonction de sa vitesse
            moveBall(&balle, &niveau3, &joueur);
            moveBall2(&balle2, &niveau3, &joueur);

            char direction;
            // Demande à l'utilisateur d'entrer une commande
            printf("Appuyez sur h, b, g, d (Haut, Bas , Gauche , Droite ) pour bouger et sur  'c' pour casser : ");
            direction = getchar();
            while (getchar() != '\n'); // Vide le tampon d'entrée

            // Interprète la commande de l'utilisateur
            switch (direction) {
                case 'q': // Quitte le niveau
                    printf("Fin du jeu.\n");
                case 'h': // Déplace Snoopy vers le haut
                    bougerhaut(&niveau3, &joueur, distanceDeplacement);
                    break;
                case 'b': // Déplace Snoopy vers le bas
                    bougerbas(&niveau3, &joueur, distanceDeplacement);
                    break;
                case 'g': // Déplace Snoopy vers la gauche
                    bougergauche(&niveau3, &joueur, distanceDeplacement);
                    break;
                case 'd': // Déplace Snoopy vers la droite
                    bougerdroite(&niveau3, &joueur, distanceDeplacement);
                    break;
                case 'c': // Casse un bloc 'C'
                    casserBlocC(&niveau3, &joueur);
                    break;
                case 'p': // Pause or resume the game
                    printf("Le jeu est en pause. Appuyez sur 'p' pour reprendre.\n");
                    while (getchar() != 'p'); // Wait for 'p' to resume
                    printf("Reprise du jeu.\n");
                    break;
                default:
                    printf("Commande non reconnue.\n");
            }

            // Récupère un oiseau après le déplacement de Snoopy
            recupererOiseau(&niveau3, &joueur, temps_restant);

            // Vérifie si tous les oiseaux ont été récupérés
            if (niveau3.oiseauxRecuperes == 4) {
                break;
            }

        }
    }
}
// sp niveau 2
void niveau2() {
    time_t debut = time(NULL);
    int duree = 120;
    struct Joueur joueur;
    strcpy(joueur.nom, "Joueur1");
    joueur.score = 0;
    joueur.vies = 3;

    printf("Niveau 2\n");
    struct niveau niveau2 = {
            {{'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 5, ' ', ' ', ' ', 'O'},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', 0xF, 0xF, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', 0xF, ' ', ' ', 5, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', 0xF, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '>', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', 5 , ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', '<', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 0xF, ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 0xF, ' '},
             {'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 5, ' ', ' ', ' ', ' ', 'O'}},
            10,
            5,
            0,
            0};

    struct Balle balle = {1, 1, 1, 1};  // Initialization of the Balle structure
    int distanceDeplacement = 1;


    struct EtatJeu etatJeu;
    etatJeu.niveau2 = niveau2;
    etatJeu.balle = balle;
    etatJeu.joueur = joueur;
    etatJeu.estEnPause = 0;

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
            int temps_restant = duree - (int) tempsecoule;
            // Affiche le temps restant
            printf("Temps restant : %d secondes\n", temps_restant);

            // Affiche les informations du joueur (nom, score, vies)
            printf("Nom du joueur: %s\n Score: %d\n Vies: %d\n", joueur.nom, joueur.score, joueur.vies);

            // Affiche le niveau avec la position actuelle de la balle
            afficherniveau(&niveau2, &balle);

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




            // Vérifie si les quatre coins sont occupés par des espaces
            if (niveau2.matrix[0][0] == ' ' && niveau2.matrix[0][colonnes - 1] == ' ' &&
                niveau2.matrix[lignes - 1][0] == ' ' && niveau2.matrix[lignes - 1][colonnes - 1] == ' ') {
                int score1= temps_restant*100;
                printf("Félicitations! Vous avez récupéré tous les oiseaux!\n");
                printf("Score final : %d\n",score1 );

                niveau3();
            }
        }
    }
}
//sp niveau 1
void niveau1() {// idem que avant
    time_t debut = time(NULL);
    int duree = 120;
    struct Joueur joueur;
    strcpy(joueur.nom, "Joueur1");
    joueur.score = 0;
    joueur.vies = 3;
    joueur.oiseauxrecuperes = 0;

    printf("Niveau 1\n");
    struct niveau niveau1 = {
            {{'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 5, ' ', ' ', ' ', 'O'},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
             {'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'O'}},
            10,
            5,
            0};

    struct Balle balle = {1, 1, 1, 1};  // Initialization of the Balle structure
    int distanceDeplacement = 1;


    struct EtatJeu etatJeu;
    etatJeu.niveau2 = niveau1;
    etatJeu.balle = balle;
    etatJeu.joueur = joueur;
    etatJeu.estEnPause = 0;

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
            int temps_restant = duree - (int) tempsecoule;
            // Affiche le temps restant
            printf("Temps restant : %d secondes\n", temps_restant);

            // Affiche les informations du joueur (nom, score, vies)
            printf("Nom du joueur: %s\n Score: %d\n Vies: %d\n", joueur.nom, joueur.score, joueur.vies);

            // Affiche le niveau avec la position actuelle de la balle
            afficherniveau(&niveau1, &balle);

            // Déplace la balle en fonction de sa vitesse
            moveBall(&balle, &niveau1, &joueur);

            char direction;
            // Demande à l'utilisateur d'entrer une commande
            printf("Appuyez sur h, b, g, d (Haut, Bas , Gauche , Droite ) pour bouger et sur  'c' pour casser : ");
            direction = getchar();
            while (getchar() != '\n'); // Vide le tampon d'entrée

            // Interprète la commande de l'utilisateur
            switch (direction) {
                case 'q': // Quitte le niveau
                    printf("Fin du jeu.\n");

                case 'h': // Déplace Snoopy vers le haut
                    bougerhaut(&niveau1, &joueur, distanceDeplacement);
                    break;
                case 'b': // Déplace Snoopy vers le bas
                    bougerbas(&niveau1, &joueur, distanceDeplacement);
                    break;
                case 'g': // Déplace Snoopy vers la gauche
                    bougergauche(&niveau1, &joueur, distanceDeplacement);
                    break;
                case 'd': // Déplace Snoopy vers la droite
                    bougerdroite(&niveau1, &joueur, distanceDeplacement);
                    break;
                case 'c': // Casse un bloc 'C'
                    casserBlocC(&niveau1, &joueur);
                    break;
                default:
                    printf("Commande non reconnue.\n");
            }







            // Vérifie si les 4 oiseaux ont été recupéré  (4 coins vides)
            if (niveau1.matrix[0][0] == ' ' && niveau1.matrix[0][colonnes - 1] == ' ' &&
                niveau1.matrix[lignes - 1][0] == ' ' && niveau1.matrix[lignes - 1][colonnes - 1] == ' ') {
                int score1= temps_restant*100;
                printf("Félicitations! Vous avez récupéré tous les oiseaux!\n");
                printf("Score final : %d\n",score1 );

                niveau2();
            }
        }
    }
}






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
void lancerNiveauAvecMotDePasse() {
    printf("Entrez le mot de passe du niveau : \n");
    char motDePasse[50];
    scanf("%s", motDePasse);

    //entree des mdp
    if (strcmp(motDePasse, "niveau1") == 0) {
        printf("Mot de passe correct. Lancement du niveau 1...\n");
        niveau1();  // Appelle la fonction pour lancer le niveau &
    } else if (strcmp(motDePasse, "niveau2") == 0) {
        printf("Mot de passe correct. Lancement du niveau 2...\n");
        niveau2();  // Appelle la fonction pour lancer le niveau 2
    }else if (strcmp(motDePasse, "niveau3") == 0) {
        printf("Mot de passe correct. Lancement du niveau 3...\n");
        niveau3();  // Appelle la fonction pour lancer le niveau 3
    }else {
        printf("Mot de passe incorrect. Le jeu ne peut pas être lancé.\n");
    }
}

void score (){//score joueur
    printf("Votre score est de: %f\n ",score);
}
int main() {//menu
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
                niveau1();
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

