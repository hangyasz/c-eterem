#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include "debugmalloc.h"
#include "beolvasok.h"
#include "lancolat_listak.h"
#include "szines.h"
#include "eterembealitas.h"
#include "asztal_muvelet.h"

asztal *hozado(int emelet, char jeleg, asztal *asztal_lista) {
    int asztal_szam;
    bool folalt = false;
    bool idopont;
    char *foglalasido = NULL;
    int vendegszam;
    menu *rendelesek = NULL;
    int kordinata_szam = 0;
    asztalkordinata *kordinata = NULL;
    asztal *lista = asztal_lista;
    bool talalat = false;
    fflush(stdin);
    printf("Kerem irja be az asztal a sorszamat, amit hozza akkar adni, es amikor vegzett, akkor irja be: -1    ");
    while (scanf("%d", &asztal_szam) && asztal_szam != -1) {
        talalat = false;
        asztal *koz = lista;
        while (koz != NULL && talalat == false) {
            if (emelet == koz->emelet && jeleg == koz->jeleg && asztal_szam == koz->asztal_szam) {
                koz->kordinata = kordinatatomb(&koz->kordinata_szam, koz->kordinata);
                fflush(stdin);
                printf("Hany fos a bovitett asztal? ");
                scanf("%d", &koz->vendegszam);
                talalat = true;
            }
            koz = koz->kov;
        }
        if (talalat == false) {
            fflush(stdin);
            idopont = foglalas(&foglalasido);
            kordinata = kordinatatomb(&kordinata_szam, kordinata);
            printf("Hany fos az asztal? ");
            scanf("%d", &vendegszam);
            lista = asztal_lancolat(lista, asztal_szam, folalt, idopont, foglalasido, vendegszam, rendelesek, jeleg,
                                    emelet, kordinata_szam, kordinata);
        }
        foglalasido = NULL;
        kordinata = NULL;
        kordinata_szam = 0;
        printf("Kerem irja be az asztal a sorszamat, amit hozza akkar adni, es amikor vegzett, akkor irja be: -1 ");
        fflush(stdin);
    }

    return lista;
}


void rendeles_felvetel(int szam, char jeleg, asztal *asztal_lista) {

    int asztal_szam;
    fflush(stdin);
    printf("Kerem az asztal szamat: ");
    scanf("%d", &asztal_szam);
    char tipus;
    char *sorszam;
    asztal *kovetkezo_asztal = asztal_lista;
    while (kovetkezo_asztal != NULL) {
        if (kovetkezo_asztal->emelet == szam && kovetkezo_asztal->jeleg == jeleg &&
            kovetkezo_asztal->asztal_szam == asztal_szam) {
            while (tipus != '-') {
                printf("Kerem vigye be a menu a sorszamat!");
                sorszam = hosszu_sort_olvas();
                tipus = sorszam[0];
                sorszam = elejevag(sorszam);
                if (tipus != '-') {
                    kovetkezo_asztal->folalt = true;
                    kovetkezo_asztal->rendelesek = menu_asztal(kovetkezo_asztal->rendelesek, tipus, sorszam);
                    return;
                }
            }
        }

        kovetkezo_asztal = kovetkezo_asztal->kov;
    }
}

void meret_csokentes(asztal *kereset) {
    int x;
    int y;
    asztalkordinata *kordinatakov = kereset->kordinata;
    asztalkordinata *lemarad = NULL;
    printf("A koordinatat az alabbi formaban irja be x:y\n");
    fflush(stdin);
    int kordinata_szam = kereset->kordinata_szam - 1;
    scanf("%d:%d", &x, &y);
    while (kordinatakov != NULL) {
        if (x == kordinatakov->x && y == kordinatakov->y) {
            if (0 < kordinata_szam) {
                if (lemarad == NULL) {
                    asztalkordinata *ujeleje = kordinatakov->kov;
                    free(kordinatakov);
                    kereset->kordinata = ujeleje;
                } else {
                    lemarad->kov = kordinatakov->kov;
                    free(kordinatakov);
                }
                kereset->kordinata_szam = kereset->kordinata_szam - 1;
                return;
            } else {
                printf("Hiba! Ilyen modon nem lehet asztalt torolni!\n");
                return;
            }
        }

        lemarad = kordinatakov;
        kordinatakov = kordinatakov->kov;
    }

}

