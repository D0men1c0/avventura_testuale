#include <stdlib.h>
#include <stdio.h>
#include "analizzatore_sintattico.h"
#include "../utility/utility.h"
#include "../gestione_file/file_di_testo/lettura_file_testo.h"

#define NOME_FILE_LINGUAGGIO "parole_linguaggio.txt"

void scrivere_dimensione_simboli(int dimensione);
int leggere_dimensione_simboli();
void inserire_simbolo_tabella(simbolo simb);

void scrivere_dimensione_parole_chiave(int dimensione);
int leggere_dimensione_parole_chiave();
void inserire_parola_chiave_tabella(parola_chiave parola);

void leggere_sorgente()
{
	stringa str = "";

	str = leggere_stringa_tastiera(str);
}


/*token estrarre_token()
{
	token t;

	return t;
}*/


void leggere_simboli_parole()
{
	int i;
	int pos;
	stringa str = "";
	simbolo simb;
	parola_chiave parola;
	bool leggere;

	str = leggere_file_testo(NOME_FILE_LINGUAGGIO, str);

	i = 0;
	pos = 0;
	leggere = true;

	scrivere_dimensione_simboli(0);

	while(i < leggere_lunghezza(str))
	{
		if((str[i] == '\n') && leggere == true)
		{
			simb[pos] = '\0';
			inserire_simbolo_tabella(simb);
			pos = 0;
			leggere = false;
		}
		else
		{
			if(leggere == true)
			{
				simb[pos] = str[i];
				pos++;
			}
			else
			{
				if(str[i] == '\n')
				{
					leggere = true;
				}
			}
		}

		i++;
	}

	leggere = false;
	i = 0;
	scrivere_dimensione_parole_chiave(0);

	while(i < leggere_lunghezza(str) + 1)
	{
		if((str[i] == '\n'|| str[i] == '\0') && leggere == true)
		{
			parola = scrivere_carattere(parola, pos, '\0');
			inserire_parola_chiave_tabella(parola);
			pos = 0;
			leggere = false;
		}
		else
		{
			if(leggere == true)
			{
				if(str[i] != ' ')
				{
					parola = scrivere_carattere(parola, pos, str[i]);
					pos++;
				}
				else
				{
					parola = scrivere_carattere(parola, pos, '\0');
					pos = 0;
					inserire_parola_chiave_tabella(parola);
				}
			}
			else
			{
				if(str[i] == '\n')
				{
					leggere = true;
				}
			}
		}

		i++;
	}
}

void inserire_simbolo_tabella(simbolo simb)
{
	int dimensione;

	dimensione = leggere_dimensione_simboli();

	int i;

	i = 0;

	while(i < MAX_SIMBOLO)
	{
		struttura_simboli.simboli[dimensione][i] = simb[i];
		i++;
	}


	scrivere_dimensione_simboli(dimensione + 1);
}

void inserire_parola_chiave_tabella(parola_chiave parola)
{
	int dimensione;

	dimensione = leggere_dimensione_parole_chiave();

	struttura_parole_chiave.parole_chiave[dimensione] = allocare_stringa(struttura_parole_chiave.parole_chiave[dimensione], 0);

	struttura_parole_chiave.parole_chiave[dimensione] = scrivere_stringa(struttura_parole_chiave.parole_chiave[dimensione], parola);

	scrivere_dimensione_parole_chiave(dimensione + 1);
}


void scrivere_dimensione_simboli(int dimensione)
{
	struttura_simboli.dimensione = dimensione;
}


int leggere_dimensione_simboli()
{
	return struttura_simboli.dimensione;
}

void scrivere_dimensione_parole_chiave(int dimensione)
{
	struttura_parole_chiave.dimensione = dimensione;
}

int leggere_dimensione_parole_chiave()
{
	return struttura_parole_chiave.dimensione;
}


void stampare_simboli_tabella()
{
	int i;
	int j;

	i = 0;

	while(i < leggere_dimensione_simboli(struttura_simboli))
	{
		j = 0;

		while(j < MAX_SIMBOLO - 1)
		{
			printf("%c", struttura_simboli.simboli[i][j]);
			j++;
		}

		i++;
	}
}

void stampare_parole_chiave_tabella()
{
	int i;

	i = 0;

	while(i < leggere_dimensione_parole_chiave(struttura_parole_chiave))
	{

		printf("%s ", leggere_stringa(struttura_parole_chiave.parole_chiave[i]));

		i++;
	}
}

