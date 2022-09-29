#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include "raggi.h"
#define N 2048
/** \file raggi.c
       \author Gianfranco Cordella
     Si dichiara che il contenuto di questo file e' in ogni sua parte opera
     originale delgli autori.  */
 
     
/*leggi_registrazione*/
/*Utilizzando la stringa buf si è analizzata la riga del file che si vuole acquisire e nel caso tale linea non termini con '\n' si restituisce NULL;  altrimenti si dichiara una variabile di tipo elem_t* (e si alloca sullo heap uno spazio di memoria puntato da tale variabile) e si procede acquisendo i tre valori presenti nella riga del file. */ 
elem_t* leggi_registrazione (FILE* fd){
char buf[N+2];
bool_t Bool=FALSE;
int i=0,a;

if ( fgets(buf,N+2,fd) == NULL ){
	return NULL;}

while (!Bool)
	if (buf[i]!= '\0')
		i++;
	else
		Bool = TRUE;
		
if (buf[i-1] != '\n')
	return NULL;
	
elem_t* ele;
if ( ( ele = malloc(sizeof(elem_t)) ) == NULL )
	return NULL;
fseek(fd, -i, SEEK_CUR);
fscanf(fd,"%lf", &(ele->position));
fscanf(fd,"%lf", &(ele->time));
fscanf(fd,"%d", &a);
fseek(fd, 1, SEEK_CUR);
if (a==0)
	ele->flag = OK;
else if (a==2)
	ele->flag = NOISE;

ele->next =NULL;
return ele;}


/*inserisci*/
/*Se la lista non è ordinata si inseriscono man mano i nuovi elementi in testa. Se la lista è ordinata per tempo o posizione  , si scorre la stessa attraverso un puntatore ausiliario fino a che non si verifica una delle seguenti condizioni:
1) Il valore dell'elemento da inserire è minore di quello della testa della lista  allora l'elemento è aggiunto in testa;
2) Il valore dell'elemento da inserire  è maggiore di ogni elemento della lista allora l'elemento è aggiunto in coda;
3) Il valore dell'elemento da inserire è compreso fra i valori di due elementi della lista , allora l'elemento è inserito fra tali elementi della lista.   */
int inserisci ( lista_t * l , elem_t* pelem){
if (l== NULL)
	return -1;
	
if ( l->ord == NOTORD ){
	pelem->next = l->head;
	l->head= pelem;
	return 0;
	}

else if ( l->ord == TIME ){
	elem_t* aux;
	elem_t* aux1;
	/*elem_t* aus;
	if ( ( aus = malloc(sizeof(elem_t)) ) == NULL )
		return -1;*/
		
	if (l->head == NULL){
		l->head= pelem;
		return 0;
		}
		
	aux= l->head;
	if (aux->time < pelem->time){
		while (aux!=NULL && (aux->time)<(pelem->time) ){
			aux1=aux;
			aux= aux->next;}
			
		if (aux== NULL){
			/*aus=pelem;
			aux1->next = aus;*/
			aux1->next = pelem;
			return 0;}
		else{
			pelem->next = aux;
			aux1->next = pelem;
			return 0;}
		}
	else{
		pelem->next = l->head;
		l->head=pelem;
		return 0;}
}


else if ( l->ord == POSITION ){
	elem_t* aux;
	elem_t* aux1;
	/*elem_t* aus;
	if ( ( aus = malloc(sizeof(elem_t)) ) == NULL )
		return -1;*/
		
	if (l->head == NULL){
		/*if ( ( l->head = malloc(sizeof(elem_t)) ) == NULL )
			return -1;*/
		l->head= pelem;
		return 0;
		}
		
	aux= l->head;
	if (aux->position < pelem->position){
		while (aux!=NULL && (aux->position)<(pelem->position) ){
			aux1=aux;
			aux= aux->next;}
		if (aux== NULL){
/*			aus=pelem;*/
			aux1->next = pelem;
			return 0;}
		else{
			pelem->next = aux;
			aux1->next = pelem;
			return 0;}
		}
	else{
		pelem->next = l->head;
		l->head=pelem;
		return 0;}
}
return 0;
}

/*set_nonordinata*/
void set_nonordinata (lista_t * l){
if (l==NULL){
	errno=EINVAL;
	return;}
l->ord = NOTORD;
}


