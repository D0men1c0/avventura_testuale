#ifndef STRUTTURE_ANALIZZATORE_H
#define STRUTTURE_ANALIZZATORE_H

#include "../utility/utility.h"
#include "comandi.h"

stringa token;
stringa sorgente;

/**
 * STRUTTURA PAROLE CHIAVE
 */
typedef stringa parola_chiave;
struct{
	parola_chiave parole_chiave[MAX_PAROLE];
	int dimensione;
}struttura_parole_chiave;

/**
 * STRUTTURA TABELLA SIMBOLI
 */
typedef int simbolo;
struct{
	simbolo simboli[MAX_TOKEN];
	parola_chiave token[MAX_TOKEN];
	int dimensione;
}tabella_simboli;

struct{
	simbolo simboli[MAX_SIMBOLI];
	int numero_parole_chiave[MAX_SIMBOLI];
	int dimensione;
}struttura_simboli;

void leggere_comando();
void inizializzare_strutture_analizzatore();

int leggere_dimensione_parole_chiave();
int leggere_numero_parole_chiave(int indice);
int leggere_dimensione_simboli();
void scrivere_dimensione_tabella_simboli(int dimensione);
int leggere_dimensione_tabella_simboli();
void scrivere_simbolo_tabella_simboli(simbolo simb, int indice);
simbolo leggere_simbolo_tabella_simboli(int indice);
void scrivere_token_tabella_simboli(parola_chiave token, int indice);
parola_chiave leggere_token_tabella_simboli(int indice);
stringa leggere_parola_chiave_tabella(int indice);

void scrivere_parola_chiave_struttura_parole_chiave(int indice, parola_chiave parola);

void scrivere_parola_chiave_struttura_simboli(int indice, int valore);
void scrivere_simboli_struttura_simboli(int indice, simbolo simb);
#endif
