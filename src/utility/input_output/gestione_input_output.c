/**
 * Il seguente modulo contiene funzioni utili alla gestione dell'output di una stringa in modalità "lenta".
 * Ciò è reso possibile attraverso una funzione che permette di ottenere un delay sul programma, così da poterlo
 * sfruttare per visualizzare una qualsiasi stringa più lentamente e dare quindi un effetto migliore anche agli occhi del giocatore.
 * Nello specifico è presente la funzione "ritardare_programma" grazie alla quale, dando in input i millisecondi, è possibile
 * ottenere un delay di quella tempistica. Nella funzione "rallentare_output" invece ci sono istruzioni utili alla stampa
 * di un messaggio attraverso l'utilizzo del delay ottenuto con la precedente funzione. La funzione "pulire_schermo" infine
 * ha il solo compito di ripulire il CMD da tutti i messaggi.
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../stringa/stringa.h"
#include "gestione_input_output.h"


//DEFINIZIONE COLORI


#define STRINGA_COLORE_ROSSO "COLORE_ROSSO#"
#define STRINGA_COLORE_VERDE "COLORE_VERDE#"
#define STRINGA_COLORE_GIALLO "COLORE_GIALLO#"
#define STRINGA_COLORE_BLU "COLORE_BLU#"
#define STRINGA_COLORE_CIANO  "COLORE_CIANO#"
#define STRINGA_COLORE_PORPORA 	"COLORE_PORPORA#"
#define STRINGA_COLORE_BIANCO "COLORE_BIANCO#"

void leggi_linea();
int controllare_colore(stringa messaggio, int indice);

void ritardare_programma(int millisecondi)
{
    setbuf(stdout, NULL);                                   //Disabilitazione del buffering su stdout
    long ticks;                                             //Variabile contenente i tick presenti nella quantità di tempo desiderata
    clock_t tempo_attuale;                                  //Variabile contenente il tempo attuale
    clock_t tempo_iniziale;                                 //Variabile contenente il tempo iniziale

    /**
     * La costante CLOCK_PER_SEC contiene il numero di tick presenti in un secondo. Per ottenere la quantità in millisecondi
     * bisogna quindi dividere tale costante per mille e, per ottenere i tick desiderati per il tempo da noi scelto, è sufficiente
     * moltiplicare il risultato per i millisecondi desiderati.
    */
    ticks = millisecondi * (CLOCKS_PER_SEC / 1000);

    tempo_iniziale = clock();                               //Assegnazione dei tick trascorsi dall'avvio del programma
    tempo_attuale = tempo_iniziale;                         //Impostazione del tempo attuale alla stessa quantità del tempo iniziale

    /**
     * Tramite questa struttura di ripetizione si confronta la differenza tra i tick del tempo attuale e quelli del tempo iniziale
     * con il numero dei tick presenti nella quantità di tempo desiderata. All'interno della struttura il tempo attuale viene
     * costantemente aggiornato. Quando la differenza raggiungerà i tick previsti, termineranno le ripetizioni e la pausa sarà avvenuta.
    */
    while(tempo_attuale - tempo_iniziale < ticks)
    {
        tempo_attuale = clock();
    }
}

void rallentare_output(stringa messaggio, int millisecondi)
{
	int pos;

    int i;	                                                //Indice utilizzato per indicare il carattere corrente della stringa
    i = 0;                                                  //Inizializzazione a zero dell'indice

    while (messaggio[i] != '\0')                            //Iterazione che dura finché non si incontra il carattere di fine stringa
    {
        if (messaggio[i] != ' ')                            //Struttura di controllo per evitare che il ritardo venga utilizzato su spaziature
        {
        	if(messaggio[i] == '#')
        	{
        		pos = controllare_colore(messaggio, i+1);
        		i += pos;
        	}

        	ritardare_programma(millisecondi);              //Chiamata della funzione per il ritardo
        }


        printf("%c", messaggio[i]);							//Stampa del carattere corrente

        i++;
  }
}

int controllare_colore(stringa messaggio, int indice)
{
	int lunghezza_colore;
	lunghezza_colore = 0;

	bool esito;
	esito = false;

	stringa colore = "";
	colore = allocare_stringa(colore, 0);

	while(indice < leggere_lunghezza(messaggio) && esito == false)
	{
		if(messaggio[indice] == '#')
		{
			esito = true;
		}

		colore[lunghezza_colore] = messaggio[indice];

		lunghezza_colore++;
		indice++;
	}

	colore[lunghezza_colore] = '\0';


	if(esito == true)
	{
		lunghezza_colore += +1;

		if(confrontare_stringhe(colore, STRINGA_COLORE_ROSSO))
		{
			printf(COLORE_ROSSO);
		}
		else if(confrontare_stringhe(colore, STRINGA_COLORE_BLU))
		{
			printf(COLORE_BLU);
		}
		else if(confrontare_stringhe(colore, STRINGA_COLORE_GIALLO))
		{
			printf(COLORE_GIALLO);
		}
		else if(confrontare_stringhe(colore, STRINGA_COLORE_VERDE))
		{
			printf(COLORE_VERDE);
		}
		else if(confrontare_stringhe(colore, STRINGA_COLORE_CIANO))
		{
			printf(COLORE_CIANO);
		}
		else if(confrontare_stringhe(colore, STRINGA_COLORE_PORPORA))
		{
			printf(COLORE_PORPORA);
		}
		else if(confrontare_stringhe(colore, STRINGA_COLORE_BIANCO))
		{
			printf(COLORE_BIANCO);
		}

		else
		{
			lunghezza_colore = 0;
		}
	}

	if(esito == false)
	{
		lunghezza_colore = 0;
	}

	free(colore);

	return lunghezza_colore;
}


void pulire_schermo()
{
    system("cls");                                          //Istruzione per la pulizia lo schermo
}

int leggere_intero_tastiera()
{
	int intero;

	scanf("%d", &intero);

	leggi_linea();

	return intero;
}

stringa leggere_stringa_tastiera(stringa str)
{
	str = allocare_stringa(str, 0);

	fgets (str, sizeof(char) * DIM_STRINGA, stdin);

	if ((leggere_lunghezza(str) > 0) && (str[leggere_lunghezza (str) - 1] == '\n'))
		str[leggere_lunghezza(str) - 1] = '\0';

	return str;
}

void leggi_linea()
{
	int c;

	do
	{
	    c = getchar();
	}
	while(c != EOF && c != '\n');
}

