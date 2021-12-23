#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

// C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
#include "../elt.h"
#include "../avl.h"
#include "quick_sort.h"

void signature(char** mot);

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

    // char t[] = {26,17,28,8,2,25,1,20,15,18,30,13,22,7,29,14,27,5,19,16,23,21,6,24,11,10,4,12,9,3,0,2};

    // int n = sizeof(t)/sizeof(char);

    // quickSort(t, n);

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

            i = 0; // remet le pointeur d'index pour le string du prénom au début
        }
        
        mot[i] = c;
        i++;
        // printf("%c", c);
    }  

    createDotAVL(root, "root");    




}