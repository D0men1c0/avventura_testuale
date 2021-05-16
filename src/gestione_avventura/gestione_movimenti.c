#include <stdio.h>
#include "../utility/array/matrice.h"
#include "../utility/stringa/stringa.h"
#include "gestione_mappa.h"
#include "gestione_movimenti.h"
#include "../gestione_file/file_di_testo/lettura_file_testo.h"
#include "../inventario/gestione_inventario.h"
#include "../personaggio/personaggio.h"

void scrivere_x(posizione * pos, int x)
{
	pos->x = x;
}

void scrivere_y(posizione * pos, int y)
{
	pos->y = y;
}

int leggere_x(posizione pos)
{
	return pos.x;
}

int leggere_y(posizione pos)
{
	return pos.y;
}

void muovere_personaggio(stringa direzione)
{
	stringa stringa_file = "";

	if(confrontare_stringhe(direzione, "nord"))
	{
		if(leggere_valore_matrice(mappa, leggere_y(pos) - 1, leggere_x(pos)) != 1)
		{
			scrivere_y(&pos, leggere_y(pos) - 1);
			gestire_cella(mappa, pos, giocatore, inv);
		}
		else
		{
			stringa_file = leggere_file_testo("storia/muri/muro1.txt", stringa_file);
			rallentare_output(stringa_file, MILLISECONDI);
		}
	}

	if(confrontare_stringhe(direzione, "sud"))
	{
		if(leggere_valore_matrice(mappa, leggere_y(pos) + 1, leggere_x(pos)) != 1)
		{
			scrivere_y(&pos, leggere_y(pos) + 1);
			gestire_cella(mappa, pos, giocatore, inv);
		}
		else
		{
			stringa_file = leggere_file_testo("storia/muri/muro2.txt", stringa_file);
			rallentare_output(stringa_file, MILLISECONDI);
		}
	}

	if(confrontare_stringhe(direzione, "ovest"))
	{
		if(leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos) - 1) != 1)
		{
			scrivere_x(&pos, leggere_x(pos) - 1);
			gestire_cella(mappa, pos, giocatore, inv);
		}
		else
		{
			stringa_file = leggere_file_testo("storia/muri/muro3.txt", stringa_file);
			rallentare_output(stringa_file, MILLISECONDI);
		}
	}

	if(confrontare_stringhe(direzione, "est"))
	{
		if(leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos) + 1) != 1)
		{
			scrivere_x(&pos, leggere_x(pos) + 1);
			gestire_cella(mappa, pos, giocatore, inv);
		}
		else
		{
			stringa_file = leggere_file_testo("storia/muri/muro4.txt", stringa_file);
			rallentare_output(stringa_file, MILLISECONDI);
		}
	}
}
