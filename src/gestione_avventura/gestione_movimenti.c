#include <stdio.h>
#include "../utility/array/matrice.h"
#include "../utility/stringa/stringa.h"
#include "gestione_mappa.h"
#include "gestione_movimenti.h"
#include "../gestione_file/file_di_testo/lettura_file_testo.h"
#include "../inventario/gestione_inventario.h"
#include "../personaggio/personaggio.h"

void scrivere_x(posizione *posizione_personaggio, int x)
{
	posizione_personaggio->x = x;
}

void scrivere_y(posizione *posizione_personaggio, int y)
{
	posizione_personaggio->y = y;
}

int leggere_x(posizione posizione_personaggio)
{
	return posizione_personaggio.x;
}

int leggere_y(posizione posizione_personaggio)
{
	return posizione_personaggio.y;
}

void muovere_personaggio(matrice mappa, stringa direzione, posizione *posizione_personaggio, personaggio *info_giocatore, inventario *inventario_giocatore)
{
	leggere_mappa(mappa);
	stringa stringa_file = "";

	if(confrontare_stringhe(direzione, "nord"))
	{
		if(leggere_valore_matrice(mappa, leggere_y(*posizione_personaggio) - 1, leggere_x(*posizione_personaggio)) != 1)
		{
			scrivere_y(posizione_personaggio, leggere_y(*posizione_personaggio) - 1);
			gestire_cella(mappa, *posizione_personaggio, info_giocatore, inventario_giocatore);
		}
		else
		{
			stringa_file = leggere_file_testo("storia/muri/muro1.txt", stringa_file);
			rallentare_output(stringa_file, MILLISECONDI);
		}
	}

	if(confrontare_stringhe(direzione, "sud"))
	{
		if(leggere_valore_matrice(mappa, leggere_y(*posizione_personaggio) + 1, leggere_x(*posizione_personaggio)) != 1)
		{
			scrivere_y(posizione_personaggio, leggere_y(*posizione_personaggio) + 1);
			gestire_cella(mappa, *posizione_personaggio, info_giocatore, inventario_giocatore);
		}
		else
		{
			stringa_file = leggere_file_testo("storia/muri/muro2.txt", stringa_file);
			rallentare_output(stringa_file, MILLISECONDI);
		}
	}

	if(confrontare_stringhe(direzione, "ovest"))
	{
		if(leggere_valore_matrice(mappa, leggere_y(*posizione_personaggio), leggere_x(*posizione_personaggio) - 1) != 1)
		{
			scrivere_x(posizione_personaggio, leggere_x(*posizione_personaggio) - 1);
			gestire_cella(mappa, *posizione_personaggio, info_giocatore, inventario_giocatore);
		}
		else
		{
			stringa_file = leggere_file_testo("storia/muri/muro3.txt", stringa_file);
			rallentare_output(stringa_file, MILLISECONDI);
		}
	}

	if(confrontare_stringhe(direzione, "est"))
	{
		if(leggere_valore_matrice(mappa, leggere_y(*posizione_personaggio), leggere_x(*posizione_personaggio) + 1) != 1)
		{
			scrivere_x(posizione_personaggio, leggere_x(*posizione_personaggio) + 1);
			gestire_cella(mappa, *posizione_personaggio, info_giocatore, inventario_giocatore);
		}
		else
		{
			stringa_file = leggere_file_testo("storia/muri/muro4.txt", stringa_file);
			rallentare_output(stringa_file, MILLISECONDI);
		}
	}
}
