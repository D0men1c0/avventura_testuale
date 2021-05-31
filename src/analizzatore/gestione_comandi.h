/*
 * Il seguente modulo si occupa di introdurre le funzioni legate alle tre tipologie di comando riconosciute dall'analizzatore,
 * ovvero gestire i comandi globali (aiuto, salva, carica, nuova), gestire le azioni in partita(verbo + nome + nome) e la gestione
 * dei movimenti (questi ultimi potrebbero essere confusi con le azioni in partita ma si � preferito suddividerli in quanto i
 * movimenti vengono gestiti diversamente rispetto alle altre azioni).
 *
 * La funzione gestire_comandi_globali richiama al suo interno una delle quattro possibili alternative:
 * - iniziare_partita se il primo token � "nuova";
 * - stampare_aiuto se il primo token � "aiuto";
 * - salvare_partita se il primo token � "salva";
 * - caricare_partita se il primo token � "carica".
 *
 * La funzione gestire_azioni_partita, invece richiama:
 * - visualizzare_attributi se il primo token � "visualizza" e il secondo � "attributi";
 * - visualizzare_mappa se il primo token � "visualizza" e il secondo � "mappa";
 * - visualizzare_inventario se il primo token � "visualizza" e il secondo � "inventario";
 * - esaminare_stanza se il primo token � "esamina" e il secondo � "stanza";
 * - aprire_porta se il primo token � "apri" e il secondo � "porta";
 * - aprire_botola se il primo token � "apri" e il secondo � "botola";
 * - sfondare_botola se il primo token � "sfonda" e il secondo � "porta";
 * - prendere_chiave se il primo token � "prendi" e il secondo � "chiave";
 * - prendere_frammento se il primo token � "prendi" e il secondo � "frammento" e (non necessariamente) il terzo � "mappa";
 *
 * La funzione gestire_movimenti, invece, non fa altro che richiamare la funzione di muovere_personaggio passandogli come
 * parametro la direzione letta (nord/sud/est/ovest). Il controllo verr� poi preso da questa funzione.
 */

#ifndef GESTIONE_COMANDI_H
#define GESTIONE_COMANDI_H

bool gestire_comandi_globali();
bool gestire_azioni_partita();
void gestire_movimenti();

#endif
