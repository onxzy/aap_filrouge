#include <assert.h>
#include <sys/stat.h>
#include <string.h>

//#define CLEAR2CONTINUE
#include "../../include/traces.h" 

//#define DEBUG
#include "../../include/check.h"

#include "avl.h" // prototypes 
#include "../quick_sort.h"

char * outputPath = "."; 

static T_avl newNodeAVL(char *e); 
static T_avlNode * rotateLeftAVL (T_avlNode * A); 
static T_avlNode * rotateRightAVL (T_avlNode * B);
static T_avlNode * balanceAVL(T_avlNode * A);
static char *hash(char* mot);


// Utilitaires
static int max(int a, int b) {
	if (a > b) return a;
	else return b;
}

static int min(int a, int b) {
	if (a < b) return a;
	else return b;
}


// Base
static T_avl newNodeAVL(char *e) {

	T_avlNode * node = (T_avlNode *) malloc(sizeof(T_avlNode));

	// node->val = hash(e);
	node->hash = hash(e);
	node->words = newList(e);
	node->bal = BALANCED;
	node->l = NULL;
	node->r = NULL;

	return node;

} 

static char *hash(char* mot) {
    char *sign = strdup(mot);
    quickSort(sign, strlen(sign));
    return sign;
}

static int sign_comp(char* e, T_avlNode * pRoot) {
	return (strcmp(hash(e), pRoot->hash) <= 0);
}

// return 1 if a corresponding hash node was found
// -1 if word was already in node words list
int indexWord(T_avlNode ** pRoot, char *e) {

	#ifdef SHOWDEBUG
	printf("\n\n### indexing %s ... \n", e);

	printf(">> Word infos \n");
	printf(">> + len %d \n", strlen(e));
	printf(">> + hash %s \n", hash(e));
	#endif

	// Chercher si le hash n'est pas déjà dans l'index
	int depth;
	T_avlNode * hashNode = searchHash(*pRoot, e, &depth);
	
	
	if (hashNode != NULL) { // si oui l'ajouter dans la liste de la node où il est
		
		#ifdef SHOWDEBUG
		printf("> Found at hash %s \n", hashNode->hash);
		printf("words list : ");
		printList(hashNode->words);
		#endif


		if (!searchList(hashNode->words, e)) { // Si le mot n'est pas déjà dans la liste de cette node, l'ajouter
			pushList(&(hashNode->words), e);
			return 1; 
		} else {
			#ifdef SHOWDEBUG
			printf("! Already in list\n");
			#endif
			return -1;
		}

	} else {
		// sinon rajouter une node avec le nouvel hash
		insertAVL(pRoot, e);

		#ifdef SHOWDEBUG
		printf("> Not found, creating and inserting new node \n");
		#endif

		return 0;
	}

}

int	insertAVL (T_avlNode ** pRoot, char *e) {
	int deltaH;

	if ((*pRoot) == NULL) {
		(*pRoot) = newNodeAVL(e);
		return 1;
	} 

	if (sign_comp(e, *pRoot)) {
		deltaH = insertAVL(&((*pRoot)->l), e);
		(*pRoot)->bal += deltaH;
	} else {
		deltaH = insertAVL(&((*pRoot)->r), e);
		(*pRoot)->bal += (-deltaH);
	}


	if (deltaH == 0) {
		return 0;
	} else {
		#ifdef SHOWDEBUG
		printf(">>>> balance \n");
		#endif
		*pRoot = balanceAVL(*pRoot);
	}

	if ((*pRoot)->bal != 0) {
		return 1;
	} else {
		return 0;
	}

}

static T_avlNode * rotateLeftAVL (T_avlNode * B) {
	
	// Rotation
	T_avlNode * A = B->r;
	B->r = A->l;
	A->l = B;

	// Mise à jour des facteurs de déséquilibre
	int a_prime = A->bal;
	int b_prime = B->bal;
	int b = b_prime + 1 - min(0, a_prime);
	int a = a_prime + 1 + max(0, b);

	A->bal = a;
	B->bal = b;

	return A;

}

