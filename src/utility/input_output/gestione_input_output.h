/**
 * Il seguente modulo contiene funzioni utili alla gestione dell'input e dell'output dalla console.
 * Ciò è reso possibile attraverso una funzione che permette di ottenere un delay sul programma(rallentare_output), così da poterlo
 * sfruttare per visualizzare una qualsiasi stringa più lentamente e dare quindi un effetto migliore anche agli occhi del giocatore.
 * Nello specifico è presente la funzione "ritardare_programma" grazie alla quale, dando in input i millisecondi, è possibile
 * ottenere un delay di quella tempistica. La funzione "pulire_schermo" ha il solo compito di ripulire il CMD da tutti i caratteri.
 * Per le funzioni di input è presente leggere_intero_tastiera che legge un numero attraverso la funzione scanf mentre
 * leggere_stringa_tastiera legge un'intera stringa attraverso la funzione fgets(si è evitata la scanf con le stringhe in quanto
 * appena si incontrava uno spazio veniva ignorato quello che c'era dopo).
 */

#ifndef GESTIONE_INPUT_OUTPUT_H
#define GESTIONE_INPUT_OUTPUT_H

#include "../utility.h"

#define MILLISECONDI 35                 						//Costante intera rappresentante i millisecondi di ritardo tra un carattere e l'altro nella visualizzazione lenta di un messaggio normale.
#define MILLISEC_CASTELLO 7                 					//Costante intera rappresentante i millisecondi di ritardo tra un carattere e l'altro nella visualizzazione lenta del castello.
#define MILLISEC_MAPPA 0                    					//Costante intera rappresentante i millisecondi di ritardo tra un carattere e l'altro nella visualizzazione lenta della mappa.
#define MILLISEC_FINALE 45                  					//Costante intera rappresentante i millisecondi di ritardo tra un carattere e l'altro nella visualizzazione lenta del finale.
#define END 5                               					//Costante intera rappresentante i millisecondi di ritardo tra un carattere e l'altro nella visualizzazione lenta della scritta the end.

#define COLORE_ROSSO     	"\033[0;31m"    					//Costante stringa rappresentante il codice per il colore rosso.
#define COLORE_VERDE     	"\033[0;32m"    					//Costante stringa rappresentante il codice per il colore verde.
#define COLORE_GIALLO     	"\033[0;33m"    					//Costante stringa rappresentante il codice per il colore giallo.
#define COLORE_BLU      	"\033[0;34m"    					//Costante stringa rappresentante il codice per il colore blu.
#define COLORE_CIANO  		"\033[0;36m"    					//Costante stringa rappresentante il codice per il colore ciano.
#define COLORE_PORPORA 		"\033[0;35m"    					//Costante stringa rappresentante il codice per il colore porpora.
#define COLORE_BIANCO  		"\033[0;37m"    					//Costante stringa rappresentante il codice per il colore bianco.



void ritardare_programma(int millisecondi);     				//Funzione che permette di ritardare il programma per un tempo pari ai millisecondi passati in input.
void rallentare_output(stringa messaggio, int millisecondi);    //Funzione che permette la visualizzazione lenta di un messaggio.
void pulire_schermo();                      					//Funzione che permette la pulizia completa dello schermo.
int leggere_intero_tastiera();              					//Funzione che permette la lettura di un intero da tastiera.
stringa leggere_stringa_tastiera(stringa str);      			//Funzione che permette la lettura di una stringa da tastiera.

#endif
