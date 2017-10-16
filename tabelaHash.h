#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "materie.h"
#include "student.h"
#include <string.h>
/* PAVEL CRISTIAN - 314CB */
#ifndef _HASH_TABLE_
#define _HASH_TABLE_
typedef unsigned int(*TFHash)(const void*,size_t,size_t); //functie de hash
typedef int (*TFCmp)(void *,void *); //functie de comparare
typedef void (*TFAfi)(void *,FILE *); //functie de afisare
typedef void (*TFEli)(void *); //functie de eliberare memorie
typedef struct{
	void *val; //pointer catre un element de tip student sau materie
	void *cheie; //pointer catre cheia elementului
	size_t len; //dimensiunea cheii utila la functia hash
	TFAfi printVal; //functie de printare a valorii
	TFEli freeVal; //functie de eliberare a valorii
}TInfoCelula; //structura informatie celula
typedef struct{
	size_t range; //dimensiunea hash-ului
	TFHash fh; //functia hash
	TLG *v; //vectorul de liste
	TFCmp cmp; //compara chei
	TFAfi printCheie; //afiseaza cheie
	TFEli freeCheie; //elibereaza cheie
}TH;	//structura de hash
TH *InitTH(size_t,TFHash,TFCmp,TFAfi,TFEli); //functie de initializare hash
void AfiTH(TH *h,FILE*); //afisare hash
void DistrugeTH(TH **h); //distrugere hash
int InsTH(TH *h,void *ae); //inserare in hash a unui element
unsigned int hash_f(const void*,size_t,size_t); //functia particulara hash
void RedimensionareTH(TH *); //functie redimensionare
void findCheie(TH *h,void *,size_t,FILE*); // functie gaseste cheie
int deleteCheie(TH *h,void *,size_t); //functie sterge element de la cheie 
void DistrTH(TH **h); //functie distruge TH
#endif
	
