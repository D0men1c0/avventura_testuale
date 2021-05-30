/**
 * Il seguente modulo serve per definire tutte le strutture, i tipi di dato e le funzioni legate all'analizzatore(sia lessicale che sintattico).
 * Il tipo di dato simbolo è un intero che identifica la classe di appartenenza di un determinato token, mentre il tipo di dato parola_chiave 
 * è una stringa che rappresenta il token stesso. Per poter gestire questi tipi di dato si è fatto utilizzo di due strutture: la prima è 
 * struttura_parole_chiave in cui vengono salvati tutti i token riconosciuti dall'analizzatore con i rispettivi simboli. L'altra struttura è la
 * tabella simboli in cui, invece, vengono salvati tutti i token letti dalla sorgente con il relativo simbolo. La gestione dell'analisi lessicale e
 * sintattica seguirà nel modulo analizzatore_lessicale_sintattico.h. In questo modulo è presente la funzione inizializzare_strutture_analizzatore 
 * che inizializza i simboli e le parole chiave all'interno della struttura_parole_chiave. Inoltre, la funzione leggere_comando legge da tastiera
 * il comando inserito dall'utente(sorgente) e richiama l'analizzatore lessicale per analizzare i vari token. Seguono le varie funzioni per leggere
 * e scrivere i campi delle due strutture.
 */

#ifndef STRUTTURE_ANALIZZATORE_H
#define STRUTTURE_ANALIZZATORE_H

#include "../utility/utility.h"
#include "comandi.h"

typedef int simbolo;
typedef stringa parola_chiave;

/**
 * STRUTTURA PAROLE CHIAVE
 */
struct{
	parola_chiave parole_chiave[MAX_PAROLE];
	simbolo simboli[MAX_SIMBOLI];
	int numero_parole_chiave[MAX_SIMBOLI];
	int dimensione;
}struttura_parole_chiave;

/**
 * STRUTTURA TABELLA SIMBOLI
 */
struct{
	simbolo simboli[MAX_SIMBOLI];
	parola_chiave token[MAX_SIMBOLI];
	int dimensione;
}tabella_simboli;

// FUNZIONI DI INIZIALIZZAZIONE STRUTTURE E LETTURA DELLA SORGENTE
void inizializzare_strutture_analizzatore();
void leggere_comando();

/**
 * FUNZIONI STRUTTURA PAROLE CHIAVE
 */
int leggere_dimensione_parole_chiave();
int leggere_numero_parole_chiave(int indice);
stringa leggere_parola_chiave_tabella(int indice);
simbolo leggere_simboli_struttura_parole_chiave(int indice);
void scrivere_numero_parola_chiave_struttura_parole_chiave(int indice, int valore);
void scrivere_simboli_struttura_parole_chiave(int indice, simbolo simb);

/**
 * FUNZIONI STRUTTURA TABELLA SIMBOLI
 */
void scrivere_dimensione_tabella_simboli(int dimensione);
int leggere_dimensione_tabella_simboli();
void scrivere_simbolo_tabella_simboli(simbolo simb, int indice);
simbolo leggere_simbolo_tabella_simboli(int indice);
void scrivere_token_tabella_simboli(parola_chiave token, int indice);
parola_chiave leggere_token_tabella_simboli(int indice);

#endif
