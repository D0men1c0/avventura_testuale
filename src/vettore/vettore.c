#include <stdio.h>
#include <stdlib.h>
#include "vettore.h"

void scrivere_valori(int vettore[], int pos, int valore)
 {
    vettore[pos] = valore;
    return;
 }

int leggere_valori(int vettore[], int pos)
 {
	int valore;
    valore = vettore[pos];
    return valore;
 }

void allocare_vettore(int vettore[], int lunghezza)
{
	vettore = (int *)malloc(sizeof(int) * DIM_VETTORE);

	int pos;
	pos = 0;
	while(pos<=lunghezza)
	{
		printf("Inserisci un valore intero: ");
		scanf("%d", &vettore[pos]);
		pos++;
	}
}
