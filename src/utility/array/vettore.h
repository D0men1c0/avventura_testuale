#ifndef VETTORE_H
#define VETTORE_H

#define DIM_VETTORE 50

typedef struct{
	int * numeri;
	int dimensione;
}vettore;

vettore scrivere_valore_vettore(vettore vet, int pos, int valore);
int leggere_valore_vettore(vettore vet, int pos);
int leggere_dimensione_vettore(vettore vet);
vettore scrivere_dimensione_vettore(vettore vet, int dim);
vettore allocare_vettore(vettore vet, int lunghezza);

#endif
