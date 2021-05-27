#include <stdlib.h>
#include <stdio.h>
#include "strutture_analizzatore.h"
#include "../utility/utility.h"
#include "analizzatore_lessicale_sintattico.h"
#include "comandi.h"
#include "gestione_comandi.h"


bool gestire_errore_lessicale();

bool gestire_errore_sintattico();

char eliminare_spazi_sorgente();

void leggere_sorgente()
{
	stringa str = "";

	str = leggere_stringa_tastiera(str);

	sorgente = scrivere_stringa(sorgente, str);
}

stringa estrarre_token()
{
	stringa token = "";
	int i;
	char c;

	i = 0;

	c = eliminare_spazi_sorgente();

	while(c != ' ' && c != '\0')
	{
		token = scrivere_carattere(token, i, c);
		i++;
		c = convertire_minuscolo(leggere_carattere(sorgente, i));
	}

	sorgente = shiftare_sinistra(sorgente, i+1);


	c = eliminare_spazi_sorgente();

	token[i] = '\0';

	return token;
}

char eliminare_spazi_sorgente()
{
	char c;

	if(leggere_lunghezza(sorgente) > 0)
	{
		c = convertire_minuscolo(leggere_carattere(sorgente, 0));

		while(c == ' ')
		{
			sorgente = shiftare_sinistra(sorgente, 1);
			c = convertire_minuscolo(leggere_carattere(sorgente, 0));
		}
	}

	return c;
}


bool scansionare_token(stringa token, int indice)
{
	bool esito;
	int i;
	int j;

	esito = ERRORE;

	i = 0;

	while(i < leggere_dimensione_parole_chiave() && esito == ERRORE)
	{
		if(confrontare_stringhe(token, leggere_parola_chiave_tabella(i)))
		{
			j = 0;

			while(j < leggere_dimensione_parole_chiave() && leggere_numero_parole_chiave(j) <= i)
			{
				j++;
			}

			esito = SUCCESSO;
		}

		i++;
	}

	if(esito == SUCCESSO)
	{
		scrivere_simbolo_tabella_simboli(leggere_simboli_struttura_simboli(j), indice);
		scrivere_token_tabella_simboli(token, indice);
	}
	else
	{
		esito = gestire_errore_lessicale();
	}

	return esito;
}

bool gestire_errore_lessicale()
{
	bool esito;

	rallentare_output("\nComando non riconosciuto! ", MILLISECONDI);
	esito = ERRORE;

	return esito;
}



bool controllare_simboli_tabella()
{
	bool esito;
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

		if(esito == true)
		{
			esito = gestire_movimenti();

			if(esito == false)
			{
				gestire_errore_sintattico();
			}
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

		if(esito == true)
		{
			esito = gestire_azioni_partita();

			if(esito == false)
			{
				gestire_errore_sintattico();
			}
		}
	}
	else
	{
		esito = gestire_errore_sintattico();
	}

	return esito;
}

bool gestire_errore_sintattico()
{
	bool esito;

	rallentare_output("\nSintassi non riconosciuta! ", MILLISECONDI);
	esito = false;

	return esito;
}


