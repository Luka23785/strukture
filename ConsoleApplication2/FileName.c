#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definicija cvora za vezanu listu
typedef struct Node {
    int value;
    struct Node* next;
} Node;

// Stog implementiran pomocu vezane liste
typedef struct Stack {
    Node* top;
} Stack;

// Red implementiran pomocu vezane liste
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Funkcija za stvaranje novog cvora
Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Greška pri alokaciji memorije!\n");
        exit(1);
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void init_stack(Stack* stack) {
    stack->top = NULL;
}

// Push operacija za stog (dodavanje na vrh stoga)
void push(Stack* stack, int value) {
    Node* new_node = create_node(value);
    new_node->next = stack->top;
    stack->top = new_node;
    printf("Push: %d dodano na stog.\n", value);
}

// Pop operacija za stog (uklanjanje s vrha stoga)
int pop(Stack* stack) {
    if (stack->top == NULL) {
        printf("Stog je prazan!\n");
        return -1;
    }
    Node* temp = stack->top;
    int value = temp->value;
    stack->top = stack->top->next;
    free(temp);
    printf("Pop: %d uklonjeno sa stoga.\n", value);
    return value;
}

void init_queue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

// Enqueue operacija za red (dodavanje na kraj reda)
void enqueue(Queue* queue, int value) {
    Node* new_node = create_node(value);
    if (queue->rear == NULL) {
        queue->front = queue->rear = new_node;
    }
    else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
    printf("Enqueue: %d dodano u red.\n", value);
}

// Dequeue operacija za red (uklanjanje s pocetka reda)
int dequeue(Queue* queue) {
    if (queue->front == NULL) {
        printf("Red je prazan!\n");
        return -1;
    }
    Node* temp = queue->front;
    int value = temp->value;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    printf("Dequeue: %d uklonjeno iz reda.\n", value);
    return value;
}

int main() {
    srand(time(NULL)); 

    Stack stack;
    Queue queue;

    init_stack(&stack);
    init_queue(&queue);

    printf("=== Testiranje stoga ===\n");
    for (int i = 0; i < 5; i++) {
        push(&stack, rand() % 91 + 10); 
    }
    for (int i = 0; i < 3; i++) {
        pop(&stack);
    }

    printf("\n=== Testiranje reda ===\n");
    for (int i = 0; i < 5; i++) {
        enqueue(&queue, rand() % 91 + 10); 
    }
    for (int i = 0; i < 3; i++) {
        dequeue(&queue);
    }

    return 0;
}
