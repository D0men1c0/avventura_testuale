#include <stdio.h>
#include <stdlib.h>
#include "vettore.h"

void scrivere_valore(int vettore[], int pos, int valore)
 {
    vettore[pos] = valore;
    return;
 }

int leggere_valore(int vettore[], int pos)
 {
	int valore;
    valore = vettore[pos];
    return valore;
 }

void allocare_vettore(int vettore[], int lunghezza)
{
	int pos;
	pos = 0;
	while(pos<=lunghezza)
	{
		printf("Inserisci un valore intero: ");
		scanf("%d", &vettore[pos]);
		pos++;
	}
    return;
}
