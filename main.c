#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Joueur{
    char nom[40];
    int score
};
void lvl2(){
    struct Joueur *joueur;
    printf("Niveau 2");
    printf("Nom du joueur: %s\n Score: %d\n", joueur->nom, joueur->score);
}