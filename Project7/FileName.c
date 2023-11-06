#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE (1024)


typedef struct _polinom* position;
typedef struct _polinom {
    int coef; 
    int exp;  
    position next; 
} Polinom;


int menu() {
    printf("\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n"
        "\t\t\tIZBORNIK\n\n"
        "\ta) zbrajanje polinoma\n"
        "\tb) mnozenje polinoma\n"
        "\tx) izlaz\n\n"
        "Vas odabir: ");

    return 0;
}


int adding(position, position, position);
int multiplying(position, position, position);

int readFile(position x, position y);
int addPoly(position, char*);

int print(position);

int insertSort(position, position);
int insertAfter(position, position);

int memoryAllocation(position*);

int checker(position);
int merge(position);
int delete(position);

int main(int argc, char** argv)
{
    
    Polinom Head1 = { .coef = 0, .exp = 0, .next = NULL };
    Polinom Head2 = { .coef = 0, .exp = 0, .next = NULL };

    
    readFile(&Head1, &Head2);

    
    print(Head1.next);
    print(Head2.next);

    char choice;

    while (1) {
        // Inicijalizacija glave 
        Polinom HeadRes = { .coef = 0, .exp = 0, .next = NULL };

        
        menu();
        scanf(" %c", &choice);

        switch (tolower(choice)) {
        case 'a':
            
            adding(&Head1, &Head2, &HeadRes);
            
            print(HeadRes.next);
            break;
        case 'b':
            
            multiplying(Head1.next, Head2.next, &HeadRes);
            
            print(HeadRes.next);
            break;
        case 'x':
            
            printf("Kraj!");
            return 0;
        default:
            
            printf("Pogresan unos!");
            break;
        }
    }
    return 0;
}

// Funkcija za alociranje memorije za novi cvor polinoma
int memoryAllocation(position* q) {
    *q = (position)malloc(sizeof(Polinom));

    if (*q == NULL) {
        printf("Memorija nije alocirana!\n");
        return 1;
    }

    (*q)->coef = 0;
    (*q)->exp = 0;
    (*q)->next = NULL;

    return 0;
}

// Funkcija za umetanje 
int insertAfter(position p, position q) {
    q->next = p->next;
    p->next = q;

    return 0;
}

// Funkcija za umetanje u sortiranom redoslijedu po eksponentu
int insertSort(position p, position q) {
    while (p->next != NULL && q->exp > p->next->exp)
        p = p->next;

    mergeAfter(p, q);

    return 0;
}

// Funkcija za provjeru i brisanje s koeficijentom 0
int checker(position p) {
    while (p->next != NULL) {
        if (p->next->coef == 0)
            delete(p);
        p = p->next;
    }
    return 0;
}

// Funkcija za spajanje dva polinoma na istim eksponentima
int mergeAfter(position p, position q) {
    if (p->next == NULL || q->exp < p->next->exp) {
        insertAfter(p, q);
    }
    else /* if (q->exp == p->next->exp) */ {
        p->next->coef += q->coef;
        free(q);
    }
    return 0;
}

// Brisanje odredjenog cvora iz polinoma
int delete(position p) {
    position q = p->next;
    p->next = p->next->next;
    free(q);

    return 0;
}

// Ispis polinoma
int print(position p) {
    while (p != NULL) {
        printf("(%dx^%d) ", p->coef, p->exp);

        if (p->next != NULL)
            printf(" + ");
        else
            printf(",");
        p = p->next;
    }

    return 0;
}

// Citanje polinoma iz datoteke
int readFile(position x, position y) {
    FILE* fp = NULL;
    char buffer[MAX_SIZE];

    fp = fopen("polinomi.txt", "r");
    if (fp == NULL) {
        printf("Pogreska pri otvaranju datoteke!");
        return -1;
    }

    fgets(buffer, MAX_SIZE, fp);
    addPoly(x, buffer);

    fgets(buffer, MAX_SIZE, fp);
    addPoly(y, buffer);

    fclose(fp);

    return 0;
}

// Funkcija za dodavanje polinoma iz teksta u cvorove polinoma
int addPoly(position p, char* buffer) {
    char* pB = buffer;
    int coef = 0;
    int exp = 0;
    int i = 0;

    while (strlen(pB) > 0) {
        position q = NULL;
        memoryAllocation(&q);

        sscanf(pB, " %d %d %n", &q->coef, &q->exp, &i);

        insertSort(p, q);
        pB += i;
    }

    return 0;
}

// Funkcija za zbrajanje dvaju polinoma
int adding(position head1, position head2, position pA) {
    position temp = NULL;
    position p1 = head1->next;
    position p2 = head2->next;

    while (p1 != NULL && p2 != NULL) {
        position new = NULL;
        memoryAllocation(&new);

        if (p1->exp < p2->exp) {
            new->exp = p1->exp;
            new->coef = p1->coef;
            p1 = p1->next;
        }
        else if (p1->exp > p2->exp) {
            new->exp = p2->exp;
            new->coef = p2->coef;
            p2 = p2->next;
        }
        else {
            new->exp = p1->exp;
            new->coef = (p1->coef + p2->coef);
            p1 = p1->next;
            p2 = p2->next;
        }
        insertAfter(pA, new);
    }

    if (p1 == NULL)
        temp = p2;
    else
        temp = p1;
    while (temp != NULL) {
        position new = NULL;
        memoryAllocation(&new);

        new->next = NULL;
        new->exp = temp->exp;
        new->coef = temp->coef;
        insertAfter(pA, new);

        temp = temp->next;
    }

    return 0;
}

// Funkcija za mnozenje dvaju polinoma
int multiplying(position p1, position p2, position pM) {
    position new = NULL;
    position p2Start = p2;

    while (p1 != NULL) {
        p2 = p2Start;
        while (p2 != NULL) {
            memoryAllocation(&new);
            new->exp = p1->exp + p2->exp;
            new->coef = p1->coef * p2->coef;

            insertSort(pM, new);

            p2 = p2->next;
        }
        p1 = p1->next;
    }
    return 0;
}
