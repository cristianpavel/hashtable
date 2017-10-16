#include "tabelaHash.h"
/* PAVEL CRISTIAN - 314CB
 * aici am pus definitiile functiilor pentru structura TStudent
 * freeStud dezaloca spatiul pentru un pointer catre un student
 * afiStud afiseaza un student
 */
void freeStud(void *ae){
	TStudent *s = (TStudent *)ae;
	free(s->nume);
	free(s);
}
void afiStud(void *ae,FILE *f){
	TStudent *s = (TStudent *)ae;
	fprintf(f,"[Nume: %s, Grupa: %s, Medie: %0.2f, Varsta: %d]",
			s->nume,s->grupa,s->medie,s->varsta);


}
