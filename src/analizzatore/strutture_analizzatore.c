/**
 * Questo modulo definisce le funzioni di gestione struttura parole chiavi e struttura tabella simboli. Innanzitutto è presente
 * la funzione di inizializzare_strutture_analizzatore: questa funzione inserisce tramite un ciclo i simboli(intero) all'interno
 * della struttura parole chiave, dopodichè uno alla volta inserisce le parole chiavi legali riconosciute dall'analizzatore,
 * quindi scrive il numero di parole chiave legate a quella classe di simboli(esempio: se il simbolo dello spostamento ha 4
 * parole chiave ad esso legato, verrà inserito il numero 4 all'interno del campo numero_parole_chiave il cui indice è proprio
 * il simbolo).
 * L'altra funzione principale è leggere_comando: questa funzione legge la sorgente da tastiera e ripete in ciclo l'analisi lessicale
 * richiamando la funzione estrarre_token e di conseguenza la scansionare_token. Dall'analisi lessicale di ogni token verrà restituito
 * un esito, se true l'analisi lessicale procede fin quando sorgente non ha più token, altrimenti si ferma e stampa un messaggio di
 * "Comando non riconosciuto".
 */

#include <stdlib.h>
#include <stdio.h>
#include "strutture_analizzatore.h"
#include "../utility/utility.h"
#include "../gestione_file/gestione_file.h"
#include "analizzatore_lessicale_sintattico.h"

void scrivere_dimensione_simboli(int dimensione);
void inserire_simbolo_tabella(simbolo simb);
void scrivere_dimensione_parole_chiave(int dimensione);
void scrivere_parola_chiave_struttura_parole_chiave(parola_chiave parola);

void inizializzare_strutture_analizzatore()
{
	// INIZIALIZZAZIONE SIMBOLI
	int i;

	i = 1;

	scrivere_dimensione_simboli(0);							// Inizializza la dimensione dei simboli a 0

	while(i <= MAX_SIMBOLI)									// Ripete il ciclo tot volte(quanti sono i simboli)
	{
		inserire_simbolo_tabella(i);						// Inserisce il simbolo(intero) nella struttura parole chiave
		i++;
	}

	// INIZIALIZZAZIONE PAROLE CHIAVE

	scrivere_dimensione_parole_chiave(0);					// Inizializza la dimensione delle parole chiave a 0

	// Inserisce le parole chiave dello spostamento e imposta il numero di parole chiave dello spostamento
	scrivere_parola_chiave_struttura_parole_chiave(NORD);
	scrivere_parola_chiave_struttura_parole_chiave(SUD);
	scrivere_parola_chiave_struttura_parole_chiave(EST);
	scrivere_parola_chiave_struttura_parole_chiave(OVEST);
	scrivere_numero_parola_chiave_struttura_parole_chiave(0, leggere_dimensione_parole_chiave());

	// Inserisce le parole chiave dei comandi globali e imposta il numero di parole chiave dei comandi globali
	scrivere_parola_chiave_struttura_parole_chiave(SALVA);
	scrivere_parola_chiave_struttura_parole_chiave(CARICA);
	scrivere_parola_chiave_struttura_parole_chiave(NUOVA);
	scrivere_parola_chiave_struttura_parole_chiave(AIUTO);
	scrivere_numero_parola_chiave_struttura_parole_chiave(1, leggere_dimensione_parole_chiave());

	/**
	 * Inserisce le parole chiave delle parole relative ai comandi globali e imposta il numero di parole chiave
	 * delle parole relative ai comandi globali
	 */
	scrivere_parola_chiave_struttura_parole_chiave(PARTITA);
	scrivere_numero_parola_chiave_struttura_parole_chiave(2, leggere_dimensione_parole_chiave());

	// Inserisce le parole chiave dei verbi e imposta il numero di parole chiave dei verbi
	scrivere_parola_chiave_struttura_parole_chiave(PRENDI);
	scrivere_parola_chiave_struttura_parole_chiave(SFONDA);
	scrivere_parola_chiave_struttura_parole_chiave(ESAMINA);
	scrivere_parola_chiave_struttura_parole_chiave(VISUALIZZA);
	scrivere_parola_chiave_struttura_parole_chiave(APRI);
	scrivere_numero_parola_chiave_struttura_parole_chiave(3, leggere_dimensione_parole_chiave());

	/**
	 * Inserisce le parole chiave delle parole relative ai verbi e imposta il numero di parole chiave
	 * delle parole relative ai verbi
	 */
	scrivere_parola_chiave_struttura_parole_chiave(CHIAVE);
	scrivere_parola_chiave_struttura_parole_chiave(PORTA);
	scrivere_parola_chiave_struttura_parole_chiave(FRAMMENTO);
	scrivere_parola_chiave_struttura_parole_chiave(MAPPA);
	scrivere_parola_chiave_struttura_parole_chiave(BOTOLA);
	scrivere_parola_chiave_struttura_parole_chiave(STANZA);
	scrivere_parola_chiave_struttura_parole_chiave(ATTRIBUTI);
	scrivere_parola_chiave_struttura_parole_chiave(INVENTARIO);
	scrivere_numero_parola_chiave_struttura_parole_chiave(4, leggere_dimensione_parole_chiave());
}

