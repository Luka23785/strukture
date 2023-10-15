#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct {
	char ime[10];
	char prezime[10];
	double bodovi;
}student;

int main() {
	int brojredova = 0;
	char charbuffer[1024] = "";
	FILE* filepointer = NULL;
	filepointer = fopen("tekst.txt", "r");
	if (filepointer == NULL) {
		printf("datoteka nije pronadjena!\n");
		return 1;

	}
	while (foef(filepointer)) {
		if (fgets(charbuffer, 1024, filepointer) == "\n")
			brojredova++;
	}
	printf("%d", brojredova);
	fclose(filepointer);
return 0;
}
