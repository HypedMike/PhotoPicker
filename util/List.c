//
// Created by miche on 06/04/2023.
//

#include <dirent.h>
#include <stdio.h>


#include "List.h"

void push(Node **list, char *filename, int grade){
    Node *new_node = malloc(sizeof (Node));

    strcpy(new_node->filename, filename);
    new_node->grade = grade;
    new_node->next = NULL;

    if(*list == NULL){
        *list = new_node;
        return;
    }

    push(&(*list)->next, filename, grade);
}

/**
 *
 * @param list
 * @param filename
 * @return -1 if no match was found. 0 if a match was found
 */
int seekAndPop(Node**list, char *filename){
    if((*list) == NULL){
        return -1;
    }

    if((*list)->next == NULL && strcmp((*list)->filename, filename) != 0){
        return -1;
    }

    if(strcmp((*list)->next->filename, filename) == 0){
        Node *temp = (*list)->next;
        (*list)->next = (*list)->next->next;
        free(temp);
        return 0;
    }

    return seekAndPop(&(*list)->next, filename);
}

Node *createList(char *path){
    Node *list = NULL;
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            push(&list, dir->d_name, 0);
        }
        closedir(d);
    }

    return list;
}

void print(Node *list){
    if(list == NULL){
        return;
    }
    printf("%s\n", list->filename);

    print(list->next);
}

int seek(Node *list, char *filename){
    if((list) == NULL){
        return -1;
    }

    if(strcmp((list)->filename, filename) == 0){
        return 1;
    }

    return seek(list->next, filename);
}

int save(Node *list, char *path){
    FILE *file = fopen(path, "w");
    fprintf(file, "");
    fclose(file);


    file = fopen(path, "a");
    Node *counter = list;
    while(counter != NULL){
        fprintf(file, "%s, %d\n", counter->filename, counter->grade);
        counter = counter->next;
    }
    fclose(file);
    return 0;
}

void *saveAsync(void *args){
    SaveAsyncInterface *sai = (SaveAsyncInterface *) args;
    save(sai->list, sai->path);
}