void foglalas_szerket(asztal *kereset) {
    char valasz;
    printf("Az asztal foglalasa/foglalasi idopont modositasa/beallitasa= f, asztal foglalas torlese= n\n");
    fflush(stdin);
    char *sor = NULL;
    scanf("%c", &valasz);
    if (valasz == 'n') {
        kereset->idopont = false;
        if (kereset->foglalasido != NULL)
            free(kereset->foglalasido);
        kereset->foglalasido = NULL;
    } else {
        kereset->idopont = true;
        printf("Az idopont: ");
        free(kereset->foglalasido);
        sor = hosszu_sort_olvas();
        kereset->foglalasido = sor;
    }


}

void rendeles_torles(asztal *kerest) {
    menu *aktualis = kerest->rendelesek;
    menu *lemarado = NULL;
    printf("Kerem a torolje a kivant menusorszamot\n");
    char tipus;
    char *sorszam = hosszu_sort_olvas();
    tipus = sorszam[0];
    sorszam = elejevag(sorszam);

    while (aktualis != NULL) {
        if (tipus == aktualis->tipus && 0 == strcmp(sorszam, aktualis->sorszam)) {
            if (lemarado == NULL) {
                menu *ujeleje = aktualis->kov;
                free(aktualis->sorszam);
                free(aktualis);
                kerest->rendelesek = ujeleje;
            } else {
                lemarado->kov = aktualis->kov;
                free(aktualis->sorszam);
                free(aktualis);
            }
            return;
        } else {
            lemarado = aktualis;
            aktualis = aktualis->kov;
        }
    }
    printf("A sorszam nem talalhato!");

}

void letszam_modosit(asztal *kereset) {
    printf("Hany fos legyen az asztal? ");
    scanf("%d", &kereset->vendegszam);
}

void asztal_kezeles(asztal *asztal_lista, int szam, char jeleg) {
    int asztal_szam;
    fflush(stdin);
    printf("Kerem az asztal szamat: ");
    scanf("%d", &asztal_szam);
    asztal *kovetkezo_asztal = asztal_lista;
    bool van = false;
    int oszeg = 0;
    char muvelet;
    asztal *kerest = NULL;
    while (van != true && kovetkezo_asztal != NULL) {
        if (kovetkezo_asztal->emelet == szam && kovetkezo_asztal->jeleg == jeleg &&
            kovetkezo_asztal->asztal_szam == asztal_szam) {
            kerest = kovetkezo_asztal;
            asztalkordinata *kordinata = kovetkezo_asztal->kordinata;
            printf("Az asztal adatai:\n");
            printf("A koordinatak:");
            while (kordinata != NULL) {
                printf(" [%d:%d]", kordinata->x, kordinata->y);
                kordinata = kordinata->kov;
            }
            printf("\n Foglalt az asztal?=%d Idopont=%s", kovetkezo_asztal->folalt, kovetkezo_asztal->foglalasido);
            printf("\n Vendegszam %d\n", kovetkezo_asztal->vendegszam);
            menu *rendelt = kovetkezo_asztal->rendelesek;
            printf("Rendelesek\n");
            while (rendelt != NULL) {
                printf("%c%s %s %d\n", rendelt->tipus, rendelt->sorszam, rendelt->nev, rendelt->arra);
                oszeg += rendelt->arra;
                rendelt = rendelt->kov;
            }
            printf("Eddigi rendelesek: %d Ft\n", oszeg);
            van = true;

        }

        kovetkezo_asztal = kovetkezo_asztal->kov;
    }

    if (van == false) {
        printf("Nincs ilyen asztal!");
        return;
    } else {
        printf("Asztal mereteinek csokkentese=c, foglalas=f, rendeles torles=r, letszam modositas=l, tovabb enter: ");
        fflush(stdin);
        scanf("%c", &muvelet);
        if (muvelet == 'c') {
            meret_csokentes(kerest);
            asztal_kezeles(asztal_lista, szam, jeleg);

        } else if (muvelet == 'f') {
            foglalas_szerket(kerest);
            asztal_kezeles(asztal_lista, szam, jeleg);

        } else if (muvelet == 'r') {
            rendeles_torles(kerest);
            asztal_kezeles(asztal_lista, szam, jeleg);
        } else if (muvelet == 'l') {
            letszam_modosit(kerest);
            asztal_kezeles(asztal_lista, szam, jeleg);
        } else
            return;

    }

}

