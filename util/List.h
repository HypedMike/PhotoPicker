//
// Created by miche on 06/04/2023.
//

#ifndef PHOTOPICKER_LIST_H
#define PHOTOPICKER_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_list{
    char filename[300];
    int grade;
    struct node_list *next;
} Node;

typedef struct saveasync_interface{
    char path[300];
    Node **list;
} SaveAsyncInterface;


int seekAndPop(Node**list, char *filename);

void push(Node **list, char *filename, int grade);

Node *createList(char *path);

void print(Node *list);


/**
 *
 * @param list
 * @param filename
 * @return -1 if no match is found, 1 if a match is found
 */
int seek(Node *list, char *filename);

int save(Node *list, char *path);

void *saveAsync(void *args);
#endif //PHOTOPICKER_LIST_H
