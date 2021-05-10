#include <stdlib.h>
#include <stdio.h>
#include "analizzatore_sintattico.h"
#include "strutture_analizzatore.h"
#include "../utility/utility.h"

int gestire_errore();

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

	c = leggere_carattere(sorgente, 0);

	while(c == ' ')
	{
		sorgente = shiftare_sinistra(sorgente, 1);
		c = leggere_carattere(sorgente, 0);
	}

	while(c != ' ' && c != '\0')
	{
		token = scrivere_carattere(token, i, c);
		i++;
		c = leggere_carattere(sorgente, i);
	}

	sorgente = shiftare_sinistra(sorgente, i+1);

	return token;
}


int scansionare_token(stringa token, int indice)
{
	int esito;
	int i;
	int j;

	esito = ERRORE;

	i = 0;

	while(i < leggere_dimensione_parole_chiave() && esito == ERRORE)
	{
		if(confrontare_stringhe(token, leggere_parola_chiave_tabella(i)))
		{
			j = 0;

			while(j < leggere_dimensione_simboli() && leggere_numero_parole_chiave(j) <= i)
			{
				j++;
			}

			esito = SUCCESSO;
		}

		i++;
	}

	if(esito == SUCCESSO)
	{
		tabella_simboli[indice] = struttura_simboli.simboli[j];
	}
	else
	{
		esito = gestire_errore();
	}

	return esito;
}

int gestire_errore()
{
	int esito;

	rallentare_output("Comando non riconosciuto! ", MILLISECONDI);
	esito = ERRORE;

	return esito;
}

