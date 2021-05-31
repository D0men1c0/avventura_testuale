/**
 * Il seguente modulo contiene il tipo di dato personaggio e le relative funzioni di scrittura e lettura per ogni suo campo.
 * I campi scelti sono 3 interi e un vettore di caratteri con dimensione massima di 50.
 * Sono presenti le funzioni di lettura e scrittura per ogni campo e le funzioni che hanno qualche modifica in particolare
 * sono : scrivere_vita,leggere_nome,scrivere_nome.
 * Scrivere_nome ha in input il tipo di dato personaggio e una stringa restituisce il campo nome aggiornato in cui ogni
 * carattere è stato preso dalla stringa passata in input.
 * Leggere_nome invece ha in input il tipo di dato personaggio e restituisce una stringa. Quest'ultima ha i caratteri presi
 * dal dato di input.
 * Scrivere_vita invece, ha in input il tipo di dato personaggio e il valore intero vita, restituisce il campo vita aggiornato
 * con il valore intero vita. Questa funzione ha una struttura differente dalle classiche funzioni di lettura e scrittura dei
 * campi di un record in quanto gestisce l'input dei valori dell'avventura e la morte del personaggio richiamando la funzione
 * impostare_inizio. Quest'ultima ha il compito di reimpostare i valori del personaggio , leggere la mappa da file richiamando
 * l'apposita funzione e impostare lo spawn del personaggio.
 * La funzione impostare_valori_personaggio ha il compito di far inserire all'utente tutti i valori dei campi presenti nella
 * struttura personaggio, ad eccezione della vita che viene settata a 5 senza l'intervento dell'utente e richiamare la funzione
 * inizializza inventario la quale viene descritta nell'apposito modulo.
 * Infine è presente la funzione controllare_valori_inseriti che riceve in input 2 interi che rappresentano i valori massimi
 * e minimi che l'utente può inserire per la forza e intelligenza e una stringa che rappresenta l'attributo da settare.
 * Ha il compito di restituire un valore intero inserito dall'utente in base ai vincoli presenti.
 * Perciò l'utilità di tale modulo risiede nell'impostare i valori iniziali del personaggio e eventualmente reimpostarli in caso
 * di morte di quest'ultimo.
 */
#include "../utility/utility.h"
#include "../gestione_avventura/gestione_avventura.h"

#ifndef PERSONAGGIO_H
#define PERSONAGGIO_H

#define DIM_NOME 50

typedef struct
{
	char nome[DIM_NOME];
	int vita;
	int forza;
	int intelligenza;
}personaggio;

stringa leggere_nome(personaggio personaggio_nome);
void scrivere_nome(personaggio *personaggio_nome, stringa nome);
int leggere_vita(personaggio personaggio_vita);
void scrivere_vita(personaggio *personaggio_vita, int valore);
int leggere_forza(personaggio personaggio_forza);
void scrivere_forza(personaggio *personaggio_forza, int valore);
int leggere_intelligenza(personaggio personaggio_intelligenza);
void scrivere_intelligenza(personaggio *personaggio_intelligenza, int valore);
int controllare_valori_inseriti(int min, int max, stringa attributo);
void impostare_valori_personaggio();
void impostare_inizio();

#endif
