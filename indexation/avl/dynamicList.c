#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void printList(T_list list) {
    printf("[");
    for (int i = 0; i < list.used; i++)
    {
        // printf("%s\n", list.list[i]);
        printf("%s,", list.list[i]);
    }
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
// }