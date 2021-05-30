/**
 * Il seguente modulo racchiude le funzioni dell'analizzatore lessicale e sintattico. Appena verr� letta una nuova sorgente viene richiamata
 * per prima la funzione estrarre_token, passandogli per l'appunto la sorgente in input. Questa funzione eliminer� tutti gli spazi all'inizio
 * della sorgente tramite la funzione eliminare_spazi_sorgente, la quale continua ad eliminare dalla sorgente tutti gli spazi fino a quando non
 * incontra un carattere diverso dallo spazio; dopodich� il controllo ritorner� alla funzione estrarre_token, la quale prelever� tutti i
 * caratteri diversi da uno spazio e li inserir� nella stringa chiamata token; infine si elimineranno anche tutti gli spazi presenti dopo il token.
 * E' da notare che tutti questi caratteri letti(spazi e non) verranno eliminati dalla sorgente tramite una funzione di shifting verso sinistra per
 * facilitare l'estrazione del prossimo token.
 * Una volta che � stato estratto il token, questo verr� passato alla funzione scansionare_token insieme ad un indice che indica la posizione in cui
 * inserire il token e il suo corrispondente simbolo all'interno della tabella dei simboli: l'obiettivo di base di questa funzione � quello
 * di restituire un esito se la parola � accettata o meno dall'analizzatore. Quindi l'esito inizialmente viene impostato a false e seguir� un ciclo
 * che si ripeter� tot volte quante sono le parole legali del linguaggio fino a quando non verr� riconosciuta la parola (se non viene riconosciuta
 * allora verr� stampato un messaggio di "Comando non riconosciuto" tramite la funzione gestire errore_lessicale). Se la parola viene riconosciuta
 * esito verr� impostato a true. A questo punto, per�, � necessario prelevare anche il simbolo corrispondente a quel token, per effettuare poi
 * l'analisi sintattica: l'indice del simbolo verr� prelevato dal campo numero_parole_chiave della struttura_parole_chiave che memorizza il numero di
 * parole chiave per ogni token. Infine verranno salvati sia il simbolo e sia il token all'interno della tabella dei simboli.
 * La funzione legata all'analisi sintattica verr� effettuata solamente dopo aver effettuato tutta l'analisi lessicale ed � stata implementata tramite
 * un automa a stati finiti con la funzione controllare_simboli_tabella: verr� letto il primo simbolo e si proceder� con l'analisi del secondo simbolo
 * solo se il primo � un simbolo del movimento, dell'HELP o un verbo. In base alla categoria del primo simbolo verranno effettuati controlli pi� specifici
 * e se verr� superata l'analisi sintattica, verranno richiamate tre funzioni: gestire_movimenti se il primo simbolo � del movimento, gestire_comandi_globali
 * se il primo simbolo � dell'HELP e gestire_azioni_partita se il primo simbolo � un verbo.
 */

#include <stdlib.h>
#include <stdio.h>
#include "../utility/utility.h"
#include "comandi.h"
#include "strutture_analizzatore.h"
#include "gestione_comandi.h"


bool controllare_simboli_tabella();
bool gestire_errore_lessicale();
bool gestire_errore_sintattico();

char eliminare_spazi_sorgente(stringa sorgente);

stringa estrarre_token(stringa sorgente)
{
	stringa token = "";
	int i;
	char c;

	i = 0;

	c = eliminare_spazi_sorgente(sorgente);								// Elimina eventuali spazi all'inizio della sorgente

	while(c != ' ' && c != '\0')										// Fino a quando non trova uno spazio o fine stringa
	{
		token = scrivere_carattere(token, i, c);						// Continua a scrivere nel token il carattere
		i++;
		c = convertire_minuscolo(leggere_carattere(sorgente, i));		// Preleva il carattere successivo convertendolo in minuscolo
	}

	sorgente = shiftare_sinistra(sorgente, i+1);						// Shifta la sorgente di tot caratteri quant'� la lunghezza del token


	c = eliminare_spazi_sorgente(sorgente);								// Elimina eventuali spazi dopo la lettura del token

	token[i] = '\0';													// Imposta il fine stringa al token

	return token;
}

char eliminare_spazi_sorgente(stringa sorgente)
{
	char c;

	if(leggere_lunghezza(sorgente) > 0)									// Se la sorgente non � vuota
	{
		c = convertire_minuscolo(leggere_carattere(sorgente, 0));		// Preleva il primo carattere

		while(c == ' ')													// Fin quando il carattere � uno spazio
		{
			sorgente = shiftare_sinistra(sorgente, 1);					// Continua a shiftare la sorgente eliminando lo spazio iniziale
			c = convertire_minuscolo(leggere_carattere(sorgente, 0));	// Preleva il prossimo carattere(che � in posizione 0 in quanto la sorgente � stata shiftata)
		}
	}

	return c;
}


bool scansionare_token(stringa token, int indice)
{
	bool esito;
	int i;
	int j;

	esito = false;														// Imposta l'esito a falso

	i = 0;

	// Ripeti il ciclo fin quando non � stato trovato il token oppure esci dopo aver confrontato tutte le parole legali con il token
	while(i < leggere_dimensione_parole_chiave() && esito == false)
	{
		// Se il token � uguale ad una parola legale riconosciuta dall'analizzatore
		if(confrontare_stringhe(token, leggere_parola_chiave_tabella(i)))
		{
			j = 0;

			// Preleva l'indice del simbolo corrispondente al token
			while(leggere_numero_parole_chiave(j) <= i)
			{
				j++;
			}

			esito = true;
		}

		i++;
	}

	// Se il token � stato trovato
	if(esito == true)
	{
		// Inserisci il simbolo corrispondente all'interno della tabella dei simboli leggendolo dalla struttura_parole_chiave
		scrivere_simbolo_tabella_simboli(leggere_simboli_struttura_parole_chiave(j), indice);

		// Inserisci il token all'interno della tabella dei simboli
		scrivere_token_tabella_simboli(token, indice);
	}
	else
	{
		esito = gestire_errore_lessicale();			// Altrimenti dai errore di "comando non riconosciuto"
	}

	return esito;
}

