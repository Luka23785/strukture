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
    if (novaOsoba == NULL) {
        printf("Greska pri alokaciji memorije za novu osobu\n");
        exit(1);
    }
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
    if (novaOsoba == NULL) {
        printf("Greska pri alokaciji memorije za novu osobu\n");
        exit(1);
    }
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

// Funkcija za dodavanje nove osobe iza odredjene osobe
struct Osoba* dodajIzaOsobe(struct Osoba* glava, char ime[], char prezime[], int godina_rodjenja, char prezimeTrazenaOsoba[]) {
    struct Osoba* novaOsoba = (struct Osoba*)malloc(sizeof(struct Osoba));
    if (novaOsoba == NULL) {
        printf("Greska pri alokaciji memorije za novu osobu\n");
        exit(1);
    }
    strcpy(novaOsoba->ime, ime);
    strcpy(novaOsoba->prezime, prezime);
    novaOsoba->godina_rodjenja = godina_rodjenja;

    struct Osoba* trenutnaOsoba = glava;
    while (trenutnaOsoba != NULL) {
        if (strcmp(trenutnaOsoba->prezime, prezimeTrazenaOsoba) == 0) {
            novaOsoba->sljedeci = trenutnaOsoba->sljedeci;
            trenutnaOsoba->sljedeci = novaOsoba;
            return glava;
        }
        trenutnaOsoba = trenutnaOsoba->sljedeci;
    }

    printf("Osoba s prezimenom %s nije pronadjena za dodavanje iza nje.\n", prezimeTrazenaOsoba);
    free(novaOsoba);
    return glava;
}

// Funkcija za dodavanje nove osobe ispred odredjene osobe
struct Osoba* dodajIspredOsobe(struct Osoba* glava, char ime[], char prezime[], int godina_rodjenja, char prezimeTrazenaOsoba[]) {
    struct Osoba* novaOsoba = (struct Osoba*)malloc(sizeof(struct Osoba));
    if (novaOsoba == NULL) {
        printf("Greska pri alokaciji memorije za novu osobu\n");
        exit(1);
    }
    strcpy(novaOsoba->ime, ime);
    strcpy(novaOsoba->prezime, prezime);
    novaOsoba->godina_rodjenja = godina_rodjenja;

    if (glava != NULL && strcmp(glava->prezime, prezimeTrazenaOsoba) == 0) {
        novaOsoba->sljedeci = glava;
        return novaOsoba;
    }

    struct Osoba* trenutnaOsoba = glava;
    while (trenutnaOsoba != NULL) {
        if (trenutnaOsoba->sljedeci != NULL && strcmp(trenutnaOsoba->sljedeci->prezime, prezimeTrazenaOsoba) == 0) {
            novaOsoba->sljedeci = trenutnaOsoba->sljedeci;
            trenutnaOsoba->sljedeci = novaOsoba;
            return glava;
        }
        trenutnaOsoba = trenutnaOsoba->sljedeci;
    }

    printf("Osoba s prezimenom %s nije pronadjena za dodavanje ispred nje.\n", prezimeTrazenaOsoba);
    free(novaOsoba);
    return glava;
}

// Funkcija za sortiranje liste po prezimenima osoba (bubble sort)
struct Osoba* sortirajListuPoPrezimenima(struct Osoba* glava) {
    int zamijenjeno;
    struct Osoba* glavaS;
    struct Osoba* tmp;

    if (glava == NULL) {
        return NULL;
    }

    do {
        zamijenjeno = 0;
        glavaS = glava;
        while (glavaS->sljedeci != NULL) {
            if (strcmp(glavaS->prezime, glavaS->sljedeci->prezime) > 0) {
                // Zamijeni mjesta dvije susjedne osobe
                tmp = glavaS;
                glavaS = glavaS->sljedeci;
                tmp->sljedeci = glavaS->sljedeci;
                glavaS->sljedeci = tmp;
                if (tmp == glava) {
                    glava = glavaS;
                }
                zamijenjeno = 1;
            }
            glavaS = glavaS->sljedeci;
        }
    } while (zamijenjeno);

    return glava;
}

// Funkcija za upisivanje liste u datoteku
void upisiListuUDatoteku(struct Osoba* glava, const char* listadatoteka) {
    FILE* file = fopen(listadatoteka, "w");
    if (file == NULL) {
        printf("Greska pri otvaranju datoteke za pisanje\n");
        return;
    }

    struct Osoba* trenutnaOsoba = glava;
    while (trenutnaOsoba != NULL) {
        fprintf(file, "%s %s %d\n", trenutnaOsoba->ime, trenutnaOsoba->prezime, trenutnaOsoba->godina_rodjenja);
        trenutnaOsoba = trenutnaOsoba->sljedeci;
    }

    fclose(file);
}

