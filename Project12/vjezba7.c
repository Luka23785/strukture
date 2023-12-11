#define _CRT_SECURE_NO_WARNIGNS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

struct Directory {
    char name[MAX_NAME_LENGTH];
    struct Directory* parent;
    struct Directory* subdirectories;
};

struct Directory* createDirectory(char name[], struct Directory* parent) {
    struct Directory* newDir = (struct Directory*)malloc(sizeof(struct Directory));
    strcpy(newDir->name, name);
    newDir->parent = parent;
    newDir->subdirectories = NULL;
    return newDir;
}

void listDirectory(struct Directory* currentDir) {
    printf("Contents of directory '%s':\n", currentDir->name);
    struct Directory* subdir = currentDir->subdirectories;
    while (subdir != NULL) {
        printf("%s\n", subdir->name);
        subdir = subdir->subdirectories;
    }
}

struct Directory* changeDirectory(struct Directory* currentDir, char dirName[]) {
    if (strcmp(dirName, "..") == 0) {
        if (currentDir->parent != NULL) {
            return currentDir->parent;
        }
        else {
            printf("You are already in the root directory.\n");
            return currentDir;
        }
    }
    else {
        struct Directory* subdir = currentDir->subdirectories;
        while (subdir != NULL) {
            if (strcmp(subdir->name, dirName) == 0) {
                return subdir;
            }
            subdir = subdir->subdirectories;
        }
        printf("Directory '%s' not found.\n", dirName);
        return currentDir;
    }
}

int main() {
    struct Directory* rootDirectory = createDirectory("Root", NULL);
    struct Directory* currentDirectory = rootDirectory;
    char choice[2];
    char dirName[MAX_NAME_LENGTH];

    while (1) {
        printf("\nMenu:\n");
        printf("1 - Create Directory ('md')\n");
        printf("2 - Change Directory ('cd dir')\n");
        printf("3 - Move Up One Level ('cd..')\n");
        printf("4 - List Contents ('dir')\n");
        printf("5 - Exit\n");

        printf("Enter your choice: ");
        scanf("%s", choice);

        if (strcmp(choice, "1") == 0) {
            printf("Enter new directory name: ");
            scanf("%s", dirName);
            currentDirectory->subdirectories = createDirectory(dirName, currentDirectory);
        }
        else if (strcmp(choice, "2") == 0) {
            printf("Enter directory name: ");
            scanf("%s", dirName);
            currentDirectory = changeDirectory(currentDirectory, dirName);
        }
        else if (strcmp(choice, "3") == 0) {
            currentDirectory = changeDirectory(currentDirectory, "..");
        }
        else if (strcmp(choice, "4") == 0) {
            listDirectory(currentDirectory);
        }
        else if (strcmp(choice, "5") == 0) {
            break;
        }
        else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}