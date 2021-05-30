/**
 * Il seguente modulo definisce le costanti che verranno utilizzate durante il corso dell'analisi lessicale, sintattica
 * e gestione dei vari comandi, quindi contiene le costanti legate alle strutture parole chiave ed alla tabella dei simboli.
 * Definisce anche le costanti numeriche per ogni simbolo e ciascuna parola legale riconosciuta dall'analizzatore.
 */

#ifndef COMANDI_H
#define COMANDI_H

#define FILE_SALVATAGGIO "salvataggi.dat"

#define MAX_SIMBOLI 5					// NUMERO DI SIMBOLI PRESENTI NEL LINGUAGGIO
#define MAX_PAROLE 22					// NUMERO DI PAROLE PRESENTI NEL LINGUAGGIO

// costanti simboli
#define MOV 1							// SIMBOLO DEL MOVIMENTO
#define HLP 2							// SIMBOLO DELL'HELP
#define PRH 3							// SIMBOLO DELLE PAROLE LEGATE ALL'HELP
#define VRB 4							// SIMBOLO DEI VERBI
#define PRL 5							// SIMBOLO DELLE PAROLE LEGATE AI VERBI

// HELP
#define NUOVA "nuova"
#define AIUTO "aiuto"
#define CARICA "carica"
#define SALVA "salva"

// PAROLE HELP
#define PARTITA "partita"

// MOVIMENTI
#define NORD "nord"
#define SUD "sud"
#define EST "est"
#define OVEST "ovest"

// VERBI
#define VISUALIZZA "visualizza"
#define ESAMINA "esamina"
#define APRI "apri"
#define SFONDA "sfonda"
#define PRENDI "prendi"

// PAROLE LEGATE AI VERBI
#define ATTRIBUTI "attributi"
#define INVENTARIO "inventario"
#define MAPPA "mappa"
#define BOTOLA "botola"
#define FRAMMENTO "frammento"
#define STANZA "stanza"
#define CHIAVE "chiave"
#define PORTA "porta"

#endif
