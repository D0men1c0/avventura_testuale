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
#include "../utility/array/matrice.h"
#include "../utility/stringa/stringa.h"
#include "../gestione_file/gestione_file.h"
#include "gestione_avventura.h"
#include "gestione_mappa.h"
#include "gestione_movimenti.h"
#include "../personaggio/personaggio.h"
#include "../inventario/gestione_inventario.h"

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
		rallentare_output("Non c'e' niente di interessante qui!\n\n", MILLISECONDI);		//Chiamata della funzione che permette di rallentare l'output.
	}
	else
	{
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
			rallentare_output(stringa_file, MILLISECONDI);									//Chiamata della funzione che permette di rallentare l'output della stringa.
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
			rallentare_output("\nC'e' una porta chiusa davanti a te!\n", MILLISECONDI);		//Chiamata della funzione che permette di rallentare l'output.
		}

		/**
		 * Se la cella attuale contiene l'elemento BOTOLE tra i suoi divisori, viene stampato un messaggio che avvisa il giocatore
		 * dell'ostacolo incontrato.
		 */

		if(cella_attuale % BOTOLE == 0)
		{
			rallentare_output("Davanti a te c'e' una botola!\n\n", MILLISECONDI);			//Chiamata della funzione che permette di rallentare l'output.
		}
	}

	scrivere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos), cella_attuale);			//Modifica effettiva della mappa con le celle aggiornate.

	free(nome_file);																		//Deallocazione della stringa nome_file.
}
