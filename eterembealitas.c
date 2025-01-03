#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "debugmalloc.h"
#include "beolvasok.h"
#include "lancolat_listak.h"
#include "asztal_muvelet.h"
#include "felszabadito.h"
#include "eterembealitas.h"

void eterem_bealitas(void) {
    FILE *eterem_falj;
    eterem_falj = fopen("etterem_adatok.txt", "w");
    int sorszam;
    char tipus; //t ha terasz e ha emelet
    int hosz;
    int szel;
    printf("On elkezdte beallitani az ettermet.\n");
    printf("Kerem az adatok bevitelet. Az elso karakter legyen a helyiseg sorszama, a masodik karakter pedig a helyiseg tipusanak betuje,\n");
    printf("azutan pedig a szelesseget es hosszt adja meg meterben.\n");
    printf("Peldaul: '4e 34x56'. Amikor vegzett, irja be, hogy 'vege' es utana usson entert. \n");
    while (scanf("%d%c %dx%d", &sorszam, &tipus, &szel, &hosz) == 4 && sorszam != -1)
        fprintf(eterem_falj, "%d%c %dx%d\n", sorszam, tipus, szel, hosz);
    fclose(eterem_falj);
}

void menu_bealitas(void) {
    FILE *eterem_menu;
    eterem_menu = fopen("menu.txt", "w");
    printf("Kezdesnek irja be a menu sorszamat, usson entert, majd a menu nevet, enter es vegul az arat, majd enter.\n pl.1501 belszin steak 3500Ft");
    int szam;
    char *nev;
    int ar;
    printf("\nSorszam: ");
    fflush(stdin);
    while (scanf("%d", &szam) && szam != -1) {
        fflush(stdin);
        printf("Nev: ");
        nev = hosszu_sort_olvas();
        printf("Ar: ");
        scanf("%d", &ar);
        fprintf(eterem_menu, "%d+%s-%d:\n", szam, nev, ar);
        printf("Sorszam: ");
        free(nev);
    }
    fclose(eterem_menu);
}

asztalkordinata *kordinatatomb(int *szamalo, asztalkordinata *regi) {
    int x;
    int y;
    asztalkordinata *tomb = regi;
    printf("\nIrja be az asztal koordinatait! Kerem egyesevel vigye be az adatokat!)\n");
    printf("Az alabbi formaban: x:y\n");
    fflush(stdin);
    scanf("%d:%d", &x, &y);
    tomb = asztalkordinata_lancolat(tomb, x, y);
    *szamalo = 1 + *szamalo;
    return tomb;
}
void asztalok_faljir(asztal *asztal_lista) {
    FILE *asztal_kiro;
    asztal_kiro = fopen("asztal.txt", "w");
    asztal *kov = asztal_lista;
    asztalkordinata *kordintakov = NULL;
    menu *rendelesek = NULL;
    while (kov != NULL) {
        fprintf(asztal_kiro, "%d,%c", kov->emelet, kov->jeleg);
        fprintf(asztal_kiro, "%d!%d!", kov->asztal_szam, kov->kordinata_szam);
        kordintakov = kov->kordinata;
        while (kordintakov != NULL) {
            fprintf(asztal_kiro, "[%d:%d]", kordintakov->x, kordintakov->y);
            kordintakov = kordintakov->kov;
        }
        fprintf(asztal_kiro, "%d!%d!%s?%d+", kov->folalt, kov->idopont, kov->foglalasido, kov->vendegszam);
        rendelesek = kov->rendelesek;
        while (rendelesek != NULL) {
            fprintf(asztal_kiro, "%c%s$", rendelesek->tipus, rendelesek->sorszam);
            rendelesek = rendelesek->kov;
        }
        fprintf(asztal_kiro, "_");
        fprintf(asztal_kiro, "\n");
        kov = kov->kov;
    }
    fclose(asztal_kiro);
}


