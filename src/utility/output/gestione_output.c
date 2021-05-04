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
    int i;                                                  //Indice utilizzato per indicare il carattere corrente della stringa
    i = 0;                                                  //Inizializzazione a zero dell'indice

    while (messaggio[i] != '\0')                            //Iterazione che dura finché non si incontra il carattere di fine stringa
    {
        printf("%c", messaggio[i]);                         //Stampa del carattere corrente
        if (messaggio[i] != ' ')                            //Struttura di controllo per evitare che il ritardo venga utilizzato su spaziature
            ritardare_programma(millisecondi);              //Chiamata della funzione per il ritardo
        i++;
  }
}

void pulire_schermo()
{
    system("cls");                                          //Istruzione per la pulizia lo schermo
}
