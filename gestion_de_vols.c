#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

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
    if (fichier == NULL) {
        printf("Aucun fichier de donnees trouve. Un nouveau fichier sera cree lors de la sauvegarde.\n");
        return;
    }

    while (fscanf(fichier, "%s %s %s %d %d", vols[nombreDeVols].code, vols[nombreDeVols].destination,
                  vols[nombreDeVols].date, &vols[nombreDeVols].seatsTotal, &vols[nombreDeVols].seatsRemaining) == 5) {
        nombreDeVols++;
        if (nombreDeVols >= MAX_VOLS) {
            printf("Attention: Nombre maximal de vols atteint. Tous les vols n'ont pas pu etre charges.\n");
            break;
        }
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
    printf("Code du vol (max 9 caracteres): ");
    fgets(nouveauVol.code, sizeof(nouveauVol.code), stdin);
    strtok(nouveauVol.code, "\n");
    if (strlen(nouveauVol.code) == 0) {
        printf("Erreur: Le code du vol ne peut pas etre vide.\n");
        return;
    }
    if (!verifierCodeUnique(nouveauVol.code)) {
        printf("Erreur: Un vol avec ce code existe deja.\n");
        return;
    }

    printf("Destination (max 49 caracteres): ");
    fgets(nouveauVol.destination, 50, stdin);
    strtok(nouveauVol.destination, "\n");

    do {
        printf("Date (JJ/MM/AAAA): ");
        fgets(nouveauVol.date, sizeof(nouveauVol.date), stdin);
        strtok(nouveauVol.date, "\n");
        if (!verifierDateValide(nouveauVol.date)) {
            printf("Erreur: La date est invalide ou deja passee. Veuillez reessayer.\n");
        }
    } while (!verifierDateValide(nouveauVol.date));

    printf("Nombre total de sieges: ");
    while (scanf("%d", &nouveauVol.seatsTotal) != 1 || nouveauVol.seatsTotal <= 0) {
        printf("Erreur: Veuillez entrer un nombre entier positif pour le nombre de sieges: ");
        nettoyerBuffer();
    }
    nettoyerBuffer();

    nouveauVol.seatsRemaining = nouveauVol.seatsTotal;
    vols[nombreDeVols++] = nouveauVol;
    printf("Vol ajoute avec succes!\n");
}
void reserverSiege() {
    char code[10];
    printf("Code du vol: ");
    scanf("%9s", code);
    nettoyerBuffer();

    int A = 0;
    for (int i = 0; i < nombreDeVols; i++) {
        if (strcmp(vols[i].code, code) == 0) {
            A = 1;
            if (vols[i].seatsRemaining > 0) {
                vols[i].seatsRemaining--;
                printf("Reservation effectuee avec succes!\n");
            } else {
                printf("Aucun siege disponible sur ce vol.\n");
            }
            break;
        }
    }
    if (!A) {
        printf("Erreur: Aucun vol trouve avec le code %s.\n", code);
    }
}
void annulerReservation() {
    char code[10];
    printf("Code du vol: ");
    scanf("%9s", code);
    nettoyerBuffer();

    if (strlen(code) == 0) {
        printf("Erreur: Le code du vol ne peut pas etre vide.\n");
        return;
    }

    for (int i = 0; i < nombreDeVols; i++) {
        if (strcmp(vols[i].code, code) == 0) {
            if (vols[i].seatsRemaining < vols[i].seatsTotal) {
                vols[i].seatsRemaining++;
                printf("Reservation annulee avec succes! Sieges restants : %d/%d\n",
                       vols[i].seatsRemaining, vols[i].seatsTotal);
            } else {
                printf("Toutes les places sont deja disponibles.\n");
            }
            return;
        }
    }

    printf("Erreur: Aucun vol trouve avec le code %s.\n", code);
}
void afficherVols() {
    if (nombreDeVols == 0) {
        printf("Aucun vol disponible.\n");
        return;
    }

    printf("\nListe des vols:\n");
  for (int i = 0; i < nombreDeVols; i++) {
        printf("Code: %s, Destination: %s, Date: %s, Sièges restants: %d/%d\n",
               vols[i].code, vols[i].destination, vols[i].date,
               vols[i].seatsRemaining, vols[i].seatsTotal);
    }
}
void modifierVol() {
    char code[10];
    printf("Code du vol a modifier: ");
    scanf("%9s", code);
    nettoyerBuffer();

    if (strlen(code) == 0) {
        printf("Erreur: Le code du vol ne peut pas etre vide.\n");
        return;
    }

    for (int i = 0; i < nombreDeVols; i++) {
        if (strcmp(vols[i].code, code) == 0) {
            printf("\nVol trouve :\n");
            printf("Code: %s, Destination: %s, Date: %s, Sieges restants: %d/%d\n",
                   vols[i].code, vols[i].destination, vols[i].date,
                   vols[i].seatsRemaining, vols[i].seatsTotal);

            printf("\nNouvelle destination (laisser vide pour ne pas modifier): ");
            char nouvelleDestination[50];
            fgets(nouvelleDestination, 50, stdin);
            strtok(nouvelleDestination, "\n");
            if (strlen(nouvelleDestination) > 0) {
                strcpy(vols[i].destination, nouvelleDestination);
            }

            char nouvelleDate[11];
            do {
                printf("Nouvelle date (JJ/MM/AAAA, laisser vide pour ne pas modifier): ");
                fgets(nouvelleDate, 11, stdin);
                strtok(nouvelleDate, "\n");
                if (strlen(nouvelleDate) == 0) break; 
                if (!verifierDateValide(nouvelleDate)) {
                    printf("Erreur: La date est invalide ou deja passee. Veuillez reessayer.\n");
                } else {
                    strcpy(vols[i].date, nouvelleDate);
                    break;
                }
            } while (1);

            printf("Nouveau nombre total de sieges (laisser a 0 pour ne pas modifier): ");
            int nouveauSeatsTotal = 0;
            while (scanf("%d", &nouveauSeatsTotal) != 1 || nouveauSeatsTotal < 0) {
                printf("Erreur: Entrez un nombre valide (positif ou 0 pour ne pas modifier): ");
                nettoyerBuffer();
            }
            nettoyerBuffer();

            if (nouveauSeatsTotal > 0) {
                if (nouveauSeatsTotal < vols[i].seatsRemaining) {
                    printf("Erreur: Le nombre total de sieges ne peut pas etre inferieur aux sieges restants (%d).\n",
                           vols[i].seatsRemaining);
                } else {
                    vols[i].seatsTotal = nouveauSeatsTotal;
                }
            }

            printf("\nModification effectuee avec succes ! Nouveau vol :\n");
            printf("Code: %s, Destination: %s, Date: %s, Sieges restants: %d/%d\n",
                   vols[i].code, vols[i].destination, vols[i].date,
                   vols[i].seatsRemaining, vols[i].seatsTotal);
            return;
        }
    }

    printf("Erreur: Aucun vol trouve avec le code %s.\n", code);
}
void rechercherVol() {
    char destination[50];
    printf("Entrer la destination pour rechercher des vols : ");
    fgets(destination, 50, stdin);
    strtok(destination, "\n");

    int trouve = 0;
    for (int i = 0; i < nombreDeVols; i++) {
        if (strcasecmp(vols[i].destination, destination) == 0) {
            printf("Code: %s, Destination: %s, Date: %s, Sièges restants: %d/%d\n",
                   vols[i].code, vols[i].destination, vols[i].date,
                   vols[i].seatsRemaining, vols[i].seatsTotal);
            trouve = 1;
        }
    }
    if (!trouve) {
        printf("Aucun vol trouvé pour cette destination.\n");
    }
}

