#include <stdio.h>
#include <assert.h>

//#define CLEAR2CONTINUE
#include "include/traces.h" 

// C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
#include "elt.h"
#include "avl.h"

int main(int argc, char ** argv) {
	T_avl root = NULL; 
	T_avlNode * pAux = NULL;

	T_elt srch; 

	CLRSCR();
	WHOAMI(); 

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	//coucou

	outputPath = "output";
	
	// 8, 11, 16, 5, 7, 14, 6, 1, 3, 10, 12,16
	// insertAVL(&root, 8);
	// insertAVL(&root, 11);
	// insertAVL(&root, 16);
	// insertAVL(&root, 5);
	// insertAVL(&root, 7);
	// insertAVL(&root, 14);
	// insertAVL(&root, 6);
	// insertAVL(&root, 1);
	// insertAVL(&root, 3);
	// insertAVL(&root, 10);
	// insertAVL(&root, 12);

	insertAVL(&root, 8);
	insertAVL(&root, 1);
	insertAVL(&root, 7);
	insertAVL(&root, 4);
	insertAVL(&root, 9);
	insertAVL(&root, 2);
	insertAVL(&root, 3);
	insertAVL(&root, 17);
	insertAVL(&root, 23);
	insertAVL(&root, 10);
	insertAVL(&root, 16);
	insertAVL(&root, 24);
	insertAVL(&root, 11);
	insertAVL(&root, 6);
	insertAVL(&root, 15);
	insertAVL(&root, 22);
	insertAVL(&root, 13);
	insertAVL(&root, 12);
	insertAVL(&root, 5);
	insertAVL(&root, 21);
	insertAVL(&root, 25);
	insertAVL(&root, 20);
	insertAVL(&root, 19);
	insertAVL(&root, 18);
	insertAVL(&root, 14);
	

	// printf("\n\n#1\n");
	// insertAVL(&root, 8);
	// printf("==== affichage 1 ====\n");
	// printAVL(root, 0);

	// printf("\n\n#2\n");
	// insertAVL(&root, 11);
	// printf("==== affichage 2 ====\n");
	// printAVL(root, 0);

	// printf("\n\n#3\n");
	// insertAVL(&root, 16);
	printf("==== affichage final ====\n");
	printAVL(root, 0); 

	srch = 16;
	pAux = searchAVL_it(root,srch); 
	printf("trouvé : %s\n",toString(pAux->val));
	pAux = searchAVL_rec(root,srch); 
	printf("trouvé : %s\n",toString(pAux->val));
	
	if (root==NULL) printf("null");
	printf("hauteur : %d\n",heightAVL(root));
	printf("nb noeuds : %d\n",nbNodesAVL(root));

	createDotAVL(root, "root");

	return 0;
}







