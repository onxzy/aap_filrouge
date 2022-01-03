#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../main.h"
#include "dynamicList.h"

T_list newList(char *word) {
    T_list list;
    list.list = (char **) malloc(sizeof(char)*MAXWORDLEN*START_LEN);
    list.list[0] = strdup(word);
    list.used = 1;
    list.size = START_LEN;
    
    return list;
}

void pushList(T_list *list, char *word) {
    if (list->used == list->size) {
        list->size *= 2;
        list->list = realloc(list->list, list->size * sizeof(char)*MAXWORDLEN);
    }
    list->list[list->used++] = strdup(word);
}

int lengthList(T_list list) {
    return list.used;
}

void printList(T_list list) {
    printf("[");
    int i;
    for (i = 0; i < list.used - 1; i++)
    {
        // printf("%s\n", list.list[i]);
        printf("%s, ", list.list[i]);
    }
    printf("%s", list.list[i]);
    printf("]\n");
}

void sprintList(char **str, T_list list) {
    sprintf(*str, "[");
    for (int i = 0; i < list.used; i++)
    {
        sprintf(*str + strlen(*str), "%s,", list.list[i]);
    }
    sprintf(*str + strlen(*str), "]");
}

void fprintList(FILE * fp, T_list list) {
    fprintf(fp, "[");
    int i;
    for (i = 0; i < list.used - 1; i++)
    {
        fprintf(fp, list.list[i]);
        fprintf(fp, ", ");
    }
    fprintf(fp, list.list[i]);
    fprintf(fp, "]\n");
}

int searchList(T_list list, char *word) {
    for (int i = 0; i < list.used; i++)
    {
        if (strcmp(list.list[i], word) == 0) return 1;
    }
    return 0;
}

// // Test
// void main() {
//     T_list list = newList("bonjour");
//     pushList(&list, "je");
//     pushList(&list, "suis");
//     pushList(&list, "Thomas");
//     pushList(&list, "et");

//     printList(list);

//     pushList(&list, "j'essaye");
//     pushList(&list, "les");
//     pushList(&list, "listes");
//     pushList(&list, "dynamiques");
//     printList(list);

//     char *str = (char *) malloc(sizeof(char)*MAXWORDLEN*list.size);
//     sprintList(&str, list);
//     printf("%s\n", str);

//     printf("search 'je' : %d\n", searchList(list, "je"));
//     printf("search 'listes' : %d\n", searchList(list, "listes"));
//     printf("search 'non' : %d\n", searchList(list, "non"));
// }