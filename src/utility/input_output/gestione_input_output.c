/**
 * La funzione ritardare_programma riceve in input i millisecondi e blocca l'esecuzione del programma per quei millisecondi utilizzando la libreria time.h
 * La funzione rallentare_output stampa il messaggio dato in input, rallentandolo di tot millisecondi(sempre dati in input). All'interno di questa funzione,
 * inoltre, viene effettuato il controllo sul colore, cioè se un carattere è #, allora verrà richiamata la funzione apposita, cioè controllare_colore. Quest'ultima
 * ha in input la stessa stringa di rallentare_output e in più anche l'indice da dove incominciare il controllo(cioè della posizione di #). Se è stata inserita la
 * costante per il cambio di colore, allora verrà cambiato colore e restituito la lunghezza della costante(serve per non stampare a video la costante) altrimenti
 * verrà restituito 0 e si continuerà a leggere la stringa. La funzione pulire_schermo ripulisce la console attraverso il comando "cls".
 * Per le funzioni di input è presente leggere_intero_tastiera che legge un numero attraverso la funzione scanf mentre leggere_stringa_tastiera legge un'intera
 * stringa attraverso la funzione fgets(si è evitata la scanf con le stringhe in quanto appena si incontrava uno spazio veniva ignorato quello che c'era dopo). E'
 * presente anche la funzione leggi_linea che ripulisce tutti i caratteri presenti nel buffer dopo la funzione di leggere_intero_tastiera.
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../stringa/stringa.h"
#include "gestione_input_output.h"


//DEFINIZIONE COLORI


#define STRINGA_COLORE_ROSSO "COLORE_ROSSO#"				//Costante stringa rappresentante il colore rosso.
#define STRINGA_COLORE_VERDE "COLORE_VERDE#"				//Costante stringa rappresentante il colore verde.
#define STRINGA_COLORE_GIALLO "COLORE_GIALLO#"				//Costante stringa rappresentante il colore giallo.
#define STRINGA_COLORE_BLU "COLORE_BLU#"					//Costante stringa rappresentante il colore blu.
#define STRINGA_COLORE_CIANO  "COLORE_CIANO#"				//Costante stringa rappresentante il colore ciano.
#define STRINGA_COLORE_PORPORA 	"COLORE_PORPORA#"			//Costante stringa rappresentante il colore porpora.
#define STRINGA_COLORE_BIANCO "COLORE_BIANCO#"				//Costante stringa rappresentante il colore bianco.

void leggi_linea();											//Funzione per la lettura di una linea di input da tastiera.
int controllare_colore(stringa messaggio, int indice);		//Funzione per controllare il colore presente in una stringa e successivamente colorarla.

void ritardare_programma(int millisecondi)
{
    setbuf(stdout, NULL);                                   //Disabilitazione del buffering su stdout.
    long ticks;                                             //Variabile contenente i tick presenti nella quantità  di tempo desiderata.
    clock_t tempo_attuale;									//Variabile contenente il tempo attuale.
    clock_t tempo_iniziale;									//Variabile contenente il tempo iniziale.

    /**
     * La costante CLOCK_PER_SEC contiene il numero di tick presenti in un secondo. Per ottenere la quantità  in millisecondi
     * bisogna quindi dividere tale costante per mille e, per ottenere i tick desiderati per il tempo da noi scelto, è sufficiente
     * moltiplicare il risultato per i millisecondi desiderati.
    */
    ticks = millisecondi * (CLOCKS_PER_SEC / 1000);

    tempo_iniziale = clock();                               //Assegnazione dei tick trascorsi dall'avvio del programma.
    tempo_attuale = tempo_iniziale;                         //Impostazione del tempo attuale alla stessa quantità  del tempo iniziale.

    /**
     * Tramite questa struttura di ripetizione si confronta la differenza tra i tick del tempo attuale e quelli del tempo iniziale
     * con il numero dei tick presenti nella quantità  di tempo desiderata. All'interno della struttura il tempo attuale viene
     * costantemente aggiornato. Quando la differenza raggiungerà  i tick previsti, termineranno le ripetizioni e la pausa sarà  avvenuta.
    */
    while(tempo_attuale - tempo_iniziale < ticks)
    {
        tempo_attuale = clock();
    }
}

