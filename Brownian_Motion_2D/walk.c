/* per l'output */
#include <stdio.h>
/* per la randomizzazione */
#include <stdlib.h>
#include <time.h>
/* qua sono definite le macro N e K  */
#include "walk.h"

/*=== modificare solo da qua in poi =============== */

/** \file walk.c
       \author Gianfranco Cordella
     Si dichiara che il contenuto di questo file e' in ogni sua parte opera
     originale dell'autore. */

#define false 0
#define true 1

int main()
{
int i,l,k,n,j,j1,j2,j3,j4,numero,M,Bool;
float freq1,freq2,freq3,freq4;
char mat[N][N];

i=0;
j=0;
l=0;
j1=0;
j2=0;
j3=0;
j4=0;
numero=0;
/* generatore del seme dei numeri casuali*/
srand(time(NULL));

/*calcolo delle frequenze degli spostamenti */
for(i=0 ; i<K; i++)
{	numero= (rand() %4) +1;
	switch(numero){
		case 1:	j1++; break;		/* spostamento verso l'alto   */
		case 2:	j2++; break;		/* spostamento verso il basso */
		case 3:  j3++; break;		/* spostamento verso sinistra */
		case 4:  j4++; break;}		/* spostamento verso destra   */
}
		
freq1=(float)j1 /K;
freq2=(float)j2 /K;
freq3=(float)j3 /K;
freq4=(float)j4 /K;

printf("N %2.2f\n", 100*freq1);	
printf("S %2.2f\n", 100*freq2);	
printf("E %2.2f\n", 100*freq3);	
printf("O %2.2f\n", 100*freq4);	

/*assegnamento matrice vuota*/
for(i=0; i<N;i++)
	for(j=0;j<N;j++)
		mat[i][j] = ' ';
		
		
/*avvio simulazione e stampa su standard output*/
M=(N + N%2)/2;
k=M;
n=M;

for(l=0; l<=K; l++)     
{
	/*  griglia con particella al centro */
	if(l==0)                       
	{	for(j=0; j<=N+1;j++)
			printf("=");
		printf("\n");
		mat[M][M] ='*';
		
		for(i=0; i<N ;i++){
			printf("|");	
			for(j=0; j<N; j++)
				printf("%c",mat[i][j]); 
			printf("|\n");} 
		
		for(j=0; j<=N+1 ;j++)
			printf("=");
		printf("\n");
	}		
	
	/* passi successivi della simulazione */
	else                          
	{	numero= (rand() %4) +1; ;
		Bool=false;
		if(k+1== N || n+1==N || k==0 || n==0)
		{	while(!Bool)
			{	if( (k+1==N) && (n+1==N) && (numero ==2 || numero ==4))
					{	numero= (rand() %4) +1;
						if (numero ==2 || numero ==4)
							Bool=false;
						else
							Bool=true;
					}
				
				else if((k==0) && (n+1==N) && (numero ==1 || numero ==4)) 
					{	numero = (rand() %4) +1;
						if (numero ==1 || numero ==4)
							Bool=false;
						else
							Bool=true;
					}
				
				else if((k==0) && (n==0) && (numero ==1 || numero ==3)) 
					{	numero = (rand() %4) +1;
						if ((numero ==1) || (numero ==3))
							Bool=false;
						else
							Bool=true;
					}
				
				else if((k+1==N) && (n==0) && (numero ==2 || numero ==3)) 
					{	numero= (rand() %4) +1;
						if ((numero ==2) || (numero ==3))
							Bool=false;
						else
							Bool=true;
					}
		
				else if( (k+1==N) &&(n!=0) && (n!=N-1) && (numero ==2))                              
					{	numero = (rand() %4) +1;
						if (numero ==2)
							Bool=false;
						else
							Bool=true;
					}
					
				else if((n+1==N ) &&(k!=0) &&(k!= N-1) && (numero ==4))
					{	numero= (rand() %4) +1;
						if (numero==4)
							Bool=false;
						else
							Bool=true;
					}
				
				else if( (k==0) &&(n!=0) &&(n!=N-1) && (numero ==1))                              
					{	numero= (rand() %4) +1;
						if (numero==1)
							Bool=false;
						else
							Bool=true;
					}
					
				else if( (n==0) &&(k!=0) &&(k!=N-1) && (numero ==3))                              
					{	numero= (rand() %4) +1;
						if (numero==3)
							Bool=false;
						else
							Bool=true;
					}
					
				else
					Bool=true;			
			}		
		}
		switch(numero){
			case 1:	mat[k-1][n]='*'; mat[k][n]='+'; k--; break;
			case 3:  mat[k][n-1]='*'; mat[k][n]='+'; n--; break;
			case 2:	mat[k+1][n]='*'; mat[k][n]='+'; k++; break;
			case 4:  mat[k][n+1]='*'; mat[k][n]='+'; n++; break;}
		
		/*stampa griglia*/
		for(j=0; j<=N+1;j++)
			printf("=");
		printf("\n");
		
		for(i=0; i<N ;i++){
			printf("|");	
			for(j=0; j<N; j++)
				printf("%c",mat[i][j]); 
			printf("|\n");} 
		
		for(j=0; j<=N+1 ;j++)
			printf("=");
		printf("\n");
	}
	
}

return 0;}	 
