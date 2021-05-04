#ifndef MATRICE_H
#define MATRICE_H

typedef struct{
	int righe;
	int colonne;
	int* *valori;
} matrice;

int leggere_colonna_matrice(matrice matrice_a);
int leggere_riga_matrice(matrice matrice_a);
int leggere_valore_matrice(matrice matrice_a,int riga,int colonna);
void scrivere_colonna_matrice(matrice *matrice_a,int num_colonne);
void scrivere_riga_matrice(matrice *matrice_a,int num_righe);
void scrivere_valore_matrice(matrice *matrice_a,int riga,int colonna,int valore);
void stampare_matrice(matrice matrice_a);
void allocare_matrice(matrice *matrice_a);

#endif
