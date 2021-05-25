/**
 * Questo modulo permette la gestione della mappa e delle sue celle in particolare. Vengono definite una serie di costanti corrispondente ad ogni tipo
 * di elemento che è possibile trovare in cella. Per il muro ho scelto il valore 0 perché non è divisore di alcun numero e per la cella vuota ho scelto
 * il valore 1, perché divisore di ogni numero. Le successive celle sono tutti numeri primi.
 * Questa scelta è stata effettuata sulla base della necessità di poter gestire la presenza di più elementi nella stessa cella: agendo così, infatti,
 * ogni cella sarà divisibile solo per gli elementi lì presenti.
 * La funzione leggere_mappa() ha il compito di leggere la mappa da file, la funzione gestire_cella() ha invece il compito di stabilire il comportamento
 * delle celle nelle quali non sono presenti comandi particolari effettuati dal giocatore oppure la semplice gestione di messaggi di output.
*/

#include <stdio.h>
#include <stdlib.h>
#include "../utility/utility.h"
#include "../gestione_file/gestione_file.h"
#include "gestione_avventura.h"
#include "gestione_mappa.h"
#include "../inventario/gestione_inventario.h"
#include "../personaggio/gestione_personaggio.h"

int leggere_valore_matrice(matrice matrice_a, int riga, int colonna)
{
	return matrice_a[riga][colonna];
}


void scrivere_valore_matrice(matrice matrice_a, int riga, int colonna, int valore)
{
	matrice_a[riga][colonna] = valore;
	return;
}

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
	direzioni = scrivere_stringa(direzioni, "Direzioni disponibili: ");		//Inizializzazione della stringa "direzioni"

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
		direzioni = concatenare_stringhe(direzioni, "NORD - ");					//Concatenazione della direzione nord alla stringa "direzioni".
	if(sud)
		direzioni = concatenare_stringhe(direzioni, "SUD - ");					//Concatenazione della direzione sud alla stringa "direzioni".
	if(est)
		direzioni = concatenare_stringhe(direzioni, "EST - ");					//Concatenazione della direzione est alla stringa "direzioni".
	if(ovest)
		direzioni = concatenare_stringhe(direzioni, "OVEST - ");				//Concatenazione della direzione ovest alla stringa "direzioni".

	/**
	 * Con le successive due istruzioni viene sovrascritto lo spazio successivo all'ultima delle direzioni disponibili
	 * con un carattere di new line e il carattere successivo viene sovrascritto dal carattere di fine stringa.
	 * È stato fatto ciò allo scopo di migliorare esteticamente il messaggio delle direzioni.
	*/

	direzioni[leggere_lunghezza(direzioni) - 3] = '\n';
	direzioni[leggere_lunghezza(direzioni) - 2] = '\0';

	return direzioni;												//Restituzione della stringa contenente le direzioni disponibili.
}

void leggere_mappa(matrice mappa)
{
	leggere_mappa_file("mappa.txt");									//Chiamata della funzione che legge la mappa da file.
}

