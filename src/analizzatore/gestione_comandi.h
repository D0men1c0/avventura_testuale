/*
 * Il seguente modulo si occupa di introdurre le funzioni legate alle tre tipologie di comando riconosciute dall'analizzatore,
 * ovvero gestire i comandi globali (aiuto, salva, carica, nuova), gestire le azioni in partita(verbo + nome + nome) e la gestione
 * dei movimenti (questi ultimi potrebbero essere confusi con le azioni in partita ma si è preferito suddividerli in quanto i
 * movimenti vengono gestiti diversamente rispetto alle altre azioni).
 *
 * La funzione gestire_comandi_globali richiama al suo interno una delle quattro possibili alternative:
 * - iniziare_partita se il primo token è "nuova";
 * - stampare_aiuto se il primo token è "aiuto";
 * - salvare_partita se il primo token è "salva";
 * - caricare_partita se il primo token è "carica".
 *
 * La funzione gestire_azioni_partita, invece richiama:
 * - visualizzare_attributi se il primo token è "visualizza" e il secondo è "attributi";
 * - visualizzare_mappa se il primo token è "visualizza" e il secondo è "mappa";
 * - visualizzare_inventario se il primo token è "visualizza" e il secondo è "inventario";
 * - esaminare_stanza se il primo token è "esamina" e il secondo è "stanza";
 * - aprire_porta se il primo token è "apri" e il secondo è "porta";
 * - aprire_botola se il primo token è "apri" e il secondo è "botola";
 * - sfondare_botola se il primo token è "sfonda" e il secondo è "porta";
 * - prendere_chiave se il primo token è "prendi" e il secondo è "chiave";
 * - prendere_frammento se il primo token è "prendi" e il secondo è "frammento" e (non necessariamente) il terzo è "mappa";
 *
 * La funzione gestire_movimenti, invece, non fa altro che richiamare la funzione di muovere_personaggio passandogli come
 * parametro la direzione letta (nord/sud/est/ovest). Il controllo verrà poi preso da questa funzione.
 */

#ifndef GESTIONE_COMANDI_H
#define GESTIONE_COMANDI_H

bool gestire_comandi_globali();
bool gestire_azioni_partita();
void gestire_movimenti();

#endif
