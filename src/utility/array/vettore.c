#include <stdio.h>
#include <stdlib.h>
#include "vettore.h"

vettore scrivere_valore_vettore(vettore vet, int pos, int valore)
{
    vet.numeri[pos] = valore;								//inserimento del valore nel "vettore" in una posizione arbitraria

    return vet;
}

int leggere_valore_vettore(vettore vet, int pos)
{
    int valore;
    valore = vet.numeri[pos];								//salvataggio del valore all'interno del "vettore" nella posizione richiesta
    return valore;
}

vettore allocare_vettore(vettore vet, int lunghezza)
{
	vet.numeri = malloc(sizeof(int) * DIM_VETTORE);			//allocazione dinamica del "vettore" attraverso la funzione "malloc"
    return vet;
}

int leggere_dimensione_vettore(vettore vet)
{
	int dimensione;
	dimensione = vet.dimensione;							//salvataggio della dimensione del "vettore"

	return dimensione;
}

vettore scrivere_dimensione_vettore(vettore vet, int dim)
{
	vet.dimensione = dim;									//assegnazione di una dimensione al "vettore"

	return vet;
}
