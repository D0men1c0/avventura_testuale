#include "../utility/utility.h"
#include "../inventario/gestione_inventario.h"
#include "../personaggio/personaggio.h"
#include "gestione_avventura.h"

#ifndef GESTIONE_MOVIMENTI_H_
#define GESTIONE_MOVIMENTI_H_

typedef struct
{
	int x;
	int y;
}posizione;

void scrivere_x(posizione *posizione_personaggio, int x);
void scrivere_y(posizione *posizione_personaggio, int y);
int leggere_x(posizione posizione_personaggio);
int leggere_y(posizione posizione_personaggio);
stringa trovare_direzioni_disponibili();
void muovere_personaggio(stringa direzione);

#endif
