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


void leggere_mappa(matrice mappa)
{
	leggere_mappa_file("mappa.txt");
}

void gestire_cella()
{
	int cella_attuale;
	stringa nome_file = "";
	stringa stringa_file = "";

	nome_file = allocare_stringa(nome_file, 0);

	cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));

	if(cella_attuale == CELLA_VUOTA)
	{
		rallentare_output("Non c'e' niente di interessante qui!\n\n", MILLISECONDI);
	}
	else
	{
		if(cella_attuale % STORIA == 0)
		{
			sprintf(nome_file, "storia/[%d][%d].txt", leggere_y(pos), leggere_x(pos));
			stringa_file = leggere_file_testo(nome_file, stringa_file);
			rallentare_output(stringa_file, MILLISECONDI);
			cella_attuale /= STORIA;
		}

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

		if((cella_attuale % PORTA_CHIUSA_SFONDABILE == 0 || cella_attuale % PORTA_SEMPLICE == 0 || cella_attuale % PORTA_RE == 0))
		{
			rallentare_output("\nC'e' una porta chiusa davanti a te!\n", MILLISECONDI);
		}

		if(cella_attuale % BOTOLE == 0)
		{
			rallentare_output("Davanti a te c'e' una botola!\n\n", MILLISECONDI);
		}
	}

	scrivere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos), cella_attuale);

	free(nome_file);
}
