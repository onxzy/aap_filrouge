#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <math.h>

//#define CLEAR2CONTINUE
#include "../include/traces.h" 
#include "../include/ansi_colors.h" 

#include "main.h"
#include "avl/avl.h"

long ms();
long start_time, end_time;
T_avl indexing(char* filepath);

int main(int argc, char ** argv) {

    system("clear");
    
    // récuperer les arguments en entrée
    if (argc != 2) {
        printf(REDB " ERREUR " reset " " "Nombre d'arguments incorrect. Nombre attendu : " MAG "1\n" reset);
        printf("\n");
        printf(CYNB " INFO " reset " " "Merci de préciser un chemin vers un dictionnaire.\n");
        printf("\n");
        return 0;
    }
    char *filepath = argv[1];

    T_avl root = indexing(filepath);

    if (root == NULL) return 0;

    printf("\n");
    printf("\n");
    printf("\n");


    // outputPath = "output";
    // createDotAVL(root, "root");  

    searching(root);
    
    // scanf();
    // // printf("• Nombre de hash : %d\n", nb_found);
    // // printf("%d\n", nb_found);
    // printf("\n\n");
    // createDotAVL(root, "root");    
    return 0;
}


long ns() {
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return t.tv_sec*1000000 + t.tv_nsec/1e3;
}

T_avl indexing(char* filepath) {

    T_avl root = NULL;

    // récupérer le fichier
    FILE *file = fopen(filepath, "r");

    // Vérifie que le fichier existe
    if (file == NULL) {
        printf(REDB " ERREUR " reset " " "Le fichier renseigné n'existe pas. \n" reset);
        printf("\n");
        return NULL;
    }

    // Vérifie que le fichier n'est pas vide
    fseek (file, 0, SEEK_END);
    int size = ftell(file);
    if (0 == size) {
        printf(REDB " ERREUR " reset " " "Le fichier renseigné est vide. \n" reset);
        printf("\n");
        return NULL;
    }
    fseek(file, 0, SEEK_SET); // retourne au début du fichier


    printf(CYNB " INFO " reset " " "Indexation du fichier " MAG "%s" reset "\n", filepath);
    printf("\n");

    // Intilialisation du compteur de temps
    start_time = ns();

    // lire le fichier ligne par lignes jusqu'à n lignes
    int nb_lignes = 0;
    char mot[MAXWORDLEN] = {'\0'}; // On fixe la longueur max d'un mot à 128

    char c;
    int i = 0;
    // Stats
    int nb_found = 0;
    int nb_char = 0;
    while ( (c = fgetc(file)) != EOF) {
        nb_char++;

        if (c == '\n') {
            nb_lignes++;

            mot[i] = '\0'; // indique la fin du string
            nb_found += indexWord(&root, mot);

            i = 0; // remet le pointeur d'index pour le string du mot au début
        } else {
            mot[i] = c;
            i++;
        }
           
    }  

    end_time = ns();

    system("clear");
    
    printf(GRNB " SUCCESS                                                                       \n" reset);
    printf(GRNB " " reset " Fichier indexé : "  MAG "%s" reset "\n", filepath);
    printf(GRNB " " reset " Temps écoulé : "  MAG "%fms" reset "\n", (end_time-start_time)/1e3);
    printf("\n");

    int nbNodes = nbNodesAVL(root);
    printf(BLUB " STATISTIQUES                                                                  \n" reset);
    printf(BLUB " " reset " • Nombre de mots : %d\n", nb_lignes);
    printf(BLUB " " reset " • Taille des mots : %d\n", nb_char);
    printf(BLUB " " reset " • Nombre de noeuds : %d\n", nbNodes);
    printf(BLUB " " reset " • Hauteur de l'AVL : %d\n", heightAVL(root));
    printf(BLUB " " reset " • Hauteur minimale d'un arbre avec ce nombre de noeuds : %d\n", (int) log2(nbNodes));
    printf("\n");

    return root;

}


void searching(T_avl root) {

    static int displayHeading = 1;
    if (displayHeading) {
        printf(BLK WHTB " CHERCHER UN MOT DANS LE DICTIONNAIRE                                          "reset "\n");
        printf("\n");
        printf(BLK WHTB " ^C " reset " Quitter" "\n");
        printf("\n");
        displayHeading = 0;
    }

    
    printf(CYN "Entrez votre mot en MAJUSCULES, sans espaces et caractères spéciaux." reset "\n");
    printf("> Mot à chercher : " MAG);
    char word[128] = {'\0'};
    scanf("%127s", word);
    printf(reset "\n");

    search(root, word);

    
    searching(root);

}

void search(T_avl root, char * word) {
    int depth;
    
    printf(CYNB " INFO " reset " " "Recherche du mot " MAG "%s" reset, word);

    start_time = ns(); // Intilialisation du compteur de temps
    T_list * words = searchWord(root, word, &depth);
    end_time = ns();

    printf("\33[2K\r"); // Permet d'effacer la dernière ligne du terminal

    if (words == NULL) {
        printf(REDB " " reset RED " ✘ Non trouvé !\n" reset);

        printf(REDB " " reset " • Temps écoulé : " MAG "%fms" reset "\n", (end_time - start_time)/1e3);
    } else {
        printf(GRNB " " reset GRN " ✓ Trouvé !\n" reset);

        printf(GRNB " " reset " • Temps écoulé : " MAG "%fms" reset "\n", (end_time - start_time)/1e3);
        printf(GRNB " " reset " • Profondeur : " MAG "%d" reset "\n", depth);
        printf(GRNB " " reset " • Mots dans cette node : " MAG); printList(*words); printf(reset);

    }

    printf("\n");
}