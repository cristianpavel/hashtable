STRUCTURI DE DATE - TEMA1
STUDENT - PAVEL CRISTIAN
GRUPA - 314CB



TASK1 - INSERARE IN HASH SI PRINTARE

	Pentru a insera in tabela hash, am facut mai intai o functie de initia-
lizare care aloca memorie pentru o tabela, si atribuie campurile structurii.
De asemenea am facut structura TInfoCelula care pastreaza informatia unei celu-
le din tabela hash. Aici, pe langa campurile date in enunt, am mai pus un camp,
'len' pentru a memora dimensiunea cheii si a-mi usura apelul functiei de hash.
Am construit functia de inserare, care primeste informatia unei celuli si o ta-
bela hash, si aloca memorie pentru o celula cu acea informatie. In functie de
unde introduce noua cheie (pe o pozitie deja existenta sau pe una noua) retur-
neaza codul de iesire. In main, am citit fiecare operatie intr-un for, si daca
primeam operatia de "inserare", alocam memorie pentru o informatie celula pe 
care sa o atribui functiei de inserare deja construite. Am citit in functie de
cheia primita si in functie de tipul valorii date, campurile informatiei celu-
lei. Am facut inserarea si daca am reusit sa inserez pe o pozitie noua, am ma-
rit numarul de elemente din tabela.
	Pentru printare am facut o functie parcurgea tabela si apela functiile 
de afisare din structurile construite.

TASK2 - REDIMENSIONARE SI CAUTARE

	Pentru redimensionare, am realocat vectorul din tabela hash. Dupa care,
am parcurs vectorul pana la jumatatea noului range(range-ul vechi). In acel for
de parcurgere, verificam daca dupa realocare s-a schimbat bucket-ul in care
se afla elementul. Daca se schimba, pun elementul in noul bucket la sfarsit si
il sterg de aici. Daca nu se modifica bucket-ul, trec la urmatorul element.
	Pentru cautare, parcurg bucket-ul (dat de functia haash) in care ar 
trebui sa se afle elementul (daca nu e gol) si il compar cu cele din lista. 
Daca il gasesc,ies din for. Daca am ajuns la elementul NULL din lista inseamna 
ca nu am gasit cheia si printez mesaj corespunzator.

TASK3 - STERGERE

	Pentru stergere, parcurg bucket-ul in care ar trebui sa se afle cheia.
Ma folosesc de un anterior pentru a sterge elementul. Parcurg bucket-ul pana
ajung la final sau dau de element. Daca ajung la final si lista nu e nula sterg
elementul (2 cazuri: daca sterg primul element sau unul din interior). Elibe-
rez memoria si refac legaturile. La sfarsit returnez 0 in caz ca nu am eli-
minat nimic.

BONUS - Distrugere Tabela

	Pentru distrugere tabela am facut o functie care imi elibereaza memoria
alocata pentru o tabela. M-am folosit de functiile de structuri pentru a eli-
bera valorile.


THE END


