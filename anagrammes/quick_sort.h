#pragma once // Inclure une seule fois ce header -> éviter les include loop

#include <stdio.h>
#include <stdlib.h>
#include "avl/avl.h"

void quickSort(char t[], int n);
void nd_quickSort(T_avlNode **ana_nodes, int n);