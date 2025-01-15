#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_VOLS 100
#define FILE_NAME "vols.txt"

typedef struct {
    char code[10];
    char destination[50];
    char date[11];
    int seatsTotal;
    int seatsRemaining;
} Vol;

Vol vols[MAX_VOLS];
int nombreDeVols = 0;

// Prototypes des fonctions
void chargerDonnees();
void sauvegarderDonnees();
void ajouterVol();
void reserverSiege();
void annulerReservation();
void afficherVols();
void modifierVol();
void rechercherVol();
int verifierCodeUnique(const char *code);
int verifierDateValide(const char *date);
void nettoyerBuffer();
void menu();

int main() {
    chargerDonnees();
    menu();
    sauvegarderDonnees();
    return 0;
}