static T_avlNode * rotateRightAVL (T_avlNode * A) {
	
	// Rotation
	T_avlNode * B = A->l;
	A->l = B->r;
	B->r = A;

	// Mise à jour des facteurs de déséquilibre
	int a = A->bal;
	int b = B->bal;
	int a_prime = a - 1 - max(0, b);
	int b_prime = b - 1 + min(0, a_prime);

	A->bal = a_prime;
	B->bal = b_prime;

	return B;

}


static T_avlNode * balanceAVL(T_avlNode * A) {
	
	if (A->bal > 0) { // Penche à gauche

		if (A->l->bal < 0) {
			A->l = rotateLeftAVL(A->l);
			return rotateRightAVL(A);
		} else {
			return rotateRightAVL(A);
		}

	} else if (A->bal < 0) { // Penche à droite
		if (A->r->bal > 0) {
			A->r = rotateRightAVL(A->r);
			return rotateLeftAVL(A);
		} else {
			return rotateLeftAVL(A);
		}
	}

	return A;

}




T_list * searchWord(T_avl root, char * word, int *pDepth) {

	T_avlNode *foundNode = searchHash(root, word, pDepth); // On cherche si le hash est dans l'AVL
	
	if (foundNode == NULL) return NULL; // si non on arrête là

	if (searchList(foundNode->words, word)) return &(foundNode->words); // si oui on cherche dans la liste de mots de ce noeud

}

T_avlNode * searchHash(T_avl root, char *e, int* pDepth) {

	*pDepth = 0;

	int test;
	char *e_hash = hash(e);

	while(root!=NULL) {	
		test = strcmp(e_hash, root->hash);

		if (test == 0) return root;
		else if  (test <= 0) root = root->l; 
		else root = root->r; 

		*pDepth += 1;
	}

	// pas trouvé (ou vide)
	return NULL;  
}

void printAVL(T_avl root, int indent) {
	int i; 
	// ordre de la récurrence : hauteur de l'arbre 
	// Affiche la racine de l'arbre passé en paramètre avec un niveau d'indentation proportionnel à la profondeur du sous-arbre 

	// pas de cas de base... 
	if (root!=NULL) {
		// afficher le sous-arbre droit avec indentation+1
		printAVL(root->r, indent+1);
		// afficher le noeud racine 
		for(i=0;i<indent;i++) printf("\t");
		printf("(%s, %d)\n", root->hash, root->bal);
		// afficher le sous-arbre gauche avec indentation+1
		printAVL(root->l, indent+1);
	}
}

int heightAVL(T_avl root){
	// hauteur d'un arbre 
	int l,r; 
	if (root == NULL) return -1;

	l = heightAVL(root->l);
	r = heightAVL(root->r);

	return 1+ ((l >= r) ? l : r); 
}

int nbNodesAVL(T_avl root){
	// nb de noeuds d'un arbre (y compris les feuilles) 
	if (root == NULL) 
		return 0;
	
	return 1+ nbNodesAVL(root->l) + nbNodesAVL(root->r);
}

static void  genDotAVL(T_avl root, FILE *fp) {
	// Attention : les fonction toString utilisent un buffer alloué comme une variable statique 
	// => elles renvoient toujours la même adresse 
	// => on ne peut pas faire deux appels à toString dans le même printf()

	char *str_words_buffer = (char *) malloc(sizeof(char)*MAXWORDLEN*root->words.size);
	
	sprintList(&str_words_buffer, root->words);

	#ifdef SHOWDEBUG
	printf("%s\n", str_words_buffer);
	#endif

    fprintf(fp, "\t\"%s\"",(root->hash)); 
    fprintf(fp, " [label = \"{{<c> %s} | {<b> %s} | { <g> | <d>}}\"];\n",root->hash, str_words_buffer);
    if (root->r == NULL && root->l == NULL) {
        fprintf(fp, "\t\"%s\"", (root->hash)); 
		fprintf(fp, " [label = \"{{<c> %s} | {<b> %s} | { <g> NULL | <d> NULL}}\"];\n",root->hash, str_words_buffer);
	}
    else if (root->r == NULL) {
        fprintf(fp, "\t\"%s\"", (root->hash));
		fprintf(fp, " [label = \"{{<c> %s} | {<b> %s} | { <g> | <d> NULL}}\"];\n",root->hash, str_words_buffer);
	}
	else if ( root->l == NULL) {
        fprintf(fp, "\t\"%s\"",(root->hash));
		fprintf(fp, " [label = \"{{<c> %s} | {<b> %s} | { <g> NULL | <d>}}\"];\n",root->hash, str_words_buffer);
	}
	
    if (root->l) {
        fprintf(fp, "\t\"%s\"",(root->hash));
		fprintf(fp, ":g -> \"%s\";\n", (root->l->hash));
        genDotAVL(root->l, fp);
    }

    if (root->r) {
        fprintf(fp, "\t\"%s\"",(root->hash));
		fprintf(fp,":d -> \"%s\";\n", (root->r->hash));
        genDotAVL(root->r, fp);
    }

}


