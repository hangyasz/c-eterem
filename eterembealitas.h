#ifndef ETEREMBEALITAS_H_INCLUDED
#define ETEREMBEALITAS_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "debugmalloc.h"
#include "beolvasok.h"
#include "lancolat_listak.h"
#include "asztal_muvelet.h"
#include "felszabadito.h"

void eterem_bealitas(void);
void menu_bealitas(void);
void sorszam_valtoztatas(menu *lista);
void nev_valtozatas(menu *lista);
void menu_noveles(menu* lista);
void menu_kiiro(menu* lista);
menu *mennu_muveletek(menu* lista);
void falj_muveletek(menu **menuk, meret **lista);
void fajlok_kezelese(void);
meret *terem_muveletek(meret* lista);
meret *torles_terem(meret *lista);
void tererm_meret_valtoztat(meret *lista);
void meret_noveles(meret* lista);
void meret_kiiro(meret* lista);
char *sorszam_felhaszanalo(char *tipus);
menu *menu_torles(menu *lista);
void arvalzotatas(menu *lista);
asztal * falj_asztal(void);
menu * falj_menu(void );
meret *falj_eterm(void);
asztalkordinata *kordinatatomb(int *szamalo, asztalkordinata *regi);
void asztalok_faljir(asztal *asztal_lista);



#endif // ETEREMBEALITAS_H_INCLUDED
