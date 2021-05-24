/**
 * Il seguente modulo, presenta al suo interno la funzione leggere_file_bin che serve per poter leggere i vari caratteri presenti in un
 * file binari e memorizzarli.
 * Perciò la funzione ha come parametri il nome del file binario su cui si andrà ad operare, e stringa_file che è la stringa in cui
 * si dovranno aggiornare i suoi elementi.
 */
#ifndef LETTURA_FILE_H
#define LETTURA_FILE_H

#include "../utility/utility.h"
#include "../personaggio/personaggio.h"
#include "../inventario/gestione_inventario.h"

bool leggere_file_salvataggio(stringa nome_file);
bool accodare_file_salvataggio(stringa nome_file, personaggio giocatore, inventario inv, matrice mappa, posizione pos);

/**
 * Il seguente modulo, presenta al suo interno la funzione leggere_file_testo che serve per poter leggere i vari caratteri presenti in un
 * file di testo e memorizzarli.
 * Perciò la funzione ha come parametri il nome del file di testo su cui si andrà ad operare, e stringa_file che è la stringa in cui
 * si dovranno aggiornare i suoi elementi.
 */
stringa leggere_file_testo(stringa nome_file, stringa stringa_file);
void leggere_mappa_file(stringa nome_file);
stringa leggere_file_storia(stringa nome_file, stringa stringa_file);

#endif
