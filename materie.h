#ifndef _MATERIE_H_
#define _MATERIE_H_
/* PAVEL CRISTIAN - 314CB */
typedef struct
{
	char *materie;
	int ore_curs;
	int ore_lab;
	int credit;
	int teme;
} TMaterie;
void freeMat(void *);	//functie de afisare materie
void afiMat(void *,FILE*);	//functie de printare materie
#endif
