#include "tabelaHash.h"
/* PAVEL CRISTIAN - 314CB
 * aici am pus definitiile functiilor pentru materie
 * freeMat dezaloca spatiul pentru un pointer catre o structura TMaterie
 * afiMat afiseaza o materie 
 */
void freeMat(void *ae){

	TMaterie *m = (TMaterie *)ae;
	free(m->materie);
	free(m);

}
void afiMat(void *ae,FILE* f){
	TMaterie *m = (TMaterie *)ae;
	fprintf(f,"[Materie: %s, Ore_curs: %d, Ore_lab: %d, Credit: %d, Teme: %d]",
			m->materie,m->ore_curs,m->ore_lab,m->credit,m->teme);
}
