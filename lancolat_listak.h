#ifndef LANCOLAT_LISTAK_H_INCLUDED
#define LANCOLAT_LISTAK_H_INCLUDED
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "debugmalloc.h"


typedef struct meret
{
    int szam;
    char jeleg;
    int x;
    int y;
    struct meret *kov;
} meret;

typedef struct menu
{
    char tipus;
    char *sorszam;
    char *nev;
    int arra;
    struct menu* kov;
} menu;

typedef struct asztalkordinata
{
    int x;
    int y;
    struct asztalkordinata *kov;
} asztalkordinata;

typedef struct asztal
{
    int asztal_szam;
    bool folalt;
    bool idopont;
    char *foglalasido;
    int vendegszam;
    menu *rendelesek;
    char jeleg;
    int emelet;
    int kordinata_szam;
    asztalkordinata *kordinata;
    struct asztal *kov;

} asztal;

menu *menu_elmei(menu *atvet,char tipus,char *sorszam,int arra,char *nev);
menu *menu_asztal(menu *atvet,char tipus,char *sorszam);
asztalkordinata *asztalkordinata_lancolat(asztalkordinata *regi,int x,int y);
void feltoltes_infomenu(asztal* lista, menu *menuk);
asztal *asztal_lancolat(asztal *regi,int asztal_szam,bool foglat,bool idopont,char *foglalasido,int vendegszam,menu *rendelesek,char jeleg,int emelet,int kordinata_szam,asztalkordinata *kordinata);
meret *meret_lancolat(meret* lista,int szam,char jeleg,int x, int y);


#endif // LANCOLAT_LISTAK_H_INCLUDED
