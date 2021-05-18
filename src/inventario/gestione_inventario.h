#include "../utility/utility.h"
#include "../gestione_avventura/gestione_avventura.h"

#ifndef GESTIONE_INVENTARIO_H
#define GESTIONE_INVENTARIO_H

typedef struct
{
	bool frammento_mappa_est;
	bool frammento_mappa_ovest;
	bool frammento_mappa_nord;
	bool frammento_mappa_sud;
	bool chiave_semplice;
	bool chiave_re;
}inventario;



//prototipi lettura
bool leggere_frammento_est(inventario inv);
bool leggere_frammento_ovest(inventario inv);
bool leggere_frammento_nord(inventario inv);
bool leggere_frammento_sud(inventario inv);
bool leggere_chiave_semplice(inventario inv);
bool leggere_chiave_re(inventario inv);

//prototipi scrittura
void scrivere_frammento_est(inventario *inv, bool valore);
void scrivere_frammento_ovest(inventario *inv, bool valore);
void scrivere_frammento_nord(inventario *inv, bool valore);
void scrivere_frammento_sud(inventario *inv, bool valore);
void scrivere_chiave_semplice(inventario *inv, bool valore);
void scrivere_chiave_re(inventario *inv, bool valore);

//inizializzazione inventario
void inizializza_inventario(inventario *inv);

//visualizzazione inventario e mappa
void visualizzare_inventario();
stringa visualizzare_frammenti_mappa(stringa risposta);

#endif
