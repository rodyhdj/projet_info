CC=gcc
CFLAGS= -Wall -pedantic -std=c99 #-Werror

SRC_DIR=projet_info
OBJ_DIR=obj
BIN_DIR=bin

# Liste des fichiers source pour le client et le vendeur
CLIENT_SRC=$(SRC_DIR)/fichier_client.c
VENDEUR_SRC=$(SRC_DIR)/fichier_vendeur.c

# Liste des fichiers objet correspondants
CLIENT_OBJ=$(OBJ_DIR)/fichier_client.o
VENDEUR_OBJ=$(OBJ_DIR)/fichier_vendeur.o

# Programme principal et son fichier source
#MAIN=main
MAIN=$(BIN_DIR)/program
MAIN_SRC=$(SRC_DIR)/main.c

all: $(MAIN)

$(MAIN): $(CLIENT_OBJ) $(VENDEUR_OBJ) $(MAIN_SRC)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT_OBJ): $(CLIENT_SRC)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(VENDEUR_OBJ): $(VENDEUR_SRC)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*

.PHONY: all clean
