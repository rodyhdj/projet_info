#include "main.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------- Gestion Fichiers ---------------------------

// CLIENTF
void lire_fichier_client() {
  FILE *fichier = fopen("client.txt", "r");
  char ligne[MAX_DESCRIPTION * 2]; // SECU
  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier client.\n");
    exit(1);
  }

  nb_client = 0;
  // Lecture des données du fichier et remplissage du tableau de structures
  while (fgets(ligne, sizeof(ligne), fichier) && nb_client < MAX_CLIENT * 2) {
    sscanf(ligne, "%s %s %s %s %s %s %s %d", client[nb_client].nom,
           client[nb_client].prenom, client[nb_client].adresse,
           client[nb_client].ville, client[nb_client].code_postal,
           client[nb_client].telephone, client[nb_client].email,
           &client[nb_client].points_fidelite);
    fget_result = fgets(ligne, sizeof(ligne), fichier);
    memcpy(client[nb_client].historique_achat, ligne, MAX_DESCRIPTION);
    nb_client++;
  }
  fclose(fichier);
}

// PRODUITF
void lire_fichier_produit() {
  FILE *fichier = fopen("produit.txt", "r");
  char ligne[MAX_DESCRIPTION * 2]; // SECU
  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier produit.\n");
    exit(1);
  }

  nb_produit = 0;
  while (fgets(ligne, sizeof(ligne), fichier) && nb_produit < MAX_PRODUIT) {
    memcpy(produit[nb_produit].nom, ligne, MAX_CARACTERES);
    fget_result = fgets(ligne, sizeof(ligne), fichier);
    memcpy(produit[nb_produit].description, ligne, MAX_DESCRIPTION);
    fget_result = fgets(ligne, sizeof(ligne), fichier);
    sscanf(ligne, "%d %d", &produit[nb_produit].prix,
           &produit[nb_produit].quantite);
    nb_produit++;
  }
  fclose(fichier);
}

// --------------------------- FONCTIONS D'ECRITURE ---------------------------

// CLIENTF
void ecrire_fichier_client() {
  remove("client.txt");
  FILE *fichier = fopen("client.txt", "w");

  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier.\n");
    exit(1);
  }

  for (int index = 0; index < nb_client; index++) {
    if (strcmp(client[index].nom, "") != 0) {
      fprintf(fichier, "%s %s %s %s %s %s %s %d\n", client[index].nom,
              client[index].prenom, client[index].adresse, client[index].ville,
              client[index].code_postal, client[index].telephone,
              client[index].email, client[index].points_fidelite);
      fprintf(fichier, "%s", client[index].historique_achat);
    }
  }

  fclose(fichier);
  free(client);
  client = malloc(MAX_CLIENT * sizeof(struct Client));
  lire_fichier_client();
}

// PRODUITF
void ecrire_fichier_produit() {
  remove("produit.txt");
  FILE *fichier = fopen("produit.txt", "w");

  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier.\n");
    exit(1);
  }

  for (int index = 0; index < nb_produit; index++) {
    if (strcmp(produit[index].nom, "") != 0) {
      fprintf(fichier, "%s%s%d %d\n", produit[index].nom,
              produit[index].description, produit[index].prix,
              produit[index].quantite);
    }
  }

  fclose(fichier);
  free(produit);
  produit = malloc(MAX_PRODUIT * sizeof(struct Produit));
  lire_fichier_produit();
}

// --------------------------- Client ---------------------------

// TODO
void afficher_produit() {
  printf("\nVoici notre liste de produit :\n");
  for (int index = 0; index < nb_produit; index++) {
    printf("numero %d, %s avec %d unites en stock\n", index, produit[index].nom,
           produit[index].quantite);
  }
}

// TODO
void afficher_description_produit(int index_produit) {
  if (index_produit >= nb_produit || index_produit < 0) {
    printf("\nVeuliez entrer un numero de produit correct\n");
  } else {
    printf("\nNumero: %d\n", index_produit);
    printf("Nom: %s\n", produit[index_produit].nom);
    printf("Description: %s\n", produit[index_produit].description);
    printf("Prix: %d\n", produit[index_produit].prix);
    printf("Quantité: %d\n", produit[index_produit].quantite);
  }
}

// TODO
void ajouter_panier(int index_produit) {
  if (index_produit >= nb_produit || index_produit < 0) {
    printf("\nVeuliez entrer un numero de produit correct\n");
  } else if (panier[index_produit] + 1 > produit[index_produit].quantite) {
    printf("\n%s n'est pas disponible en stock pour le moment.\n",
           produit[index_produit].nom);
  } else {
    printf("Couleur souhaitee (rouge, bleue, noir, gris) : ");
    char couleur[MAX_CARACTERES];
    scantf_result = scanf("%s", couleur);

    panier[index_produit]++;
    printf("\n%s a été ajouté(e) à votre panier.\n",
           produit[index_produit].nom);
  }
}

