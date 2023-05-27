// VAL Struct
#define MAX_CARACTERES 50
#define MAX_DESCRIPTION 256 * 10

// VAL consigne
#define MAX_CLIENT 50
#define MAX_PRODUIT 4

// UN INT EN %
#define COTE_FIDELITE 1

// DEF struct
struct Produit {
  char nom[MAX_CARACTERES];
  char description[MAX_DESCRIPTION];
  int prix;
  int quantite;
} Produit;

struct Client {
  char nom[MAX_CARACTERES];
  char prenom[MAX_CARACTERES];
  char adresse[MAX_CARACTERES];
  char ville[MAX_CARACTERES];
  char code_postal[MAX_CARACTERES];
  char telephone[MAX_CARACTERES];
  char email[MAX_CARACTERES];
  int points_fidelite;
  char historique_achat[MAX_DESCRIPTION];
} Client;

// VAR Globale
struct Produit *produit;
int nb_produit;

struct Client *client;
int nb_client;

int numero_client_actif;

int panier[MAX_PRODUIT];
int scantf_result;
char *fget_result;