#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Node {
    int data;
    struct Node* next;
};

// Funkcija za stvaranje novog cvora
struct Node* createNode(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}

// Funkcija za umetanje cvora na kraj liste
void insert(struct Node** head, int val) {
    struct Node* newNode = createNode(val);
    if (*head == NULL) {
        *head = newNode;
    }
    else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Funkcija za prikaz elemenata liste
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Funkcija za citanje brojeva iz datoteke i umetanje u vezanu listu
void loadFromFile(struct Node** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Greska pri otvaranju datoteke %s!\n", filename);
        exit(1);
    }

    int num;
    while (fscanf(file, "%d", &num) != EOF) {
        insert(head, num);
    }

    fclose(file);
}

// Funkcija za uniju dviju sortiranih listi
struct Node* unionLists(struct Node* L1, struct Node* L2) {
    struct Node* unionHead = NULL;
    struct Node* temp1 = L1;
    struct Node* temp2 = L2;

    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->data < temp2->data) {
            insert(&unionHead, temp1->data);
            temp1 = temp1->next;
        }
        else if (temp1->data > temp2->data) {
            insert(&unionHead, temp2->data);
            temp2 = temp2->next;
        }
        else {
            insert(&unionHead, temp1->data);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    while (temp1 != NULL) {
        insert(&unionHead, temp1->data);
        temp1 = temp1->next;
    }

    while (temp2 != NULL) {
        insert(&unionHead, temp2->data);
        temp2 = temp2->next;
    }

    return unionHead;
}

// Funkcija za presjek dviju sortiranih listi
struct Node* intersectionLists(struct Node* L1, struct Node* L2) {
    struct Node* intersectionHead = NULL;
    struct Node* temp1 = L1;
    struct Node* temp2 = L2;

    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->data < temp2->data) {
            temp1 = temp1->next;
        }
        else if (temp1->data > temp2->data) {
            temp2 = temp2->next;
        }
        else {
            insert(&intersectionHead, temp1->data);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    return intersectionHead;
}

int main() {
    struct Node* L1 = NULL;
    struct Node* L2 = NULL;

    loadFromFile(&L1, "L1.txt");
    loadFromFile(&L2, "L2.txt");

    printf("Lista L1: ");
    printList(L1);

    printf("Lista L2: ");
    printList(L2);

    struct Node* unionList = unionLists(L1, L2);
    printf("Unija L1 i L2: ");
    printList(unionList);

    struct Node* intersectionList = intersectionLists(L1, L2);
    printf("Presjek L1 i L2: ");
    printList(intersectionList);

    return 0;
}