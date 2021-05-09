#include <stdlib.h>
#include <stdio.h>
#include "analizzatore_sintattico.h"
#include "strutture_analizzatore.h"
#include "../utility/utility.h"


void leggere_sorgente()
{
	stringa str = "";

	str = leggere_stringa_tastiera(str);

	sorgente = scrivere_stringa(sorgente, str);
}


stringa estrarre_token()
{
	stringa token;
	int i;
	char c;

	i = 0;
	c = leggere_carattere(sorgente, i);

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
	int k;

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


			k = 0;

			while(k < MAX_SIMBOLO)
			{
				tabella_simboli[indice][k] = struttura_simboli.simboli[j][k];
				printf("%c", tabella_simboli[indice][k]);
				k++;
			}

			esito = SUCCESSO;
		}

		i++;
	}


	return esito;
}

