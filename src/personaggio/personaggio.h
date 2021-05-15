#ifndef PERSONAGGIO_H
#define PERSONAGGIO_H

#include "../utility/utility.h"

#define DIM_NOME 50

typedef struct
{
	char nome[DIM_NOME];
	int vita;
	int forza;
	int intelligenza;
}personaggio;

personaggio giocatore;

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

#endif
