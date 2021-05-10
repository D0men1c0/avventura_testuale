#ifndef STRUTTURE_ANALIZZATORE_H
#define STRUTTURE_ANALIZZATORE_H

#include "../utility/utility.h"

#define MAX_SIMBOLI 10
#define MAX_TOKEN 10
#define MAX_PAROLE 50

typedef stringa parola_chiave;
typedef int simbolo;
stringa token;

struct{
	simbolo simboli[MAX_SIMBOLI];
	int numero_parole_chiave[MAX_SIMBOLI];
	int dimensione;
}struttura_simboli;

struct{
	parola_chiave parole_chiave[MAX_PAROLE];
	int dimensione;
}struttura_parole_chiave;

stringa sorgente;

struct{
	simbolo simboli[MAX_TOKEN];
	int dimensione;
}tabella_simboli;


void leggere_comando();
void inizializzare_strutture_analizzatore();
int leggere_dimensione_parole_chiave();
int leggere_numero_parole_chiave(int indice);
int leggere_dimensione_simboli();
void scrivere_dimensione_tabella_simboli(int dimensione);
int leggere_dimensione_tabella_simboli();
void scrivere_simbolo_tabella_simboli(simbolo simb, int indice);
simbolo leggere_simbolo_tabella_simboli(int indice);
stringa leggere_parola_chiave_tabella(int indice);

#endif
