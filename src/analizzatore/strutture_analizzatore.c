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

void scrivere_numero_parola_chiave_struttura_parole_chiave(int indice, int valore);
void scrivere_simbolo_struttura_parole_chiave(simbolo simb, int indice);
void scrivere_parola_chiave_struttura_parole_chiave(parola_chiave parola, int indice);

void inizializzare_strutture_analizzatore()
{
	// INIZIALIZZAZIONE SIMBOLI
	int i;

	i = 1;

	while(i <= MAX_SIMBOLI)									// Ripete il ciclo tot volte(quanti sono i simboli)
	{
		scrivere_simbolo_struttura_parole_chiave(i, i-1);						// Inserisce il simbolo(intero) nella struttura parole chiave
		i++;
	}

	// INIZIALIZZAZIONE PAROLE CHIAVE0

	// Inserisce le parole chiave dello spostamento e imposta il numero di parole chiave dello spostamento
	scrivere_parola_chiave_struttura_parole_chiave(NORD, 0);
	scrivere_parola_chiave_struttura_parole_chiave(SUD, 1);
	scrivere_parola_chiave_struttura_parole_chiave(EST, 2);
	scrivere_parola_chiave_struttura_parole_chiave(OVEST, 3);
	scrivere_numero_parola_chiave_struttura_parole_chiave(0, 4);

	// Inserisce le parole chiave dei comandi globali e imposta il numero di parole chiave dei comandi globali
	scrivere_parola_chiave_struttura_parole_chiave(SALVA, 4);
	scrivere_parola_chiave_struttura_parole_chiave(CARICA, 5);
	scrivere_parola_chiave_struttura_parole_chiave(NUOVA, 6);
	scrivere_parola_chiave_struttura_parole_chiave(AIUTO, 7);
	scrivere_numero_parola_chiave_struttura_parole_chiave(1, 8);

	/**
	 * Inserisce le parole chiave delle parole relative ai comandi globali e imposta il numero di parole chiave
	 * delle parole relative ai comandi globali
	 */
	scrivere_parola_chiave_struttura_parole_chiave(PARTITA, 8);
	scrivere_numero_parola_chiave_struttura_parole_chiave(2, 9);

	// Inserisce le parole chiave dei verbi e imposta il numero di parole chiave dei verbi
	scrivere_parola_chiave_struttura_parole_chiave(PRENDI, 9);
	scrivere_parola_chiave_struttura_parole_chiave(SFONDA, 10);
	scrivere_parola_chiave_struttura_parole_chiave(ESAMINA, 11);
	scrivere_parola_chiave_struttura_parole_chiave(VISUALIZZA, 12);
	scrivere_parola_chiave_struttura_parole_chiave(APRI, 13);
	scrivere_numero_parola_chiave_struttura_parole_chiave(3, 14);

	/**
	 * Inserisce le parole chiave delle parole relative ai verbi e imposta il numero di parole chiave
	 * delle parole relative ai verbi
	 */
	scrivere_parola_chiave_struttura_parole_chiave(CHIAVE, 14);
	scrivere_parola_chiave_struttura_parole_chiave(PORTA, 15);
	scrivere_parola_chiave_struttura_parole_chiave(FRAMMENTO, 16);
	scrivere_parola_chiave_struttura_parole_chiave(MAPPA, 17);
	scrivere_parola_chiave_struttura_parole_chiave(BOTOLA, 18);
	scrivere_parola_chiave_struttura_parole_chiave(STANZA, 19);
	scrivere_parola_chiave_struttura_parole_chiave(ATTRIBUTI, 20);
	scrivere_parola_chiave_struttura_parole_chiave(INVENTARIO, 21);
	scrivere_numero_parola_chiave_struttura_parole_chiave(4, 22);
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

void scrivere_simbolo_struttura_parole_chiave(simbolo simb, int indice)
{
	struttura_parole_chiave.simboli[indice] = simb;
}

simbolo leggere_simboli_struttura_parole_chiave(int indice)
{
	return struttura_parole_chiave.simboli[indice];
}

void scrivere_parola_chiave_struttura_parole_chiave(parola_chiave parola, int indice)
{
	struttura_parole_chiave.parole_chiave[indice] = parola;
}

stringa leggere_parola_chiave_tabella(int indice)
{
	return leggere_stringa(struttura_parole_chiave.parole_chiave[indice]);
}

void scrivere_numero_parola_chiave_struttura_parole_chiave(int indice, int valore)
{
	struttura_parole_chiave.numero_parole_chiave[indice] = valore;
}

int leggere_numero_parole_chiave(int indice)
{
	return  struttura_parole_chiave.numero_parole_chiave[indice];
}
