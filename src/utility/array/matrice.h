#ifndef MATRICE_H
#define MATRICE_H

#define RIGHE 10
#define COLONNE 14

/*typedef struct{
	const int righe = RIGHE;
	const int colonne = COLONNE;
	int valori[RIGHE][COLONNE];
} matrice;*/

typedef int matrice[RIGHE][COLONNE];

/*int leggere_colonna_matrice(matrice matrice_a);
int leggere_riga_matrice(matrice matrice_a);*/
int leggere_valore_matrice(matrice matrice_a, int riga, int colonna);
//void scrivere_colonna_matrice(matrice *matrice_a,int num_colonne);
//void scrivere_riga_matrice(matrice *matrice_a,int num_righe);
void scrivere_valore_matrice(matrice matrice_a, int riga, int colonna, int valore);
void stampare_matrice(matrice matrice_a);
//void allocare_matrice(matrice *matrice_a);

#endif
