/** \file pippo.c
       \author Gianfranco Cordella
     Si dichiara che il contenuto di questo file e' in ogni sua parte opera
     originale delgli autori.  */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include "percolation.h"

/*free_matrix*/
/*procedura per deallocare una matrice in allocazione dinamica*/
void free_matrix (double *** pm, unsigned n){
int i;
for (i=0; i <n; i++)
	free((*pm)[i]);
free(*pm);
*pm= NULL;
}


/*prettyprint_matrix*/
/* procedura per stampare una matrice su file in ASCII art. E' stata utilizzata una cornice simile ad uno smile. Tale procedura scorre tutta la matrice usando due cicli for. Tutti i numeri sono stamati con due cifre decimali.A seconda della quantità di cifre intere di ogni numero è stata scelta una particolare formattazione di stampa, come è evidente dalle istruzioni if.  */ 
void prettyprint_matrix (FILE * f, double ** a, unsigned n, unsigned m){
int i,j;
                 
for(j=0; j< m ;j++)
	fprintf(f,"◕ ‿ ◕   ");
fprintf(f,"\n");

for(i=0; i<n ;i++){
	fprintf(f,"/ ");	
	for(j=0; j<m; j++){
		if (a[i][j] == -2)
			fprintf(f,"(o.~)   ");
		else if (a[i][j] == -1)
			fprintf(f,"(X_X)   ");
		else if (a[i][j] <10)
			fprintf(f,"%1.2f    ",a[i][j]); 
		else if (a[i][j] <100)
			fprintf(f,"%1.2f   ",a[i][j]); 
		else if  (a[i][j] <1000)
			fprintf(f,"%1.2f  " ,a[i][j]); 
		else
			fprintf(f,"%1.2f ",a[i][j]); 
		}
	fprintf(f,"|\n");
	}
	 
for(j=0; j< m;j++)
	fprintf(f,"◕ ‿ ◕   ");
fprintf(f,"\n");
}	



/*load_matrix*/
/* Il ciclo while serve per contare quanti double ci sono nel file da cui si vuole caricare la matrice. La variabile di controllo del ciclo è feof(f) che permette di capire quando si è arrivati alla fine del file. Tramite un contatore ci si accorge se nel file ci sono tanti dati quanti nè sono richiesti per riempire la matrice. Ciò è stato possibile valutando l'espressione di ( fscanf() != 0 ). Se il valore del contatore è minore del numero di dati necessari per riempire la matrice allora viene restituito un errore; altrimenti la matrice viene riempita usando due cicli for. Restituisce l'errore EIO cioè (input/output error) nel caso in cui il numero di colonne o righe della matrice sia non positivo. Restituisce l'errore EPERM ( Operation not permitted ) nel caso in cui il numero di dati contenuti nel file sia inferiore a quello necessario per riempire la matrice. */
int load_matrix (FILE * f, double ** a, unsigned n, unsigned m){
int i,j,cont1=0,cont2=0;
double x;

if (n<=0 || m<=0){
	errno = EIO;
	return -1;
}

while (!feof(f)) {
	if ( fscanf(f, "%lf", &x) != 0 )
		cont1++;
}

if (cont1!= n*m +1){
	errno = EPERM;
	return -1;
}
else {
	rewind(f);								/*serve per tornare in testa al file in modo da leggerlo interamente e riempire poi la matrice. */
	for(i=0; i <n; i++)
		for(j=0; j <m; j++)
			fscanf(f,"%lf", &a[i][j]) ;
}

return 0;}




/* init_percolation*/
/* Lo scopo è riempire una matrice con numeri reali casuali in un intervallo scelto. Per fare ciò si sono creati numeri casuali reali tra 0 e 1, dividendo il valore di rand() per il massimo numero casuale calcolabile ( cioè RAND_MAX) . Poi tali numeri sono stati trasformati in numeri casuali nell'intervallo (a,b).
La matrice è stata riempita usando due cicli for. Viene restituito l'errore EIO cioè (input/output error) nel caso in cui il numero di colonne o righe della matrice sia non positivo , oppure nel caso gli estremi dell'intervallo assumano valori non permessi.*/
int init_percolation (double ** mat, unsigned n, unsigned m, double a, double b){
int i,j;
srand(time(NULL));

if (b<a || b<=0 || a<=0 || n<=0 || m<=0 ){
	errno = EIO;
	return -1;
	}
	
for(i=0; i <n; i++)
	for(j=0; j <m; j++)
		mat[i][j] = (rand() / (double)RAND_MAX)*(b - a) + a;

return 0;
}




/* first_step */
/* Questa funzione calcola le coordinate del centro della matrice così come indicato in percolation.h  ed effettua il primo passo della simulazione assegnando -2 alla casella centrale della matrice. Restituisce l'errore EIO cioè (input/output error) nel caso in cui il numero di colonne o righe della matrice sia non positivo. */
int first_step (double ** mat, unsigned n, unsigned m){
int N,M;

N= (n - n%2)/2 ;
M= (m - m%2)/2 ;

if ( n<=0 || m<=0){
	errno = EIO;
	return -1;
	}

mat[N][M] = -2;

return 0;
}





/* step */
/*Questa funzione serve per eseguire i passi successivi della simulazione. Attraverso due cicli for, vengono trovati tutti gli elementi della matrice che hanno valore -1 o -2 . Successivamente con altri due cicli for (per ogni valore -1 o -2 prima trovato) vengono letti tutti e 9 i valori adiacenti per trovare il minimo. La variabile min è stata dichiarata fuori dai quattro cicli for, in modo tale che potesse esserne cambiato il valore, dai quattro cicli, ogni volta si trovi un valore che è minore del minimo precedentemente trovato. Inoltre vengono anche assegnate le coordinate di tale minimo alle variabili h e t , in modo tale che una volta trovato il minimo si possa assegnare a tale casella della matrice il valore -2.
Restituisce l'errore EIO cioè (input/output error) nel caso in cui il numero di colonne o righe della matrice sia non positivo , oppure nel caso gli estremi dell'intervallo assumano valori non permessi.*/
int step (double ** mat, unsigned n, unsigned m, double a, double b){
int i,j,k,l,h,t,i1,j1;
double min;

if ( n<=0 || m<=0 ||b<a || b<=0 || a<=0){
	errno = EIO;
	return -1;
	}
min=b;
for (i=0; i<n; i++)
	for (j=0; j<m; j++){
		if (mat[i][j]== -2){
			mat[i][j]=-1;
			for(k=i-1; k<i+2; k++){
				for(l=j-1; l<j+2; l++){
					i1=k;
					j1=l;
					if (k==-1)
						i1=n-1;
					else if(k==n)
						i1=0;
					if (l==-1)
						j1= m-1;
					else if (l== m)
						j1=0;
					if( (mat[i1][j1] < min) &&( mat[i1][j1] !=-1) ){
						min = mat[i1][j1]	;
						h=i1;
						t=j1;
					}
				}
			}
		}
		else if (mat[i][j]== -1){
			for(k=i-1; k<i+2; k++){
				for(l=j-1; l<j+2; l++){
					i1=k;
					j1=l;
					if (k==-1)
						i1=n-1;
					else if(k==n)
						i1=0;
					if (l==-1)
						j1= m-1;
					else if (l== m)
						j1=0;
					if( (mat[i1][j1] < min) &&( mat[i1][j1] !=-1) &&( mat[i1][j1] !=-2) ){
						min = mat[i1][j1]	;
						h=i1;
						t=j1;
					}
				}
			}
		}
	}

mat[h][t] = -2;
return 0;
}
