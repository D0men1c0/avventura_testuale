#include <stdio.h>
#include <stdlib.h>
#include "vettore.h"

vettore scrivere_valore_vettore(vettore vet, int pos, int valore)
{
    vet.numeri[pos] = valore;

    return vet;
}

int leggere_valore_vettore(vettore vet, int pos)
{
    int valore;
    valore = vet.numeri[pos];
    return valore;
}

vettore allocare_vettore(vettore vet, int lunghezza)
{
	vet.numeri = malloc(sizeof(int) * DIM_VETTORE);
    return vet;
}

int leggere_dimensione_vettore(vettore vet)
{
	int dimensione;
	dimensione = vet.dimensione;

	return dimensione;
}

vettore scrivere_dimensione_vettore(vettore vet, int dim)
{
	vet.dimensione = dim;

	return vet;
}
