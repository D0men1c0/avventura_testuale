/**
 * Questo è uno dei moduli principali ai fini della gestione generale dell'avventura.
 * Esso contiene infatti tutte la variabili globali che servono a gestire interamente il personaggio e l'ambiente di gioco.
 * Sono inoltre presenti due funzioni molto importanti per il funzionamento del gioco.
 * La funzione per la gestione dell'avventura è quella che di fatto la imposta, richiamando la funzione apposita e occupandosi
 * della continua richiesta di input da parte del giocatore.
 * La funzione per l'impostazione dell'avventura visualizza la schermata principale del gioco tramite la funzione che permette
 * la visualizzazione lenta dei messaggi e successivamente imposta le strutture dell'analizzatore lessicale tramite funzione dedicata. 
*/

#ifndef GESTIONE_AVVENTURA_H
#define GESTIONE_AVVENTURA_H

#include "gestione_mappa.h"
#include "../inventario/gestione_inventario.h"
#include "../personaggio/gestione_personaggio.h"

bool chiusura_gioco;

void gestire_avventura();									//Funzione per la gestione principale dell'avventura.
void impostare_avventura();                                 //Funzione che imposta l'avventura e che visualizza la schermata iniziale del gioco.

matrice mappa;                                              //Variabile globale che contiene la mappa del gioco.
posizione pos;                                              //Variabile globale che contiene la posizione del personaggio.
posizione posizione_precedente;                             //Variabile globale che contiene la posizione precedente a quella del personaggio.
inventario inv;                                             //Variabile globale che contiene l'inventario del personaggio.
personaggio giocatore;                                      //Variabile globale che contiene gli attributi del personaggio.

#endif
