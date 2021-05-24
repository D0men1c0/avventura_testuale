/**
 * Questo modulo gestisce i movimenti del personaggio. Attraverso una struttura che salva la posizione, le funzioni presenti in
 * questo modulo permettono, oltre alla modifica dei dati che compongono la struttura, di trovare le direzioni percorribili dal
 * giocatore in quella cella e il movimento vero e proprio del personaggio nella mappa.
*/

#include <stdio.h>
#include <string.h>
#include "../utility/array/matrice.h"
#include "../utility/stringa/stringa.h"
#include "gestione_movimenti.h"
#include "../gestione_file/gestione_file.h"
#include "../inventario/gestione_inventario.h"
#include "../personaggio/gestione_personaggio.h"
#include "gestione_mappa.h"

void scrivere_x(posizione * posizione_personaggio, int x)
{
	posizione_personaggio->x = x;		//Sovrascrittura della x nella posizione del personaggio.
}

void scrivere_y(posizione * posizione_personaggio, int y)
{
	posizione_personaggio->y = y;		//Sovrascrittura della y nella posizione del personaggio.
}

int leggere_x(posizione posizione_personaggio)
{
	return posizione_personaggio.x;		//Restituzione della x della posizione del personaggio.
}

int leggere_y(posizione posizione_personaggio)
{
	return posizione_personaggio.y;		//Restituzione della y della posizione del personaggio.
}

stringa trovare_direzioni_disponibili()
{
	int cella_attuale;												//Cella in cui il personaggio si trova attualmente.
	posizione posizione_nord;										//Posizione a nord del personaggio.
	posizione posizione_sud;										//Posizione a sud del personaggio.
	posizione posizione_est;										//Posizione a est del personaggio.
	posizione posizione_ovest;										//Posizione a ovest del personaggio.
	bool nord;														//Variabile che stabilisce se il nord è disponibile.
	bool sud;														//Variabile che stabilisce se il sud è disponibile.
	bool est;														//Variabile che stabilisce se il est è disponibile.
	bool ovest;														//Variabile che stabilisce se il ovest è disponibile.

	stringa direzioni = "";											//Stringa contenente le varie direzioni percorribili.

	cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));		//Assegnazione del valore corrispondente alla cella attuale della mappa.

	direzioni = allocare_stringa(direzioni, 0);						//Allocazione della stringa "direzioni".
	direzioni = scrivere_stringa(direzioni, "");					//Inizializzazione della stringa "direzioni"
	direzioni = strcat(direzioni, "Direzioni disponibili: ");		//Assegnazione di un valore alla stringa "direzioni"

	posizione_nord = posizione_sud = posizione_est = posizione_ovest = pos;		//Assegnazione alle varie variabili di posizione lo stesso valore della posizione del personaggio.

	scrivere_y(&posizione_nord, leggere_y(pos) - 1);				//Modifica di "posizione_nord" per impostarla a nord della posizione del personaggio.
	scrivere_y(&posizione_sud, leggere_y(pos) + 1);					//Modifica di "posizione_sud" per impostarla a sud della posizione del personaggio.
	scrivere_x(&posizione_est, leggere_x(pos) + 1);					//Modifica di "posizione_est" per impostarla a est della posizione del personaggio.
	scrivere_x(&posizione_ovest, leggere_x(pos) - 1);				//Modifica di "posizione_ovest" per impostarla a ovest della posizione del personaggio.

	/**
	 * Se la cella attuale contiene l'elemento PORTA_CHIUSA_SFONDABILE, PORTA_SEMPLICE o PORTA_RE tra i suoi divisori,
	 * si controlla se la cella nella posizione in corrispondenza di ogni punto cardinale è diversa da un muro
	 * e se questa è uguale alla posizione precedente del giocatore. Se queste condizioni sono entrambi vere,
	 * allora la variabile diverrà true e la direzione sarà segnata come disponibile.
	 * Se la cella attuale non contiene nessuno di quei tre elementi, viene controllata la sola presenza di un muro nella posizione
	 * in corrispondenza di ogni punto cardinale. Se questo non è presente, la variabile diverrà true e 
	 * la direzione sarà segnata come disponibile.
	*/

	if(cella_attuale % PORTA_CHIUSA_SFONDABILE == 0 || cella_attuale % PORTA_SEMPLICE == 0 || cella_attuale % PORTA_RE == 0)
	{
		nord = leggere_valore_matrice(mappa, leggere_y(pos) - 1, leggere_x(pos)) != MURO && (leggere_y(posizione_precedente) == leggere_y(posizione_nord) && leggere_x(posizione_precedente) == leggere_x(posizione_nord));
		sud = leggere_valore_matrice(mappa, leggere_y(pos) + 1, leggere_x(pos)) != MURO && (leggere_y(posizione_precedente) == leggere_y(posizione_sud) && leggere_x(posizione_precedente) == leggere_x(posizione_sud));
		est = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos) + 1) != MURO && (leggere_y(posizione_precedente) == leggere_y(posizione_est) && leggere_x(posizione_precedente) == leggere_x(posizione_est));
		ovest = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos) - 1) != MURO && (leggere_y(posizione_precedente) == leggere_y(posizione_ovest) && leggere_x(posizione_precedente) == leggere_x(posizione_ovest));
	}
	else
	{
		nord = leggere_valore_matrice(mappa, leggere_y(pos) - 1, leggere_x(pos)) != MURO;
		sud = leggere_valore_matrice(mappa, leggere_y(pos) + 1, leggere_x(pos)) != MURO;
		est = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos) + 1) != MURO;
		ovest = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos) - 1) != MURO;
	}

	/**
	 * Se le variabili corrispondenti ai punti cardinali sono vere, la direzione sarà concatenata alla stringa "direzioni".
	*/

	if(nord)
		direzioni = strcat(direzioni, "NORD - ");					//Concatenazione della direzione nord alla stringa "direzioni".
	if(sud)
		direzioni = strcat(direzioni, "SUD - ");					//Concatenazione della direzione sud alla stringa "direzioni".
	if(est)
		direzioni = strcat(direzioni, "EST - ");					//Concatenazione della direzione est alla stringa "direzioni".
	if(ovest)
		direzioni = strcat(direzioni, "OVEST - ");					//Concatenazione della direzione ovest alla stringa "direzioni".

	/**
	 * Con le successive due istruzioni viene sovrascritto lo spazio successivo all'ultima delle direzioni disponibili
	 * con un carattere di new line e il carattere successivo viene sovrascritto dal carattere di fine stringa.
	 * È stato fatto ciò allo scopo di migliorare esteticamente il messaggio delle direzioni.
	*/

	direzioni[leggere_lunghezza(direzioni) - 3] = '\n';
	direzioni[leggere_lunghezza(direzioni) - 2] = '\0';

	return direzioni;												//Restituzione della stringa contenente le direzioni disponibili.
}

