#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_
/* PAVEL CRISTIAN - 314CB */
typedef struct celulag
{
  void *info;
  struct celulag *urm;
} TCelulaG, *TLG, **ALG;
TLG AlocaCelula(void *ae); //functie ce aloca celula si returneaza adresa ei
void NodSf(ALG,TLG); //functie ce adauga un nod la sfarsitul unei liste 
#endif
