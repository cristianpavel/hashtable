#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabelaHash.h"
/* PAVEL CRISTIAN - 314CB
 * sursa principala in care citesc
 * la inceput sunt functii pentru compararea si afisarea cheii
 */
int comparString(void *a,void *b){
	char *x = (char *)a;
	char *y = (char *)b;
	return strcmp(x,y);

}
int comparNr(void *a,void *b){
	return *(int *)a - *(int *)b;
}
void afisezString(void *a,FILE *f){
	fprintf(f,"%s",(char *)a);
	
}
void afisezNr(void *a,FILE *f){
	fprintf(f,"%d",*(int *)a);

}
int main(){
	FILE *input,*output; //deschid fisierele
	input = fopen("input.in","rt");
	output = fopen("output.out","wt");
	if (!input){
		printf("eroare la deschidere fisier intrare");
		return 0;
	}
	TH *h = NULL; 
	char init[8],tip; //pentru 'inithash' si tipul cheii
	size_t range; //range-ul hash-ului
	
	//citesc prima linie
	fscanf(input,"%s %c %zu",init,&tip,&range);
	
	if (tip == 'd'){ //initializez hash-ul cu cheia corespunzatoare

		h = InitTH(range,hash_f,comparNr,afisezNr,free);
	}else{
		h = InitTH(range,hash_f,comparString,afisezString,free);
	}
	int nrOp, i; 
	float k = 0; //numarul de elemente din hash
	fscanf(input,"%d",&nrOp); //citesc nr de operatii
	for (i = 0; i < nrOp; i++){

		char op[7]; //operatia
		fscanf(input,"%s",op);
		if (strcmp("insert",op) == 0){
			//aloc informatia din celula noua
			TInfoCelula *new = (TInfoCelula *)malloc(
						sizeof(TInfoCelula));
			if (!new){

				printf("eroare la alocare celula informatie\n");
				return -1;
			}
			if (tip == 'd'){ //citesc cheie in functie de tipul ei
				new->cheie =(int *)malloc(sizeof(int));
				if (!new->cheie){
					printf("eroare la alocare cheie celula\n");
					return -1;
				}
				fscanf(input,"%d",(int *)new->cheie); //citesc cheia
				new->len = sizeof(int); //atribui dimensiunea cheii
			}else{

				new->cheie = (char *)malloc(50*sizeof(char));
				if (!new->cheie){
					printf("eroare la alocare cheie celula\n");
					return -1;
				}
				fscanf(input,"%s",(char *)new->cheie); //citesc cheia
				new->len = strlen(new->cheie) + 1; //atribui dimensiunea cheii
					//realoc cat sa ocup doar dimensiunea necesara
				new->cheie = realloc(new->cheie,new->len*sizeof(char));		
				if (!new->cheie){
					printf("eroare la realocare cheie celula\n");
					return -1;
				}
				
			}	
			char tipVal[5];//citesc tipul de valoare
			fscanf(input,"%s",tipVal); 
			if(strcmp("stud",tipVal) == 0){ //citesc valoarea
				TStudent *s = (TStudent *)malloc(
							sizeof(TStudent));
				if (!s){
					printf("eroare la alocare valoare\n");
					return -1;
				}
				s->nume = (char *)malloc(30*
							sizeof(char));
				if (!s->nume){
					printf("eroare la alocare nume student\n");
					return -1;
				}
				fscanf(input,"%s",s->nume);
				fscanf(input,"%f",&s->medie);
				fscanf(input,"%s",s->grupa);
				fscanf(input,"%d",&s->varsta);
				new->val = s; //pun valoarea in info celula
				//atribui functiile necesare
				new->printVal = afiStud;
				new->freeVal = freeStud;
			}else{
				TMaterie *m = (TMaterie *)malloc(
							sizeof(TMaterie));
				if (!m){
					printf("eroare la alocare valoare\n");
					return -1;	
				}
				m->materie = (char *)malloc(30*
							sizeof(char));
				if (!m->materie){
					printf("eroare la alocare materie\n");
					return -1;
				}	
				fscanf(input,"%s",m->materie);
				fscanf(input,"%d",&m->ore_curs);
				fscanf(input,"%d",&m->ore_lab);
				fscanf(input,"%d",&m->credit);
				fscanf(input,"%d",&m->teme);
				new->val = m; //pun valoarea in info celula
				//atribui functiile necesare
				new->printVal = afiMat;
				new->freeVal = freeMat;
			}
			int res = InsTH(h,(void *)new); //inserez informatia in hash
			if (res == 1){ //daca am adaugat pe o pozitie noua
				k++;
				if (k/h->range >= 0.75){ //daca depasesc load factor-ul
					RedimensionareTH(h);
			
				}
			}
		}else if (strcmp("print",op) == 0){
			
			AfiTH(h,output);
		}else if(strcmp("find",op) == 0){
			size_t l; //dimensiunea cheii citite
			void *cheie; //cheia
			if (tip == 'd'){//citesc cheia
				
				cheie = (int *)malloc(sizeof(int));
				if (!cheie){
					printf("eroare la alocare cheie find\n");
					return -1;
				}
				fscanf(input,"%d",(int *)cheie);
				l = sizeof(int);
			}
			else if (tip == 's'){
				cheie = (char *)malloc(50*sizeof(char));
				if (!cheie){
					printf("eroare la alocare cheie find\n");
					return -1;
				}
				fscanf(input,"%s",(char *)cheie);
				l = strlen(cheie) + 1;
				cheie = (char *)realloc(cheie,l*sizeof(char));
			}
			//caut cheia
			findCheie(h,(void *)cheie,l,output);
			//eliberez memoria alocata
			h->freeCheie(cheie);
		}else if(strcmp("delete",op) == 0){
			size_t l; //dimensiunea cheii
			void *cheie; //cheia
			if (tip == 'd'){ //citesc cheia

				cheie = (int *)malloc(sizeof(int));
				if (!cheie){
					printf("eroare la alocare cheie delete\n");
					return -1;
				}
				fscanf(input,"%d",(int *)cheie);
				l = sizeof(int);
			}
			else if (tip == 's'){
				cheie = (char *)malloc(50*sizeof(char));
				if (!cheie){
					printf("eroare la alocare cheie delete\n");
					return -1;
				}
				fscanf(input,"%s",(char *)cheie);
				l = strlen(cheie) + 1;
				cheie = (char *)realloc(cheie,l*sizeof(char));
			} 
			//sterg cheia
			int res = deleteCheie(h,(void *)cheie,l);
			if (res  == 1) k--; //daca am gasit cheia scad numarul de elemente
			h->freeCheie(cheie); //eliberez memoria pentru cheie
		}
	}
	//inchid fisierele si dau distrug tabela hash
	fclose(input);
	fclose(output);
	DistrTH(&h);
	return 0;
}
