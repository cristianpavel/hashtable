#include "tabelaHash.h"
/* PAVEL CRISTIAN - 314CB 
 * definitii ale functiilor pentru liste generale
 * AlocaCelula aloca o celula TCelulaG si returneaza adresa ei
 * NodSf pune o nod TLG l la sfarsitul unei liste ALG al
 */	
TLG AlocaCelula(void *ae){

	TLG aux = (TLG)malloc(sizeof(TCelulaG));
	if(!aux){
		printf("eroare la alocare nod lista\n");
		return NULL;
	}
	aux->info = ae;
	aux->urm = NULL;
	return aux;
}
void NodSf(ALG aL,TLG l){
        TLG p = *aL;
        if (p == NULL)
                *aL = l;
        else{
        
                while (p->urm != NULL)
                        p = p->urm;
                p->urm = l;

        }
}

