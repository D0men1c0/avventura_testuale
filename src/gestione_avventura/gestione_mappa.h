#include "../utility/array/matrice.h"
#include "gestione_movimenti.h"
#include "../personaggio/personaggio.h"
#include "../inventario/gestione_inventario.h"
#include "gestione_avventura.h"

#ifndef GESTIONE_MAPPA_H_
#define GESTIONE_MAPPA_H_

#define CELLA_VUOTA 0
#define MURO 1
#define STORIA 2
#define PORTA_LIBERA 3
#define PORTA_CHIUSA_SFONDABILE 5
#define PORTA_SEMPLICE 7
#define PORTA_RE 11
#define SALA_TRONO 13
#define CHIAVE_SEMPLICE 17
#define CHIAVE_PORTA_RE 19
#define POWER_UP 23
#define MALUS 29
#define BOTOLE 31
#define PEZZO_MAPPA_OVEST 37
#define PEZZO_MAPPA_EST 41
#define PEZZO_MAPPA_NORD 43
#define PEZZO_MAPPA_SUD 47

#define RIGHE 10
#define COLONNE 14


void leggere_mappa(matrice mappa);
void gestire_cella();

#endif

