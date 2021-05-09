#include <stdlib.h>
#include <stdio.h>
#include "analizzatore_sintattico.h"
#include "../utility/utility.h"
#include "../gestione_file/file_di_testo/lettura_file_testo.h"

#define NOME_FILE_LINGUAGGIO "parole_linguaggio.txt"

void scrivere_dimensione_simboli(int dimensione);
int leggere_dimensione_simboli();
void inserire_simbolo_tabella(simbolo simb);
void leggere_simbolo(int indice);

void scrivere_dimensione_parole_chiave(int dimensione);
int leggere_dimensione_parole_chiave();
stringa leggere_parola_chiave_tabella(int indice);
void inserire_parola_chiave_tabella(parola_chiave parola);

void inserire_parole_chiave(stringa str);
void inserire_simboli(stringa str);

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
	int numero_parole;
	simbolo simb;

	esito = ERRORE;

	i = 0;

	while(i < leggere_dimensione_parole_chiave() && esito == ERRORE)
	{
		if(confrontare_stringhe(token, leggere_parola_chiave_tabella(i)))
		{
			j = 0;
			numero_parole = struttura_simboli.numero_parole_chiave[j];

			while(j < leggere_dimensione_simboli() && numero_parole <= i)
			{
				j++;
				numero_parole = struttura_simboli.numero_parole_chiave[j];
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

void leggere_simboli_parole()
{
	stringa str = "";

	str = leggere_file_testo(NOME_FILE_LINGUAGGIO, str);


	inserire_simboli(str);

	inserire_parole_chiave(str);
}

void leggere_simbolo(int indice)
{
	printf("%s ", struttura_simboli.simboli[indice]);
	//return struttura_simboli.simboli[indice];
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
		if((str[i] == '\n'|| str[i] == '\0') && leggere == true)
		{
			parola = scrivere_carattere(parola, pos, '\0');
			inserire_parola_chiave_tabella(parola);

			numero_parole++;
			pos = 0;
			leggere = false;

			struttura_simboli.numero_parole_chiave[indice_simbolo] = numero_parole;

			indice_simbolo++;
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
					numero_parole++;
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

/*
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


		printf(": %d\n", struttura_simboli.numero_parole_chiave[i]);

		i++;
	}
}*/

stringa leggere_parola_chiave_tabella(int indice)
{
	return leggere_stringa(struttura_parole_chiave.parole_chiave[indice]);
}

/*
void stampare_parole_chiave_tabella()
{
	int i;

	i = 0;

	printf("\n");

	while(i < leggere_dimensione_parole_chiave(struttura_parole_chiave))
	{

		printf("%s\n", leggere_stringa(struttura_parole_chiave.parole_chiave[i]));

		i++;
	}
}*/

