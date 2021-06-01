/**
 * Questo modulo contiene tutte le informazioni necessarie alla gestione dell'inventario. È presente una struttura contenente
 * una serie di valori booleani che rappresentano la presenza o meno di un determinato oggetto nell'inventario.
 * Sono presenti poi tutte le funzioni utili alla lettura e alla modifica dei valori presenti nella struttura appena descritta.
 * Poi questo modulo si occupa di descrivere la funzione che inizializza l'inventario, settando tutti i valori della struttura a false,
 * eccezion fatta per il frammento ovest della mappa. Un'altra funzione descritta è quella che si occupa di visualizzare a video l'inventario.
 * L'ultima funzione presente è quella che si occupa di visualizzare i frammenti della mappa che il giocatore possiede nell'inventario,
 * evitando di mostrare quindi anche quelli da lui non ancora raccolti.
*/

#include "../utility/utility.h"
#include "../gestione_avventura/gestione_avventura.h"

#ifndef GESTIONE_INVENTARIO_H
#define GESTIONE_INVENTARIO_H

//Struttura di dati che descrive l'inventario del giocatore.
typedef struct
{
	bool frammento_mappa_est;								//Valore che dice se è presente il frammento est della mappa.
	bool frammento_mappa_ovest;								//Valore che dice se è presente il frammento ovest della mappa.
	bool frammento_mappa_nord;								//Valore che dice se è presente il frammento nord della mappa.
	bool frammento_mappa_sud;								//Valore che dice se è presente il frammento sud della mappa.
	bool chiave_semplice;									//Valore che dice se è presente la chiave semplice.
	bool chiave_re;											//Valore che dice se è presente la chiave del Re.
}inventario;



//Prototipi funzioni lettura dati dell'inventario.
bool leggere_frammento_est(inventario inv);					//Funzione per la lettura del valore che dice se è presente il frammento est.
bool leggere_frammento_ovest(inventario inv);				//Funzione per la lettura del valore che dice se è presente il frammento ovest.
bool leggere_frammento_nord(inventario inv);				//Funzione per la lettura del valore che dice se è presente il frammento nord.
bool leggere_frammento_sud(inventario inv);					//Funzione per la lettura del valore che dice se è presente il frammento sud.
bool leggere_chiave_semplice(inventario inv);				//Funzione per la lettura del valore che dice se è presente la chiave semplice.
bool leggere_chiave_re(inventario inv);						//Funzione per la lettura del valore che dice se è presente la chiave del Re.

//Prototipi funzioni modifica dati dell'inventario.
void scrivere_frammento_est(inventario *inv, bool valore);		//Funzione per la modifica del valore che dice se è presente il frammento est.
void scrivere_frammento_ovest(inventario *inv, bool valore);	//Funzione per la modifica del valore che dice se è presente il frammento ovest.
void scrivere_frammento_nord(inventario *inv, bool valore);		//Funzione per la modifica del valore che dice se è presente il frammento nord.
void scrivere_frammento_sud(inventario *inv, bool valore);		//Funzione per la modifica del valore che dice se è presente il frammento sud.
void scrivere_chiave_semplice(inventario *inv, bool valore);	//Funzione per la modifica del valore che dice se è presente la chiave semplice.
void scrivere_chiave_re(inventario *inv, bool valore);			//Funzione per la modifica del valore che dice se è presente la chiave del Re.

void inizializza_inventario(inventario *inv);				//Funzione per l'inizializzazione dell'inventario con i valori di default.

void stampare_inventario();									//Funzione per la stampa a video dell'inventario dei giocatori.
stringa visualizzare_frammenti_mappa(stringa risposta);		//Funzione per la visualizzazione dei frammenti di mappa posseduti.

#endif
