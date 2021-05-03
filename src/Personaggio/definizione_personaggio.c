#include <stdio.h>
#include <stdlib.h>
#include "definizione_personaggio.h"
#include "../utility/stringa/stringa.h"
#include "../gestione_file/file_di_testo/lettura_file_testo.h"
#include "../gestione_file/file_binari/scrittura_file_binari.h"

stringa leggere_nome(personaggio personaggio_nome)
{
	return personaggio_nome.nome;
}

void scrivere_nome(personaggio *personaggio_nome,stringa nome)
{
	personaggio_nome->nome=nome;
}

int leggere_vita(personaggio personaggio_vita)
{
	return personaggio_vita.vita;
}

void scrivere_vita(personaggio *personaggio_vita,int valore)
{
	personaggio_vita->vita=valore;
}

int leggere_forza(personaggio personaggio_forza)
{
	return personaggio_forza.forza;
}

void scrivere_forza(personaggio *personaggio_forza,int valore)
{
	personaggio_forza->forza=valore;
}

int leggere_intelligenza(personaggio personaggio_intelligenza)
{
	return personaggio_intelligenza.intelligenza;
}

void scrivere_intelligenza(personaggio *personaggio_intelligenza,int valore)
{
	personaggio_intelligenza->intelligenza=valore;
}

int controllare_valori_inseriti(int min,int max,stringa attributo)
{
  int valore;
	do
	{
		printf("\n\nInserisci quanta %s vuoi avere (con un minimo di %d e un massimo di %d) :  ",attributo,min,max);
		scanf("%d",&valore);
		if ((valore < min) || (valore > max))
		{
			printf("\nValore Errato, reinserisci un valore da dare a %s compreso tra %d e %d",attributo,min,max);
		}
	}
	while ((valore < min) || (valore > max));
	return valore;
}

void settare_valori_personaggio()
{
	personaggio inizio_personaggio;
	stringa nome_partenza = "";
	stringa stringa_file = "";
	stringa stringa_nome_file = "";
	int forza;
	int intelligenza;


	printf("Benvenuto in questa nuova avventura, inserisci il tuo nome : ");
	scanf("%s", nome_partenza);
	scrivere_nome(&inizio_personaggio,nome_partenza);
	printf("Ciao %s ",nome_partenza);
	stringa_file = scrivere_stringa(stringa_file,"statistiche.txt");
	stringa_nome_file=leggere_file_testo(stringa_file,stringa_nome_file);

	forza = controllare_valori_inseriti(0,5,"forza");
	scrivere_forza(&inizio_personaggio,forza);
	intelligenza = controllare_valori_inseriti(0,5,"intelligenza");
	scrivere_intelligenza(&inizio_personaggio,intelligenza);

}