void menu_noveles(menu *lista) {
    char tipus;
    char *sorszam = NULL;
    char *nev = NULL;
    int arra;
    printf("Sorszam: ");
    fflush(stdin);
    while (true) {
        sorszam = hosszu_sort_olvas();
        tipus = sorszam[0];
        if (tipus == '-') {
            free(sorszam);
            return;
        }
        char *list_sorszam = elejevag(sorszam);
        fflush(stdin);
        printf("Nev: ");
        nev = hosszu_sort_olvas();
        printf("Ar: ");
        scanf("%d", &arra);
        lista = menu_elmei(lista, tipus, list_sorszam, arra, nev);
        printf("Sorszam: ");
        sorszam = NULL;
        nev = NULL;
    }
}

void menu_kiiro(menu *lista) {
    menu *aktualis = lista;
    FILE *eterem_menu;
    eterem_menu = fopen("menu.txt", "w");
    if (aktualis == NULL) {
        fprintf(eterem_menu, "");
        fclose(eterem_menu);
        return;
    }
    while (aktualis != NULL) {
        fprintf(eterem_menu, "%c%s+%s-%d:\n", aktualis->tipus, aktualis->sorszam, aktualis->nev, aktualis->arra);
        aktualis = aktualis->kov;
    }
    fclose(eterem_menu);

}

char *sorszam_felhaszanalo(char *tipus) {
    char *sorszam;
    printf("kerem irja be a menu sorszamat: ");
    sorszam = hosszu_sort_olvas();
    *tipus = sorszam[0];
    if (1==strlen(sorszam)){
        printf("rosz formatum\n");
        return NULL;}
    return elejevag(sorszam);
}
void sorszam_valtoztatas(menu *lista){
    menu *aktulis = lista;
    char tipus;
    char *sorszam = sorszam_felhaszanalo(&tipus);
    if (sorszam==NULL)
        return;
    while (aktulis != NULL) {
        if (aktulis->tipus == tipus && 0 == strcmp(aktulis->sorszam, sorszam)) {
            free(sorszam);
            sorszam = sorszam_felhaszanalo(&tipus);
            if (sorszam==NULL){
                printf("nem elvegezheto muvelet");
                return;
            }
            free(aktulis->sorszam);
            aktulis->sorszam=sorszam;
            aktulis->tipus=tipus;
            return;
        }
        aktulis = aktulis->kov;
    }
    printf("sorszam nem talahato\n");
    free(sorszam);

}


void nev_valtozatas(menu *lista){
    menu *aktulis = lista;
    char tipus;
    char *sorszam = sorszam_felhaszanalo(&tipus);
    if (sorszam==NULL)
        return;
    while (aktulis != NULL) {
        if (aktulis->tipus == tipus && 0 == strcmp(aktulis->sorszam, sorszam)) {
            printf("mi legyen az uj nev ");
            free(aktulis->nev);
            aktulis->nev=hosszu_sort_olvas();
            free(sorszam);
            return;
        }
        aktulis = aktulis->kov;
    }
    printf("sorszam nem talahato\n");
    free(sorszam);

}

void arvalzotatas(menu *lista) {
    menu *aktulis = lista;
    char tipus;
    char *sorszam = sorszam_felhaszanalo(&tipus);
    if (sorszam==NULL)
        return;
    while (aktulis != NULL) {
        if (aktulis->tipus == tipus && 0 == strcmp(aktulis->sorszam, sorszam)) {
            printf("mi legyen az uj arr? ");
            scanf("%d", &aktulis->arra);
            free(sorszam);
            return;
        }
        aktulis = aktulis->kov;
    }
    printf("sorszam nem talahato\n");
    free(sorszam);
}


menu* menu_torles(menu *lista) {
    menu *aktulis = lista;
    menu *lemarado = NULL;
    char tipus;
    char *sorszam = sorszam_felhaszanalo(&tipus);
    if (sorszam==NULL)
        return lista;
    while (aktulis != NULL) {
        if (aktulis->tipus == tipus && 0 == strcmp(aktulis->sorszam, sorszam)) {
            if (lemarado == NULL) {
                menu *ujeje = aktulis->kov;
                free(aktulis->sorszam);
                free(aktulis->nev);
                free(aktulis);
                free(sorszam);
                return ujeje;
            } else {
                lemarado->kov = aktulis->kov;
                free(aktulis->sorszam);
                free(aktulis->nev);
                free(aktulis);
                free(sorszam);
                return lista;
            }
        }
        lemarado = aktulis;
        aktulis = aktulis->kov;

    }
    printf("sorszam nem talahato\n");
    free(sorszam);
    return lista;
}

