/**
 * Il seguente modulo serve per gestire la lettura da file di testo e la lettura e scrittura da file binario.
 * Presenta al suo interno la funzione leggere_file_testo che serve per poter leggere i vari caratteri presenti in un file di testo e
 * memorizzarli all'interno di una stringa.
 * Perciò la funzione ha come parametri il nome del file di testo su cui si andrà ad operare, e stringa_file che è la stringa in cui
 * si dovranno aggiornare i suoi elementi.
 * Funzionamento analogo ha la funzione leggere_mappa_file che non opera su una stringa ma sulla mappa, cioè aggiorna il campo valore
 * in base agli interi letti da file.
 * Funzione analoga a leggere_file_testo è leggere_file_storia con il cambiamento che è richiamata quando la cella viene svuotata dal suo
 * valore con l'apposita funzione, e con il comando "esamina_stanza" per visualizzare il file di testo presente in quella cella, serve per
 * stampare il messaggio "Non c'è nulla di interresante qui" cioè il file vuoto.
 * La funzione accodare_file_salvataggio, riceve in input il nome del file da scrivere, salvando il tipo di dato personaggio, inventario,
 * matrice e posizione restituendo un esito booleano che indica se la scrittura è andata a buon fine(true) o no (false).
 * E' presente la funzione di leggere_file_salvataggio che riceve in input il nome del file BINARIO da aprire e restituisce un esito booleano.
 * Tale funzione serve per caricare da file binario: l'inventario, gli attributi del personaggio, la sua ultima posizione salvata e lo stato
 * della mappa(matrice) salvato in precedenza. Se la lettura è andata a buon fine restituisce come esito = true.
 */
#ifndef GESTIONE_FILE_H
#define GESTIONE_FILE_H

#include "../utility/utility.h"
#include "../inventario/gestione_inventario.h"
#include "../personaggio/gestione_personaggio.h"

bool leggere_file_salvataggio(stringa nome_file);
bool accodare_file_salvataggio(stringa nome_file);
stringa leggere_file_testo(stringa nome_file, stringa stringa_file);
void leggere_mappa_file(stringa nome_file);
stringa leggere_file_storia(stringa nome_file, stringa stringa_file);

#endif