// TODO
void voir_panier() {
  bool etatPanier = false;

  for (int index = 0; index < MAX_PRODUIT; index++) {
    if (panier[index] != 0) {
      if (!etatPanier) {
        printf("\nContenu du panier :\n");
        etatPanier = true;
      }
      printf("%d x %s dont %d en stock\n", panier[index], produit[index].nom,
             produit[index].quantite);
    }
  }
  if (!etatPanier) {
    printf("\nVotre panier est vide.\n");
  }
}

// TODO
int acheter_contenu_panier() {
  int result = 0;
  for (int index = 0; index < MAX_PRODUIT; index++) {
    result += panier[index] * produit[index].prix; // Somme prix
    produit[index].quantite -= panier[index];      // Gestion Stock
    strcpy(client[numero_client_actif].historique_achat,
           ""); // Supprime l'Historique
    strcat(client[numero_client_actif].historique_achat,
           produit[index].nom); // Gestion Historique
  }
  if (result != 0) {
    printf("Prix avant utilisation des points de fidelité : %d\n", result);
    printf("points de fidelité utilisés : %d\n",
           client[numero_client_actif].points_fidelite);
    result -= client[numero_client_actif].points_fidelite * COTE_FIDELITE;

    client[numero_client_actif].points_fidelite =
        (int)COTE_FIDELITE * result / 100;
    printf("nouveau solde de points de fidelité : %d\n",
           client[numero_client_actif].points_fidelite);
  }
  return result;
}

// Log menu
void log_menu() {
  int numero_client = -1;
  printf("Veuillez entrer votre numero de client : ");
  scantf_result = scanf("%d", &numero_client);
  while (numero_client >= nb_client || numero_client < 0) {
    printf("Veuliez entrer un numero de client correct : ");
    scantf_result = scanf("%d", &numero_client);
  }
  numero_client_actif = numero_client;
}

// Main menu
int menu_client() {
  int choix;
  printf("Bienvenue %s %s, Vos derniers achat: %s",
         client[numero_client_actif].nom, client[numero_client_actif].prenom,
         client[numero_client_actif].historique_achat);
  do {
    printf("\n\n\n\n\nMenu :\n");
    printf("1. Afficher les produit en stock\n");
    printf("2. Afficher les informations sur un produit\n");
    printf("3. Ajouter un produit au panier\n");
    printf("4. Voir le contenu du panier\n");
    printf("5. Quitter\n");
    printf("Votre choix : ");
    scantf_result = scanf("%d", &choix);
    switch (choix) {
    case 1:
      afficher_produit();
      break;
    case 2: {
      int choixInfo;
      printf("Numero du produit : ");
      scantf_result = scanf("%d", &choixInfo);
      afficher_description_produit(choixInfo);
      break;
    }
    case 3: {
      int choixProduit;
      printf("Numero du produit a ajouter: ");
      scantf_result = scanf("%d", &choixProduit);
      ajouter_panier(choixProduit);
      break;
    }
    case 4:
      voir_panier();
      break;
    case 5:
      printf("Au revoir !\n");
      break;
    default:
      printf("Erreur : choix invalide.\n");
      break;
    }
  } while (choix != 5);
  printf("Prix total des achats : %d euros.\n", acheter_contenu_panier());
  return scantf_result;
}

int main_client() {
  // Initialisations
  client = malloc(MAX_CLIENT * sizeof(struct Client));
  produit = malloc(MAX_PRODUIT * sizeof(struct Produit));
  for (int index = 0; index < MAX_PRODUIT; index++) {
    panier[index] = 0;
  }
  lire_fichier_client();
  lire_fichier_produit();

  // login
  log_menu();
  // Fonction principale
  menu_client();
  // SAVE
  ecrire_fichier_client();
  ecrire_fichier_produit();
  // MEM FREE
  free(client);
  free(produit);
  return 0;
}

// --------------------------- Vendeur ---------------------------

// TODO
void afficher_liste_client() {
  printf("\nVoici la liste des client :\n");
  for (int index = 0; index < nb_client; index++) {
    printf("client numero %d, %s %s %s %s %s %s %s %d\n", index,
           client[index].nom, client[index].prenom, client[index].adresse,
           client[index].ville, client[index].code_postal,
           client[index].telephone, client[index].email,
           client[index].points_fidelite);
  }
}

// TODO
void creer_fiche_client() {
  if (nb_client >= MAX_CLIENT) {
    printf("Impossible de créer une nouvelle fiche client : le nombre maximum "
           "de client a été atteint (%d).\n",
           MAX_CLIENT);
    return;
  }

  printf("Nom : ");
  scantf_result = scanf("%s", client[nb_client].nom);
  printf("Prénom : ");
  scantf_result = scanf("%s", client[nb_client].prenom);
  printf("Adresse : ");
  scantf_result = scanf("%s", client[nb_client].adresse);
  printf("Ville : ");
  scantf_result = scanf("%s", client[nb_client].ville);
  printf("Code postal : ");
  scantf_result = scanf("%s", client[nb_client].code_postal);
  printf("Téléphone : ");
  scantf_result = scanf("%s", client[nb_client].telephone);
  printf("Email : ");
  scantf_result = scanf("%s", client[nb_client].email);
  client[nb_client].points_fidelite = 0;

  nb_client++;

  ecrire_fichier_client();
}