void rallentare_output(stringa messaggio, int millisecondi)
{
	int lunghezza_colore;									//Variabile contenente la lunghezza della costante del colore all'interno del messaggio.

    int i;	                                                //Indice utilizzato per indicare il carattere corrente della stringa.
    i = 0;                                                  //Inizializzazione a zero dell'indice.

    while (messaggio[i] != '\0')                            //Iterazione che dura finchè non si incontra il carattere di fine stringa.
    {
        if (messaggio[i] != ' ')                            //Struttura di controllo per evitare che il ritardo venga utilizzato su spaziature.
        {
			/**
			 * Se il carattere corrente è #, viene inserita in "lunghezza_colore" la lunghezza della stringa che indica il colore
			 * presente nel messaggio. Successivamente l'indice viene incrementato di quella grandezza per evitare che il ritardo
			 * venga utilizzato su una stringa dei colori.
			*/
        	if(messaggio[i] == '#') 
        	{
        		lunghezza_colore = controllare_colore(messaggio, i+1);		//Chiamata della funzione per controllare il colore del messaggio.
        		i += lunghezza_colore;										//Incremento dell'indice per un valore pari alla lunghezza del colore della stringa.
        	}

        	ritardare_programma(millisecondi);              //Chiamata della funzione per il ritardo.
        }


        printf("%c", messaggio[i]);							//Stampa del carattere corrente.

        i++;												//Incremento dell'indice.
  	}
}

