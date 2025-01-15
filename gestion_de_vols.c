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
void chargerDonnees() {
    FILE *fichier = fopen(FILE_NAME, "r");
    if (fichier == NULL) return;

    while (fscanf(fichier, "%s %s %s %d %d", vols[nombreDeVols].code, vols[nombreDeVols].destination,
                  vols[nombreDeVols].date, &vols[nombreDeVols].seatsTotal, &vols[nombreDeVols].seatsRemaining) == 5) {
        nombreDeVols++;
    }

    fclose(fichier);
}

void sauvegarderDonnees() {
    FILE *fichier = fopen(FILE_NAME, "w");
    if (fichier == NULL) {
        printf("Erreur: Impossible de sauvegarder les données.\n");
        return;
    }

    for (int i = 0; i < nombreDeVols; i++) {
        fprintf(fichier, "%s %s %s %d %d\n", vols[i].code, vols[i].destination, vols[i].date, vols[i].seatsTotal, vols[i].seatsRemaining);
    }

    fclose(fichier);
}