menu *mennu_muveletek(menu *lista) {
    int menuszam = 0;
    menu *lep =  lista;
    while (lep != NULL) {
        printf("%c%s %s %d\n", lep->tipus, lep->sorszam, lep->nev, lep->arra);
        ++menuszam;
        lep = lep->kov;
    }
    if (menuszam == 0) {
        menu_bealitas();
        return falj_menu();
    }

    printf("Egesz menu ujrairasa=i menuhoz hozzaadas=h  menu torles=t  arr valzotatas=a nev valzotatas=n sorszam valtoztatas=s visszateres=enter ");
    fflush(stdin);
    char beolvasot;
    scanf("%c", &beolvasot);
    if (beolvasot == 'i') {
        menu_bealitas();
        menu_felszabadito(lista);
        return falj_menu();
    } else if (beolvasot == 'h') {
        menu_noveles(lista);
        menu_kiiro(lista);
        return lista;
    } else if (beolvasot == 't') {
        lista=menu_torles(lista);
        menu_kiiro(lista);
        lista=mennu_muveletek(lista);
        return lista;
    } else if (beolvasot == 'a') {
        arvalzotatas(lista);
        menu_kiiro(lista);
        lista=mennu_muveletek(lista);
        return lista;
    } else if(beolvasot == 'n'){
        nev_valtozatas(lista);
        menu_kiiro(lista);
        lista=mennu_muveletek(lista);
        return lista;
    }
    else if(beolvasot == 's'){
        sorszam_valtoztatas(lista);
        menu_kiiro(lista);
        lista=mennu_muveletek(lista);
        return lista;
    }

    return lista;
}

void meret_kiiro(meret *lista) {
    FILE *eterem_falj;
    eterem_falj = fopen("etterem_adatok.txt", "w");
    meret *kov = lista;
    while (kov != NULL) {
        fprintf(eterem_falj, "%d%c %dx%d\n", kov->szam, kov->jeleg, kov->x, kov->y);
        kov = kov->kov;
    }
    fclose(eterem_falj);


}

void meret_noveles(meret *lista) {
    int sorszam;
    char tipus; //t ha terasz e ha emelet
    int hosz;
    int szel;
    printf("Etterem novelese, uj emelet\n");
    printf("Kerem az adatok bevitelet. Az elso karakter legyen a helyiseg sorszama, a masodik karakter pedig a helyiseg tipusanak betuje,\n");
    printf("azutan pedig a szelesseget es hosszt adja meg meterben.");
    printf("Peldaul: '4e 34x56' Amikor vegzett, irja be: vege es utana usson entert. \n");
    while (scanf("%d%c %dx%d", &sorszam, &tipus, &szel, &hosz) == 4 && sorszam != -1)
        lista = meret_lancolat(lista, sorszam, tipus, szel, hosz);


}
meret *torles_terem(meret *lista){
    printf("kerem az helyet amelyet tolrni szeretne: ");
    char jeleg;
    int sorszam;
    scanf("%d%c",&sorszam,&jeleg);
    meret *aktulis = lista;
    meret *lemarado = NULL;
    while (aktulis != NULL) {
        if (aktulis->szam==sorszam&&aktulis->jeleg==jeleg) {
            if (lemarado == NULL) {
                meret *ujeje = aktulis->kov;
                free(aktulis);
                return ujeje;
            } else {
                lemarado->kov = aktulis->kov;
                free(aktulis);
                return lista;
            }
        }
        lemarado = aktulis;
        aktulis = aktulis->kov;

    }
    printf("hely nem talahato\n");
    return lista;
}

