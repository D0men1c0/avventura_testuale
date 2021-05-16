#include <stdio.h>
#include <stdlib.h>
#include "gestione_inventario.h"
#include "../gestione_file/file_di_testo/lettura_file_testo.h"


stringa concatenare_frammenti_file(stringa * frammenti, int indice, stringa risposta);


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
	stringa frammenti[4];

	int i;

	if(leggere_frammento_nord(inv) == true)
	{
		frammenti[0] = leggere_file_testo("mappa/pezzo_mappa1.txt", frammenti[0]);
	}
	else
	{
		frammenti[0] = leggere_file_testo("mappa/pezzo_mappa_vuoto_2.txt", frammenti[0]);
	}

	if(leggere_frammento_est(inv) == true)
	{
		frammenti[1] = leggere_file_testo("mappa/pezzo_mappa2.txt", frammenti[1]);
	}
	else
	{
		frammenti[1] = leggere_file_testo("mappa/pezzo_mappa_vuoto.txt", frammenti[1]);
	}

	if(leggere_frammento_ovest(inv) == true)
	{
		frammenti[2] = leggere_file_testo("mappa/pezzo_mappa3.txt", frammenti[2]);
	}
	else
	{
		frammenti[2] = leggere_file_testo("mappa/pezzo_mappa_vuoto_3.txt", frammenti[2]);
	}

	if(leggere_frammento_sud(inv) == true)
	{
		frammenti[3] = leggere_file_testo("mappa/pezzo_mappa4.txt", frammenti[3]);
	}
	else
	{
		frammenti[3] = leggere_file_testo("mappa/pezzo_mappa_vuoto.txt", frammenti[3]);
	}


	i = 0;

	while(i < 4)
	{
		risposta = concatenare_frammenti_file(frammenti,  i, risposta);

		i += 2;
	}

	return risposta;
}

stringa concatenare_frammenti_file(stringa * frammenti, int indice, stringa risposta)
{
	int pos, pos_precedente;
	int i, j;
	int temp;

	pos = 0;
	pos_precedente = 0;
	i = leggere_lunghezza(risposta);

	do
	{
		j = indice + 2;

		while(indice < j)
		{
			while(frammenti[indice][pos] != '\n')
			{
				risposta = scrivere_carattere(risposta, i, frammenti[indice][pos]);
				pos++;
				i++;
			}

			pos++;
			indice++;

			temp = pos;
			pos = pos_precedente;
			pos_precedente = temp;
		}

		risposta = scrivere_carattere(risposta, i, '\n');
		i++;
		indice -= 2;
	}while(pos_precedente < leggere_lunghezza(frammenti[indice+1]));

	return risposta;
}



