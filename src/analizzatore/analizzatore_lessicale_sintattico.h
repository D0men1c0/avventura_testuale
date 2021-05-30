/*
 * Questo modulo si occupa di effettuare l'analisi lessicale e sintattica. Per quanto riguarda l'analisi lessicale
 * due funzioni sono associate ad essa, cio�: la prima funzione estrarre_token si occupa di estrarre i token dalla sorgente
 * passata in input separati da spazi, dopodich� ogni token verr� scansionato dalla funzione scansionare_token ed in base al
 * riconoscimento o meno del token verr� restituito un esito ed inserito il token all'interno della tabella dei simboli.
 * Per quanto riguarda l'analisi sintattica, la funzione ad essa legata � controllare_simboli_tabella che controlla la struttura
 * dei vari token inseriti nella tabella dei simboli e richiama (se la struttura � esatta) una delle tre funzioni possibili,
 * cio�: gestire_movimenti, gestire_comandi_globali e gestire_azioni_partita. L'obiettivo di questa funzione � quello di controllare
 * solamente se la struttura � esatta, ad esempio VRB + PRL ma non se quella specifica coppia "prendi" + "stanza" � accettata.
 */

#ifndef ANALIZZATORE_LESSICALE_SINTATTICO_H
#define ANALIZZATORE_LESSICALE_SINTATTICO_H

#include "../utility/utility.h"

//ANALISI LESSICALE
stringa estrarre_token(stringa sorgente);
bool scansionare_token(stringa token, int indice);

//ANALISI SINTATTICA
bool controllare_simboli_tabella();

#endif
