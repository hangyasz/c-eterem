#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "debugmalloc.h"
#include "lancolat_listak.h"
#include "felszabadito.h"

void asztal_felszabadit(asztal*lista)
{
    asztal *kov=lista;
    while(kov!=NULL)
    {
        asztal *aujeleje = kov->kov;
        if (kov->foglalasido!=NULL)
            free(kov->foglalasido);
        menu *mfelszabasit=kov->rendelesek;
        while(mfelszabasit!=NULL)
        {
            menu *mujeleje = mfelszabasit->kov;
            free(mfelszabasit->sorszam);
            free(mfelszabasit);
            kov->rendelesek = mujeleje;
            mfelszabasit=kov->rendelesek;
        }
        asztalkordinata* afelszabadit=kov->kordinata;
        while(afelszabadit!=NULL)
        {
            asztalkordinata *kujeleje = afelszabadit->kov;
            free(afelszabadit);
            kov->kordinata = kujeleje;
            afelszabadit=kov->kordinata;

        }
        free(kov);
        lista = aujeleje;
        kov=lista;
    }

}
void menu_felszabadito(menu* lista)
{
    menu *mfelszabasit=lista;
    while(mfelszabasit!=NULL)
    {
        menu *ujeleje = mfelszabasit->kov;
        free(mfelszabasit->nev);
        free(mfelszabasit->sorszam);
        free(mfelszabasit);
        lista = ujeleje;
        mfelszabasit=lista;
    }
}

void eterem_felszabadito(meret* lista)
{
    meret *tfelszabadit=lista;
    while(tfelszabadit!=NULL)
    {
        meret *ujeleje = tfelszabadit->kov;
        free(tfelszabadit);
        lista = ujeleje;
        tfelszabadit=lista;
    }
}
