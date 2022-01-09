#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "../include/traces.h" 
#include "../include/ansi_colors.h" 

// C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
#include "avl/elt.h"
#include "avl/avl.h"

#include "main.h"

int main(int argc, char ** argv) {
    system("clear");

    // récuperer les arguments en entrée
    if (argc != 3) {
        printf(REDB " ERREUR " reset " " "Nombre d'arguments incorrect. Nombre attendu : " MAG "2\n" reset);
        printf("\n");
        printf(CYNB " AIDE " reset " " "./display_avl.exe <filePath> <stepCount>\n");
        printf(MAG "Exemple : " reset "./display_avl.exe PrenomsV2.txt 10\n");
        printf("\n");
        return 0;
    }

    char *filePath = argv[1];
    int n = atoi(argv[2]);

    if (n < 1) {
        printf(REDB " ERREUR " reset " " "Merci d'entrer un nombre de mots " MAG ">= 1\n" reset);
        printf("\n");
        return 0;
    }

    
    // initialisation des variables pour l'AVL et dot/graphviz
    T_avl root = NULL; 
    outputPath = "output";


    // récupérer le fichier
    FILE *file = fopen(filePath, "r");

    // Vérifie que le fichier existe
    if (file == NULL) {
        printf(REDB " ERREUR " reset " " "Le fichier renseigné n'existe pas. \n" reset);
        printf("\n");
        return 0;
    }

    // Vérifie que le fichier n'est pas vide
    fseek (file, 0, SEEK_END);
    int size = ftell(file);
    if (0 == size) {
        printf(REDB " ERREUR " reset " " "Le fichier renseigné est vide. \n" reset);
        printf("\n");
        return 0;
    }
    fseek(file, 0, SEEK_SET); // retourne au début du fichier

    printf(CYNB " INFO " reset " " "Affichage des étapes de construction d'un AVL contenant les " MAG "%d" reset " premiers mots du fichier " MAG "%s" reset "\n",n,  filePath);
    printf("\n");

    // lire le fichier ligne par lignes jusqu'à n lignes
    int nb_lignes = 0;
    char prenom[MAX_PRENOM_LENGTH] = {'\0'}; // On fixe la longueur max d'un prenom à 128

    char c;
    int i = 0;
    while ( (c = fgetc(file)) != EOF) {
        if (c == '\n') {
            nb_lignes++;

            prenom[i] = '\0'; // indique la fin du string
            insertAVL(&root, prenom);
            createDotAVL(root, "root");

            i = 0; // remet le pointeur d'index pour le string du prénom au début
            if (nb_lignes >= n) break; // finir la boucle si on a lu n lignes
            
        } else {
            prenom[i] = c;
            i++;
        }
        
        
    }      

    printf("\n");
    printf(GRNB " SUCCESS " reset " " "Affichage terminé. \n" reset);
    printf("\n");


    return 0;
}