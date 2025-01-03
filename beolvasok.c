#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "debugmalloc.h"
#include "lancolat_listak.h"
#include "beolvasok.h"

char *hozzafuz(char *mihez, char mit) {
    int ujhosz = 1;
    if (mihez != NULL) {
        ujhosz = strlen(mihez);
        char *ujtomb = (char *) malloc(sizeof(char) * (ujhosz + 2));
        for (int i = 0; i < ujhosz; ++i)
            ujtomb[i] = mihez[i];
        free(mihez);
        ujtomb[ujhosz] = mit;
        ujtomb[ujhosz + 1] = '\0';
        return ujtomb;
    }
    char *ujtomb = (char *) malloc(sizeof(char) * (ujhosz + 1));
    ujtomb[0] = mit;
    ujtomb[ujhosz] = '\0';
    return ujtomb;
}

char *hosszu_sort_olvas() {
    int db = 0;
    char *sor = (char *) malloc(sizeof(char) * 1);
    sor[0] = '\0';
    char ujkar;
    fflush(stdin);
    while (scanf("%c", &ujkar) == 1 && ujkar != '\n') {
        char *ujtomb = (char *) malloc(sizeof(char) * (db + 1 + 1));
        strcpy(ujtomb, sor);
        free(sor);
        sor = ujtomb;
        ujtomb[db] = ujkar;
        ujtomb[db + 1] = '\0';
        ++db;
    }

    return sor;
}

char *elejevag(char *s) {
    int karakter_db = strlen(s);
    if (karakter_db == 1) {
        free(s);
        return NULL;
    }
    char *vag = (char *) malloc(karakter_db * sizeof(char));
    int poz = 0;
    int kezd = 1;
    while (kezd < karakter_db)
        vag[poz++] = s[kezd++];
    vag[poz] = '\0';
    free(s);
    return vag;
}

meret *helyek_azetermben(FILE *eterem_falj) {
    meret *meret_tomb = NULL;
    int sorszam;
    char jeleg;
    int hosz;
    int szel;
    while (fscanf(eterem_falj, "%d%c %dx%d\n", &sorszam, &jeleg, &szel, &hosz) == 4) {
        meret_tomb = meret_lancolat(meret_tomb, sorszam, jeleg, szel, hosz);
    }
    return meret_tomb;
}


bool foglalas(char **foglalasiido) {
    printf("Van foglalas az asztalra? Igen=i Nem=n ");
    char foglal;
    fflush(stdin);
    scanf("%c", &foglal);
    if (foglal == 'i') {
        printf("Mely idopontban erkeznek a vendegek? Formatum: (17:15 vagy 05:25) ");
        fflush(stdin);
        *foglalasiido = hosszu_sort_olvas();
        return true;
    } else {
        *foglalasiido = NULL;
        return false;
    }
}



menu *menubeolvas(FILE *eterem_menu) {
    char *sorszam = NULL;
    char *nev = NULL;
    char tipus;
    int arra;
    menu *menuk = NULL;
    char get;
    while (fscanf(eterem_menu, "%c", &get) == 1 && get != EOF) {
        tipus = get;
        while (fscanf(eterem_menu, "%c", &get) == 1 && get != '+')
            sorszam = hozzafuz(sorszam, get);
        while (fscanf(eterem_menu, "%c", &get) == 1 && get != '-')
            nev = hozzafuz(nev, get);
        fscanf(eterem_menu, "%d:\n", &arra);
        menuk = menu_elmei(menuk, tipus, sorszam, arra, nev);
        sorszam = NULL;
        nev = NULL;
    }

    return menuk;
}

asztal *asztal_addatokplvas(FILE *eterem_asztal) {
    int asztal_szam;
    bool folalt;
    bool idopont;
    char *foglalasido = NULL;
    int vendegszam;
    menu *rendelesek = NULL;
    char jeleg;
    int emelet;
    int kordinata_szam;
    asztalkordinata *kordinata = NULL;
    char get;
    int x;
    int y;
    int fog;
    int ido;
    char *sorszam = NULL;
    char tipus;
    asztal *tomb = NULL;
    while (fscanf(eterem_asztal, "%d,%c%d!%d!", &emelet, &jeleg, &asztal_szam, &kordinata_szam) == 4) {
        for (int i = 0; i < kordinata_szam; ++i) {
            fscanf(eterem_asztal, "[%d:%d]", &x, &y);
            kordinata = asztalkordinata_lancolat(kordinata, x, y);
        }
        fscanf(eterem_asztal, "%d!%d!", &fog, &ido);
        if (fog == 1)
            folalt = true;
        else
            folalt = false;
        if (ido == 1) {
            idopont = true;
            while (fscanf(eterem_asztal, "%c", &get) == 1 && get != '?')
                foglalasido = hozzafuz(foglalasido, get);
            fscanf(eterem_asztal, "%d+", &vendegszam);
        } else {
            idopont = false;
            foglalasido = NULL;
            fscanf(eterem_asztal, "(null)?%d+", &vendegszam);
        }
        while (fscanf(eterem_asztal, "%c", &get) && get != '_') {
            tipus = get;
            while (fscanf(eterem_asztal, "%c", &get) == 1 && get != '$')
                sorszam = hozzafuz(sorszam, get);
            rendelesek = menu_asztal(rendelesek, tipus, sorszam);
            sorszam = NULL;
        }
        fscanf(eterem_asztal, "%c", &get);
        tomb = asztal_lancolat(tomb, asztal_szam, folalt, idopont, foglalasido, vendegszam, rendelesek, jeleg, emelet,
                               kordinata_szam, kordinata);
        foglalasido = NULL;
        rendelesek = NULL;
        kordinata = NULL;
        sorszam = NULL;
    }
    return tomb;
}