void leggere_comando()
{
	int i;
	int esito;
	stringa sorgente = "";

	printf(COLORE_ROSSO);
	rallentare_output("Inserisci il comando: ", MILLISECONDI);
	printf(COLORE_BIANCO);

	sorgente = leggere_stringa_tastiera(sorgente);			// Legge da tastiera la sorgente

	i = 0;

	esito = false;

	scrivere_dimensione_tabella_simboli(0);					// Inizializza la dimensione dei simboli a 0

	if(leggere_lunghezza(sorgente) != 0)					// Se la sorgente non è vuota
	{
		esito = true;

		/**
		 * Continua a leggere la sorgente fino a quando la sua lunghezza è maggiore di 0 e fin quando
		 * esito è uguale a true, quindi esce dal ciclo se almeno un token non è stato riconosciuto.
		 * Esce dal ciclo anche se si leggono più token rispetto alla dimensione della tabella dei simboli,
		 * cioè MAX_SIMBOLI
		 */
		while(leggere_lunghezza(sorgente) != 0 && esito == true && i < MAX_SIMBOLI)
		{
			esito = scansionare_token(estrarre_token(sorgente), i);		// Estrae il token dalla sorgente e lo scansiona
			i++;
		}
	}

	if(esito == true)								// Se tutti i token sono stati riconosciuti, si passa all'analisi sintattica
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
	scrivere_dimensione_tabella_simboli(leggere_dimensione_tabella_simboli() + 1);
}

parola_chiave leggere_token_tabella_simboli(int indice)
{
	return tabella_simboli.token[indice];
}


void inserire_simbolo_tabella(simbolo simb)
{
	int dimensione;

	dimensione = leggere_dimensione_parole_chiave();
	scrivere_simboli_struttura_parole_chiave(dimensione, simb);

	scrivere_dimensione_simboli(dimensione + 1);
}

void scrivere_dimensione_simboli(int dimensione)
{
	struttura_parole_chiave.dimensione = dimensione;
}

int leggere_numero_parole_chiave(int indice)
{
	return  struttura_parole_chiave.numero_parole_chiave[indice];
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

void scrivere_numero_parola_chiave_struttura_parole_chiave(int indice, int valore)
{
	struttura_parole_chiave.numero_parole_chiave[indice] = valore;
}

void scrivere_simboli_struttura_parole_chiave(int indice, simbolo simb)
{
	struttura_parole_chiave.simboli[indice] = simb;
}

simbolo leggere_simboli_struttura_parole_chiave(int indice)
{
	simbolo simb;

	simb = struttura_parole_chiave.simboli[indice];

	return simb;
}

void scrivere_parola_chiave_struttura_parole_chiave(parola_chiave parola)
{
	int dimensione;

	dimensione = leggere_dimensione_parole_chiave();
	struttura_parole_chiave.parole_chiave[dimensione] = parola;

	scrivere_dimensione_parole_chiave(dimensione + 1);
}
