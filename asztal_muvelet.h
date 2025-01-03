#ifndef ASZTAL_MUVELET_H_INCLUDED
#define ASZTAL_MUVELET_H_INCLUDED
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "debugmalloc.h"
#include "beolvasok.h"
#include "lancolat_listak.h"
#include "eterembealitas.h"


void rendeles_felvetel(int szam,char jeleg,asztal *asztal_lista);
void meret_csokentes(asztal* kereset);
void foglalas_szerket(asztal* kereset);
void rendeles_torles(asztal *kerest);
void letszam_modosit(asztal*kereset);
void asztal_kezeles(asztal *asztal_lista,int szam, char jeleg);
void fizetet(int szam, char jeleg,asztal *asztal_lista);
bool asztal_torlo(asztal*lista,int szam, char jeleg);
asztal *asztal_muveletek(int szam, char jeleg,asztal *asztal_lista,menu *menukbe,meret *tomb);
void terem_terkep(asztal *lista,int szam,char jeleg,meret* tomb);
asztal *valsztlehetosegek(meret **tomb, asztal *asztal_lista,menu **menukbe);
asztal *hozado(int emelet, char jeleg, asztal *asztal_lista);



#endif // ASZTAL_MUVELET_H_INCLUDED
