#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MEMORY_ALLOCATION_ERROR (-2)
#define FILE_OPENINIG_ERROR (-3)

struct _node;
typedef struct _node* position;

typedef struct _node
{
	int number;
	position left;
	position right;
} Node;

struct _stog;
typedef struct _stog* positionStog;
typedef struct _stog
{
	int element;
	positionStog next;
} Stog;

position addElement(int num);
position insert(position root, position newP);
position readElements(position root, int numbers[]);

positionStog addElementOnStog(int num);
int push(positionStog head, int num);
int printInOrder(position root, positionStog head);

int deleteAfter(positionStog head);
int pop(positionStog head);
int writeInFile(positionStog head, char* filename);

int calculateSum(position root, int* sum);
position replace(position root);

position deleteTree(position root);
position randomTree(position root);


int main()
{
	Stog head;
	position root;
	int num;
	int numbers[10] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	head.element = 0;
	head.next = NULL;
	root = NULL;
	num = 0;

	root = readElements(root, numbers);

	printInOrder(root, &head);
	num = writeInFile(&head, "treeA.txt");

	root = replace(root);

	printInOrder(root, &head);
	num = writeInFile(&head, "treeB.txt");

	root = deleteTree(root);
	root = randomTree(root);

	printInOrder(root, &head);
	num = writeInFile(&head, "treeC.txt");

	return 0;
}

position addElement(int num)
{
	position newElement = (position)malloc(sizeof(Node));
	if (!newElement)
	{
		printf("Memory is not allocated.\n");
		return NULL;
	}

	newElement->number = num;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}

position insert(position root, position newP)
{
	if (root == NULL)
		root = newP;

	else if (newP->number > root->number)
		root->left = insert(root->left, newP);

	else if (newP->number <= root->number)
		root->right = insert(root->right, newP);

	return root;
}

position readElements(position root, int numbers[])
{
	position newP = NULL;
	int i = 0;

	for (i = 0; i < 10; i++)
	{
		newP = addElement(numbers[i]);

		root = insert(root, newP);
	}

	return root;
}

positionStog addElementOnStog(int num)
{
	positionStog newP = NULL;

	newP = (positionStog)malloc(sizeof(Stog));
	if (!newP)
	{
		printf("Memory is not allocated.\n");
		return MEMORY_ALLOCATION_ERROR;
	}

	newP->element = num;
	newP->next = NULL;

	return newP;
}

int push(positionStog head, int broj)
{
	positionStog newP = NULL;

	newP = addElementOnStog(broj);
	if (!newP)
		return -1;

	newP->next = head->next;
	head->next = newP;

	return 0;
}

int printInOrder(position root, positionStog head)
{
	if (root)
	{
		printInOrder(root->right, head);
		push(head, root->number);
		printInOrder(root->left, head);
	}

	return 0;
}

int deleteAfter(positionStog head)
{
	positionStog temp = NULL;

	temp = head->next;
	head->next = temp->next;
	free(temp);

	return 0;
}

int pop(positionStog head)
{
	int broj;

	broj = head->next->element;

	deleteAfter(head);

	return broj;
}

int writeInFile(positionStog head, char* filename)
{
	FILE* fp = NULL;
	fp = fopen(filename, "w");
	if (!fp)
	{
		printf("File didn't open.\n");
		return FILE_OPENINIG_ERROR;
	}

	while (head->next != NULL)
		fprintf(fp, "%d ", pop(head));

	fclose(fp);
	return 0;
}

int calculateSum(position root, int* sum)
{
	if (root->left)
		(*sum) += calculateSum(root->left, sum);

	if (root->right)
		(*sum) += calculateSum(root->right, sum);

	return root->number;
}

position replace(position root)
{
	int sum = 0;

	calculateSum(root, &sum);
	root->number = sum;

	if (root->left)
		root->left = replace(root->left);

	if (root->right)
		root->right = replace(root->right);

	return root;
}

position deleteTree(position root)
{
	if (root->right)
		root->right = deleteTree(root->right);

	if (root->left)
		root->left = deleteTree(root->left);

	free(root);

	return NULL;
}

position randomTree(position root)
{
	position newP = NULL;

	int numbers[10] = { 0 };
	int i = 0;

	srand(time(NULL));

	for (i = 0; i < 10; i++)
	{
		numbers[i] = (rand() % (90 - 10 + 1)) + 10;
		newP = addElement(numbers[i]);

		root = insert(root, newP);
	}

	return root;
}