void fizetet(int szam, char jeleg, asztal *asztal_lista) {
    printf("Kerem az asztal szamat ahol fizetni szeretne: ");
    int asztalszam;
    fflush(stdin);
    scanf("%d", &asztalszam);
    asztal *kovetkezo_asztal = asztal_lista;
    int oszeg = 0;
    while (kovetkezo_asztal != NULL) {
        if (kovetkezo_asztal->emelet == szam && kovetkezo_asztal->jeleg == jeleg &&
            kovetkezo_asztal->asztal_szam == asztalszam) {
            menu *rendelt = kovetkezo_asztal->rendelesek;
            printf("Rendelesek\n");
            while (rendelt != NULL) {
                printf("%c%s %s %d\n", rendelt->tipus, rendelt->sorszam, rendelt->nev, rendelt->arra);
                oszeg += rendelt->arra;
                menu *ujeleje = rendelt->kov;
                free(rendelt->sorszam);
                free(rendelt);
                kovetkezo_asztal->rendelesek = ujeleje;
                rendelt = kovetkezo_asztal->rendelesek;
            }
            kovetkezo_asztal->folalt = false;
            printf("Fizetendo osszeg: %d Ft\n", oszeg);
            return;

        }
        kovetkezo_asztal = kovetkezo_asztal->kov;

    }
}

bool asztal_torlo(asztal *lista, int szam, char jeleg) {
    printf("Kerem az asztal szamat amit torolni szeretne: ");
    int asztalszam;
    fflush(stdin);
    scanf("%d", &asztalszam);
    asztal *kov = lista;
    asztal *lemarad = NULL;
    while (kov != NULL) {
        if (kov->emelet == szam && kov->jeleg == jeleg && kov->asztal_szam == asztalszam) {
            if (lemarad == NULL) {
                asztal *aujeleje = kov->kov;
                free(kov->foglalasido);
                menu *mfelszabasit = kov->rendelesek;
                while (mfelszabasit != NULL) {
                    menu *mujeleje = mfelszabasit->kov;
                    free(mfelszabasit->sorszam);
                    free(mfelszabasit);
                    kov->rendelesek = mujeleje;
                    mfelszabasit = kov->rendelesek;
                }
                asztalkordinata *afelszabadit = kov->kordinata;
                while (afelszabadit != NULL) {
                    asztalkordinata *kujeleje = afelszabadit->kov;
                    free(afelszabadit);
                    kov->kordinata = kujeleje;
                    afelszabadit = kov->kordinata;

                }
                free(kov);
                lista = aujeleje;
                if (lista == NULL)
                    return true;
                else
                    return false;
            } else {
                lemarad->kov = kov->kov;
                free(kov->foglalasido);
                menu *mfelszabasit = kov->rendelesek;
                while (mfelszabasit != NULL) {
                    menu *mujeleje = mfelszabasit->kov;
                    free(mfelszabasit->sorszam);
                    free(mfelszabasit);
                    kov->rendelesek = mujeleje;
                    mfelszabasit = kov->rendelesek;
                }
                asztalkordinata *afelszabadit = kov->kordinata;
                while (afelszabadit != NULL) {
                    asztalkordinata *kujeleje = afelszabadit->kov;
                    free(afelszabadit);
                    kov->kordinata = kujeleje;
                    afelszabadit = kov->kordinata;

                }
                free(kov);
                return false;

            }

        }
        lemarad = kov;
        kov = kov->kov;
    }
    return false;
}

