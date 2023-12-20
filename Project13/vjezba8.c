#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define MEMORY_ALLOCATION_ERROR (2)

struct _tree;
typedef struct _tree* Position;
typedef struct _tree {
    int el;
    Position left;
    Position right;
} Tree;

struct _array;
typedef struct _array* ArrayP;
typedef struct _array {
    Position data;
    ArrayP next;
} Array;

int menu();

ArrayP AllocateMemmoryForArray(Position);
int Push(ArrayP, Position);
Position Pop(ArrayP);

Position AllocateMemmoryForTree(int);

Position addElement(int, Position);

int printInorder(Position);
int printPreorder(Position);
int printPostorder(Position);
int printLevelOrder(Position);

int deleteElement(int, Position);

Position findMin(Position);
Position findMax(Position);
Position findElement(int, Position);

int freeTree(Position);

int main(int argc, char** argv) {
    char choice;
    int element;

    Position Root = NULL;

    while (1) {
        menu();

        scanf(" %c", &choice);

        switch (tolower(choice)) {
        case 'a':
            printf("\nUnesite vrijednost koju zelite dodati u stablo: ");
            scanf("%d", &element);
            Root = addElement(element, Root);
            break;
        case 'b':
            printf("\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n"
                "\t\tKako zelite ispisati stablo?\n\n"
                "\ta) inorder\n"
                "\tb) preorder\n"
                "\tc) postorder\n"
                "\td) level order\n"
                "Vas odabir: ");

            scanf(" %c", &choice);

            switch (tolower(choice)) {
            case 'a':
                printInorder(Root);
                break;
            case 'b':
                printPreorder(Root);
                break;
            case 'c':
                printPostorder(Root);
                break;
            case 'd':
                printLevelOrder(Root);
                break;
            }

            break;
        case 'c':
            printf("\nUnesite vrijednost koju zelite izbrisati iz stabla: ");
            scanf("%d", &element);
            Root = deleteElement(element, Root);
            break;
        case 'd':
            printf("\nUnesite vrijednost koju zelite pronaci u stablu: ");
            scanf("%d", &element);
            Position found = findElement(element, Root);
            if (found != NULL) {
                printf("Pronadeni element: %d\n", found->el);
            }
            else {
                printf("Element nije pronaden.\n");
            }
            break;
        case 'x':
            printf("Dovidenja!");
            freeTree(Root);
            return 0;
        default:
            printf("Pogresan odabir.");
            break;
        }
    }
}

int menu() {
    printf("\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n"
        "\t\t\tIZBORNIK\n\n"
        "\ta) unos novog elemente\n"
        "\tb) ispis stabla\n"
        "\tc) brisanje elementa\n"
        "\td) trazenje elementa\n"
        "\tx) izlaz\n\n"
        "Vas odabir: ");
}

ArrayP AllocateMemmoryForArray(Position p) {
    ArrayP newArray = (ArrayP)malloc(sizeof(Array));

    if (newArray == NULL)
        return NULL;

    newArray->data = p;
    newArray->next = NULL;
    return newArray;
}

int Push(ArrayP head, Position p) {
    if (head == NULL)
        return MEMORY_ALLOCATION_ERROR;

    ArrayP newArray = AllocateMemmoryForArray(p);
    if (newArray == NULL)
        return MEMORY_ALLOCATION_ERROR;

    newArray->next = head->next;
    head->next = newArray;
    newArray->data = p;
    return 0;
}

Position Pop(ArrayP head) {
    if (head->next == NULL) {
        return NULL;
    }
    else {
        while (head->next->next != NULL) {
            head = head->next;
        }
    }

    ArrayP temp = head->next;
    Position position = temp->data;
    head->next = NULL;
    free(temp);

    return position;
}

Position AllocateMemmoryForTree(int number) {
    Position new = (Position)malloc(sizeof(Tree));

    if (new == NULL)
        return NULL;

    new->el = number;
    new->left = NULL;
    new->right = NULL;
    return new;
}

Position addElement(int x, Position p) {
    if (p == NULL) {
        p = AllocateMemmoryForTree(x);
    }

    if (x < p->el)
        p->left = addElement(x, p->left);
    else if (x > p->el)
        p->right = addElement(x, p->right);
    else
        printf("Element vec postoji u stablu");

    return p;
}

int printInorder(Position p) {
    if (p == NULL) {
        return 0;
    }

    printInorder(p->left);
    printf("%d\n", p->el);
    printInorder(p->right);

    return 0;
}

int printPreorder(Position p) {
    if (p == NULL) {
        return 0;
    }

    printf("%d\n", p->el);
    printPreorder(p->left);
    printPreorder(p->right);

    return 0;
}

int printPostorder(Position p) {
    if (p == NULL) {
        return 0;
    }

    printPostorder(p->left);
    printPostorder(p->right);
    printf("%d\n", p->el);

    return 0;
}

int printLevelOrder(Position p) {
    if (p == NULL) {
        return 0;
    }

    ArrayP head = AllocateMemmoryForArray(p);
    if (head == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }

    while (head->next != NULL) {
        Position current = Pop(head);
        printf("%d ", current->el);

        if (current->left != NULL) {
            Push(head, current->left);
        }
        if (current->right != NULL) {
            Push(head, current->right);
        }
    }
    free(head);
    return 0;
}

int deleteElement(int x, Position p) {
    if (p == NULL) {
        printf("Trazene vrijednosti nema u stablu.");
        return NULL;
    }

    if (x < p->el)
        p->left = deleteElement(x, p->left);
    else if (x > p->el)
        p->right = deleteElement(x, p->right);
    else {
        if (p->left) {
            Position temp = findMax(p->left);
            p->el = temp->el;
            p->left = deleteElement(temp->el, p->left);
        }
        else if (p->right) {
            Position temp = findMin(p->right);
            p->el = temp->el;
            p->right = addElement(temp->el, p->right);
        }
        else {
            free(p);
            return NULL;
        }
    }
    return p;
}

Position findMin(Position p) {
    if (p == NULL)
        return NULL;
    else if (p->left == NULL)
        return p;
    else
        return findMin(p->left);
}

Position findMax(Position p) {
    while (p->right != NULL)
        p = p->right;

    return p;
}

Position findElement(int x, Position p) {
    if (p == NULL)
        return NULL;
    else if (x < p->el)
        return findElement(x, p->left);
    else if (x > p->el)
        return findElement(x, p->right);
    else
        return p;
}

int freeTree(Position p) {
    if (p == NULL)
        return 0;

    freeTree(p->left);
    freeTree(p->right);
    free(p);

    return 0;
}
