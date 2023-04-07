//
// Created by miche on 07/04/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#include "FolderFormatter.h"

void rename_arw_files(const char *dir_path) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        printf("Could not open directory '%s'\n", dir_path);
        return;
    }

    int counter = 0;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".arw") != NULL) {
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

            struct stat st;
            if (stat(path, &st) == 0 && S_ISREG(st.st_mode)) {
                char new_path[1024];
                snprintf(new_path, sizeof(new_path), "%s/%d.arw", dir_path, counter++);

                if (rename(path, new_path) != 0) {
                    printf("Failed to rename file '%s'\n", entry->d_name);
                }
            }
        }
    }

    closedir(dir);
}