/*set_ordinata_time*/
/*Si parte trovando l'elemento della lista con il minimo valore di tempo e lo si sposta in testa alla lista. Dopo si passa ad analizzare la lista ottenuta togliendo la testa della prima lista. Si trova nuovamente il minimo di questa seconda lista e lo si sposta in testa. L'algoritmo procede riducendo sempre di più la lista e trovando man mano il minimo in tale lista e spostandolo in testa. La procedura termina quando la testa della lista coincide con NULL. A questo punto il campo ord della lista viene posto uguale a TIME e la procedura è terminata. */
void set_ordinata_time (lista_t * l){
double min,temp,temp1;
elem_t* aux;
elem_t* aux1;
flag_t temp2;

if (l==NULL){
	errno=EINVAL;
	return;}
	
if (l->head == NULL){
	l->ord = TIME;
	return;	}
	
if (l->ord == TIME)
		return;
		
aux = l->head;
aux1 = l->head;
min = l->head->time;

do{
	if ((aux->time) < min){
		min = aux->time;
		temp= l->head->time;
		temp1=l->head->position;
		temp2 = l->head->flag;
		l->head->time = aux->time;
		l->head->position= aux->position;
		l->head->flag =aux->flag;
		aux->time =temp;
		aux->position =temp1;
		aux->flag =temp2;
		}
	aux= aux->next;
	}while (aux !=NULL);

l->head = l->head->next;
set_ordinata_time (l);
l->head = aux1;
}	

/*set_ordinata_position*/
/*Si parte trovando l'elemento della lista con il minimo valore di posizione e lo si sposta in testa alla lista. Dopo si passa ad analizzare la lista ottenuta togliendo la testa della prima lista. Si trova nuovamente il minimo di questa seconda lista e lo si sposta in testa. L'algoritmo procede riducendo sempre di più la lista e trovando man mano il minimo in tale lista e spostandolo in testa. La procedura termina quando la testa della lista coincide con NULL. A questo punto il campo ord della lista viene posto uguale a POSITION e la procedura è terminata. */
void set_ordinata_position (lista_t * l){
double min,temp,temp1;
elem_t* aux;
elem_t* aux1;
flag_t temp2;

if (l==NULL){
	errno=EINVAL;
	return;}
	
if (l->head == NULL){
	l->ord = POSITION;
	return;
	}
	
if (l->ord == POSITION)
		return;
		
aux = l->head;
aux1 = l->head;
min = l->head->position;

do{
	if ((aux->position) < min){
		min = aux->position;
		temp= l->head->position;
		temp1=l->head->time;
		temp2 = l->head->flag;
		l->head->position = aux->position;
		l->head->time= aux->time;
		l->head->flag =aux->flag;
		aux->position =temp;
		aux->time =temp1;
		aux->flag =temp2;
		}
	aux= aux->next;
	}while (aux !=NULL);

l->head = l->head->next;
set_ordinata_position (l);
l->head = aux1;
}	


/*free_lista*/
/*Tale procedura serve per deallocare una lista. Attraverso un medoto ricorsivo si scorre la lista e si libera lo spazio di memoria associato all'elemento in testa. La procedura termina quando il puntatore alla testa è NULL e si mette a Null anche il puntatore alla lista stessa.     */
void free_lista (lista_t ** pl){
if ((*pl)==NULL)
	return;
if( ((*pl)->head) !=NULL ){
	elem_t* aux;
	aux= (*pl)->head->next;
	free( (*pl)->head);
	(*pl)->head = aux;
	free_lista (pl);
	}
(*pl)=NULL;
}

/*compute_theta*/
/*La funzione restituisce il valore dell'angolo in gradi e setta errno=EDOM nel caso in cui l'argomento dell'arcoseno risulta essere fuori dall'intervallo di definizione della funzione stessa. */
int compute_theta (elem_t* pi, elem_t* pj, double* pth){
double x,teta;

x= (V*(pi->time - pj->time))/(pi->position - pj->position);

if (x>1 || x<-1){
	errno=EDOM;
	return -1;}
else
	teta = asin(x);

*pth = teta*RAD2DEG;
return 0;
}

/*media*/
/*Calcola la media di alcuni dati acquisiti da file , utilizzando un ciclo while con variabile di controllo feof(f) che restituisce vero quando si arriva a fine file. Viene incrementato anche un contatore per conoscere il numero di dati contenuti nel file*/
int media (FILE * f, double* pm){
double teta;
int i=0;
*pm =0;
while (!feof(f)){
	fscanf(f, "%lf", &teta);
	*pm =*pm + teta;
	i++;;}
	
if (i==0)
	return -1;
	
(*pm) = (*pm)/(i-1) ;
return 0;
}

/*deviazione*/
/*Calcola la deviazione standard di alcuni dati acquisiti da file , utilizzando un ciclo while con variabile di controllo feof(f) che restituisce vero quando si arriva a fine file. Viene incrementato anche un contatore per conoscere il numero di dati contenuti nel file*/
int deviazione (FILE * f, double* ps, double m){
double teta;
int i=0;
*ps=0;
while (!feof(f)){
	fscanf(f,"%lf",&teta);
	*ps= *ps + (teta-m)*(teta-m);
	i++;}
	
if (i==0)
	return -1;
			
*ps = (*ps)/(i-1);
*ps = sqrt(*ps);
return 0;
}

