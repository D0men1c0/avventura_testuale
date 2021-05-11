#include <stdlib.h>
#include <stdio.h>
#include "../utility/utility.h"
#include "comandi.h"
#include "strutture_analizzatore.h"
#include "analizzatore_lessicale.h"
#include "gestione_comandi_globali.h"

int gestire_errore_sintattico();

int controllare_simboli_tabella()
{
	int esito;
	simbolo simb;

	simb = leggere_simbolo_tabella_simboli(0);

	esito = false;

	if(simb == MOV)
	{
		esito = true;

		if(leggere_dimensione_tabella_simboli() > 1)
		{
			esito = gestire_errore_sintattico();
		}
	}
	else if(simb == HLP)
	{
		esito = true;

		if(leggere_dimensione_tabella_simboli() > 1)
		{
			simb = leggere_simbolo_tabella_simboli(1);

			if(simb == PRH)
			{
				esito = true;

				if(leggere_dimensione_tabella_simboli() > 2)
				{
					esito = gestire_errore_sintattico();
				}
			}
			else
			{
				esito = gestire_errore_sintattico();
			}
		}

		if(esito == true)
		{
			esito = gestire_comandi_globali();

			if(esito == false)
			{
				gestire_errore_sintattico();
			}
		}
	}
	else if(simb == VRB)
	{
		esito = false;

		if(leggere_dimensione_tabella_simboli() > 1)
		{
			simb = leggere_simbolo_tabella_simboli(1);

			if(simb == PRL)
			{
				esito = true;

				if(leggere_dimensione_tabella_simboli() > 2)
				{
					simb = leggere_simbolo_tabella_simboli(2);

					if(simb == PRL)
					{
						esito = true;

						if(leggere_dimensione_tabella_simboli() > 3)
						{
							esito = gestire_errore_sintattico();
						}
					}
					else
					{
						esito = gestire_errore_sintattico();
					}
				}
			}
			else
			{
				esito = gestire_errore_sintattico();
			}
		}
		else
		{
			esito = gestire_errore_sintattico();
		}
	}

	return esito;
}

int gestire_errore_sintattico()
{
	int esito;

	rallentare_output("Sintassi non riconosciuta! ", MILLISECONDI);
	esito = false;

	return esito;
}
