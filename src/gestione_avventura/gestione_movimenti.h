#include "../utility/array/matrice.h"
#include "../utility/stringa/stringa.h"
#include "../inventario/gestione_inventario.h"
#include "../personaggio/personaggio.h"

#ifndef GESTIONE_MOVIMENTI_H_
#define GESTIONE_MOVIMENTI_H_

typedef struct
{
	int x;
	int y;
}posizione;


void scrivere_x(posizione *personaggio, int x);
void scrivere_y(posizione *personaggio, int y);
int leggere_x(posizione personaggio);
int leggere_y(posizione personaggio);
void muovere_personaggio(matrice mappa, stringa direzione, posizione *posizione_personaggio, personaggio *info_giocatore, inventario *inventario_giocatore);

#endif
