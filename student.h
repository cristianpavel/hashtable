#ifndef _STUDENT_H_
#define _STUDENT_H_
/* PAVEL CRISTIAN - 314CB */
typedef struct
{
	char *nume;
	float medie;
	char grupa[6]; // 324CB + NULL
	int varsta;
} TStudent;
void freeStud(void *ae); //functie de afisare student
void afiStud(void *ae,FILE*);	//functie de printare student
#endif