void createDotAVL(const T_avl root, const char *basename) {
	static char oldBasename[FILENAME_MAX + 1] = "";
	static unsigned int noVersion = 0;

	char DOSSIER_DOT[FILENAME_MAX + 1]; 
	char DOSSIER_PNG[FILENAME_MAX + 1]; 

	char fnameDot [FILENAME_MAX + 1];
	char fnamePng [FILENAME_MAX + 1];
	char	cmdLine [2 * FILENAME_MAX + 20];
	FILE *fp;
	struct stat sb;
	

	// Au premier appel, création (si nécessaire) des répertoires
	// où seront rangés les fichiers .dot et .png générés par cette fonction	

	// il faut créer le répertoire outputPath s'il n'existe pas 
	if (stat(outputPath, &sb) == 0 && S_ISDIR(sb.st_mode)) {
    } else {
        printf("Création du répertoire %s\n", outputPath);
		mkdir(outputPath, 0777);
    }

	// il faut créer les répertoires outputPath/png et /dot 
	sprintf(DOSSIER_DOT, "%s/dot/",outputPath);
	sprintf(DOSSIER_PNG, "%s/png/",outputPath);

	if (oldBasename[0] == '\0') {
		mkdir(DOSSIER_DOT,	S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
		mkdir(DOSSIER_PNG,	S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	}

	 // S'il y a changement de nom de base alors recommencer à zéro
	 // la numérotation des fichiers 

	if (strcmp(oldBasename, basename) != 0) {
		noVersion = 0;
		strcpy(oldBasename, basename); 
	}

	sprintf(fnameDot, "%s%s_v%02u.dot", DOSSIER_DOT, basename, noVersion);
	sprintf(fnamePng, "%s%s_v%02u.png", DOSSIER_PNG, basename, noVersion);

	CHECK_IF(fp = fopen(fnameDot, "w"), NULL, "erreur fopen dans saveDotBST"); 
	
	noVersion ++;
    fprintf(fp, "digraph %s {\n", basename);
 	fprintf(fp, 
		"\tnode [\n"
			"\t\tfontname  = \"Arial bold\" \n"
			"\t\tfontsize  = \"14\"\n"
			"\t\tfontcolor = \"red\"\n"
			"\t\tstyle     = \"rounded, filled\"\n"
			"\t\tshape     = \"record\"\n"
			"\t\tfillcolor = \"grey90\"\n"
			"\t\tcolor     = \"blue\"\n"
			"\t\twidth     = \"2\"\n"
			"\t]\n"
		"\n"
		"\tedge [\n"
			"\t\tcolor     = \"blue\"\n"
		"\t]\n\n"
	);

    if (root == NULL)
        fprintf(fp, "\n");
    else
        genDotAVL(root, fp);

    fprintf(fp, "}\n");	
    fclose(fp);

    sprintf(cmdLine, "dot -Tpng  %s -o %s -Gcharset=latin1", fnameDot, fnamePng);
    system(cmdLine);

    printf("Creation de '%s' et '%s' ... effectuee\n", fnameDot, fnamePng);
}

