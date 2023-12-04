#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Item {
    char name[50];
    int quantity;
    float price;
    struct Item* next;
};


struct Invoice {
    char date[11];
    struct Item* items;
    struct Invoice* next;
};

//Dodavanje artikla u vezanu listu artikala
void addItem(struct Item** head, char name[], int quantity, float price) {
    struct Item* newItem = (struct Item*)malloc(sizeof(struct Item));
    strcpy(newItem->name, name);
    newItem->quantity = quantity;
    newItem->price = price;
    newItem->next = NULL;

    if (*head == NULL) {
        *head = newItem;
    }
    else {
        struct Item* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newItem;
    }
}

//Dodavanje racuna u vezanu listu racuna
void addInvoice(struct Invoice** head, char date[], struct Item* items) {
    struct Invoice* newInvoice = (struct Invoice*)malloc(sizeof(struct Invoice));
    strcpy(newInvoice->date, date);
    newInvoice->items = items;
    newInvoice->next = NULL;

    if (*head == NULL) {
        *head = newInvoice;
    }
    else {
        struct Invoice* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newInvoice;
    }
}


void calculateTotal(struct Invoice* head, char itemName[], char startDate[], char endDate[]) {
    float totalCost = 0;
    int totalQuantity = 0;
    while (head != NULL) {
        if (strcmp(head->date, startDate) >= 0 && strcmp(head->date, endDate) <= 0) {
            struct Item* item = head->items;
            while (item != NULL) {
                if (strcmp(item->name, itemName) == 0) {
                    totalCost += item->price * item->quantity;
                    totalQuantity += item->quantity;
                }
                item = item->next;
            }
        }
        head = head->next;
    }
    printf("Ukupan trosak za %s u razdoblju od %s do %s je: %.2f\n", itemName, startDate, endDate, totalCost);
    printf("Kolicina kupljena: %d\n", totalQuantity);
}

int main() {
    FILE* file = fopen("racuni.txt", "r");
    if (file == NULL) {
        printf("Ne mogu otvoriti datoteku.\n");
        return 1;
    }

    struct Invoice* invoices = NULL;
    char date[11], itemName[50];
    int quantity;
    float price;

    while (fscanf(file, "%s", date) != EOF) {
        struct Item* items = NULL;
        while (fscanf(file, "%s %d %f", itemName, &quantity, &price) != EOF) {
            addItem(&items, itemName, quantity, price);
            char nextChar = fgetc(file);
            if (nextChar == '\n' || nextChar == EOF) {
                break;
            }
        }
        addInvoice(&invoices, date, items);
    }

    fclose(file);

    char start[11], end[11];
    printf("Unesite pocetni datum (YYYY-MM-DD): ");
    scanf("%s", start);
    printf("Unesite krajnji datum (YYYY-MM-DD): ");
    scanf("%s", end);

    printf("Unesite naziv artikla za koji zelite saznati informacije: ");
    scanf("%s", itemName);

    calculateTotal(invoices, itemName, start, end);

    return 0;
}