int controllare_colore(stringa messaggio, int indice)
{
	int lunghezza_colore;									//Variabile che conterrÃ  la lunghezza della stringa indicante il colore del messaggio.
	stringa colore = "";									//Stringa in cui andrÃ  il valore della stringa indicante il colore del messaggio.
	bool esito;												//Variabile che indica l'esito del controllo della presenza del colore.

	esito = false;											//Inizializzazione a false di "esito".
	lunghezza_colore = 0;									//Inizializzazione a 0 di "lunghezza_stringa".
	
	colore = allocare_stringa(colore, 0);					//Allocazione della stringa che conterrÃ  il colore del messaggio.

	/**
	 * Questa struttura di ripetizione serve a controllare la presenza di un colore nel messaggio.
	 * Quindi comincia ad inserire in "colore" (che usa lunghezza_colore come indice) i caratteri presenti nel messaggio,
	 * finchè non trova il carattere #. Se lo trova, la struttura di ripetizione si interrompe, altrimenti prosegue fino alla fine del
	 * messaggio, lasciando la variabile "esito" pari a false.
	*/

	while(indice < leggere_lunghezza(messaggio) && esito == false)
	{
		if(messaggio[indice] == '#')						//Struttura di controllo che verifica la presenza del carattere #.
		{
			esito = true;									//Se il carattere # è presente, esito diventerà  true.
		}

		colore[lunghezza_colore] = messaggio[indice];		//Assegnazione del carattere corrente di colore con il carattere corrente di messaggio.

		lunghezza_colore++;									//Incremento della variabile che indica lunghezza del colore.
		indice++;											//Incremento dell'indice della struttura di ripetizione.
	}

	colore[lunghezza_colore] = '\0';						//Assegnazione del carattere di fine stringa all'ultima posizione di "colore".


	if(esito == true)										//Struttura di controllo che contiene le istruzioni che si verificano se "esito" è true.
	{
		lunghezza_colore++;									//Incremento della lunghezza del colore.

		if(confrontare_stringhe(colore, STRINGA_COLORE_ROSSO))		//Struttura di controllo che verifica che "colore" è uguale alla stringa indicante il colore rosso.
		{
			printf(COLORE_ROSSO);							//Stampa che serve a colorare i successivi messaggi di rosso.
		}
		else if(confrontare_stringhe(colore, STRINGA_COLORE_BLU))		//Struttura di controllo che verifica che "colore" è uguale alla stringa indicante il colore blu.
		{
			printf(COLORE_BLU);								//Stampa che serve a colorare i successivi messaggi di blu.
		}
		else if(confrontare_stringhe(colore, STRINGA_COLORE_GIALLO))	//Struttura di controllo che verifica che "colore" è uguale alla stringa indicante il colore giallo.
		{
			printf(COLORE_GIALLO);							//Stampa che serve a colorare i successivi messaggi di giallo.
		}
		else if(confrontare_stringhe(colore, STRINGA_COLORE_VERDE))		//Struttura di controllo che verifica che "colore" è uguale alla stringa indicante il colore verde.
		{
			printf(COLORE_VERDE);							//Stampa che serve a colorare i successivi messaggi di verde.
		}
		else if(confrontare_stringhe(colore, STRINGA_COLORE_CIANO))		//Struttura di controllo che verifica che "colore" è uguale alla stringa indicante il colore ciano.
		{
			printf(COLORE_CIANO);							//Stampa che serve a colorare i successivi messaggi di ciano.
		}
		else if(confrontare_stringhe(colore, STRINGA_COLORE_PORPORA))	//Struttura di controllo che verifica che "colore" è uguale alla stringa indicante il colore porpora.
		{
			printf(COLORE_PORPORA);							//Stampa che serve a colorare i successivi messaggi di porpora.
		}
		else if(confrontare_stringhe(colore, STRINGA_COLORE_BIANCO))	//Struttura di controllo che verifica che "colore" è uguale alla stringa indicante il colore bianco.
		{
			printf(COLORE_BIANCO);							//Stampa che serve a colorare i successivi messaggi di bianco.
		}
		else
		{
			lunghezza_colore = 0;							//Assegnazione di "lunghezza_colore" a zero nel caso in cui "colore" non sia uguale a nessuna delle stringhe indicanti colori.
		}
	}

	if(esito == false)										//Se esito è uguale a false, la lunghezza del colore sarà  uguale a zero.
	{
		lunghezza_colore = 0;								//Assegnazione di "lunghezza_colore" a zero.
	}

	free(colore);											//Deallocazione della stringa "colore".

	return lunghezza_colore;								//Restituzione della lunghezza del colore.
}


void pulire_schermo()
{
    system("cls");                                          //Istruzione per la pulizia lo schermo.
}

int leggere_intero_tastiera()
{
	int valore;												//Variabile in cui andrà l'intero letto da tastiera.

	scanf("%d", &valore);									//Chiamata della funzione di stdin per la lettura di un intero da tastiera.

	leggi_linea();											//Chiamata della funzione che legge una linea di input da tastiera.

	return valore;											//Restituzione dell'intero letto da tastiera.
}

stringa leggere_stringa_tastiera(stringa str)
{
	str = allocare_stringa(str, 0);							//Allocazione della stringa da leggere.

	fgets (str, sizeof(char) * DIM_STRINGA, stdin);			//Chiamata della funzione che permette di leggere una stringa da tastiera.

	/**
	 * Se la lunghezza della stringa è maggiore di zero e il penultimo carattere è \n, allora questo sarà  sovrascritto dal carattere
	 * di fine stringa.
	*/

	if ((leggere_lunghezza(str) > 0) && (str[leggere_lunghezza (str) - 1] == '\n'))
		str[leggere_lunghezza(str) - 1] = '\0';				//Modifica del penultimo carattere della stringa col carattere di fine stringa.

	return str;												//Restituzione della stringa letta da tastiera.
}

void leggi_linea()
{
	int c;													//Variabile in cui andranno i valori letti da tastiera.
	
	/**
	 * La struttura di ripetizione terminerà  quando "c" sarà uguale al carattere EOF oppure al carattere di new line
	*/

	do
	{
	    c = getchar();										//Lettura dei valori da tastiera.
	}
	while(c != EOF && c != '\n');
}
