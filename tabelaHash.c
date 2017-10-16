#include "tabelaHash.h"
/* PAVEL CRISTIAN - 314CB
 * functiile de prelucrare tabela hash
 * IniTH initializeaza o tabela hash cu valori primite ca argumente
 * AfiTH afiseaza o tabela hash intr-un fisier de iesire deschis prealabil
 * InsTH insereaza intr-o tabela o informatie de tip void* si returneaza un cod de iesire
 * Redimensionare dubleaza capacitatea tabelei si reintroduce valorile
 * findCheie gaseste o cheie in tabela
 * deleteCheie sterge un element cu o anumita cheie
 * DistrTH elibereaza memoria alocata tabelei
 */
TH *InitTH(size_t range,TFHash f,TFCmp fc,TFAfi fa,TFEli fe){
	/* range - dimensiune hash
	 * f - functie hash
	 * fc - compara 2 chei
	 * fa - afiseaza cheie
	 * fe - elibereaza cheie
	 */
	TH *h = (TH *)malloc(sizeof(TH));
	if(!h){
		printf("eroare alocare hash\n");
		return NULL;
	}
	h->v = (TLG *)calloc(range,sizeof(TLG));
	if(!(h->v)){
		printf("eroare alocare vectori de liste din hash\n");
		free(h);
		return NULL;
	}
	h->range = range;
	h->fh = f;
	h->cmp = fc;
	h->printCheie = fa;
	h->freeCheie = fe;
	return h;

}
void AfiTH(TH *h,FILE *f){
	/* h -tabela hash
	 * f - fisier iesire
	 */
	TLG *p = h->v;
	for (; p < h->v + h->range; p++){
		fprintf(f,"[%d] :",p-h->v); //printez bucket-ul la care ma aflu
		if (*p){
			//daca nu am lista goala
			TLG el = *p;  //parcurg lista
			for (;el != NULL; el = el->urm){
				TInfoCelula *a = (TInfoCelula *)el->info; //folosesc functiile de afisare	
				fprintf(f," (");
				h->printCheie(a->cheie,f);
				fprintf(f," -> ");
				a->printVal(a->val,f);
				fprintf(f,")");
			}
		}
		fprintf(f,"\n");
	} 

}
int InsTH(TH *h,void *ae){
	/* h - tabela hash
	 * ae - informatie celula
	 */
	TInfoCelula *a = (TInfoCelula *)ae;
	int bucket = h->fh(a->cheie,a->len,h->range); //gasesc bucket-ul corespunzator
	if (bucket < 0){
		printf("eroare la atribuire cheie in hash\n");
		return 0;
	}
	TLG p = h->v[bucket]; // folosesc o lista ca sa parcurg bucket-ul
	TLG ant = NULL; //anterior ca sa adaug la sfarsitul listei
	TLG aux = AlocaCelula(ae); //aloc celula cu informatia de la adresa ae
	for(;p!= NULL;ant = p,p = p->urm){ 	//parcurg lista
		TInfoCelula *info_p = (TInfoCelula *)p->info;
		if(h->cmp(info_p->cheie,a->cheie) == 0)
			break; 	//daca gasesc elementul ies din lista

	}
	if (h->v[bucket] == NULL){ //daca nu aveam niciun element in lista pun informatia la inceput
		h->v[bucket] = aux;
		return 1;
	}
	if (p != NULL){ //daca am mai gasit un element cu acea cheie
		aux->urm = p->urm; 
		if (ant != NULL){
			ant->urm = aux;
		}else{
			h->v[bucket] = aux;	
		}
			//dau free la informatia inlocuita
		TInfoCelula *pInfo = (TInfoCelula *)p->info;
		pInfo->freeVal(pInfo->val);
		h->freeCheie(pInfo->cheie);
		free(pInfo);
		free(p);
		return 2;
		
	}
	ant->urm = aux; //daca inca nu am iesit din functie, pun elementul la sfarsit
	return 1;
}
void RedimensionareTH(TH *h){
	h->range = h->range*2; 
	h->v =(TLG *)realloc(h->v,h->range*sizeof(TLG));
	if (!h->v){
		printf("eroare la realocare hash\n");
		return;
	}
	TLG *p,el,aux; //liste folosite pentru parcurgere si readaugare hash
	for (p = h->v; p < h->v + h->range/2; p++){
		TLG ant = NULL; //anterior pentru eliminare
		for (el = *p; el != NULL;){

			aux = el; //pointez catre el
			TInfoCelula *a = (TInfoCelula *)aux->info;
			int bucket = h->fh(a->cheie,a->len,h->range);
			if (bucket != p-h->v){ //daca dupa redim schimb bucket-ul
				if (ant == NULL) //la inceputul listei
					h->v[p-h->v] = el->urm;
				else //il elimin
					ant->urm = el->urm;	
				el = el->urm; //trec la urm element
				aux->urm = NULL; //scot aux din lista
				NodSf(h->v + bucket, aux); //adaug aux in noua lista din hash
			}else{ //daca ramane in acelasi bucket, continui parcurgerea
				ant = el; 
				el = el->urm;
			}
			
		}

	}

}
void findCheie(TH *h,void *d,size_t len,FILE *f){
	/* h - tabela hash
	 * d - cheia
	 * len - dimensiunea cheii
	 * f - fisierul de iesire
  	 */
	int bucket = h->fh(d,len,h->range);
	if (bucket < 0){
		printf("eroare la gasire bucket in hash cu find\n");
		return;
	}
	TLG p = h->v[bucket]; //parcurg lista
	for (;p != NULL; p = p->urm){
		TInfoCelula *pInfo = (TInfoCelula *)p->info;
		if (h->cmp(pInfo->cheie,d) == 0){
			//daca am gasit elementul il printez	
			pInfo->printVal(pInfo->val,f);
			fprintf(f,"\n");
			break;
		}
	}
	if (p == NULL) //daca nu am iesit din for elementul nu exista
		fprintf(f,"Nu exista\n");

}
int deleteCheie(TH *h,void *d,size_t len){
	/* h - tabela hash
	 * d - cheie
	 * len - dimensiune cheie
	 */
	int bucket = h->fh(d,len,h->range);
	if (bucket < 0) {
		printf("eroare la gasire bucket in hash din delete\n");
		return 0;
	}
	TLG p = h->v[bucket],ant = NULL;
	for (;p != NULL;ant = p, p = p->urm){
		TInfoCelula *pInfo = (TInfoCelula *)p->info;
		if (h->cmp(pInfo->cheie,d) == 0)
			break;
		
	} //am parcurs lista pana am gasit elementul sau pana la sfarsitul ei
	if (h->v[bucket] != NULL){ //daca lista nu e nula

		if (ant == NULL){ //daca m-am oprit dupa primul element
				//dau free si elimin
			TInfoCelula *pInfo = (TInfoCelula *)(h->v[bucket])->info;
			pInfo->freeVal(pInfo->val);
			h->freeCheie(pInfo->cheie);
			free(pInfo);
			free(h->v[bucket]);
			h->v[bucket] = p->urm; 
			return 1;
		}else if (p != NULL){ //daca am gasit element
				//dau free si elimin
			ant->urm = p->urm;
			TInfoCelula *pInfo = (TInfoCelula *)p->info;	
			pInfo->freeVal(pInfo->val);
			h->freeCheie(pInfo->cheie);
			free(pInfo);
			free(p);
			return 1;

		}
	}
	return 0;
}
void DistrTH(TH **h){
		//parcurg hash-ul si dau free element cu element
	TLG *p = (*h)->v;
	for(;p < (*h)->v + (*h)->range; p++){
	
		if(*p){

			TLG el = *p;
			for (;el != NULL;){
				TLG aux = el;
				TInfoCelula *elInfo = (TInfoCelula *)aux->info;
				el = el->urm;
				elInfo->freeVal(elInfo->val);
				(*h)->freeCheie(elInfo->cheie);
				free(elInfo);
				free(aux);
			}
		}
		*p = NULL;	
	}
	free((*h)->v);
	free(*h);
	*h = NULL;

}
