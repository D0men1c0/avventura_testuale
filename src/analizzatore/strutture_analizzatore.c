#include <stdlib.h>
#include <stdio.h>
#include "strutture_analizzatore.h"
#include "../utility/utility.h"
#include "../gestione_file/file_di_testo/lettura_file_testo.h"
#include "analizzatore_lessicale.h"

#define NOME_FILE_LINGUAGGIO "parole_linguaggio.txt"

void scrivere_dimensione_simboli(int dimensione);
void inserire_simbolo_tabella(simbolo simb);
void scrivere_dimensione_parole_chiave(int dimensione);
void inserire_parola_chiave_tabella(parola_chiave parola);
void inserire_parole_chiave();
void inserire_simboli();


void inizializzare_strutture_analizzatore()
{
	inserire_simboli();

	inserire_parole_chiave();
}

void leggere_comando()
{
	int i;
	int esito;

	rallentare_output("Inserisci il comando: ", MILLISECONDI);

	leggere_sorgente();

	i = 0;

	esito = ERRORE;

	scrivere_dimensione_tabella_simboli(0);

	if(leggere_lunghezza(sorgente) != 0)
	{
		esito = SUCCESSO;

		while(leggere_lunghezza(sorgente) != 0 && esito == SUCCESSO)
		{
			esito = scansionare_token(estrarre_token(), i);
			i++;
		}
	}

	if(esito == SUCCESSO)
	{
		esito = controllare_simboli_tabella();

	}
}


void scrivere_dimensione_tabella_simboli(int dimensione)
{
	tabella_simboli.dimensione = dimensione;
}

int leggere_dimensione_tabella_simboli()
{
	return tabella_simboli.dimensione;
}


void scrivere_simbolo_tabella_simboli(simbolo simb, int indice)
{
	tabella_simboli.simboli[indice] = simb;
}

simbolo leggere_simbolo_tabella_simboli(int indice)
{
	return tabella_simboli.simboli[indice];
}

void scrivere_token_tabella_simboli(parola_chiave token, int indice)
{
	tabella_simboli.token[indice] = token;
}

parola_chiave leggere_token_tabella_simboli(int indice)
{
	return tabella_simboli.token[indice];
}

void inserire_simboli()
{
	int i;

	i = 1;

	scrivere_dimensione_simboli(0);


	while(i <= 5)
	{
		inserire_simbolo_tabella(i);
		i++;
	}
}

void inserire_parole_chiave()
{
	scrivere_dimensione_parole_chiave(0);

	inserire_parola_chiave_tabella("nord");
	inserire_parola_chiave_tabella("sud");
	inserire_parola_chiave_tabella("est");
	inserire_parola_chiave_tabella("ovest");
	//inserimento all'interno della struttura
	scrivere_parola_chiave_struttura_simboli(0,leggere_dimensione_parole_chiave());

	inserire_parola_chiave_tabella("salva");
	inserire_parola_chiave_tabella("carica");
	inserire_parola_chiave_tabella("nuova");
	inserire_parola_chiave_tabella("aiuto");
	//inserimento all'interno della struttura
	scrivere_parola_chiave_struttura_simboli(1,leggere_dimensione_parole_chiave());

	inserire_parola_chiave_tabella("partita");
	//inserimento all'interno della struttura
	scrivere_parola_chiave_struttura_simboli(2,leggere_dimensione_parole_chiave());

	inserire_parola_chiave_tabella("prendi");
	inserire_parola_chiave_tabella("sfonda");
	inserire_parola_chiave_tabella("esamina");
	inserire_parola_chiave_tabella("visualizza");
	inserire_parola_chiave_tabella("apri");
	//inserimento all'interno della struttura
	scrivere_parola_chiave_struttura_simboli(3,leggere_dimensione_parole_chiave());

	inserire_parola_chiave_tabella("chiave");
	inserire_parola_chiave_tabella("porta");
	inserire_parola_chiave_tabella("frammento");
	inserire_parola_chiave_tabella("mappa");
	inserire_parola_chiave_tabella("botola");
	inserire_parola_chiave_tabella("stanza");
	inserire_parola_chiave_tabella("attributi");
	inserire_parola_chiave_tabella("inventario");
	//inserimento all'interno della struttura
	scrivere_parola_chiave_struttura_simboli(4,leggere_dimensione_parole_chiave());
}

void inserire_simbolo_tabella(simbolo simb)
{
	int dimensione;

	dimensione = leggere_dimensione_simboli();
	scrivere_simboli_struttura_simboli(dimensione,simb);

	scrivere_dimensione_simboli(dimensione + 1);
}

void inserire_parola_chiave_tabella(parola_chiave parola)
{
	int dimensione;

	dimensione = leggere_dimensione_parole_chiave();
	scrivere_parola_chiave_struttura_parole_chiave(dimensione, parola);

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

void scrivere_parola_chiave_struttura_simboli(int indice, int valore)
{
	struttura_simboli.numero_parole_chiave[indice] = valore;
}

void scrivere_simboli_struttura_simboli(int indice, simbolo simb)
{
	struttura_simboli.simboli[indice] = simb;
}

void scrivere_parola_chiave_struttura_parole_chiave(int indice, parola_chiave parola)
{
	struttura_parole_chiave.parole_chiave[indice] = parola;
}
