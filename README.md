# Système de Réservation de Vols ✈️

## Description 📋

Ce projet est un programme en C qui permet de gérer un système de réservation de vols. Il inclut des fonctionnalités comme :

- Ajouter un vol.
- Réserver un siège.
- Annuler une réservation.
- Afficher la liste des vols disponibles.
- Modifier les détails d'un vol.
- Rechercher un vol par destination.

L'objectif est de fournir une solution simple pour simuler un système de gestion de vols.

---

## Fonctionnalités 🚀

- **Ajout de vols** : Ajoutez un vol avec son code, sa destination, sa date, et son nombre de sièges disponibles.
- **Réservation** : Réservez un siège sur un vol spécifique.
- **Annulation** : Annulez une réservation et libérez un siège.
- **Affichage des vols** : Consultez les informations des vols disponibles.
- **Modification** : Modifiez les informations d'un vol (destination, date ou nombre de sièges).
- **Recherche** : Trouvez des vols selon leur destination.

---

## Compilation et Exécution 🛠️

### Prérequis

- Un compilateur C (comme GCC ou Clang).
- Un éditeur de texte ou IDE (Visual Studio Code, Code::Blocks, etc.).

### Étapes

1. **Cloner le projet** :

   ```bash
   git clone https://github.com/freeguy310/Skyconnect
   cd Flights-Manager
   ```

2. **Compiler le programme** :
   Avec GCC :

   ```bash
   gcc main.c -o skyconnect
   ```

3. **Exécuter le programme** :

   ```bash
   ./skyconnect
   ```

---

## Utilisation 💻

Lorsque vous exécutez le programme, un menu interactif s'affiche. Voici les options disponibles :

1. **Ajouter un vol** : Fournissez les détails du vol (code, destination, date, sièges).
2. **Réserver un siège** : Entrez le code du vol pour réserver une place.
3. **Annuler une réservation** : Entrez le code du vol pour libérer une place.
4. **Afficher les vols** : Affiche les informations sur tous les vols disponibles.
5. **Modifier un vol** : Modifiez les informations d'un vol existant.
6. **Rechercher un vol** : Trouvez un vol par destination.
7. **Quitter** : Fermez le programme.

---

## Structure des Fichiers 📂

- **main.c** : Contient tout le code source du programme.
- **vols.txt** : Fichier de sauvegarde des informations des vols (créé automatiquement).
- **README.md** : Ce fichier, contenant les instructions et informations sur le projet.

---

## Notes Importantes ⚠️

- Le fichier `vols.txt` est utilisé pour sauvegarder les données des vols entre les sessions.
- Le programme vérifie l'unicité des codes de vols pour éviter les doublons.
- Les dates doivent être fournies au format `JJ/MM/AAAA`.

---

## Améliorations Futures 🛠️

- Implémenter une interface graphique.
- Ajouter une validation plus avancée des entrées utilisateur.
- Permettre l'import/export des données au format CSV.

---
