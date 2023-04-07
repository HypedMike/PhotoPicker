#include <stdio.h>
#include "util/List.h"
#include <pthread.h>
#include <string.h>

int main(void) {
    Node *list = createList(".");
    Node *new_list = NULL;

    pthread_t saveThread;
    SaveAsyncInterface *sai = malloc(sizeof(SaveAsyncInterface));
    strcpy(sai->path, "./text.txt");
    sai->list = new_list;

    printf("List is ready. Type the number of the image you want to add followed by a grading, like this\n456 2\n");

    int loop = 1;

    while(loop == 1){
        char name[100];
        int grade;

        scanf("%s %d", name, &grade);

        if(strcmp(name, "q") == 0){
            loop = 0;
            break;
        }

        if(seek(list, name) == 1 && seek(new_list, name) == -1){
            push(&new_list, name, grade);
            pthread_create(&saveThread, NULL, saveAsync, (void *) sai);
        }else{
            printf("The current file: %s does not exist\n", name);
        }
    }

    return(0);
}