asztal *asztal_muveletek(int szam, char jeleg, asztal *asztal_lista, menu *menukbe, meret *tomb) {

    terem_terkep(asztal_lista, szam, jeleg, tomb);
    printf("\n");
    char valasztas;
    printf("Uj asztal hozzadasa =a, Rendelesfelvetel=r, Asztal kezelese=k, Asztal fizetes=f, Asztal torlese=t, Kilepes=e\n");
    fflush(stdin);
    scanf("%c", &valasztas);
    if (valasztas == 'a') {
        asztal_lista = hozado(szam, jeleg, asztal_lista);
        asztalok_faljir(asztal_lista);
        asztal_lista = asztal_muveletek(szam, jeleg, asztal_lista, menukbe, tomb);
    } else if (valasztas == 'r') {
        rendeles_felvetel(szam, jeleg, asztal_lista);
        feltoltes_infomenu(asztal_lista, menukbe);
        asztalok_faljir(asztal_lista);
        asztal_lista = asztal_muveletek(szam, jeleg, asztal_lista, menukbe, tomb);
    } else if (valasztas == 'k') {
        asztal_kezeles(asztal_lista, szam, jeleg);
        asztalok_faljir(asztal_lista);
        asztal_lista = asztal_muveletek(szam, jeleg, asztal_lista, menukbe, tomb);

    } else if (valasztas == 'f') {

        fizetet(szam, jeleg, asztal_lista);
        asztalok_faljir(asztal_lista);
        asztal_lista = asztal_muveletek(szam, jeleg, asztal_lista, menukbe, tomb);

    } else if (valasztas == 't') {
        if (true == asztal_torlo(asztal_lista, szam, jeleg))
            asztal_lista = NULL;
        asztalok_faljir(asztal_lista);
        asztal_lista = asztal_muveletek(szam, jeleg, asztal_lista, menukbe, tomb);

    }
    return asztal_lista;

}

void terem_terkep(asztal *lista, int szam, char jeleg, meret *tomb) {
    meret *lep = tomb;
    bool hely = false;
    asztal *kovasztal;
    while (lep != NULL) {
        if (lep->szam == szam && lep->jeleg == jeleg) {
            for (int x = 0; x <= lep->x; ++x) {
                if (x == 0)
                    printf("    ");
                else
                    printf(" %4d ", x);
            }
            printf("\n");
            for (int y = 0; y < lep->y; ++y) {
                printf("%4d", 1 + y);
                for (int x = 0; x < lep->x; ++x) {
                    hely = false;
                    kovasztal = lista;
                    while (kovasztal != NULL && hely == false) {
                        asztalkordinata *kordinata = kovasztal->kordinata;
                        while (kordinata != NULL) {
                            if (kovasztal->emelet == szam && kovasztal->jeleg == jeleg && kordinata->x == 1 + x &&
                                kordinata->y == 1 + y) {
                                if (kovasztal->folalt == true) {
                                    SetColor(4);
                                    printf(" %3d", kovasztal->asztal_szam);
                                    printf("F");
                                } else if (kovasztal->idopont == true) {
                                    SetColor(1);
                                    printf(" %3d", kovasztal->asztal_szam);
                                    printf("X");
                                } else {
                                    SetColor(2);
                                    printf(" %3d", kovasztal->asztal_szam);
                                    printf("S ");
                                }
                                hely = true;
                                //SetColor(15);
                            }
                            kordinata = kordinata->kov;
                        }
                        kovasztal = kovasztal->kov;
                    }
                    if (hely == false)
                        printf(" xxxx ");
                }
                printf("\n");
            }
        }
        lep = lep->kov;
    }

}


asztal *valsztlehetosegek(meret **tomb, asztal *asztal_lista, menu **menukbe) {
    printf("Ha be szeretne zarni a programot irja be hogy zaras\n");
    int szam;
    char jeleg;
    meret *lep = *tomb;
    while (lep != NULL) {
        printf("%d%c  ", lep->szam, lep->jeleg);
        lep = lep->kov;
    }
    printf("Melyik helyen szeretne dolgozni? ");
    fflush(stdin);
    char *zaras = hosszu_sort_olvas();
    if (0 == strcmp(zaras, "zaras")) {
        free(zaras);
        return asztal_lista;} else{
        if (sscanf(zaras, "%d%c", &szam, &jeleg) == 2) {
            free(zaras);
            if (szam == -0 && jeleg == 't')
                falj_muveletek(&*menukbe, &*tomb);
            else
                asztal_lista = asztal_muveletek(szam, jeleg, asztal_lista, *menukbe, *tomb);
            asztal_lista = valsztlehetosegek(&*tomb, asztal_lista, &*menukbe);

        } else {
            free(zaras);
            asztal_lista = valsztlehetosegek(&*tomb, asztal_lista, &*menukbe);
        }
    }
}
