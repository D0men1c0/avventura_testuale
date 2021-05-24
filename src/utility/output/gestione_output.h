/**
 * Il seguente modulo contiene funzioni utili alla gestione dell'output di una stringa in modalità "lenta".
 * Ciò è reso possibile attraverso una funzione che permette di ottenere un delay sul programma, così da poterlo
 * sfruttare per visualizzare una qualsiasi stringa più lentamente e dare quindi un effetto migliore anche agli occhi del giocatore.
 * Nello specifico è presente la funzione "ritardare_programma" grazie alla quale, dando in input i millisecondi, è possibile
 * ottenere un delay di quella tempistica. Nella funzione "rallentare_output" invece ci sono istruzioni utili alla stampa
 * di un messaggio attraverso l'utilizzo del delay ottenuto con la precedente funzione. La funzione "pulire_schermo" infine
 * ha il solo compito di ripulire il CMD da tutti i messaggi.
 */

#ifndef GESTIONE_OUTPUT_H
#define GESTIONE_OUTPUT_H

#include "../stringa/stringa.h"


void ritardare_programma(int millisecondi);
void rallentare_output(stringa messaggio, int millisecondi);
void pulire_schermo();

#endif
