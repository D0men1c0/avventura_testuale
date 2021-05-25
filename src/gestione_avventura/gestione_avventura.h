#ifndef GESTIONE_AVVENTURA_H
#define GESTIONE_AVVENTURA_H

#include "gestione_mappa.h"
#include "../inventario/gestione_inventario.h"
#include "../personaggio/gestione_personaggio.h"

void gestire_avventura();
void impostare_avventura();

matrice mappa;
posizione pos;
posizione posizione_precedente;
inventario inv;
personaggio giocatore;

#endif