// TODO
void supprimer_client(int numero_client) {
  if (numero_client >= nb_client || numero_client < 0) {
    printf("\nVeuliez entrer un numero de client correct\n");
  } else {
    strncpy(client[numero_client].nom, "",
            MAX_CARACTERES); // mettre le nom du client sur la chaine vide
                             // permet de le marquer a supprimer
    ecrire_fichier_client();
  }
}

// TODO
void augmenter_stock(int numero_produit, int nb_augmenter) {
  if (numero_produit >= nb_produit || numero_produit < 0) {
    printf("\nVeuliez entrer un numero de produit correct\n");
  } else {
    produit[numero_produit].quantite += nb_augmenter;
    ecrire_fichier_produit();
  }
}

// TODO
void supprimer_produit(int numero_produit) {
  if (numero_produit >= nb_produit || numero_produit < 0) {
    printf("\nVeuliez entrer un numero de prooduit correct\n");
  } else {
    strncpy(produit[numero_produit].nom, "",
            MAX_CARACTERES); // mettre le nom du client sur la chaine vide
                             // permet de le marquer a supprimer
    ecrire_fichier_produit();
  }
}

void menu_vendeur() {
  int choix;
  do {
    printf("\nMenu vendeur :\n");
    printf("\n1. Afficher la liste des client\n");
    printf("2. Ajouter un client\n");
    printf("3. Supprimer un client\n");
    printf("4. Afficher les produit en stock\n");
    printf("5. Modifier le stock d'un produitt\n");
    printf("6. Supprimer un produit\n");
    printf("7. Quitter\n");
    printf("Votre choix : ");
    scantf_result = scanf("%d", &choix);
    switch (choix) {
    case 1:
      afficher_liste_client();
      break;
    case 2:
      creer_fiche_client();
      break;
    case 3:
      printf("Numero du client a supprimer : ");
      scantf_result = scanf("%d", &choix);
      supprimer_client(choix);
      break;
    case 4:
      afficher_produit();
      break;
    case 5: {
      int numero_produit;
      int nb_augmenter;
      printf("Numero du produit : ");
      scantf_result = scanf("%d", &numero_produit);
      printf("Quatité a ajouté : ");
      scantf_result = scanf("%d", &nb_augmenter);
      augmenter_stock(numero_produit, nb_augmenter);
      break;
    }
    case 6:
      printf("Numero du produit a supprimer : ");
      scantf_result = scanf("%d", &choix);
      supprimer_produit(choix);
      break;
    case 7:
      printf("Au revoir !\n");
      break;
    default:
      printf("Erreur : choix invalide.\n");
      break;
    }
  } while (choix != 7);
}

int main_vendeur() {
  // Initialisations
  client = malloc(MAX_CLIENT * sizeof(struct Client));
  produit = malloc(MAX_PRODUIT * sizeof(struct Produit));
  lire_fichier_client();
  lire_fichier_produit();

  // Fonction principale
  menu_vendeur();
  // SAVE
  ecrire_fichier_client();
  ecrire_fichier_produit();
  // MEM FREE
  free(client);
  free(produit);
  return 0;
}

// --------------------------- MAIN ---------------------------
void helpMessage(char *programmeName) {
  fprintf(stderr, "Usage: %s [option] command\n", programmeName);
  fprintf(stderr, "\nOptions:\n");
  fprintf(stderr, "-c, -C\t\t\tcustomer's menu\n");
  fprintf(stderr, "-v, -V\t\t\tvendor's menu\n");
  fprintf(stderr, "-h, -H, --help\t\tgive this help list.\n");
}

int main(int argc, char *argv[]) {
  printf("Hello World !\n");
  printf("Version 1.0 de l'executable %s\n\n", argv[0]);
  char scanChar[2];

  switch (argc) {
  case 1:
    do {
      printf(
          "Vous n'avez pas renseigné de parametre, choisissez ce dont que vous "
          "voulez acceder: \n");
      printf("0 pour le menu client\n1 pour le menu vendeur\nVotre choix : ");
      if (scanf("%s", scanChar) != 1) {
        fprintf(stderr, "\nErreur: saisie invalide.\n");
        return (1);
      }
      int uselessWarningButReturn = atoi(scanChar); //-Werror counter
      if (uselessWarningButReturn == 0) {
        return main_client();
      } else if (uselessWarningButReturn == 1) {
        return main_vendeur();
      } else {
        printf("Erreur: choix invalide.\n");
      }
    } while (true);
    break;
  case 2:
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-H") == 0 ||
        strcmp(argv[1], "--help") == 0) {
      helpMessage(argv[0]);
      return (0);
    } else if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "-C") == 0) {
      printf("Option -c ou -C spécifiée.\n");
      return (main_client());
    } else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "-V") == 0) {
      printf("Option -v ou -V spécifiée.\n");
      return (main_vendeur());
    } else {
      helpMessage(argv[0]);
      return (1);
    }
    break;
  default:
    helpMessage(argv[0]);
    return (1);
  }
  return (-1); // impossible normalement
}