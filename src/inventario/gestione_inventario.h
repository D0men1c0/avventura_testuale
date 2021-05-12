#ifndef GESTIONE_INVENTARIO_H
#define GESTIONE_INVENTARIO_H
#include "../utility/utility.h"

typedef struct
{
	bool frammento_mappa_est;
	bool frammento_mappa_ovest;
	bool frammento_mappa_nord;
	bool frammento_mappa_sud;
	bool chiave_semplice;
	bool chiave_del_re;
}
inventario;
//prototipi lettura
bool leggere_frammento_est(inventario mappa_est);
bool leggere_frammento_ovest(inventario mappa_ovest);
bool leggere_frammento_nord(inventario mappa_nord);
bool leggere_frammento_sud(inventario mappa_sud);
bool leggere_chiave_semplice(inventario chiave_semplice);
bool leggere_chiave_re(inventario chiave_re);
//prototipi scrittura
void scrivere_frammento_est(inventario *mappa_est, bool valore);
void scrivere_frammento_ovest(inventario *mappa_ovest, bool valore);
void scrivere_frammento_nord(inventario *mappa_nord, bool valore);
void scrivere_frammento_sud(inventario *mappa_sud, bool valore);
void scrivere_chiave_semplice(inventario *chiave_semplice, bool valore);
void scrivere_chiave_re(inventario *chiave_re, bool valore);




#endif
