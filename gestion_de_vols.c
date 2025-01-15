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
void ajouterVol() {
    if (nombreDeVols >= MAX_VOLS) {
        printf("Limite de vols atteinte.\n");
        return;
    }

    Vol nouveauVol;
    printf("Code du vol (max 9 caractères): ");
    scanf("%9s", nouveauVol.code);
    nettoyerBuffer();

    if (!verifierCodeUnique(nouveauVol.code)) {
        printf("Erreur: Un vol avec ce code existe déjà.\n");
        return;
    }

    printf("Destination (max 49 caractères): ");
    fgets(nouveauVol.destination, 50, stdin);
    strtok(nouveauVol.destination, "\n");

    do {
        printf("Date (JJ/MM/AAAA): ");
        scanf("%10s", nouveauVol.date);
        nettoyerBuffer();
        if (!verifierDateValide(nouveauVol.date)) {
            printf("Erreur: Format de date invalide.\n");
        }
    } while (!verifierDateValide(nouveauVol.date));

    printf("Nombre total de sièges: ");
    scanf("%d", &nouveauVol.seatsTotal);
    nettoyerBuffer();

    if (nouveauVol.seatsTotal <= 0) {
        printf("Erreur: Le nombre total de sièges doit être positif.\n");
        return;
    }

    nouveauVol.seatsRemaining = nouveauVol.seatsTotal;
    vols[nombreDeVols++] = nouveauVol;
    printf("Vol ajouté avec succès!\n");
}

void reserverSiege() {
    char code[10];
    printf("Code du vol: ");
    scanf("%9s", code);

    for (int i = 0; i < nombreDeVols; i++) {
        if (strcmp(vols[i].code, code) == 0) {
            if (vols[i].seatsRemaining > 0) {
                vols[i].seatsRemaining--;
                printf("Réservation effectuée avec succès!\n");
            } else {
                printf("Aucun siège disponible sur ce vol.\n");
            }
            return;
        }
    }

    printf("Vol introuvable.\n");
}