void tererm_meret_valtoztat(meret *lista){
    printf("kerem a modositani kivant helyet: ");
    char jeleg;
    int sorszam;
    scanf("%d%c",&sorszam,&jeleg);
    meret *aktulis = lista;
    while (aktulis!=NULL){
        if (aktulis->szam==sorszam&&aktulis->jeleg==jeleg) {
            printf("kerem az uj mereteket 3x5 formaban: ");
            scanf("%dx%d",&aktulis->x,&aktulis->y);
            return;
        }
        aktulis=aktulis->kov;
    }
    printf("hely nem talahato\n");
    return;
}



meret *terem_muveletek(meret *lista) {
    int mert_szam = 0;
    meret *lep = lista;
    while (lep != NULL) {
        printf("%d%c %dx%d\n", lep->szam, lep->jeleg, lep->x, lep->y);
        ++mert_szam;
        lep = lep->kov;
    }
    if (mert_szam == 0) {
        eterem_bealitas();
        return falj_eterm();
    }

    printf("Egesz etterem mereteinek ujrairasa=i etterem novelese=n hely torles=t terem adatok modositasa=m visszateres=enter ");
    fflush(stdin);
    char beolvasot;
    scanf("%c", &beolvasot);
    if (beolvasot == 'i') {
        eterem_bealitas();
        eterem_felszabadito(lista);
        return falj_eterm();
    } else if (beolvasot == 'n') {
        meret_noveles(lista);
        meret_kiiro(lista);
        return lista;
    }
    else if (beolvasot == 't') {
        lista= torles_terem(lista);
        meret_kiiro(lista);
        lista=terem_muveletek(lista);
        return lista;}
    else if (beolvasot == 'm') {
        tererm_meret_valtoztat(lista);
        meret_kiiro(lista);
        terem_muveletek(lista);
        return lista;}
    return lista;

}


void falj_muveletek(menu **menuk, meret **lista) {
    printf("Ha menut szeretne modositani, irjon: m, ha az etterem termeit, irjon: t, bezarashoz nyomjon entert. ");
    fflush(stdin);
    char beolvasot;
    scanf("%c", &beolvasot);
    if (beolvasot == 'm') {
        *menuk = mennu_muveletek(*menuk);
        falj_muveletek(menuk, lista);
    } else if (beolvasot == 't') {
        *lista=terem_muveletek(*lista);
        falj_muveletek(menuk,lista);
    }
}

meret *falj_eterm(void) {
    FILE *eterem_falj;
    eterem_falj = fopen("etterem_adatok.txt", "r");
    if (eterem_falj == NULL) {
        fclose(eterem_falj);
        eterem_bealitas();
        eterem_falj = fopen("etterem_adatok.txt", "r");
    }

    meret *eteremadat = helyek_azetermben(eterem_falj);
    fclose(eterem_falj);
    return eteremadat;
}

menu *falj_menu(void) {
    FILE *eterem_menu;
    eterem_menu = fopen("menu.txt", "r");
    if (eterem_menu == NULL) {
        fclose(eterem_menu);
        menu_bealitas();
        eterem_menu = fopen("menu.txt", "r");
    }
    menu *menukbe = menubeolvas(eterem_menu);
    fclose(eterem_menu);
    return menukbe;
}

asztal *falj_asztal(void) {
    FILE *eterem_asztal;
    asztal *beolvas = NULL;
    eterem_asztal = fopen("asztal.txt", "r");
    if (eterem_asztal != NULL) {
        beolvas = asztal_addatokplvas(eterem_asztal);
        fclose(eterem_asztal);
    } else
        fclose(eterem_asztal);
    return beolvas;
}


void fajlok_kezelese(void) {
    meret *eteremadat = falj_eterm();
    menu *menukbe = falj_menu();
    asztal *beolvas = falj_asztal();
    feltoltes_infomenu(beolvas, menukbe);
    beolvas = valsztlehetosegek(&eteremadat, beolvas, &menukbe);
    menu_felszabadito(menukbe);
    eterem_felszabadito(eteremadat);
    asztal_felszabadit(beolvas);

}



