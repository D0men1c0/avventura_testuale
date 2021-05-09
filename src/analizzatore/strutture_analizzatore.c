#include <stdlib.h>
#include <stdio.h>
#include "strutture_analizzatore.h"
#include "analizzatore_sintattico.h"
#include "../utility/utility.h"
#include "../gestione_file/file_di_testo/lettura_file_testo.h"

#define NOME_FILE_LINGUAGGIO "parole_linguaggio.txt"

void scrivere_dimensione_simboli(int dimensione);
void inserire_simbolo_tabella(simbolo simb);
void scrivere_dimensione_parole_chiave(int dimensione);
void inserire_parola_chiave_tabella(parola_chiave parola);
void inserire_parole_chiave(stringa str);
void inserire_simboli(stringa str);


void inizializzare_strutture_analizzatore()
{
	stringa str = "";

	str = leggere_file_testo(NOME_FILE_LINGUAGGIO, str);


	inserire_simboli(str);

	inserire_parole_chiave(str);
}

void leggere_comando()
{
	leggere_sorgente();

	int i;
	i = 0;

	while(leggere_lunghezza(sorgente) != 0)
	{
		scansionare_token(estrarre_token(), i);
		i++;
	}
}

void inserire_simboli(stringa str)
{
	int i;
	int pos;
	simbolo simb;
	bool leggere;

	i = 0;
	pos = 0;
	leggere = true;

	scrivere_dimensione_simboli(0);

	while(i < leggere_lunghezza(str))
	{
		if(leggere == true)
		{
			if((str[i] == '\n'))
			{
				simb[pos] = '\0';
				inserire_simbolo_tabella(simb);
				pos = 0;
				leggere = false;
			}
			else
			{
				simb[pos] = str[i];
				pos++;
			}
		}
		else
		{
			if(str[i] == '\n')
				leggere = true;
		}

		i++;
	}
}

void inserire_parole_chiave(stringa str)
{
	bool leggere;
	int i;
	int pos;
	int numero_parole;
	int indice_simbolo;
	parola_chiave parola;

	leggere = false;
	i = 0;
	numero_parole = 0;
	indice_simbolo = 0;
	scrivere_dimensione_parole_chiave(0);

	while(i < leggere_lunghezza(str) + 1)
	{
		if(leggere == true)
		{
			if(str[i] != ' ' && (str[i] != '\n' && str[i] != '\0'))
			{
				parola = scrivere_carattere(parola, pos, str[i]);
				pos++;
			}
			else
			{
				parola = scrivere_carattere(parola, pos, '\0');
				pos = 0;
				inserire_parola_chiave_tabella(parola);
				numero_parole++;

				if(str[i] == '\n'|| str[i] == '\0')
				{
					leggere = false;

					struttura_simboli.numero_parole_chiave[indice_simbolo] = numero_parole;

					indice_simbolo++;
				}
			}
		}
		else if(str[i] == '\n')
			leggere = true;

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

	struttura_parole_chiave.parole_chiave[dimensione] = parola;

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

int leggere_numero_parole_chiave(int indice)
{
	return  struttura_simboli.numero_parole_chiave[indice];
}

void scrivere_dimensione_parole_chiave(int dimensione)
{
	struttura_parole_chiave.dimensione = dimensione;
}

int leggere_dimensione_parole_chiave()
{
	return struttura_parole_chiave.dimensione;
}

stringa leggere_parola_chiave_tabella(int indice)
{
	return leggere_stringa(struttura_parole_chiave.parole_chiave[indice]);
}

