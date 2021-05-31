/**
 * Il seguente modulo serve per poter gestire le funzioni di lettura e scrittura dei campi del record "personaggio".
 * La funzione leggere_nome serve per scrivere carattere per carattere all'interno di una stringa nome, tutti i
 * caratteri del campo personaggio_nome.nome.
 * La funzione scrivere_nome aggiorna il campo personaggio_nome in base ai caratteri passati in input dalla stringa
 * nome. Le altre funzioni leggere_vita,scrivere_forza_leggere_forza,scrivere_intelligenza,leggere_intelligenza,
 * non hanno nulla di particolare ma servono solo per riferirsi ai campi della struttura personaggio mediante
 * funzioni di lettura e scrittura.
 * Scrivere_vita invece, oltre a aggiornare il campo vita (con un intero "valore") del record "personaggio" , presenta
 * due controlli: il primo se il valore è maggiore o uguale a 5 non può essere incrementata ulteriormente in quanto
 * in gioco sono presenti dei bonus per incrementare la vita; il secondo controllo serve per gestire la morte del personaggio
 * cioè quando le sue vite diventano pari o inferiore di 0, una volta che tale condizione è soddisfatta, viene
 * richiamata la funzione impostare_inizio che richiama la funzione impostare_valori personaggio, inoltre imposta
 * lo spawn iniziale del giocatore, cioè la sua posizione iniziale all'interno della mappa, e la mappa stessa,
 * inoltre presenta un controllo sul valore assegnato al campo intelligenza che è stato deciso dall'utente.
 * La funzione impostare_valori_personaggio ha il compito di chiedere all'utente il suo nome, quanta forza e quanta
 * intelligenza assegnare ai rispettivi campi della struttura, avendo al massimo 5 punti distribuibili per forza e intelligenza
 * e dunque per controllare il corretto inserimento dei valori, viene richiamata la funzione controllare_valori_inseriti.
 * Inoltre è presente un ciclo che serve per reimpostare i valori assegnati ai campi forza e intelligenza, qualora l'utente
 * decida di cambiarli e dunque non iniziando immediatamente la storia. Inoltre questa funzione stampa a video un file
 * di testo dove si spiega a cosa servono i campi forza e intelligenza all'interno dell'avventura.
 * Infine vengono inizializzati i campi della struttura "inventario".
 */
#include "gestione_personaggio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../gestione_avventura/gestione_avventura.h"
#include "../utility/utility.h"
#include "../inventario/gestione_inventario.h"
#include "../gestione_avventura/gestione_mappa.h"
#include "../gestione_file/gestione_file.h"

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

void scrivere_vita(personaggio *personaggio_vita, int valore)
{
	if(leggere_vita(*personaggio_vita) <= 5)
	{
		personaggio_vita->vita = valore;
	}

	if (leggere_vita(*personaggio_vita) <= 0)
	{
		rallentare_output("\nOh no! Hai esaurito le vite a disposizione. Hai perso...\n",MILLISECONDI);
		ritardare_programma(3000);                                                //serve per far ritardare l'intero programma
		pulire_schermo();														  //pulisce lo schermo dai vecchi messaggi
		impostare_inizio();
	}
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

	//Cicla fin quando il valore assegnato non è compreso tra 0 e 5.

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

	scrivere_vita(&giocatore,5);

	rallentare_output("Benvenuto in questa nuova avventura!!\nInserisci il tuo nome: ", MILLISECONDI);

	str = leggere_stringa_tastiera(str);
	scrivere_nome(&giocatore, str);

	stringa_out = allocare_stringa(stringa_out, 0);
	sprintf(stringa_out, "\nCiao %s!", str);
	rallentare_output(stringa_out, MILLISECONDI);

	//stampa il file che spiega a cosa servono gli attributi forza e intelligenza.
	stringa_file = leggere_file_testo("statistiche.txt", stringa_file);
	rallentare_output(stringa_file, MILLISECONDI);

	do
	{
		punti = 5;
		forza = controllare_valori_inseriti(0, punti, "forza");
		punti -= forza;
		//Assegno i valori ai campi forza e intelligenza della struttura "personaggio", la loro somma è al massimo pari a 5.
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
			//Se l'utente non è convinto dei valori inseriti può sempre decidere di reimpostarli prima di iniziare la storia

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

void impostare_inizio()
{
	impostare_valori_personaggio();
	leggere_mappa(mappa);

	/**Se abbiamo impostato un'intelligenza maggiore di 3,
	 *consideriamo la cella [4][1] come un muro, cioè con
	 *un valore pari a 0.
	 */

	if(leggere_intelligenza(giocatore) < 3)
		scrivere_valore_matrice(mappa, 4, 1, 0);

	scrivere_y(&pos, SPAWN_Y);
	scrivere_x(&pos, SPAWN_X);

	pulire_schermo();
	ritardare_programma(3000);

	gestire_cella();                                                //gestisce la cella in cui si trova il personaggio
	rallentare_output("Ti vedo disorientato, per maggiori informazioni inserisci \"aiuto\".\n\n", MILLISECONDI);

}
