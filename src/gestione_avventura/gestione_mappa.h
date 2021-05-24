/**
 * Questo modulo permette la gestione della mappa e delle sue celle in particolare. Vengono definite una serie di costanti corrispondente ad ogni tipo
 * di elemento che è possibile trovare in cella. Per il muro ho scelto il valore 0 perché non è divisore di alcun numero e per la cella vuota ho scelto
 * il valore 1, perché divisore di ogni numero. Le successive celle sono tutti numeri primi.
 * Questa scelta è stata effettuata sulla base della necessità di poter gestire la presenza di più elementi nella stessa cella: agendo così, infatti,
 * ogni cella sarà divisibile solo per gli elementi lì presenti.
 * La funzione leggere_mappa() ha il compito di leggere la mappa da file, la funzione gestire_cella() ha invece il compito di stabilire il comportamento
 * delle celle nelle quali non sono presenti comandi particolari effettuati dal giocatore oppure la semplice gestione di messaggi di output.
*/

#include "../utility/array/matrice.h"
#include "gestione_movimenti.h"
#include "../inventario/gestione_inventario.h"
#include "../personaggio/gestione_personaggio.h"
#include "gestione_avventura.h"

#ifndef GESTIONE_MAPPA_H_
#define GESTIONE_MAPPA_H_

#define SPAWN_X 4
#define SPAWN_Y 8

#define MURO 0                          //Costante intera rappresentante una cella contenente il muro.
#define CELLA_VUOTA 1                   //Costante intera rappresentante una cella vuota.
#define STORIA 2                        //Costante intera rappresentante una cella contenente la storia.
#define POWER_UP_FORZA 3                //Costante intera rappresentante una cella contenente un power up che aumenta la forza.
#define PORTA_CHIUSA_SFONDABILE 5       //Costante intera rappresentante una cella contenente una porta chiusa sfondabile.
#define PORTA_SEMPLICE 7                //Costante intera rappresentante una cella contenente una porta semplice.
#define PORTA_RE 11                     //Costante intera rappresentante una cella contenente la porta del Re.
#define SALA_TRONO 13                   //Costante intera rappresentante una cella contenente l'entrata per la sala del trono
#define CHIAVE_SEMPLICE 17              //Costante intera rappresentante una cella contenente la chiave semplice.
#define CHIAVE_PORTA_RE 19              //Costante intera rappresentante una cella contenente la chiave per la porta del Re.
#define POWER_UP_VITA 23                //Costante intera rappresentante una cella contenente un power up che aumenta la vita.
#define MALUS 29                        //Costante intera rappresentante una cella contenente un malus.
#define BOTOLE 31                       //Costante intera rappresentante una cella contenente la botola.
#define PEZZO_MAPPA_OVEST 37            //Costante intera rappresentante una cella contenente la parte ovest della mappa.
#define PEZZO_MAPPA_EST 41              //Costante intera rappresentante una cella contenente la parte est della mappa.
#define PEZZO_MAPPA_NORD 43             //Costante intera rappresentante una cella contenente la parte nord della mappa.
#define PEZZO_MAPPA_SUD 47              //Costante intera rappresentante una cella contenente la parte sud della mappa.

void leggere_mappa(matrice mappa);      //Funzione per la lettura della mappa da file.
void gestire_cella();                   //Funzione per la gestione delle singole celle.

#endif

