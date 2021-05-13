#include <stdio.h>
#include <stdlib.h>
#include "gestione_inventario.h"
#include "../gestione_file/file_di_testo/lettura_file_testo.h"

bool leggere_frammento_est(inventario inv)
{
	return inv.frammento_mappa_est;
}

bool leggere_frammento_ovest(inventario inv)
{
	return inv.frammento_mappa_ovest;
}

bool leggere_frammento_nord(inventario inv)
{
	return inv.frammento_mappa_nord;
}

bool leggere_frammento_sud(inventario inv)
{
	return inv.frammento_mappa_sud;
}

bool leggere_chiave_semplice(inventario inv)
{
	return inv.chiave_semplice;
}

bool leggere_chiave_re(inventario inv)
{
	return inv.chiave_re;
}

void scrivere_frammento_est(inventario *inv, bool valore)
{
	inv->frammento_mappa_est = valore;
}

void scrivere_frammento_ovest(inventario *inv, bool valore)
{
	inv->frammento_mappa_ovest = valore;
}

void scrivere_frammento_nord(inventario *inv, bool valore)
{
	inv->frammento_mappa_nord = valore;
}

void scrivere_frammento_sud(inventario *inv, bool valore)
{
	inv->frammento_mappa_sud = valore;
}

void scrivere_chiave_semplice(inventario *inv, bool valore)
{
	inv->chiave_semplice = valore;
}

void scrivere_chiave_re(inventario *inv, bool valore)
{
	inv->chiave_re = valore;
}


void inizializza_inventario(inventario *inv)
{
	scrivere_frammento_nord(inv, true);
	scrivere_frammento_sud(inv, true);
	scrivere_frammento_est(inv, true);
	scrivere_frammento_ovest(inv, true);
	scrivere_chiave_re(inv, false);
	scrivere_chiave_semplice(inv, false);
}


stringa visualizzare_inventario(stringa risposta)
{
	if(leggere_frammento_nord(inv) == true)
	{
		risposta = concatenare_stringhe(risposta, "\nPossiedi il frammento di mappa nord!\n");
	}

	if(leggere_frammento_est(inv) == true)
	{
		risposta = concatenare_stringhe(risposta, "\nPossiedi il frammento di mappa est!\n");
	}

	if(leggere_frammento_sud(inv) == true)
	{
		risposta = concatenare_stringhe(risposta, "\nPossiedi il frammento di mappa sud!\n");
	}

	if(leggere_frammento_ovest(inv) == true)
	{
		risposta = concatenare_stringhe(risposta, "\nPossiedi il frammento di mappa ovest!\n");
	}

	if(leggere_chiave_semplice(inv) == true)
	{
		risposta = concatenare_stringhe(risposta, "\nPossiedi la chiave semplice!\n");
	}

	if(leggere_chiave_re(inv) == true)
	{
		risposta = concatenare_stringhe(risposta, "\nPossiedi la chiave del re!\n");
	}

	return risposta;
}

stringa visualizzare_frammenti_mappa(stringa risposta)
{
	stringa frammento_nord = "";
	stringa frammento_est = "";
	stringa frammento_sud = "";
	stringa frammento_ovest = "";
	stringa frammento_corrente = "";

	int i, pos_1, pos_2;

	if(leggere_frammento_nord(inv) == true)
	{
		frammento_nord = leggere_file_testo("mappa/pezzo_mappa1.txt", frammento_nord);
	}
	else
	{
		frammento_nord = leggere_file_testo("mappa/pezzo_mappa_vuoto.txt", frammento_nord);
	}

	if(leggere_frammento_est(inv) == true)
	{
		frammento_est = leggere_file_testo("mappa/pezzo_mappa2.txt", frammento_est);
	}
	else
	{
		frammento_est = leggere_file_testo("mappa/pezzo_mappa_vuoto.txt", frammento_est);
	}

	if(leggere_frammento_ovest(inv) == true)
	{
		frammento_ovest = leggere_file_testo("mappa/pezzo_mappa3.txt", frammento_ovest);
	}
	else
	{
		frammento_ovest = leggere_file_testo("mappa/pezzo_mappa_vuoto.txt", frammento_ovest);
	}

	if(leggere_frammento_sud(inv) == true)
	{
		frammento_sud = leggere_file_testo("mappa/pezzo_mappa4.txt", frammento_sud);
	}
	else
	{
		frammento_sud = leggere_file_testo("mappa/pezzo_mappa_vuoto.txt", frammento_sud);
	}

	i = 0;

	frammento_corrente = allocare_stringa(frammento_corrente, 0);
	pos_1 = 0;
	pos_2 = 0;

	do{
		while(frammento_nord[pos_1] != '\n')
		{
			risposta = scrivere_carattere(risposta, i, frammento_nord[pos_1]);
			pos_1++;
			i++;
		}
		pos_1++;

		while(frammento_est[pos_2] != '\n')
		{
			risposta = scrivere_carattere(risposta, i, frammento_est[pos_2]);
			pos_2++;
			i++;
		}
		pos_2++;
		risposta = scrivere_carattere(risposta, i, '\n');
		i++;

		}while(pos_2 < leggere_lunghezza(frammento_est));

	pos_1=0;
	pos_2=0;

	do{

		while(frammento_ovest[pos_1] != '\n')
		{
			risposta = scrivere_carattere(risposta, i, frammento_ovest[pos_1]);
			pos_1++;
			i++;
		}
			pos_1++;

		while(frammento_sud[pos_2] != '\n')
		{
			risposta = scrivere_carattere(risposta, i, frammento_sud[pos_2]);
			pos_2++;
			i++;
		}
			pos_2++;

		risposta = scrivere_carattere(risposta, i, '\n');
		i++;

	}while(pos_2 < leggere_lunghezza(frammento_sud));


	/*frammento_corrente = frammento_ovest;

	pos = 0;
	while(frammento_corrente[i] != '\n')
	{
		risposta = scrivere_carattere(risposta, i, frammento_corrente[pos]);
		i++;
	}

	frammento_corrente = frammento_sud;

	pos = 0;
	while(frammento_corrente[i] != '\n')
	{
		risposta = scrivere_carattere(risposta, i, frammento_corrente[pos]);
		i++;
	}*/

	return risposta;
}



