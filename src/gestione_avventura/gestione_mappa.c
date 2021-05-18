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
	stringa stringa_file = "";

	nome_file = allocare_stringa(nome_file, 0);

	cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));

	if(cella_attuale == 0)
	{
		rallentare_output("Non c'e' nulla di interessante qui...\n\n", MILLISECONDI);
	}
	else
	{
		if(cella_attuale % STORIA == 0)
		{
			sprintf(nome_file, "storia/[%d][%d].txt", leggere_y(pos), leggere_x(pos));
			stringa_file = leggere_file_testo(nome_file, stringa_file);
			rallentare_output(stringa_file, MILLISECONDI);
		}

		if(cella_attuale % PORTA_CHIUSA_SFONDABILE == 0)
		{

		}


		if(cella_attuale % SALA_TRONO == 0)
		{
			//messaggio entrata sala trono
		}

		if(cella_attuale % CHIAVE_SEMPLICE == 0)
		{

		}

		if(cella_attuale % CHIAVE_PORTA_RE == 0)
		{

		}

		if(cella_attuale % POWER_UP == 0)
		{

		}

		if(cella_attuale % MALUS == 0)
		{
			scrivere_vita(&giocatore, leggere_vita(giocatore) - 1);
		}

		if(cella_attuale % BOTOLE == 0)
		{

		}

		if(cella_attuale % PEZZO_MAPPA_OVEST == 0)
		{
			//if comando prendere pezzo
			scrivere_frammento_ovest(&inv, true);
		}

		if(cella_attuale % PEZZO_MAPPA_EST == 0)
		{
			//if comando prendere pezzo
			scrivere_frammento_est(&inv, true);
		}

		if(cella_attuale % PEZZO_MAPPA_NORD == 0)
		{
			//if comando prendere pezzo
			scrivere_frammento_nord(&inv, true);
		}

		if(cella_attuale % PEZZO_MAPPA_SUD == 0)
		{
			//if comando prendere pezzo
			scrivere_frammento_sud(&inv, true);
		}
	}

	free(nome_file);
}
