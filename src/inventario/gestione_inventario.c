#include <stdio.h>
#include <stdlib.h>
#include "gestione_inventario.h"
#include "../gestione_file/gestione_file.h"

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
	scrivere_frammento_nord(inv, false);
	scrivere_frammento_sud(inv, false);
	scrivere_frammento_est(inv, false);
	scrivere_frammento_ovest(inv, true);
	scrivere_chiave_re(inv, false);
	scrivere_chiave_semplice(inv, false);
}


void stampare_inventario()
{
	if(leggere_frammento_nord(inv) == true)
	{
		rallentare_output("\nPossiedi il frammento di mappa nord!\n", MILLISECONDI);
	}

	if(leggere_frammento_est(inv) == true)
	{
		rallentare_output("\nPossiedi il frammento di mappa est!\n", MILLISECONDI);
	}

	if(leggere_frammento_sud(inv) == true)
	{
		rallentare_output("\nPossiedi il frammento di mappa sud!\n", MILLISECONDI);
	}

	if(leggere_frammento_ovest(inv) == true)
	{
		rallentare_output("\nPossiedi il frammento di mappa ovest!\n", MILLISECONDI);
	}

	if(leggere_chiave_semplice(inv) == true)
	{
		rallentare_output("\nPossiedi la chiave semplice!\n", MILLISECONDI);
	}

	if(leggere_chiave_re(inv) == true)
	{
		rallentare_output("\nPossiedi la chiave del re!\n", MILLISECONDI);
	}

	rallentare_output("\n", MILLISECONDI);
}

stringa visualizzare_frammenti_mappa(stringa risposta)
{
	stringa frammenti[4];
	stringa frammento_nord = "";
	stringa frammento_est = "";
	stringa frammento_sud = "";
	stringa frammento_ovest = "";

	int i, pos_1, pos_2, j, k;

	if(leggere_frammento_nord(inv) == true)
	{
		frammento_nord = leggere_file_testo("mappa/pezzo_mappa1.txt", frammento_nord);
	}
	else
	{
		frammento_nord = leggere_file_testo("mappa/pezzo_mappa_vuoto_2.txt", frammento_nord);
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
		frammento_ovest = leggere_file_testo("mappa/pezzo_mappa_vuoto_3.txt", frammento_ovest);
	}

	if(leggere_frammento_sud(inv) == true)
	{
		frammento_sud = leggere_file_testo("mappa/pezzo_mappa4.txt", frammento_sud);
	}
	else
	{
		frammento_sud = leggere_file_testo("mappa/pezzo_mappa_vuoto.txt", frammento_sud);
	}

	frammenti[0] = frammento_nord;
	frammenti[1] = frammento_est;
	frammenti[2] = frammento_ovest;
	frammenti[3] = frammento_sud;

	i = 0;
	j = 0;
	k = 0;

	while(j < 2)
	{
		pos_1=0;
		pos_2=0;
		do{
			while(frammenti[k][pos_1] != '\n')
			{
				risposta = scrivere_carattere(risposta, i, frammenti[k][pos_1]);
				pos_1++;
				i++;
			}
			pos_1++;
			k++;

			while(frammenti[k][pos_2] != '\n')
			{
				risposta = scrivere_carattere(risposta, i, frammenti[k][pos_2]);
				pos_2++;
				i++;
			}
			pos_2++;
			risposta = scrivere_carattere(risposta, i, '\n');
			i++;
			k--;

		}while(pos_2 < leggere_lunghezza(frammenti[k+1]));

		k = 2;
		j++;
	}

	return risposta;
}
