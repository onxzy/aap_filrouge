#pragma once // Inclure une seule fois ce header -> éviter les include loop

#include "dynamicList.h"

// Type définissant le facteur d'équilibre (bal) d'un noeud d'un arbre binaire
typedef enum {
    DOUBLE_RIGHT = -2,
    RIGHT = -1,
    BALANCED,
    LEFT,
    DOUBLE_LEFT
} enum_bal;

typedef struct node{
	// char *val; // élément contenu dans le noeud 
    char *hash; // hash du mot
    T_list words; // listes des mots ayant ce hash
	enum_bal bal; // facteur de déséquilibre
	struct node *l; // pointeur vers sous-arbre gauche
	struct node *r; // pointeur vers sous-arbre droit 
} T_avlNode, *T_avl;

extern char * outputPath;

int indexWord(T_avlNode ** pRoot, char *e);
int	insertAVL (T_avlNode ** root, char *e);
void printAVL(T_avl root, int indent); 
int heightAVL(T_avl);
int nbNodesAVL(T_avl);
void loopAVL(T_avl root, void f(T_avl root, int *nb_anagrammes, T_avlNode **ana_nodes), int *nb_anagrammes, T_avlNode **ana_nodes);
T_avlNode * searchHash(T_avl root, char *e, int* pDepth);
T_list * searchWord(T_avl root, char * word, int *pDepth);

void createDotAVL(const T_avl root, const char *basename); 