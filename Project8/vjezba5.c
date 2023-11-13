#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE (1024)
#define ERROR_ALLOCATION (-1)
#define ERROR_OPENING (-2)
#define EXIT_FAIL (-3)

// Struktura za cvor stoga
struct StackNode;
typedef struct StackNode* Position;
typedef struct StackNode {
    float number;
    Position next;
} StackNode;

// Inicijalizacija glave stoga
void initializeStack(Position* head) {
    *head = (Position)malloc(sizeof(StackNode));
    (*head)->next = NULL;
}

// Alokacija memorije za novi cvor
int memoryAllocation(Position* q) {
    *q = (Position)malloc(sizeof(StackNode));

    if (*q == NULL) {
        return ERROR_ALLOCATION;
    }

    return 0;
}

// Ubacivanje cvora nakon odredjenog cvora
int insertAfter(Position p, Position q) {
    q->next = p->next;
    p->next = q;

    return 0;
}

// Brisanje cvora nakon odredjenog cvora
int deleteAfter(Position p) {
    Position q = p->next;
    p->next = p->next->next;
    free(q);

    return 0;
}

// Dodavanje broja na stog
int push(float num, Position p) {
    Position q = NULL;
    if (memoryAllocation(&q) == ERROR_ALLOCATION) {
        return ERROR_ALLOCATION;
    }

    q->number = num;
    insertAfter(p, q);

    return 0;
}

// Skidanje broja sa stoga
float pop(Position p) {
    Position q;
    float n;

    if (p->next == NULL) {
        printf("Postfix not valid!");
        return EXIT_FAIL;
    }

    q = p->next;
    p->next = q->next;
    n = q->number;
    free(q);

    return n;
}

// Provjera je li znak operatora
int isValidOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Citanje iz datoteke i izracunavanje rezultata postfiksnog izraza
int readFile(Position p, char* file) {
    FILE* fp = fopen(file, "r");

    if (fp == NULL) {
        return ERROR_OPENING;
    }

    calculate(p, fp);

    fclose(fp);

    return 0;
}

/// Izracunavanje rezultata postfiksnog izraza
int calculate(Position p, FILE* fp) {
    char buffer[MAX_LINE];
    float now;
    float x, y;

    while (fgets(buffer, MAX_LINE, fp) != NULL) {
        char* pB = buffer;
        while (sscanf(pB, "%f", &now) == 1 || isValidOperator(*pB)) {
            if (sscanf(pB, "%f", &now) == 1) {
                push(now, p);
            }
            else if (isValidOperator(*pB)) {
                y = pop(p);
                x = pop(p);

                switch (*pB) {
                case '+':
                    push(x + y, p);
                    break;
                case '-':
                    push(x - y, p);
                    break;
                case '*':
                    push(x * y, p);
                    break;
                case '/':
                    if (y == 0) {
                        printf("Postfix not valid! Division by zero.\n");
                        return EXIT_FAIL;
                    }
                    push(x / y, p);
                    break;
                }
            }

            // Pomakni pokazivac na sljedeci broj ili operator u nizu
            while (*pB != '\0' && !isspace(*pB)) {
                pB++;
            }
            while (*pB != '\0' && isspace(*pB)) {
                pB++;
            }
        }
    }

    return 0;
}

// Ispisivanje elemenata stoga
int print(Position p) {
    int i = 0;
    while (p != NULL) {
        printf("%f\n", p->number);
        i++;
        p = p->next;
    }
    return i;
}

// Brisanje cijelog stoga
int deleteStack(Position p) {
    while (p->next != NULL) {
        deleteAfter(p);
    }

    return 0;
}


void freeMemory(Position p) {
    deleteStack(p);
    free(p);
}

int main(int argc, char** argv) {
    Position Head;
    initializeStack(&Head);

    char file[MAX_LINE] = { 0 };

    printf("Dear customer, please enter the name of the file:");
    scanf(" %s", file);

    if (readFile(Head, file) == ERROR_OPENING) {
        printf("Error opening the file.\n");
        freeMemory(Head);
        return EXIT_FAIL;
    }

    printf("The result of postfix operation is: ");

    if (print(Head->next) == 1)
        print(Head->next);
    else
        printf("Postfix not valid!");

    freeMemory(Head);

    return 0;
}