/**
  \file
  \author inf 2015/16 assign 2
  \brief prototipi funzioni
 */

#ifndef __PERCOLATION_H
#define __PERCOLATION_H

/** crea una nuova matrice di double vuota (FORNITA DAI DOCENTI)
    \param n numero di righe
    \param m numero di colonne
    
    \retval p puntatore alla matrice allocata
    \retval NULL se si è verificato un errore 
    (setta errno con un codice di errore opportuno)

*/
double** new_matrix(unsigned n, unsigned m);

/** stampa la matrice sul file f in formato testuale con i valori della permeabilita' oppure **** per le posizioni già infiltrate e ++++ per quelle appena infiltrate (FORNITA DAI DOCENTI)
    (NOTARE: il file f deve essere stato già aperto )
    \param f putatore al file in cui scrivere la matrice
    \param a puntatore alla matrice
    \param n numero di righe
    \param m numero di colonne
*/
void print_matrix (FILE * f, double ** a, unsigned n, unsigned m);

/*** FUNZIONI DA REALIZZARE ***/
/**
   Libera la memoria occupata dalla matrice bidimensionale ponendo a NULL il
   puntatore alla matrice stessa nell'ambiente del chiamante
   \param pm puntatore alla variable che contiene il puntatore alla matrice
   \param n numero di righe della matrice
 */
void free_matrix (double *** pm, unsigned n);



/** stampa la matrice sul file f in ASCII art secondo un formato deciso dallo studente (NOTARE: il file deve essere stato già aperto )
    \param f putatore al file in cui scrivere la matrice
    \param a puntatore alla matrice
    \param n numero di righe
    \param m numero di colonne
*/
void prettyprint_matrix (FILE * f, double ** a, unsigned n, unsigned m);

/** carica i valori della matrice da file.
    I valori sono memorizzati su linee di
    al massimo 200 caratteri. I valori vengono letti in sequenza e devono essere memorizzati nella matrice.
   Ad esempio, per una matrice 3 X 3 devono essere letti 9 valori che possono essere memorizzati nel file su linee diverse (al max 200 caratteri) :

    3.2 4.5 6.7
    5.1 0.0 6.7 8.9
    2.1 4.5
    ....

    
    \param f file da cui legge i valori
    \param a puntatore alla matrice in cui caricare i valori
    \param n numero di righe
    \param m numero di colonne

    \retval 0 se tutto e' andato bene
    \retval -1 se non ci sono abbastanza valori o si sono verificati errori 
              (setta errno in modo opportuno: si puo' scegliere di settare errno con il valore piu' appropriato consultando man errno o mantenere il settaggio di errno dell'ultima chiamata a fscanf fallita. )
              Attenzione: in questo caso la matrice di partenza non viene modificata

*/
int load_matrix (FILE * f, double ** a, unsigned n, unsigned m);

/** inizializza in maniera casuale la matrice prendendo come parametro l'intervallo di permeabilità [a,b] (a deve essere maggiore di 0 e
 strettamente minora di b) 
   \param mat puntatore alla matrice
   \param n numero di righe
   \param m numero di colonne
   \param a estremo inferiore intervallo
   \param b estremo superiore intervallo

   \retval 0 se tutto è andato bene
   \retval -1 se si è verificato un errore (es b > a, b < 0, a < 0) setta errno 
              con un codice di errore opportuno

*/
int init_percolation (double ** mat, unsigned n, unsigned m, double a, double b);
  
/** setta il primo step (inserisce -2 in corrispondenza del centro della matrice) (n/2,m/2) parte intera inferiore
    \param mat puntatore alla matrice
    \param n numero di righe
    \param m numero di colonne
   
    \retval 0 se tutto è andato bene
    \retval -1 se si è verificato un errore (es n <= 0 ) setta errno 
              con un codice di errore opportuno


 */
int first_step (double ** mat, unsigned n, unsigned m);

/** fa evolvere la simulazione di uno step, ovvero mette a -2 il prossimo elemento invaso scegliendolo come l'elemento con il più piccolo valore di permeabilità sulla frontiera (insieme degli elementi adiacenti a quelli gi\`a con valore -1)
L'ambiente e' toroidale, ovvero l'ultima colonna e' adiacente alla prima e l'ultima riga e' adiacente alla prima.
    \param mat puntatore alla matrice
    \param n numero di righe
    \param m numero di colonne
    \param a estremo inf intervallo permeabilità
    \param b estremo sup intervallo permeabilità
   
    \retval 0 se tutto è andato bene
    \retval -1 se si è verificato un errore (es n <= 0 ) setta errno 
              con un codice di errore opportuno
 */
int step (double ** mat, unsigned n, unsigned m, double a, double b);
#endif
