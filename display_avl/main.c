#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

// C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
#include "avl/elt.h"
#include "avl/avl.h"

int main(int argc, char ** argv) {
    // récuperer les arguments en entrée
    if (argc != 3) {
        printf("Nombre d'arguments incorrect\n");
        return 0;
    }

    char *filePath = argv[1];
    int n = atoi(argv[2]);

    if (n < 1) {
        printf("Merci d'entrer un nombre de mots >= 1\n");
        return 0;
    }

    printf("Affichage des étapes de construction d'un AVL contenant les %d premiers mots du fichier %s\n", n, filePath);

    
    // initialisation des variables pour l'AVL et dot/graphviz
    T_avl root = NULL; 
    outputPath = "output";


    // récupérer le fichier
    FILE *file = fopen(filePath, "r");

    /*

        Gérer le pbm du fichier n'existe pas qui cause un seg fault !

    */


    // lire le fichier ligne par lignes jusqu'à n lignes
    int nb_lignes = 0;
    char prenom[128] = {'\0'}; // On fixe la longueur max d'un prenom à 128

    char c;
    int i = 0;
    while ( (c = fgetc(file)) != EOF) {
        if (c == '\n') {
            nb_lignes++;

            prenom[i+1] = '\0'; // indique la fin du string
            insertAVL(&root, prenom);
            createDotAVL(root, "root");

            i = 0; // remet le pointeur d'index pour le string du prénom au début
            if (nb_lignes >= n) break; // finir la boucle si on a lu n lignes
        }
        
        prenom[i] = c;
        i++;
    }      


    return 0;
}