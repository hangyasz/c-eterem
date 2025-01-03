#ifndef BEOLVASOK_H_INCLUDED
#define BEOLVASOK_H_INCLUDED


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "debugmalloc.h"
#include "lancolat_listak.h"

char *hosszu_sort_olvas();
char *elejevag(char *s);
meret *helyek_azetermben(FILE *eterem_falj);
bool foglalas(char **foglalasiido);
char *hozzafuz(char *mihez, char mit);
menu *menubeolvas(FILE *eterem_menu);
asztal* asztal_addatokplvas(FILE *eterem_asztal);

#endif // BEOLVASOK_H_INCLUDED
