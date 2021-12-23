#include "../main.h"

#define START_LEN 5

// On définit un type de liste à longueur variable
typedef struct {
    char **list;
    int used;
    int size;
} T_list;


T_list newList(char *word);
void pushList(T_list *list, char *word);
void printList(T_list list);
void sprintList(char **str, T_list list);
