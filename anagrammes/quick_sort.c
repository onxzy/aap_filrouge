#include "quick_sort.h"

static int partition (char t [], int g, int d); 

// e1 <= e2
// int comparer(const void * e1, const void * e2) {
// 	int firstInt = * (const int *) e1;
//     int secondInt = * (const int *) e2;
//     return firstInt - secondInt;
// }

static void swap(char t[], int i1, int i2) {
	char aux = t[i2];
	t[i2] = t[i1];
	t[i1] = aux;
}

static void quickSort_rec(char t[], int d, int f) {
	int iPivot;
	if (f > d) {
		iPivot = partition(t, d, f);
		quickSort_rec(t, d, iPivot - 1);
		quickSort_rec(t, iPivot + 1, f);
	}
}

void quickSort(char t[], int n) {
	quickSort_rec(t, 0, n-1);
}


static int partition (char t [], int g, int d){ 
	int pg=g , pd=d-1; // On utilise g et d comme « pointeurs » qui se déplacent
	// On choisit le dernier élément comme pivot --> t[d] (à modifier par un indice aléatoire pour éviter le n² si liste inversée)
	
	int iPivot = g + (rand() % (d-g+1));
	swap(t,iPivot,d); 

	while (pg<pd) {
		// On déplace pg et pd jusqu’à trouver des valeurs incohérentes % pivot

		// while ( (pg<pd) &&  (comparer(t[pg],pivot)) ) {pg++ ;	stats.nbComparisons ++;}
		// while ( (pg<pd) && (!comparer(t[pd],pivot)) ) {pd-- ; stats.nbComparisons ++;}
		while ( (pg<pd) &&  (t[pg] <= t[d]) ) {
			pg++;
		}
		while ( (pg<pd) && (t[pd] > t[d]) ) {
			pd--;
		}

		// Comment compter correctement ? On utilise une fonction de comparaison...
		if (pg < pd) {
			swap(t,pg,pd); 
			pg++ ; pd-- ; 
		}
	}
	if (t[pg] <= t[d]) pg++ ;  
	swap(t, pg, d) ;

	return pg ; 
}



