#include <stdio.h>
#include <stdlib.h>
#include "gestione_inventario.h"

bool leggere_frammento_est(inventario mappa_est)
{
	return mappa_est.frammento_mappa_est;
}

bool leggere_frammento_ovest(inventario mappa_ovest)
{
	return mappa_ovest.frammento_mappa_ovest;
}

bool leggere_frammento_nord(inventario mappa_nord)
{
	return mappa_nord.frammento_mappa_nord;
}

bool leggere_frammento_sud(inventario mappa_sud)
{
	return mappa_sud.frammento_mappa_sud;
}

bool leggere_chiave_semplice(inventario chiave_semplice)
{
	return chiave_semplice.chiave_semplice;
}

bool leggere_chiave_re(inventario chiave_re)
{
	return chiave_re.chiave_del_re;
}

void scrivere_frammento_est(inventario *mappa_est, bool valore)
{
	mappa_est->frammento_mappa_est = valore;
}

void scrivere_frammento_ovest(inventario *mappa_ovest, bool valore)
{
	mappa_ovest->frammento_mappa_ovest = valore;
}

void scrivere_frammento_nord(inventario *mappa_nord, bool valore)
{
	mappa_nord->frammento_mappa_nord = valore;
}

void scrivere_frammento_sud(inventario *mappa_sud, bool valore)
{
	mappa_sud->frammento_mappa_sud = valore;
}

void scrivere_chiave_semplice(inventario *chiave_semplice, bool valore)
{
	chiave_semplice->chiave_semplice = valore;
}

void scrivere_chiave_re(inventario *chiave_re, bool valore)
{
	chiave_re->chiave_del_re = valore;
}

