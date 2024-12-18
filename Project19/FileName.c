#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Struktura za cirkularni stog
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
    int size;
    int capacity;
} CircularStack;

// Funkcije za cirkularni stog
void initCircularStack(CircularStack* stack, int capacity) {
    stack->top = NULL;
    stack->size = 0;
    stack->capacity = capacity;
}

int isStackFull(CircularStack* stack) {
    return stack->size == stack->capacity;
}

int isStackEmpty(CircularStack* stack) {
    return stack->size == 0;
}

void push(CircularStack* stack, int value) {
    if (isStackFull(stack)) {
        printf("Stog je pun!\n");
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;

    if (stack->top == NULL) {
        newNode->next = newNode; // Prvi element pokazuje na samog sebe
    }
    else {
        newNode->next = stack->top->next;
        stack->top->next = newNode;
    }

    stack->top = newNode;
    stack->size++;
}

int pop(CircularStack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stog je prazan!\n");
        return -1;
    }

    Node* temp = stack->top->next;
    int value = temp->data;

    if (stack->top == temp) {
        stack->top = NULL;
    }
    else {
        stack->top->next = temp->next;
    }

    free(temp);
    stack->size--;
    return value;
}

void printCircularStack(CircularStack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stog je prazan!\n");
        return;
    }

    Node* current = stack->top->next;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != stack->top->next);
    printf("\n");
}

// Struktura za red s prioritetom
typedef struct PriorityNode {
    int data;
    int priority;
    struct PriorityNode* next;
} PriorityNode;

typedef struct {
    PriorityNode* front;
} PriorityQueue;

// Funkcije za red s prioritetom
void initPriorityQueue(PriorityQueue* queue) {
    queue->front = NULL;
}

int isQueueEmpty(PriorityQueue* queue) {
    return queue->front == NULL;
}

void enqueue(PriorityQueue* queue, int value, int priority) {
    PriorityNode* newNode = (PriorityNode*)malloc(sizeof(PriorityNode));
    newNode->data = value;
    newNode->priority = priority;
    newNode->next = NULL;

    if (isQueueEmpty(queue) || queue->front->priority < priority) {
        newNode->next = queue->front;
        queue->front = newNode;
    }
    else {
        PriorityNode* current = queue->front;
        while (current->next != NULL && current->next->priority >= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

int dequeue(PriorityQueue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Red je prazan!\n");
        return -1;
    }

    PriorityNode* temp = queue->front;
    int value = temp->data;
    queue->front = temp->next;
    free(temp);
    return value;
}

void printPriorityQueue(PriorityQueue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Red je prazan!\n");
        return;
    }

    PriorityNode* current = queue->front;
    while (current != NULL) {
        printf("[Data: %d, Priority: %d] ", current->data, current->priority);
        current = current->next;
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    // Testiranje cirkularnog stoga
    CircularStack stack;
    int capacity;
    printf("Unesite kapacitet stoga: ");
    scanf("%d", &capacity);
    initCircularStack(&stack, capacity);

    for (int i = 0; i < capacity + 2; i++) {
        int value = rand() % 91 + 10;
        printf("Pushing %d\n", value);
        push(&stack, value);
        printCircularStack(&stack);
    }

    printf("\nPopping elements:\n");
    while (!isStackEmpty(&stack)) {
        printf("Popped: %d\n", pop(&stack));
        printCircularStack(&stack);
    }

    // Testiranje reda s prioritetom
    PriorityQueue queue;
    initPriorityQueue(&queue);

    for (int i = 0; i < 10; i++) {
        int value = rand() % 91 + 10;
        int priority = rand() % 5 + 1;
        printf("Enqueueing [Data: %d, Priority: %d]\n", value, priority);
        enqueue(&queue, value, priority);
        printPriorityQueue(&queue);
    }

    printf("\nDequeuing elements:\n");
    while (!isQueueEmpty(&queue)) {
        printf("Dequeued: %d\n", dequeue(&queue));
        printPriorityQueue(&queue);
    }

    return 0;
}
