#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define TABLE_SIZE 11

// Structure for City
typedef struct City {
    char cityName[MAX];
    int population;
    struct City* left;
    struct City* right;
} City;

// Structure for Linked List of Cities
typedef struct _list {
    char stateName[MAX];
    City* TreeP;
    struct _list* Next;
} List;

// Structure for Hash Table
typedef struct {
    List* array[TABLE_SIZE];
} HashTable;
City* readCitiesFromFile(const char* filename);

// Hash Function for Mapping Key
int hashFunction(const char* stateName) {
    int sum = 0;
    for (int i = 0; i < 5 && stateName[i] != '\0'; i++) {
        sum += stateName[i];
    }
    return sum % TABLE_SIZE;
}

// Comparison function for qsort
int compareCities(const void* a, const void* b) {
    const City* city1 = (const City*)a;
    const City* city2 = (const City*)b;

    if (city1->population != city2->population) {
        return city2->population - city1->population;
    }
    else {
        return strcmp(city1->cityName, city2->cityName);
    }
}

// Insert a City into the Linked List, sorted by name
void insertCity(List* list, City* newCity) {
    while (list->Next != NULL && strcmp(list->Next->stateName, newCity->cityName) < 0) {
        list = list->Next;
    }

    List* newNode = (List*)malloc(sizeof(List));
    if (newNode == NULL) {
        perror("Failed in dynamic allocation!\n");
        exit(EXIT_FAILURE);
    }

    strcpy(newNode->stateName, newCity->cityName);
    newNode->TreeP = newCity;
    newNode->Next = list->Next;
    list->Next = newNode;
}

// Insert a State into the Hash Table
void insertState(HashTable* table, const char* stateName, City* city) {
    int key = hashFunction(stateName);

    List* newList = (List*)malloc(sizeof(List));
    if (newList == NULL) {
        perror("Failed in dynamic allocation!\n");
        exit(EXIT_FAILURE);
    }

    strcpy(newList->stateName, stateName);
    newList->TreeP = NULL;
    newList->Next = NULL;

    if (table->array[key] == NULL) {
        table->array[key] = newList;
    }
    else {
        insertCity(table->array[key], city);
    }
}

// Read Countries and Cities from File and populate Hash Table
void readCountriesAndCities(HashTable* table, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while (!feof(file)) {
        char stateName[MAX];
        char cityFileName[MAX];
        fscanf(file, "%s %s", stateName, cityFileName);

        City* cities = readCitiesFromFile(cityFileName);
        insertState(table, stateName, cities);
    }

    fclose(file);
}

// Read Cities from File and sort them
City* readCitiesFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    City* cities = NULL;
    int cityCount = 0;

    while (!feof(file)) {
        char cityName[MAX];
        int population;
        fscanf(file, "%s %d", cityName, &population);

        City newCity;
        strcpy(newCity.cityName, cityName);
        newCity.population = population;
        newCity.left = NULL;
        newCity.right = NULL;

        // Allocate memory for the new city
        cities = (City*)realloc(cities, (cityCount + 1) * sizeof(City));
        if (cities == NULL) {
            perror("Failed in dynamic allocation!\n");
            exit(EXIT_FAILURE);
        }

        // Add the new city to the array
        cities[cityCount] = newCity;
        cityCount++;
    }

    fclose(file);

    // Allocate memory for the final array and copy the data
    City* result = (City*)malloc(cityCount * sizeof(City));
    if (result == NULL) {
        perror("Failed in dynamic allocation!\n");
        exit(EXIT_FAILURE);
    }
    memcpy(result, cities, cityCount * sizeof(City));

    // Free the temporary array
    free(cities);

    return result;
}

// Print the contents of the Hash Table
void printHashTable(const HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Slot %d:\n", i);
        List* list = table->array[i];
        while (list != NULL) {
            printf("  Country: %s\n", list->stateName);
            for (int j = 0; j < 5; j++) {
                if (list->TreeP[j].population > 0) {
                    printf("    City: %s, Population: %d\n", list->TreeP[j].cityName, list->TreeP[j].population);
                }
            }
            list = list->Next;
        }
        printf("\n");
    }
}

// Free the memory allocated for the Hash Table
void freeHashTable(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        List* list = table->array[i];
        while (list != NULL) {
            List* temp = list;
            list = list->Next;
            free(temp);
        }
    }
}

int main() {
    HashTable table;
    for (int i = 0; i < TABLE_SIZE; i++) {
        table.array[i] = NULL;
    }

    const char* filename = "drzave.txt";
    readCountriesAndCities(&table, filename);

    printHashTable(&table);

    // Free allocated memory
    freeHashTable(&table);

    return EXIT_SUCCESS;
}