bool gestire_errore_lessicale()
{
	bool esito;

	rallentare_output("\nComando non riconosciuto! ", MILLISECONDI);
	esito = false;

	return esito;
}



bool controllare_simboli_tabella()
{
	bool esito;
	simbolo simb;

	esito = false;														// Imposta esito a false

	simb = leggere_simbolo_tabella_simboli(0);							// Legge il primo simbolo dalla tabella dei simboli

	if(simb == MOV)														// Se il simbolo � del movimento
	{
		esito = true;													// Imposta esito a true

		if(leggere_dimensione_tabella_simboli() > 1)					// Se il simbolo del movimento � seguito da altri simboli
		{
			esito = gestire_errore_sintattico();						// Imposta esito a false e stampa un messaggio di errore
		}

		if(esito == true)												// Se esito � uguale a true, cio� c'� solo un simbolo del movimento nella TS
		{
			gestire_movimenti();										// Richiama la funzione gestire_movimenti
		}
	}
	else if(simb == HLP)												// Se il simbolo � dell'HELP
	{
		esito = true;													// Imposta esito a true

		if(leggere_dimensione_tabella_simboli() > 1)					// Se il simbolo dell'HELP � seguito da altri simboli
		{
			simb = leggere_simbolo_tabella_simboli(1);					// Leggo il secondo simbolo

			if(simb == PRH)												// Se il secondo simbolo � delle PAROLE HELP
			{
				esito = true;											// Imposta esito a true

				if(leggere_dimensione_tabella_simboli() > 2)			// Se ci sono almeno tre simboli nella TS
				{
					esito = gestire_errore_sintattico();				// Imposta esito a false e stampa un messaggio di errore
				}
			}
			else
			{
				esito = gestire_errore_sintattico();					// Se il secondo simbolo non � delle PAROLE HELP, imposta esito a false e stampa un messaggio di errore
			}
		}

		if(esito == true)												// Se dopo il controllo sintattico esito � ancora uguale a true
		{
			esito = gestire_comandi_globali();							// Richiama la funzione gestire_comandi_globali ed assegna il risultato ad esito per un ulteriore controllo sintattico

			if(esito == false)											// Se esito � uguale a false
			{
				gestire_errore_sintattico();							// Stampa un messaggio di errore
			}
		}
	}
	else if(simb == VRB)												// Se il primo simbolo � un verbo
	{
		esito = false;													// Imposta esito a false, perch� ogni verbo deve essere seguito necessariamente da una parola

		if(leggere_dimensione_tabella_simboli() > 1)					// Se ci sono almeno due simboli nella TS
		{
			simb = leggere_simbolo_tabella_simboli(1);					// Leggo il secondo simbolo dalla TS

			if(simb == PRL)												// Se il secondo simbolo � una parola legata ai verbi
			{
				esito = true;											// Imposto esito a true

				if(leggere_dimensione_tabella_simboli() > 2)			// Se ci sono almeno tre simboli nella TS
				{
					simb = leggere_simbolo_tabella_simboli(2);			// Leggo il terzo simbolo dalla TS

					if(simb == PRL)										// Se il terzo simbolo � una parola legata ai verbi
					{
						esito = true;									// Imposto esito a true

						if(leggere_dimensione_tabella_simboli() > 3)	// Se ci sono pi� di tre simboli
						{
							esito = gestire_errore_sintattico();		// Stampo un messaggio di errore ed assegno false ad esito
						}
					}
					else
					{
						esito = gestire_errore_sintattico();			// Se il terzo simbolo non � una parola stampo un messaggio di errore ed assegno false ad esito
					}
				}
			}
			else
			{
				esito = gestire_errore_sintattico();					// Se il secondo simbolo non � una parola stampo un messaggio di errore ed assegno false ad esito
			}
		}
		else
		{
			esito = gestire_errore_sintattico();						// Se c'� solamente un simbolo verbo non seguito da una parola stampo un messaggio di errore ed assegno false ad esito
		}

		if(esito == true)												// Se tutti questi controlli hanno dato esito true
		{
			esito = gestire_azioni_partita();							// Richiamo la funzione gestire_azioni_partita ed assegna il risultato ad esito per un ulteriore controllo sintattico

			if(esito == false)											// Se esito � uguale a false
			{
				gestire_errore_sintattico();							// Stampa un messaggio di errore
			}
		}
	}
	else																// Se il primo simbolo non � n� del movimento, n� di HELP e n� un verbo
	{
		esito = gestire_errore_sintattico();							// Stampo un messaggio di errore ed assegno false ad esito
	}

	return esito;
}

bool gestire_errore_sintattico()
{
	bool esito;

	rallentare_output("\nSintassi non riconosciuta! ", MILLISECONDI);	// Stampa il messaggio di "Sintassi non riconosciuta"
	esito = false;														// Imposta esito a false

	return esito;
}


