/**
  header file terzo assegnamento
*/

#ifndef __RAGGI_H
#define __RAGGI_H
#include <stdio.h>
/* 
{ 
} 
*/

/** velocità della luce (m/s)*/
#define  V  299792458.
/** costante di conversione radianti --> gradi */
#define RAD2DEG 57.29577951308232

/**
   Valori booleani */
typedef enum { FALSE=0, TRUE=1  } bool_t;

/** tipi di ordinamento: 
   NOTORD = nessun ordinamento. 
   TIME = ordinata per tempi crescenti.
   POSITION = ordinata per posizione crescente
*/ 
typedef enum { NOTORD=0, TIME=1, POSITION=2  } ord_t;

/** flag che indica se la rilevazione contiene rumore (NOISE) o no (OK) */
typedef enum { OK=0, NOISE=2  } flag_t;

/** struttura che realizza l'elemento della lista di registrazioni */
typedef struct elem {
  /** posizione registrazione*/
  double position;
  /** tempo registrazione */
  double time;
  /** flag rumore/buono */
  flag_t flag;
  /** puntatore al prossimo elemento */
  struct elem * next;
} elem_t;

/** struttura della lista delle registrazioni */
typedef struct {
  /** puntatore alla testa della lista */
  elem_t * head;
  /** numero di elementi presenti in lista */
  int nelem; 
  /** indica se è ordinata e se l'ordinamento e' rispetto al tempo o alla posizione  */
  ord_t ord; 
} lista_t;
  
/** 
  stampa la lista (FORNITA DAI DOCENTI)

  \param l putatore alla lista da stampare
  \param f puntatore al file su cui scrivere

*/
void stampa_lista (FILE * f, lista_t * l);

/** 
  crea una nuova lista (vuota e non ordinata) (FORNITA DAI DOCENTI)


  \retval NULL se si e' verificato un errore
  \retval p puntatore alla lista appena allocata

*/
lista_t * new_lista ( void ) ;



/**
  legge da file una nuova registrazione (notare il formato analizzando il file dati, ogni registrazione è terminata da '\n')
  se il formato è corretto e la conversione è possibile alloca una struttura di tipo elem_t 
  inizializzando i campi con i valori cotenuti nella riga (nota: il campo next va inizializzato a NULL) 
  se il formato della riga non e' corretto, si è raggiunto EOF o si è verificato un errore lo segnala ritornando NULL
  
  \param fd descrittore del file 

  \retval p puntatore alla struttura allocata (!= NULL) se tutto è andato bene
  \retval NULL se si è verificato un errore

*/
elem_t* leggi_registrazione (FILE* fd);
/**
   inserisce nella lista
   -- se la lista non e' ordinata inserisce in testa alla lista
   -- se la lista e' ordinata per posizione (crescente) e se la lista e' ordinata per tempo (crescente) inserisce mantenendo la lista ordinata

   \param pelem puntatore all'elemento da inserire

   \retval -1 se si e' verificato un errore nell'allocazione del nuovo elemento
   \retval 0 altrimenti
 */
int inserisci ( lista_t * l , elem_t* pelem);


/**
  mette a false il campo ord per indicare che la lista non e' piu' ordinata
  \param l lista

 */
void set_nonordinata (lista_t * l);

 /**
  se la lista non e' ordinata rispetto al tempo setta a TIME il campo ord 
  ed ordina la lista, altrimenti non fa niente
  \param l lista

 */
void set_ordinata_time (lista_t * l);

 /**
  se la lista non e' ordinata rispetto alla posizione setta a POSITION
  il campo ord  ed ordina la lista, altrimenti non fa niente
  \param l lista

 */
void set_ordinata_position (lista_t * l);

 /**
  dealloca tutti gli elementi della lista, la struttura lista e annulla il puntatore alla lista stessa 

  \param pl puntatore al putatore della lista da deallocare

 */
void free_lista (lista_t ** pl);

/**
  calcola \theta invertendo la formula
  
  t_i - t_j = (x_i - x_j)/2 sin(\theta)

  \param pi  putatore all'elemento relativo alla rilevazione  i 
  \param pj  puntatore all'elemento relativo alla rilevazione j
  \item pth  puntatore alla variabile che conterra' il valore di theta (non viene modificata se si verifica un errore ) in GRADI

  \retval 0 se il valore di theta e' calcolabile (se l'arcsin e' definito)
  \retval -1 altrimenti

 */
int compute_theta (elem_t* pi, elem_t* pj, double* pth);

/**
   calcola la media dei valori in un file
  
  \param f file in cui leggere i valori (non viene modificato)
  \param pm puntatore alla variabile che conterrà la media


  \retval 0 se tutto è andato bene
  \retval -1 se si è verificato un errore

*/
int media (FILE * f, double* pm);

/**
   calcola la deviazione standard dei valori in un file
  
  \param f file in cui leggere i valori (non viene modificato)
  \param ps puntatore alla variabile che conterrà la varianza
  \param m media


  \retval 0 se tutto è andato bene
  \retval -1 se si è verificato un errore

*/
int deviazione (FILE * f, double* ps, double m);

#endif
  

