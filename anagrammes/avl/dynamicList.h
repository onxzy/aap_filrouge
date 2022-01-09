#pragma once // Inclure une seule fois ce header -> éviter les include loop

#define START_LEN 1

// On définit un type de liste à longueur variable
typedef struct list {
    char **list;
    int used;
    int size;
} T_list;


T_list newList(char *word);
void pushList(T_list *list, char *word);
int lengthList(T_list list);
void printList(T_list list);
void sprintList(char **str, T_list list);
void fprintList(FILE * fp, T_list list);
int searchList(T_list list, char *word);
