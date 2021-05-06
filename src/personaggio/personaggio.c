#include <stdio.h>
#include <stdlib.h>
#include "../gestione_file/file_di_testo/lettura_file_testo.h"
#include "../gestione_file/file_binari/scrittura_file_binari.h"
#include "../utility/utility.h"
#include "personaggio.h"

stringa leggere_nome(personaggio personaggio_nome)
{
	return personaggio_nome.nome;
}

void scrivere_nome(personaggio *personaggio_nome,stringa nome)
{
	personaggio_nome->nome = nome;
}

int leggere_vita(personaggio personaggio_vita)
{
	return personaggio_vita.vita;
}

void scrivere_vita(personaggio *personaggio_vita, int valore)
{
	personaggio_vita->vita = valore;
}

int leggere_forza(personaggio personaggio_forza)
{
	return personaggio_forza.forza;
}

void scrivere_forza(personaggio *personaggio_forza,int valore)
{
	personaggio_forza->forza = valore;
}

int leggere_intelligenza(personaggio personaggio_intelligenza)
{
	return personaggio_intelligenza.intelligenza;
}

void scrivere_intelligenza(personaggio *personaggio_intelligenza, int valore)
{
	personaggio_intelligenza->intelligenza = valore;
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

void settare_valori_personaggio()
{
	personaggio inizio_personaggio;
	stringa stringa_file = "";
	stringa str = "";
	stringa risposta = "";
	stringa stringa_out = "";

	int forza;
	int punti;

	scrivere_vita(&inizio_personaggio,5);

	rallentare_output("\nBenvenuto in questa nuova avventura!!\nInserisci il tuo nome: ", MILLISECONDI);

	str = leggere_stringa_tastiera(str);
	scrivere_nome(&inizio_personaggio, str);

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

		scrivere_forza(&inizio_personaggio, forza);
		scrivere_intelligenza(&inizio_personaggio, punti);

		stringa_out = allocare_stringa(stringa_out, 0);
		sprintf(stringa_out, "\nHai inserito il valore %d alla forza.\n", leggere_forza(inizio_personaggio));
		rallentare_output(stringa_out, MILLISECONDI);

		stringa_out = allocare_stringa(stringa_out, 0);
		sprintf(stringa_out, "Di conseguenza intelligenza e' stato impostato a %d.\n", leggere_intelligenza(inizio_personaggio));
		rallentare_output(stringa_out, MILLISECONDI);

		do
		{
			rallentare_output("\nVuoi incominciare con la storia? Non potrai piu' ridistribuire i punti! (si/no) ", MILLISECONDI);
			risposta = leggere_stringa_tastiera(risposta);

			if(confrontare_stringhe(risposta, "si") == false && confrontare_stringhe(risposta, "no") == false)
			{
				rallentare_output("\nComando non riconosciuto!", MILLISECONDI);
			}
		}
		while(confrontare_stringhe(risposta, "si") == false && confrontare_stringhe(risposta, "no") == false);
	}
	while(confrontare_stringhe(risposta, "si") == false);
}