void gestire_cella()
{
	int cella_attuale;													//Cella in cui il personaggio si trova attualmente.
	stringa nome_file = "";												//Stringa in cui verrà inserito il nome del file di testo da aprire.
	stringa stringa_file = "";											//Stringa in cui verrà inserito il contenuto dei file di testo.

	nome_file = allocare_stringa(nome_file, 0);							//Allocazione della stringa.

	cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));		//Assegnazione del valore corrispondente alla cella attuale della mappa.

	/**
	 * Se la cella attuale è una cella vuota, si procede con la stampa di un messaggio.
	 * In caso contrario si studiano i differenti casi.
	*/

	if(cella_attuale == CELLA_VUOTA)
	{
		printf("--------------------------------------------------------------------------\n\n");
		rallentare_output("Non c'e' niente di interessante qui!\n\n", MILLISECONDI);		//Chiamata della funzione che permette di rallentare l'output.
		printf("--------------------------------------------------------------------------\n\n");
	}

	/**
	 * Se la cella attuale contiene l'elemento STORIA tra i suoi divisori, viene utilizzata una funzione particolare per assegnare alla stringa
	 * "nome_file" un valore specifico, basato sulla posizione del personaggio in quel momento. Successivamente viene aperto un file con il nome
	 * pari al valore di quella stringa e il contenuto viene assegnato a "stringa_file", che poi sarà sfruttata per la stampa del messaggio.
	 * Infine l'elemento STORIA viene rimosso dalla cella attuale per evitare che queste operazioni si ripetino ogni volta che il giocatore passi
	 * sulla stessa cella.
	*/
	if(cella_attuale % STORIA == 0)
	{
		sprintf(nome_file, "storia/[%d][%d].txt", leggere_y(pos), leggere_x(pos));		//Utilizzo della funzione sprintf per assegnare a "nome_file" un valore particolare.
		stringa_file = leggere_file_testo(nome_file, stringa_file);						//Assegnazione a stringa_file del contenuto del file di testo.
		if (confrontare_stringhe(nome_file,"storia/[8][4].txt"))
		{
			rallentare_output(stringa_file, MILLISECONDI);
		}
		else
		{
		printf("--------------------------------------------------------------------------\n\n");
		rallentare_output(stringa_file, MILLISECONDI);									//Chiamata della funzione che permette di rallentare l'output della stringa.
		printf("--------------------------------------------------------------------------\n\n");
		}
		cella_attuale /= STORIA;														//Rimozione dell'elemento STORIA dalla cella attuale.
	}

	/**
	 * Se la cella attuale contiene l'elemento POWER_UP_VITA tra i suoi divisori, vengono incrementate le vite a disposizione del giocatore.
	 * Successivamente l'elemento in questione viene rimosso dalla cella attuale per evitare che questa operazione si ripeta ogni volta
	 * che il giocatore passa sulla stessa cella.
	*/

	if(cella_attuale % POWER_UP_VITA == 0)
	{
		scrivere_vita(&giocatore, leggere_vita(giocatore) + 1);							//Chiamata della funzione scrivere_vita per incrementare le vite a disposizione.
		cella_attuale /= POWER_UP_VITA;													//Rimozione dell'elemento POWER_UP_VITA dalla cella attuale.
	}

	/**
	 * Se la cella attuale contiene l'elemento POWER_UP_FORZA tra i suoi divisori, viene incrementata la forza del giocatore.
	 * Successivamente l'elemento in questione viene rimosso dalla cella attuale per evitare che questa operazione si ripeta ogni volta
	 * che il giocatore passa sulla stessa cella.
	*/

	if(cella_attuale % POWER_UP_FORZA == 0)
	{
		scrivere_forza(&giocatore, leggere_forza(giocatore) + 1);						//Chiamata della funzione scrivere_forza per incrementare la forza.
		cella_attuale /= POWER_UP_FORZA;												//Rimozione dell'elemento POWER_UP_FORZA dalla cella attuale.
	}

	/**
	 * Se la cella attuale contiene l'elemento MALUS tra i suoi divisori, vengono decrementate le vite a disposizione del giocatore.
	 * Successivamente l'elemento in questione viene rimosso dalla cella attuale per evitare che questa operazione si ripeta ogni volta
	 * che il giocatore passa sulla stessa cella.
	*/

	if(cella_attuale % MALUS == 0)
	{
		scrivere_vita(&giocatore, leggere_vita(giocatore) - 1);							//Chiamata della funzione scrivere_vita per decrementare le vite a disposizione.
		cella_attuale /= MALUS;															//Rimozione dell'elemento MALUS dalla cella attuale.
	}

	/**
	 * Se la cella attuale contiene l'elemento PORTA_CHIUSA_SFONDABILE, PORTA_SEMPLICE o PORTA_RE tra i suoi divisori,
	 * viene stampato un messaggio che avvisa il giocatore dell'ostacolo incontrato.
	*/

	if(cella_attuale % PORTA_CHIUSA_SFONDABILE == 0 || cella_attuale % PORTA_SEMPLICE == 0 || cella_attuale % PORTA_RE == 0)
	{
		rallentare_output("C'e' una porta chiusa davanti a te!\n\n", MILLISECONDI);		//Chiamata della funzione che permette di rallentare l'output.
	}

	/**
	 * Se la cella attuale contiene l'elemento BOTOLE tra i suoi divisori, viene stampato un messaggio che avvisa il giocatore
	 * dell'ostacolo incontrato.
	 */

	if(cella_attuale % BOTOLE == 0)
	{
		rallentare_output("Davanti a te c'e' una botola!\n\n", MILLISECONDI);			//Chiamata della funzione che permette di rallentare l'output.
	}

	if(cella_attuale % CELLA_VUOTA == 0)
	{
		rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
		printf("\n");
	}


	scrivere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos), cella_attuale);			//Modifica effettiva della mappa con le celle aggiornate.

	free(nome_file);																		//Deallocazione della stringa nome_file.
}
