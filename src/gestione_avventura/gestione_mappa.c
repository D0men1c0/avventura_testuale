#include <stdio.h>
#include <stdlib.h>
#include "../utility/array/matrice.h"
#include "../utility/stringa/stringa.h"
#include "../gestione_file/file_di_testo/lettura_file_testo.h"
#include "gestione_avventura.h"
#include "gestione_mappa.h"
#include "gestione_movimenti.h"
#include "../personaggio/personaggio.h"
#include "../inventario/gestione_inventario.h"
#include "../utility/bool.h"

void leggere_mappa(matrice mappa)
{
	leggere_mappa_file("mappa.txt");
}

void gestire_cella()
{
	int cella_attuale;
	stringa nome_file = "";

	nome_file = allocare_stringa(nome_file, 0);

	cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));


	if(cella_attuale % POWER_UP_VITA == 0)
	{
		scrivere_vita(&giocatore, leggere_vita(giocatore) + 1);
		cella_attuale /= POWER_UP_VITA;
	}

	if(cella_attuale % POWER_UP_FORZA == 0)
	{
		scrivere_forza(&giocatore, leggere_forza(giocatore) + 1);
		cella_attuale /= POWER_UP_FORZA;
	}

	if(cella_attuale % MALUS == 0)
	{
		scrivere_vita(&giocatore, leggere_vita(giocatore) - 1);
		cella_attuale /= MALUS;
	}

	free(nome_file);
}
