#ifndef ANALIZZATORE_SINTATTICO_H
#define ANALIZZATORE_SINTATTICO_H

#include "../utility/utility.h"

#define MAX_SIMBOLI 10
#define MAX_TOKEN 10
#define MAX_SIMBOLO 4
#define MAX_PAROLE 50

#define SUCCESSO 1
#define ERRORE 0

typedef stringa parola_chiave;
typedef char simbolo[MAX_SIMBOLO];
typedef stringa token;

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
simbolo tabella_simboli[MAX_TOKEN];

void leggere_simboli_parole();
void stampare_simboli_tabella();
void leggere_sorgente();
void individuare_errori(int codice);
token estrarre_token();
int scansionare_token(token t);
void leggere_tabella();
void stampare_parole_chiave_tabella();

#endif
