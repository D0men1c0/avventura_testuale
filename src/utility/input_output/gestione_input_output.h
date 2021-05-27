/**
 * Il seguente modulo contiene funzioni utili alla gestione dell'output di una stringa in modalità "lenta".
 * Ciò è reso possibile attraverso una funzione che permette di ottenere un delay sul programma, così da poterlo
 * sfruttare per visualizzare una qualsiasi stringa più lentamente e dare quindi un effetto migliore anche agli occhi del giocatore.
 * Nello specifico è presente la funzione "ritardare_programma" grazie alla quale, dando in input i millisecondi, è possibile
 * ottenere un delay di quella tempistica. Nella funzione "rallentare_output" invece ci sono istruzioni utili alla stampa
 * di un messaggio attraverso l'utilizzo del delay ottenuto con la precedente funzione. La funzione "pulire_schermo" infine
 * ha il solo compito di ripulire il CMD da tutti i messaggi.
 */

#ifndef GESTIONE_INPUT_OUTPUT_H
#define GESTIONE_INPUT_OUTPUT_H

#include "../utility.h"

#define MILLISECONDI 0 //35
#define MILLISEC_CASTELLO 7
#define MILLISEC_MAPPA 0
#define MILLISEC_FINALE 45
#define END 5

#define COLORE_ROSSO     "\033[0;31m"
#define COLORE_VERDE     "\033[0;32m"
#define COLORE_GIALLO     "\033[0;33m"
#define COLORE_BLU        "\033[0;34m"
#define COLORE_BIANCO  "\033[0;37m"


void ritardare_programma(int millisecondi);
void rallentare_output(stringa messaggio, int millisecondi);
void pulire_schermo();
int leggere_intero_tastiera();
stringa leggere_stringa_tastiera(stringa str);

#endif
