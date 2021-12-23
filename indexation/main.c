#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

#include "avl/avl.h"

int main(int argc, char ** argv) {
    
    // récuperer les arguments en entrée
    if (argc != 2) {
        printf("Nombre d'arguments incorrect\n");
        return 0;
    }

    char *filepath = argv[1];

    // initialisation des variables pour l'AVL et dot/graphviz
    T_avl root = NULL; 
    outputPath = "output";

    // récupérer le fichier
    FILE *file = fopen(filepath, "r");

    // lire le fichier ligne par lignes jusqu'à n lignes
    int nb_lignes = 0;
    char mot[128] = {'\0'}; // On fixe la longueur max d'un mot à 128

    char c;
    int i = 0;
    while ( (c = fgetc(file)) != EOF) {
        if (c == '\n') {
            nb_lignes++;

            mot[i+1] = '\0'; // indique la fin du string
            insertAVL(&root, mot);

            i = 0; // remet le pointeur d'index pour le string du mot au début
        }
        
        mot[i] = c;
        i++;
    }  

    createDotAVL(root, "root");    

}

