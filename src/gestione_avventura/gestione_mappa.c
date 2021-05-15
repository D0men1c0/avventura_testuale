#include <stdio.h>
#include <stdlib.h>
#include "../utility/array/matrice.h"
#include "../utility/stringa/stringa.h"
#include "../gestione_file/file_di_testo/lettura_file_testo.h"
#include "gestione_mappa.h"
#include "gestione_movimenti.h"
#include "../personaggio/personaggio.h"
#include "../inventario/gestione_inventario.h"

void leggere_mappa(matrice mappa)
{
	int i, j, k, l;
	stringa valori_mappa = "";
	stringa valore = "";

	valore = allocare_stringa(valore, 0);

	//scrivere_colonna_matrice(mappa, COLONNE);
	//scrivere_riga_matrice(mappa, RIGHE);

	valori_mappa = leggere_file_testo("mappa.txt", valori_mappa);

	i = 0;
	k = 0;
	while(i < RIGHE)
	{
		j = 0;
		while(j < COLONNE)
		{
			l = 0;
			while((valori_mappa[k] >= '0' && valori_mappa[k] <= '9'))
			{
				valore[l] = valori_mappa[k];
				k++;
				l++;
			}
			if((valori_mappa[k] == ' ' || valori_mappa[k] == '\n'))
				k++;
			valore[l] = '\0';
			scrivere_valore_matrice(mappa, i, j, convertire_intero(valore));
			j++;
		}
		i++;
	}

	free(valore);
	free(valori_mappa);
}

void gestire_cella(matrice mappa, posizione posizione_personaggio, personaggio *info_giocatore, inventario *inventario_giocatore)
{
	int cella_attuale;
	stringa nome_file = "";
	stringa stringa_file = "";

	nome_file = allocare_stringa(nome_file, 0);

	cella_attuale = leggere_valore_matrice(mappa, leggere_y(posizione_personaggio), leggere_x(posizione_personaggio));

	if(cella_attuale == 0)
	{
		rallentare_output("Non c'e' nulla di interessante qui...\n\n", MILLISECONDI);
	}
	else
	{
		if(cella_attuale % STORIA == 0)
		{
			sprintf(nome_file, "storia/[%d][%d].txt", leggere_y(posizione_personaggio), leggere_x(posizione_personaggio));
			stringa_file = leggere_file_testo(nome_file, stringa_file);
			rallentare_output(stringa_file, MILLISECONDI);
		}

		if(cella_attuale % PORTA_LIBERA == 0)
		{
			//print messaggio porta libera
		}

		if(cella_attuale % PORTA_CHIUSA_SFONDABILE == 0)
		{

		}

		if(cella_attuale % PORTA_SEMPLICE == 0)
		{

		}

		if(cella_attuale % PORTA_RE == 0)
		{

		}

		if(cella_attuale % SALA_TRONO == 0)
		{

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

		}

		if(cella_attuale % BOTOLA == 0)
		{

		}

		if(cella_attuale % PEZZO_MAPPA_OVEST == 0)
		{

		}

		if(cella_attuale % PEZZO_MAPPA_EST == 0)
		{

		}

		if(cella_attuale % PEZZO_MAPPA_NORD == 0)
		{

		}

		if(cella_attuale % PEZZO_MAPPA_SUD == 0)
		{

		}
	}

	free(nome_file);
}