int verifierCodeUnique(const char *code) {
    for (int i = 0; i < nombreDeVols; i++) {
        if (strcmp(vols[i].code, code) == 0) {
            return 0;
        }
    }
    return 1;
}

int verifierDateValide(const char *date) {
   if (strlen(date) != 10 || date[2] != '/' || date[5] != '/' ||
        !isdigit(date[0]) || !isdigit(date[1]) || !isdigit(date[3]) ||
        !isdigit(date[4]) || !isdigit(date[6]) || !isdigit(date[7]) ||
        !isdigit(date[8]) || !isdigit(date[9])) {
        return 0; 
    }

    int jour = (date[0] - '0') * 10 + (date[1] - '0');
    int mois = (date[3] - '0') * 10 + (date[4] - '0');
    int annee = (date[6] - '0') * 1000 + (date[7] - '0') * 100 +
                (date[8] - '0') * 10 + (date[9] - '0');

    if (mois < 1 || mois > 12 || jour < 1 || annee < 1900) return 0;

    int joursDansMois[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0)) {
        joursDansMois[1] = 29;
    }
    if (jour > joursDansMois[mois - 1]) return 0;

    time_t t = time(NULL);
    struct tm *dateActuelle = localtime(&t);
    int jourActuel = dateActuelle->tm_mday;
    int moisActuel = dateActuelle->tm_mon + 1;
    int anneeActuelle = dateActuelle->tm_year + 1900;

    if (annee < anneeActuelle ||
        (annee == anneeActuelle && mois < moisActuel) ||
        (annee == anneeActuelle && mois == moisActuel && jour < jourActuel)) {
        return 0; 
    }

    return 1; 
}

void nettoyerBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void menu() {
    int choix;
    do {
        printf("\n=== Système de réservation de vols ===\n");
        printf("1. Ajouter un vol\n");
        printf("2. Reserver un siege\n");
        printf("3. Annuler une reservation\n");
        printf("4. Afficher les vols\n");
        printf("5. Modifier un vol\n");
        printf("6. Rechercher un vol\n");
        printf("7. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix);
        nettoyerBuffer();

        switch (choix) {
            case 1:
                ajouterVol();
                break;
            case 2:
                reserverSiege();
                break;
            case 3:
                annulerReservation();
                break;
            case 4:
                afficherVols();
                break;
            case 5:
                modifierVol();
                break;
            case 6:
                rechercherVol();
                break;
            case 7:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    } while (choix != 7);
}



