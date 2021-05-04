typedef struct{
int righe;
int colonne;
int* *valori;
} matrice;

int leggere_colonna(matrice matrice_a);
int leggere_riga(matrice matrice_a);
int leggere_valore(matrice matrice_a,int riga,int colonna);
void scrivere_colonna(matrice *matrice_a,int num_colonne);
void scrivere_riga(matrice *matrice_a,int num_righe);
void scrivere_valore(matrice *matrice_a,int riga,int colonna,int valore);
void stampare_matrice(matrice matrice_a);
void allocare_matrice(matrice *matrice_a);
