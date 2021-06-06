/**
 * Questo modulo definisce il tipo di dato matrice e permette la gestione della mappa e delle sue celle in particolare.
 * Vengono definite una serie di costanti(numeri primi) corrispondente ad ogni tipo di elemento che è possibile trovare in cella. Per il muro si è
 * scelto il valore 0 perchè non è divisore di alcun numero e per la cella vuota si è scelto il valore 1, perchè divisore di ogni numero.
 * Questa scelta è stata effettuata sulla base della necessità  di poter gestire la presenza di più elementi nella stessa cella: agendo così, infatti,
 * ogni cella sarà  divisibile solo per gli elementi lì presenti.
 * Ad esempio se in una cella è stato salvato il numero 902, questo significa che lì è presente(escludendo l'1 della cella vuota):
 * - STORIA (2)
 * - PEZZO_MAPPA_EST (41)
 * - PORTA_RE (11)
 * Questo perchè 2*41*11 = 902 e questa è l'unica combinazione possibile.
 * La funzione gestire_cella() ha il compito di stabilire il comportamento delle celle nelle quali non sono presenti comandi particolari effettuati dal
 * giocatore oppure la semplice gestione di messaggi di output.
 * La funzione trovare_direzioni_disponibili(), invece, ad ogni spostamento indica le possibili direzioni in cui può andare, controllando se vi è un muro
 * oppure una porta chiusa.
*/
#ifndef GESTIONE_MAPPA_H_
#define GESTIONE_MAPPA_H_

#include "../inventario/gestione_inventario.h"
#include "../personaggio/gestione_personaggio.h"
#include "gestione_avventura.h"

#define SPAWN_X 4						//Costante intera rappresentante la x della posizione di spawn.
#define SPAWN_Y 8						//Costante intera rappresentante la y della posizione di spawn.

#define MURO 0                          //Costante intera rappresentante una cella contenente il muro.
#define CELLA_VUOTA 1                   //Costante intera rappresentante una cella vuota.
#define STORIA 2                        //Costante intera rappresentante una cella contenente la storia.
#define POWER_UP_FORZA 3                //Costante intera rappresentante una cella contenente un power up che aumenta la forza di un'unitÃ .
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
#define POWER_UP_FORZA_2 53				//Costante intera rappresentante una cella contenente un power up che aumenta la forza di due unitÃ .
#define MURO_INTELLIGENZA 59			//Costante intera rappresentante una cella contenente una cella accessibile solo con un'elevata intelligenza.

#define RIGHE 10
#define COLONNE 14

typedef int matrice[RIGHE][COLONNE];							//Tipo di dato matrice utilizzata per la mappa

typedef struct
{
	int x;														//Valore della posizione nelle ascisse.
	int y;														//Valore della posizione nelle ordinate.
}posizione;

int leggere_valore_matrice(matrice matrice_a, int riga, int colonna);		//Funzione per la lettura del valore di una matrice.
void scrivere_valore_matrice(matrice matrice_a, int riga, int colonna, int valore);		//Funzione per la modifica di un valore di una matrice.

void scrivere_x(posizione *posizione_personaggio, int x);		//Funzione per la modifica della x nella struttura della posizione.
void scrivere_y(posizione *posizione_personaggio, int y);		//Funzione per la modifica della y nella struttura della posizione.
int leggere_x(posizione posizione_personaggio);					//Funzione per la lettura della x nella struttura della posizione.
int leggere_y(posizione posizione_personaggio);					//Funzione per la lettura della y nella struttura della posizione.
void gestire_cella();         							        //Funzione per la gestione delle singole celle.
stringa trovare_direzioni_disponibili();						//Funzione per la ricerca delle direzioni disponibili al giocatore.

#endif

