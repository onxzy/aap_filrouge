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
#include "quick_sort.h"
#include "avl/avl.h"

long ms();
long start_time, end_time;
T_avl indexing(char* filepath);
void searchAnagrammes(T_avl root, int *nb_anagrammes, T_avlNode **ana_nodes);

int main(int argc, char ** argv) {

    system("clear");
    
    // récuperer les arguments en entrée
    if (argc != 2) {
        printf(REDB " ERREUR " reset " " "Nombre d'arguments incorrect. Nombre attendu : " MAG "1\n" reset);
        printf("\n");
        printf(CYNB " AIDE " reset " " "Merci de préciser un chemin vers un dictionnaire.\n");
        printf("\n");
        return 0;
    }
    char *filepath = argv[1];

    T_avl root = indexing(filepath);

    if (root == NULL) return 0;

    int nb_anagrammes = 0;
    T_avlNode **ana_nodes = (T_avlNode **) malloc(sizeof(T_avlNode *) * nbNodesAVL(root));
    loopAVL(root, searchAnagrammes, &nb_anagrammes, ana_nodes);
    printf(GRNB " " reset " • Nombre d' anagrammes : %d\n", nb_anagrammes);
    nd_quickSort(ana_nodes, nb_anagrammes + 1);

    printf("\n");
    printf("\n");
    printf("\n");


    printf(BLK WHTB " LISTE D'ANAGRAMMES PRÊTE                                                      "reset "\n");
    printf("\n");
    printf(BLK WHTB " ^C " reset " Quitter " BLK WHTB " t " reset " Afficher la liste dans le terminal " BLK WHTB " f " reset " Écrire la liste dans un fichier" "\n");
    printf("\n");
    printf(CYN "Si votre entrée n'est pas comprise, l'option t est appliquée." reset "\n");
    printf("> Votre choix : " MAG);

    char choice[1] = {'\0'};
    scanf("%1s", choice);


    printf(reset "\n");

    if (choice[0] == 'f') {
        FILE * fp = fopen("anagrammes.txt", "w");
        for (int i = 0; i <= nb_anagrammes; i++)
        {
            if ((ana_nodes[i]) != NULL) {
                fprintList(fp, (ana_nodes[i])->words);
            }
        }

        printf(GRNB " " reset GRN " ✓ Liste dans le fichier : " reset MAG "./anagrammes.txt "reset "!\n");
    } else {
        for (int i = 0; i <= nb_anagrammes; i++)
        {
            if ((ana_nodes[i]) != NULL) {
                printList((ana_nodes[i])->words);
            }
        }
    }

    printf("\n");
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
    int duplicates_words = 0;
    char mot[MAXWORDLEN] = {'\0'}; // On fixe la longueur max d'un mot à 128

    char c;
    int i = 0;
    // Stats
    // int nb_found = 0;
    int nb_char = 0;
    while ( (c = fgetc(file)) != EOF) {
        nb_char++;

        if (c == '\n') {
            nb_lignes++;

            mot[i] = '\0'; // indique la fin du string
            if (indexWord(&root, mot) == -1) {
                duplicates_words+= 1;
            }

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
    printf(BLUB " " reset " • Nombre de mots uniques : %d\n", nb_lignes - duplicates_words);
    // printf(BLUB " " reset " • Taille des mots : %d\n", nb_char);
    printf(BLUB " " reset " • Nombre de noeuds : %d\n", nbNodes);
    // printf(BLUB " " reset " • Hauteur de l'AVL : %d\n", heightAVL(root));
    // printf(BLUB " " reset " • Hauteur minimale d'un arbre avec ce nombre de noeuds : %d\n", (int) log2(nbNodes));
    printf("\n");

    return root;

}

void searchAnagrammes(T_avl root, int *nb_anagrammes, T_avlNode **ana_nodes) {
    if (lengthList(root->words) > 1) {
        *nb_anagrammes += 1;
        ana_nodes[*nb_anagrammes] = root;
    }
}