void muovere_personaggio(stringa direzione)
{
	stringa stringa_file = "";										//Stringa in cui verrà inserito il contenuto dei file di testo.
	int cella_successiva;											//Cella il cui il personaggio si troverà dopo lo spostamento
	int cella_attuale;												//Cella in cui il personaggio si trova attualmente.
	posizione posizione_nord;										//Posizione a nord del personaggio.
	posizione posizione_sud;										//Posizione a sud del personaggio.
	posizione posizione_est;										//Posizione a est del personaggio.
	posizione posizione_ovest;										//Posizione a ovest del personaggio.

	posizione_nord = posizione_sud = posizione_est = posizione_ovest = pos;		//Assegnazione alle varie variabili di posizione lo stesso valore della posizione del personaggio.

	scrivere_y(&posizione_nord, leggere_y(pos) - 1);				//Modifica di "posizione_nord" per impostarla a nord della posizione del personaggio.
	scrivere_y(&posizione_sud, leggere_y(pos) + 1);					//Modifica di "posizione_sud" per impostarla a sud della posizione del personaggio.
	scrivere_x(&posizione_est, leggere_x(pos) + 1);					//Modifica di "posizione_est" per impostarla a est della posizione del personaggio.
	scrivere_x(&posizione_ovest, leggere_x(pos) - 1);				//Modifica di "posizione_ovest" per impostarla a ovest della posizione del personaggio.

	cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));		//Assegnazione del valore corrispondente alla cella attuale della mappa.

	/**
	 * Questa sequenza di selezioni ci permette di confrontare la stringa "direzione" passata in input dalla funzione
	 * con i vari punti cardinali. Dentro ogni selezione viene prima impostata la cella successiva in base al punto cardinale
	 * con cui si sta confrontando attualmente la direzione, poi si controlla che questa non contenga un muro.
	 * Se contiene un muro, lo spostamento non avviene e viene stampato un file di testo che avverte della presenza di esso,
	 * altrimenti si procede con i controlli. Quindi è presente un altro controllo che verifica che la cella attuale contenga una porta:
	 * in questo caso l'unica direzione consentita sarà quella da cui siamo venuti. Quindi, dopo aver controllato che la posizione
	 * corrispondente al punto cardinale in questione è uguale alla posizione precedente, viene effettuato lo spostamento aggiornando
	 * prima la posizione precedente e poi aggiornando le coordinate interessate della posizione corrente, stampando le nuove direzioni
	 * disponibili e richiamando la funzione che ci permette di gestire la cella. Altrimenti verrà visualizzato un messaggio che ci
	 * avverte della presenza della porta e lo spostamento non avverrà.
	 * Se la cella attuale non contiene nessuna porta, vengono effettuate direttamente le operazioni di spostamento sopra descritte.
	*/

	if(confrontare_stringhe(direzione, "nord"))
	{
		cella_successiva = leggere_valore_matrice(mappa, leggere_y(pos) - 1, leggere_x(pos));		//Assegnazione del valore corrispondente alla cella a nord della mappa.
		if(cella_successiva != MURO)
		{
			if(cella_attuale % PORTA_CHIUSA_SFONDABILE == 0 || cella_attuale % PORTA_SEMPLICE == 0 || cella_attuale % PORTA_RE == 0)
			{
				if(leggere_y(posizione_precedente) != leggere_y(posizione_nord) || leggere_x(posizione_precedente) != leggere_x(posizione_nord))
				{
					rallentare_output("C'e' una porta chiusa davanti a te! Cerca un modo per superarla...\n", MILLISECONDI);		//Visualizzazione messaggio porta.
					rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);		//Visualizzazione lenta delle direzioni disponibili.
				}
				else
				{
					posizione_precedente = pos;						//Aggiornamento posizione precedente.
					scrivere_y(&pos, leggere_y(pos) - 1);			//Modifica della posizione attuale decrementando la y.
					rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);		//Visualizzazione lenta delle direzioni disponibili.
					printf("\n");									//Stampa carattere di new line.
					gestire_cella();								//Chiamata della funzione per la gestione delle celle.
				}
			}
			else
			{
				posizione_precedente = pos;							//Aggiornamento posizione precedente.
				scrivere_y(&pos, leggere_y(pos) - 1);				//Modifica della posizione attuale decrementando la y.
				rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);		//Visualizzazione lenta delle direzioni disponibili.
				printf("\n");										//Stampa carattere di new line.
				gestire_cella();									//Chiamata della funzione per la gestione delle celle.
			}
		}
		else
		{
			stringa_file = leggere_file_testo("storia/muri/muro1.txt", stringa_file);		//Assegnazione a stringa_file del contenuto del file di testo.
			rallentare_output(stringa_file, MILLISECONDI);			//Visualizzazione lenta del contenuto del file di testo.
		}
	}

	if(confrontare_stringhe(direzione, "sud"))
	{
		cella_successiva = leggere_valore_matrice(mappa, leggere_y(pos) + 1, leggere_x(pos));		//Assegnazione del valore corrispondente alla cella a sud della mappa.
		if(cella_successiva != MURO)
		{
			if(cella_attuale % PORTA_CHIUSA_SFONDABILE == 0 || cella_attuale % PORTA_SEMPLICE == 0 || cella_attuale % PORTA_RE == 0)
			{
				if(leggere_y(posizione_precedente) != leggere_y(posizione_sud) || leggere_x(posizione_precedente) != leggere_x(posizione_sud))
				{
					rallentare_output("C'e' una porta chiusa davanti a te! Cerca un modo per superarla...\n", MILLISECONDI);		//Visualizzazione messaggio porta.
					rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);		//Visualizzazione lenta delle direzioni disponibili.
				}
				else
				{
					posizione_precedente = pos;						//Aggiornamento posizione precedente.
					scrivere_y(&pos, leggere_y(pos) + 1);			//Modifica della posizione attuale incrementando la y.
					rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);		//Visualizzazione lenta delle direzioni disponibili.
					printf("\n");									//Stampa carattere di new line.
					gestire_cella();								//Chiamata della funzione per la gestione delle celle.
				}
			}
			else
			{
				posizione_precedente = pos;							//Aggiornamento posizione precedente.
				scrivere_y(&pos, leggere_y(pos) + 1);				//Modifica della posizione attuale incrementando la y.
				rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);		//Visualizzazione lenta delle direzioni disponibili.
				printf("\n");										//Stampa carattere di new line.
				gestire_cella();									//Chiamata della funzione per la gestione delle celle.
			}
		}
		else
		{
			stringa_file = leggere_file_testo("storia/muri/muro2.txt", stringa_file);		//Assegnazione a stringa_file del contenuto del file di testo.
			rallentare_output(stringa_file, MILLISECONDI);			//Visualizzazione lenta del contenuto del file di testo.
		}
	}

	if(confrontare_stringhe(direzione, "ovest"))
	{
		cella_successiva = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos) - 1);		//Assegnazione del valore corrispondente alla cella a sud della mappa.
		if(cella_successiva != MURO)
		{
			if(cella_attuale % PORTA_CHIUSA_SFONDABILE == 0 || cella_attuale % PORTA_SEMPLICE == 0 || cella_attuale % PORTA_RE == 0)
			{
				if(leggere_y(posizione_precedente) != leggere_y(posizione_ovest) || leggere_x(posizione_precedente) != leggere_x(posizione_ovest))
				{
					rallentare_output("C'e' una porta chiusa davanti a te! Cerca un modo per superarla...\n", MILLISECONDI);		//Visualizzazione messaggio porta.
					rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);		//Visualizzazione lenta delle direzioni disponibili.
				}
				else
				{
					posizione_precedente = pos;						//Aggiornamento posizione precedente.
					scrivere_x(&pos, leggere_x(pos) - 1);			//Modifica della posizione attuale decrementando la x.
					rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);		//Visualizzazione lenta delle direzioni disponibili.
					printf("\n");									//Stampa carattere di new line.
					gestire_cella();								//Chiamata della funzione per la gestione delle celle.
				}
			}
			else
			{
				posizione_precedente = pos;							//Aggiornamento posizione precedente.
				scrivere_x(&pos, leggere_x(pos) - 1);				//Modifica della posizione attuale decrementando la x.
				rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);		//Visualizzazione lenta delle direzioni disponibili.
				printf("\n");										//Stampa carattere di new line.
				gestire_cella();									//Chiamata della funzione per la gestione delle celle.
			}
		}
		else
		{
			stringa_file = leggere_file_testo("storia/muri/muro3.txt", stringa_file);		//Assegnazione a stringa_file del contenuto del file di testo.
			rallentare_output(stringa_file, MILLISECONDI);			//Visualizzazione lenta del contenuto del file di testo.
		}
	}

	if(confrontare_stringhe(direzione, "est"))
	{
		cella_successiva = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos) + 1);		//Assegnazione del valore corrispondente alla cella a sud della mappa.
		if(cella_successiva != MURO)
		{
			if(cella_attuale % PORTA_CHIUSA_SFONDABILE == 0 || cella_attuale % PORTA_SEMPLICE == 0 || cella_attuale % PORTA_RE == 0)
			{
				if(leggere_y(posizione_precedente) != leggere_y(posizione_est) || leggere_x(posizione_precedente) != leggere_x(posizione_est))
				{
					rallentare_output("C'e' una porta chiusa davanti a te! Cerca un modo per superarla...\n", MILLISECONDI);		//Visualizzazione messaggio porta.
					rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);		//Visualizzazione lenta delle direzioni disponibili.
				}
				else
				{
					posizione_precedente = pos;						//Aggiornamento posizione precedente.
					scrivere_x(&pos, leggere_x(pos) + 1);			//Modifica della posizione attuale incrementando la x.
					rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);		//Visualizzazione lenta delle direzioni disponibili.
					printf("\n");									//Stampa carattere di new line.
					gestire_cella();								//Chiamata della funzione per la gestione delle celle.
				}
			}
			else
			{
				posizione_precedente = pos;							//Aggiornamento posizione precedente.
				scrivere_x(&pos, leggere_x(pos) + 1);				//Modifica della posizione attuale incrementando la x.								
				rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);		//Visualizzazione lenta delle direzioni disponibili.
				printf("\n");										//Stampa carattere di new line.
				gestire_cella();									//Chiamata della funzione per la gestione delle celle.
			}
		}
		else
		{
			stringa_file = leggere_file_testo("storia/muri/muro4.txt", stringa_file);		//Assegnazione a stringa_file del contenuto del file di testo.
			rallentare_output(stringa_file, MILLISECONDI);			//Visualizzazione lenta del contenuto del file di testo.
		}
	}
}