// Funkcija za citanje liste iz datoteke
struct Osoba* citajListuIzDatoteke(const char* listadatoteka) {
    FILE* file = fopen(listadatoteka, "r");
    if (file == NULL) {
        printf("Greska pri otvaranju datoteke za citanje\n");
        return NULL;
    }

    struct Osoba* glava = NULL;
    char ime[10], prezime[10];
    int godina;

    while (fscanf(file, "%s %s %d", ime, prezime, &godina) != EOF) {
        glava = dodajNaKraj(glava, ime, prezime, godina);
    }

    fclose(file);
    return glava;
}
// Funkcija za brisanje odredjene osobe iz liste
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

int main() {
    struct Osoba* glava = NULL;
    int izbor;
    char ime[10], prezime[10];
    int godina;

    do {
        printf("\nIzaberite opciju:\n");
        printf("1. Dodaj osobu na pocetak liste\n");
        printf("2. Ispisi listu\n");
        printf("3. Dodaj osobu na kraj liste\n");
        printf("4. Pronadji osobu po prezimenu\n");
        printf("5. Obriši osobu iz liste\n");
        printf("6. Dodaj osobu iza odredjene osobe\n");
        printf("7. Dodaj osobu ispred odredjene osobe\n");
        printf("8. Sortiraj listu po prezimenima\n");
        printf("9. Upisi listu u datoteku\n");
        printf("10. Citaj listu iz datoteke\n");
        printf("0. Izlaz\n");
        scanf("%d", &izbor);

        switch (izbor) {
        case 1:
            printf("Unesite ime: ");
            scanf("%s", ime);
            printf("Unesite prezime: ");
            scanf("%s", prezime);
            printf("Unesite godinu rodjenja: ");
            scanf("%d", &godina);
            glava = dodajNaPocetak(glava, ime, prezime, godina);
            break;
        case 2:
            printf("Lista osoba:\n");
            ispisiListu(glava);
            break;
        case 3:
            printf("Unesite ime: ");
            scanf("%s", ime);
            printf("Unesite prezime: ");
            scanf("%s", prezime);
            printf("Unesite godinu rodjenja: ");
            scanf("%d", &godina);
            glava = dodajNaKraj(glava, ime, prezime, godina);
            break;
        case 4:
            printf("Unesite prezime za pretragu: ");
            scanf("%s", prezime);
            struct Osoba* pronadenaOsoba = pronadiPoPrezimenu(glava, prezime);
            if (pronadenaOsoba != NULL) {
                printf("Osoba pronadjena: Ime: %s, Prezime: %s, Godina rodjenja: %d\n", pronadenaOsoba->ime, pronadenaOsoba->prezime, pronadenaOsoba->godina_rodjenja);
            }
            else {
                printf("Osoba s prezimenom %s nije pronadjena.\n", prezime);
            }
            break;
        case 5:
            printf("Unesite prezime za brisanje: ");
            scanf("%s", prezime);
            glava = obrisiOsobu(glava, prezime);
            break;
        case 6:
            printf("Unesite ime za dodavanje iza: ");
            scanf("%s", ime);
            printf("Unesite prezime za dodavanje iza: ");
            scanf("%s", prezime);
            printf("Unesite godinu rodjenja: ");
            scanf("%d", &godina);
            glava = dodajIzaOsobe(glava, ime, prezime, godina, prezime);
            break;
        case 7:
            printf("Unesite ime za dodavanje ispred: ");
            scanf("%s", ime);
            printf("Unesite prezime za dodavanje ispred: ");
            scanf("%s", prezime);
            printf("Unesite godinu rodjenja: ");
            scanf("%d", &godina);
            glava = dodajIspredOsobe(glava, ime, prezime, godina, prezime);
            break;
        case 8:
            glava = sortirajListuPoPrezimenima(glava);
            printf("Lista sortirana po prezimenima.\n");
            break;
        case 9:
            upisiListuUDatoteku(glava, "listadatoteka.txt");
            printf("Lista upisana u datoteku 'listadatoteka.txt'.\n");
            break;
        case 10:
            glava = citajListuIzDatoteke("listadatoteka.txt");
            printf("Lista ucitana iz datoteke 'listadatoteka.txt'.\n");
            break;
        }
    } while (izbor != 0);

    // Oslobadjanje resursa (oslobodjenje memorije)
    while (glava != NULL) {
        struct Osoba* sljedecaOsoba = glava->sljedeci;
        free(glava);
        glava = sljedecaOsoba;
    }

    return 0;
}