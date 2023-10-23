#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktura za osobu
struct Osoba {
    char ime[10];
    char prezime[10];
    int godina_rodjenja;
    struct Osoba* sljedeci;
};

// Funkcija za dodavanje nove osobe na pocetak liste
struct Osoba* dodajNaPocetak(struct Osoba* glava, char ime[], char prezime[], int godina_rodjenja) {
    struct Osoba* novaOsoba = (struct Osoba*)malloc(sizeof(struct Osoba));
    strcpy(novaOsoba->ime, ime);
    strcpy(novaOsoba->prezime, prezime);
    novaOsoba->godina_rodjenja = godina_rodjenja;
    novaOsoba->sljedeci = glava;
    return novaOsoba;
}

// Funkcija za ispisivanje liste
void ispisiListu(struct Osoba* glava) {
    struct Osoba* trenutnaOsoba = glava;
    while (trenutnaOsoba != NULL) {
        printf("Ime: %s, Prezime: %s, Godina rodjenja: %d\n", trenutnaOsoba->ime, trenutnaOsoba->prezime, trenutnaOsoba->godina_rodjenja);
        trenutnaOsoba = trenutnaOsoba->sljedeci;
    }
}

// Funkcija za dodavanje nove osobe na kraj liste
struct Osoba* dodajNaKraj(struct Osoba* glava, char ime[], char prezime[], int godina_rodjenja) {
    struct Osoba* novaOsoba = (struct Osoba*)malloc(sizeof(struct Osoba));
    strcpy(novaOsoba->ime, ime);
    strcpy(novaOsoba->prezime, prezime);
    novaOsoba->godina_rodjenja = godina_rodjenja;
    novaOsoba->sljedeci = NULL;

    if (glava == NULL) {
        return novaOsoba;
    }

    struct Osoba* trenutnaOsoba = glava;
    while (trenutnaOsoba->sljedeci != NULL) {
        trenutnaOsoba = trenutnaOsoba->sljedeci;
    }
    trenutnaOsoba->sljedeci = novaOsoba;
    return glava;
}

// Funkcija za pronalazenje osobe po prezimenu
struct Osoba* pronadiPoPrezimenu(struct Osoba* glava, char prezime[]) {
    struct Osoba* trenutnaOsoba = glava;
    while (trenutnaOsoba != NULL) {
        if (strcmp(trenutnaOsoba->prezime, prezime) == 0) {
            return trenutnaOsoba;
        }
        trenutnaOsoba = trenutnaOsoba->sljedeci;
    }
    return NULL;
}

// Funkcija za brisanje odredene osobe iz liste
struct Osoba* obrisiOsobu(struct Osoba* glava, char prezime[]) {
    struct Osoba* trenutnaOsoba = glava;
    struct Osoba* prethodnaOsoba = NULL;

    while (trenutnaOsoba != NULL) {
        if (strcmp(trenutnaOsoba->prezime, prezime) == 0) {
            if (prethodnaOsoba == NULL) {
                glava = trenutnaOsoba->sljedeci;
            }
            else {
                prethodnaOsoba->sljedeci = trenutnaOsoba->sljedeci;
            }
            free(trenutnaOsoba);
            return glava;
        }

        prethodnaOsoba = trenutnaOsoba;
        trenutnaOsoba = trenutnaOsoba->sljedeci;
    }

    return glava;
}

int main() {
    struct Osoba* glava = NULL;

    // Dodavanje osoba na pocetak liste
    glava = dodajNaPocetak(glava, "Ante", "Antic", 1990);
    glava = dodajNaPocetak(glava, "Ivan", "Ivanic", 1965);
    glava = dodajNaPocetak(glava, "Luka", "Ugrina", 2001);

    // Ispisivanje liste
    printf("Lista nakon dodavanja na pocetak:\n");
    ispisiListu(glava);

    // Dodavanje osobe na kraj liste
    glava = dodajNaKraj(glava, "Josip", "Peric", 1995);

    // Ispisivanje liste
    printf("\nLista nakon dodavanja na kraj:\n");
    ispisiListu(glava);

    // Pronalazenje osobe po prezimenu
    char trazenoPrezime[] = "Ivanic";
    struct Osoba* pronadenaOsoba = pronadiPoPrezimenu(glava, trazenoPrezime);
    if (pronadenaOsoba != NULL) {
        printf("\nOsoba s prezimenom %s pronadjena: %s %s, Godina rodjenja: %d\n", trazenoPrezime, pronadenaOsoba->ime, pronadenaOsoba->prezime, pronadenaOsoba->godina_rodjenja);
    }
    else {
        printf("\nOsoba s prezimenom %s nije pronadjena.\n", trazenoPrezime);
    }

    // Brisanje osobe iz liste
    char prezimeZaBrisanje[] = "Ugrina";
    glava = obrisiOsobu(glava, prezimeZaBrisanje);

    // Ispisivanje liste nakon brisanja
    printf("\nLista nakon brisanja osobe s prezimenom %s:\n", prezimeZaBrisanje);
    ispisiListu(glava);

    // Oslobadnjanje memorije
    while (glava != NULL) {
        struct Osoba* sljedecaOsoba = glava->sljedeci;
        free(glava);
        glava = sljedecaOsoba;
    }

    return 0;
}