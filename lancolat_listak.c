#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "debugmalloc.h"
#include "lancolat_listak.h"

menu *menu_elmei(menu *atvet,char tipus,char *sorszam,int arra,char *nev)
{
    if (atvet == NULL)
    {
        menu *uj = (menu *) malloc(sizeof(menu));
        uj->tipus = tipus;
        uj->sorszam = sorszam;
        uj->arra=arra;
        uj->nev=nev;
        uj->kov = NULL;
        return uj;
    }
    atvet->kov = menu_elmei(atvet->kov, tipus, sorszam,arra,nev);
    return atvet;
}

menu *menu_asztal(menu *atvet,char tipus,char *sorszam)
{
    if (atvet == NULL)
    {
        //printf("%c %s %s %d\n",tipus,sorszam,nev,arra);
        menu *uj = (menu *) malloc(sizeof(menu));
        uj->tipus = tipus;
        uj->sorszam = sorszam;
        uj->nev=NULL;
        uj->kov = NULL;
        return uj;
    }
    atvet->kov = menu_asztal(atvet->kov, tipus, sorszam);
    return atvet;
}

asztalkordinata *asztalkordinata_lancolat(asztalkordinata *regi,int x,int y)
{
    if (regi==NULL)
    {
        asztalkordinata *uj=(asztalkordinata*) malloc(sizeof (asztalkordinata));
        uj->x=x;
        uj->y=y;
        uj->kov=NULL;
        return uj;
    }
    regi->kov=asztalkordinata_lancolat(regi->kov,x,y);
    return regi;
}

asztal *asztal_lancolat(asztal *regi,int asztal_szam,bool foglat,bool idopont,char *foglalasido,int vendegszam,menu *rendelesek,char jeleg,int emelet,int kordinata_szam,asztalkordinata *kordinata)
{
    if (regi==NULL)
    {
        asztal *uj=(asztal*) malloc(sizeof(asztal));
        uj->asztal_szam=asztal_szam;
        uj->folalt=foglat;
        uj->idopont=idopont;
        uj->foglalasido=foglalasido;
        uj->vendegszam=vendegszam;
        uj->rendelesek=rendelesek;
        uj->jeleg=jeleg;
        uj->emelet=emelet;
        uj->kordinata_szam=kordinata_szam;
        uj->kordinata=kordinata;
        uj->kov=NULL;
        return uj;
    }
    regi->kov=asztal_lancolat(regi->kov,asztal_szam,foglat,idopont,foglalasido,vendegszam,rendelesek,jeleg,emelet,kordinata_szam,kordinata);
    return regi;
}
meret *meret_lancolat(meret* lista,int szam,char jeleg,int x, int y)
{
    if (lista==NULL)
    {
        meret *uj = (meret *) malloc(sizeof(meret));
        uj->szam = szam;
        uj->jeleg = jeleg;
        uj->x=x;
        uj->y=y;
        uj->kov = NULL;
        return uj;
    }
    lista->kov = meret_lancolat(lista->kov,szam,jeleg,x,y);
    return lista;
}



void feltoltes_infomenu(asztal* lista, menu *menuk)
{
    asztal *asztal_kov=lista;
    while(asztal_kov!=NULL)
    {
        menu *koz=asztal_kov->rendelesek;
        menu *kinalat=menuk;
        bool talalat=false;
        menu *lemarado=NULL;
        while(koz!=NULL)
        {
            if (koz->sorszam==NULL)
            {
                printf("Nem megfelelo formatum vagy hibas formatum torolve!\n");
                if (lemarado == NULL)
                {
                    menu *ujeleje = koz->kov;
                    free(koz->sorszam);
                    free(koz);
                    lista->rendelesek = ujeleje;
                    koz=lista->rendelesek;
                }
                else
                {
                    lemarado->kov = koz->kov;
                    free(koz->sorszam);
                    free(koz);
                    koz=lemarado->kov;
                }

            }
            else
            {
                lemarado=koz;
                koz=koz->kov;
            }
        }
        lemarado=NULL;
        koz=asztal_kov->rendelesek;

        while (koz!=NULL)
        {
            talalat=false;
            if (koz->nev==NULL)
            {
                kinalat=menuk;
                while (kinalat!=NULL&& talalat==false)
                {
                    if (koz->tipus==kinalat->tipus&&0==strcmp(koz->sorszam,kinalat->sorszam))
                    {
                        koz->nev=kinalat->nev;
                        koz->arra=kinalat->arra;
                        talalat=true;
                    }
                    kinalat=kinalat->kov;
                }
                if (talalat==false)
                {
                    printf("Ez az elem nem szerepel a menuben: %c%s\n",koz->tipus,koz->sorszam);
                    if (lemarado == NULL)
                    {
                        menu *ujeleje = koz->kov;
                        free(koz->sorszam);
                        free(koz);
                        lista->rendelesek = ujeleje;
                        koz=lista->rendelesek;
                    }
                    else
                    {
                        lemarado->kov = koz->kov;
                        free(koz->sorszam);
                        free(koz);
                        koz=lemarado->kov;
                    }
                }
            }
            else
            {
                lemarado=koz;
                koz=koz->kov;

            }
            if (talalat==true)
            {
                lemarado=koz;
                koz=koz->kov;
            }
        }
        asztal_kov=asztal_kov->kov;
    }
}
