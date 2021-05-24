/**
 * Questo modulo gestisce i movimenti del personaggio. Attraverso una struttura che salva la posizione, le funzioni presenti in
 * questo modulo permettono, oltre alla modifica dei dati che compongono la struttura, di trovare le direzioni percorribili dal
 * giocatore in quella cella e il movimento vero e proprio del personaggio nella mappa.
*/

#include "../utility/utility.h"
#include "../inventario/gestione_inventario.h"
#include "../personaggio/gestione_personaggio.h"
#include "gestione_avventura.h"

#ifndef GESTIONE_MOVIMENTI_H_
#define GESTIONE_MOVIMENTI_H_

typedef struct
{
	int x;														//Valore della posizione nelle ascisse.
	int y;														//Valore della posizione nelle ordinate.
}posizione;

void scrivere_x(posizione *posizione_personaggio, int x);		//Funzione per la modifica della x nella struttura della posizione.
void scrivere_y(posizione *posizione_personaggio, int y);		//Funzione per la modifica della y nella struttura della posizione.
int leggere_x(posizione posizione_personaggio);					//Funzione per la lettura della x nella struttura della posizione.
int leggere_y(posizione posizione_personaggio);					//Funzione per la lettura della y nella struttura della posizione.
stringa trovare_direzioni_disponibili();						//Funzione per la ricerca delle direzioni disponibili al giocatore.
void muovere_personaggio(stringa direzione);					//Funzione per lo spostamento del personaggio.

#endif
