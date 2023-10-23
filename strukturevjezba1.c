#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char ime[10];
    char prezime[10];
    double bodovi;
} student;

int main() {
    int broj_studenata = 0;
    char charbuffer[1024] = "";
    FILE* filepointer = NULL;
    filepointer = fopen("studenti.txt", "r");
    if (filepointer == NULL) {
        printf("Datoteka nije pronadjena!\n");
        return 1;
    }

    // Koliko redaka ima u datoteci
    while (fgets(charbuffer, 1024, filepointer) != NULL) {
        if (strcmp(charbuffer, "\n") == 0) {
            continue;
        }
        broj_studenata++;
    }

    // Ponistavamo EOF indikator i ponovno otvaramo datoteku kako bismo procitali od pocetka
    fseek(filepointer, 0, SEEK_SET);

    // Dinamicki alociramo memoriju za niz struktura studenata
    student* studenti = (student*)malloc(broj_studenata * sizeof(student));
    if (studenti == NULL) {
        printf("Nije moguce alocirati memoriju.\n");
        return 1;
    }

    // Ucitavanje podataka iz datoteke
    for (int i = 0; i < broj_studenata; i++) {
        fscanf(filepointer, "%s %s %lf", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
    }

    fclose(filepointer);

    // Ispisivanje podataka o studentima
    printf("Podaci o studentima:\n");
    for (int i = 0; i < broj_studenata; i++) {
        double apsolutni_br_bodova = studenti[i].bodovi;
        double relativni_br_bodova = (studenti[i].bodovi / 100.0) * 100.0;
        printf("Ime: %s, Prezime: %s, Bodovi: %.2lf, Relativni bodovi: %.2lf%%\n", studenti[i].ime, studenti[i].prezime, apsolutni_br_bodova, relativni_br_bodova);
    }

    // Oslobadjamo alociranu memoriju
    free(studenti);

    return 0;
}
