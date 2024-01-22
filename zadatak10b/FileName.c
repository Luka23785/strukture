#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define ERROR -1
#define MAX 100

struct _list;
typedef struct _list* ListPosition;
typedef struct _list {
    char cityName[MAX];
    int population;
    ListPosition Next;
} list;

struct _tree;
typedef struct _tree* Position;
typedef struct _tree {
    char stateName[MAX];
    Position right;
    Position left;
    ListPosition ListP;
} tree;

int PrintInOrder(Position);
int PrintList(ListPosition);
int DeleteAll(Position);
int PrintBiggerThan(ListPosition, int);
int CountriesCompare(Position, Position);
int CityCompare(ListPosition, ListPosition);
int InsertAfter(ListPosition, ListPosition);
int InsertSortedCities(ListPosition, ListPosition);
Position ReadCountriesFromFile(Position, char*);
Position FindCountryByName(Position, char*);
Position InsertCountriesSorted(Position P, Position Q);
ListPosition MakeNew(char*, int);
ListPosition ReadCitiesFromFile(char*);
void InsertAfterList(ListPosition, ListPosition);
int CityCompare(ListPosition, ListPosition);

int main() {
    Position root = NULL;
    Position newroot = NULL;
    struct _list head;
    head.Next = NULL;
    int minPopulation = 0;
    char filename[MAX] = { 0 }, wantedCountry[MAX] = { 0 };

    printf("Insert filename > ");
    scanf("%s", filename);
    root = ReadCountriesFromFile(root, filename);
    PrintInOrder(root);

    printf("\nInsert name of a country > ");
    scanf("%s", wantedCountry);
    newroot = FindCountryByName(root, wantedCountry);

    if (newroot != NULL) {
        printf("%s", newroot->stateName);
        printf("\nInsert minimal population > ");
        scanf("%d", &minPopulation);
        PrintBiggerThan(newroot->ListP, minPopulation);
    }
    else {
        printf("Country not found.\n");
    }

    DeleteAll(root);
    DeleteAll(newroot);

    return EXIT_SUCCESS;
}

Position ReadCountriesFromFile(Position P, char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Failed in file opening!\n");
        return NULL;
    }

    while (!feof(fp)) {
        char countryName[MAX] = { 0 }, cityFile[MAX] = { 0 };
        fscanf(fp, "%s %s", countryName, cityFile);

        Position Q = (Position)malloc(sizeof(tree));
        if (Q == NULL) {
            perror("Failed in dynamic allocation!\n");
            return NULL;
        }

        strcpy(Q->stateName, countryName);
        Q->left = NULL;
        Q->right = NULL;
        Q->ListP = ReadCitiesFromFile(cityFile);
        P = InsertCountriesSorted(P, Q);
    }

    fclose(fp);
    return P;
}

Position InsertCountriesSorted(Position P, Position Q) {
    if (P == NULL) {
        return Q;
    }

    int result = CountriesCompare(P, Q);
    if (result > 0) {
        P->left = InsertCountriesSorted(P->left, Q);
    }
    else {
        P->right = InsertCountriesSorted(P->right, Q);
    }

    return P;
}

int CountriesCompare(Position P, Position Q) {
    return strcmp(P->stateName, Q->stateName);
}

int PrintInOrder(Position P) {
    if (P == NULL) {
        return EXIT_SUCCESS;
    }

    PrintInOrder(P->left);
    printf("%s ", P->stateName);
    PrintInOrder(P->right);

    return EXIT_SUCCESS;
}

ListPosition ReadCitiesFromFile(char* filename) {
    struct _list head;
    head.Next = NULL;
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Failed in file opening!\n");
        return NULL;
    }

    while (!feof(fp)) {
        char name[MAX] = { 0 };
        int number = 0;
        fscanf(fp, "%s %d", name, &number);

        ListPosition Q = MakeNew(name, number);
        InsertSortedCities(&head, Q);
        printf(" %s ", head.Next->cityName);
    }

    fclose(fp);
    return head.Next;
}

ListPosition MakeNew(char* name, int number) {
    ListPosition Q = (ListPosition)malloc(sizeof(list));
    if (Q == NULL) {
        perror("Failed in dynamic allocation!\n");
        return NULL;
    }

    strcpy(Q->cityName, name);
    Q->population = number;
    Q->Next = NULL;
    return Q;
}

int InsertSortedCities(ListPosition P, ListPosition Q) {
    if (P == NULL) {
        return EXIT_SUCCESS;
    }

    int result = CityCompare(P, Q);
    while (P->Next != NULL && result > 0) {
        P = P->Next;
    }

    InsertAfterList(P, Q);
    return EXIT_SUCCESS;
}

void InsertAfterList(ListPosition P, ListPosition Q) {
    Q->Next = P->Next;
    P->Next = Q;
}

int CityCompare(ListPosition P, ListPosition Q) {
    int result = P->population - Q->population;
    if (result == 0) {
        result = strcmp(P->Next->cityName, Q->cityName);
    }
    return result;
}

int PrintList(ListPosition P) {
    if (P->Next == NULL) {
        perror("The list is empty!\n");
        return ERROR;
    }

    while (P->Next != NULL) {
        printf(" %s ", P->Next->cityName);
        P = P->Next;
    }

    return EXIT_SUCCESS;
}

Position FindCountryByName(Position current, char* name) {
    if (current == NULL) {
        return NULL;
    }

    if (strcmp(current->stateName, name) == 0) {
        return current;
    }
    else if (strcmp(current->stateName, name) > 0) {
        return FindCountryByName(current->left, name);
    }
    else {
        return FindCountryByName(current->right, name);
    }
}

int PrintBiggerThan(ListPosition P, int x) {
    printf("Cities with population bigger than %d are:\n", x);

    if (P->Next == NULL) {
        perror("The list is empty!\n");
        return ERROR;
    }

    while (P->Next != NULL) {
        if (P->Next->population > x) {
            printf(" %s ", P->Next->cityName);
        }
        P = P->Next;
    }

    return EXIT_SUCCESS;
}

int DeleteAll(Position P) {
    if (P == NULL) {
        return EXIT_SUCCESS;
    }

    DeleteAll(P->left);
    DeleteAll(P->right);
    free(P);

    return EXIT_SUCCESS;
}
