#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gestione_avventura/gestione_avventura.h"
#include "../gestione_file/file_di_testo/lettura_file_testo.h"
#include "../gestione_file/file_binari/scrittura_file_binari.h"
#include "../utility/utility.h"
#include "../inventario/gestione_inventario.h"
#include "personaggio.h"

stringa leggere_nome(personaggio personaggio_nome)
{
	stringa nome;
	int i;

	i = 0;

	while(i < strlen(personaggio_nome.nome))
	{
		nome = scrivere_carattere(nome, i, personaggio_nome.nome[i]);
		i++;
	}

	nome = scrivere_carattere(nome, i, '\0');

	return nome;
}

void scrivere_nome(personaggio *personaggio_nome, stringa nome)
{
	int i;

	i = 0;

	while(i < leggere_lunghezza(nome))
	{
		personaggio_nome->nome[i] = leggere_carattere(nome, i);
		i++;
	}

	personaggio_nome->nome[i] = '\0';
}

int leggere_vita(personaggio personaggio_vita)
{
	return personaggio_vita.vita;
}



int leggere_forza(personaggio personaggio_forza)
{
	return personaggio_forza.forza;
}

void scrivere_forza(personaggio *personaggio_forza,int valore)
{
	if(leggere_forza(*personaggio_forza) < 5)
	{
		personaggio_forza->forza = valore;
	}
}

int leggere_intelligenza(personaggio personaggio_intelligenza)
{
	return personaggio_intelligenza.intelligenza;
}

void scrivere_intelligenza(personaggio *personaggio_intelligenza, int valore)
{
	if(leggere_intelligenza(*personaggio_intelligenza) < 5)
	{
		personaggio_intelligenza->intelligenza = valore;
	}
}

void scrivere_vita(personaggio *personaggio_vita, int valore)
{
	if(leggere_vita(*personaggio_vita) < 5)
	{
		personaggio_vita->vita = valore;
	}

	if (leggere_vita(*personaggio_vita) <= 0)
	{
		rallentare_output("\nOh no! hai esaurito le vite a disposizione. Hai perso...\n",MILLISECONDI);
		ritardare_programma(4000);
		pulire_schermo();

		gestire_avventura();
	}
}

int controllare_valori_inseriti(int min, int max, stringa attributo)
{
	int valore;
	stringa output;

	do
	{
		output = allocare_stringa(output, 0);
		sprintf(output, "\nInserisci quanta %s vuoi avere (con un minimo di %d e un massimo di %d):  ", attributo, min, max);
		rallentare_output(output, MILLISECONDI);
		valore = leggere_intero_tastiera();

		if ((valore < min) || (valore > max))
		{
			output = allocare_stringa(output, 0);
			sprintf(output, "\nValore errato, reinserisci un valore da dare a %s compreso tra %d e %d", attributo, min, max);
			rallentare_output(output, MILLISECONDI);
		}
	}
	while ((valore < min) || (valore > max));

	return valore;
}

void impostare_valori_personaggio()
{
	stringa stringa_file = "";
	stringa str = "";
	stringa risposta = "";
	stringa stringa_out = "";

	int forza;
	int punti;

	pulire_schermo();
	scrivere_vita(&giocatore,1);

	rallentare_output("Benvenuto in questa nuova avventura!!\nInserisci il tuo nome: ", MILLISECONDI);

	str = leggere_stringa_tastiera(str);
	scrivere_nome(&giocatore, str);

	stringa_out = allocare_stringa(stringa_out, 0);
	sprintf(stringa_out, "\nCiao %s!", str);
	rallentare_output(stringa_out, MILLISECONDI);

	stringa_file = leggere_file_testo("statistiche.txt", stringa_file);
	rallentare_output(stringa_file, MILLISECONDI);

	do
	{
		punti = 5;
		forza = controllare_valori_inseriti(0, punti, "forza");
		punti -= forza;

		scrivere_forza(&giocatore, forza);
		scrivere_intelligenza(&giocatore, punti);

		stringa_out = allocare_stringa(stringa_out, 0);
		sprintf(stringa_out, "\nHai inserito il valore %d alla forza.\n", leggere_forza(giocatore));
		rallentare_output(stringa_out, MILLISECONDI);

		stringa_out = allocare_stringa(stringa_out, 0);
		sprintf(stringa_out, "Di conseguenza intelligenza e' stato impostato a %d.\n", leggere_intelligenza(giocatore));
		rallentare_output(stringa_out, MILLISECONDI);

		do
		{
			rallentare_output("\nVuoi incominciare con la storia? Non potrai piu' ridistribuire i punti! (si/no) ", MILLISECONDI);
			risposta = leggere_stringa_tastiera(risposta);

			if(confrontare_stringhe(convertire_stringa_minuscolo(risposta), "si") == false && confrontare_stringhe(convertire_stringa_minuscolo(risposta), "no") == false)
			{
				rallentare_output("\nComando non riconosciuto!", MILLISECONDI);
			}
		}
		while(confrontare_stringhe(convertire_stringa_minuscolo(risposta), "si") == false && confrontare_stringhe(convertire_stringa_minuscolo(risposta), "no") == false);
	}
	while(confrontare_stringhe(convertire_stringa_minuscolo(risposta), "si") == false);

	inizializza_inventario(&inv);
}

void azzerare_valori()
{
	//nome
	scrivere_forza(&giocatore,0);
	scrivere_intelligenza(&giocatore,0);
	inizializza_inventario(&inv);
}
