/**
 * Il seguente modulo serve per ptoer leggere su file di testo e leggere e scrivere su file binario.
 * La funzione accodare_file_salvataggio apre in modalità append il file binario e scrive su quest'ultimo mediante la funzione di
 * libreria fwrite gli attributi del personaggio, lo stato dell'inventario, l'intera mappa mediante un ciclo per le
 * righe e le colonne e infine la posizione. Se il salvataggio è andato a buon fine restituisce un esito positivo, altrimenti
 * un'esito negativo.
 * Funzione simile è leggere_file_salvataggio che invece legge da file binario mediante la funzione fread. Il file viene sempre
 * aperto in modalità append e vengono letti le strutture memorizzate nel file quali: inventario, personaggio, matrice, posizione.
 * Sono presenti 3 funzioni di lettura da file di testo e sono: leggere_file_testo, leggere_file_storia, leggere_mappa_file.
 * La funzione leggere_file_testo serve a gestire l'apertura del file di testo in modalità di lettura.
 * Inoltre è presente anche la funzione scrivere_carattere, la quale avrà il compito di memorizzare all'interno della stringa tutti i
 * caratteri presi volta per volta dal file di testo mediante fgetc(fp), fino a quando i caratteri del file non sono terminati(!feof).
 * Inoltre alla fine del ciclo , viene richiamata ulteriormente la funzione scrivere carattere in modo tale da gestire il carattere di
 * fine stringa cioè \0. Infine se l'apertura del file dovesse andare a buon fine, quindi non dando alcun messaggio di errore (!NULL),
 * si chiuderà il file.
 * Funzionamento analogo risulta per leggere_file_storia ma cambia semplicemente il messaggio di errore qualora il file fosse vuoto.
 * Infine la funzione leggere_mappa_file serve per poter prendere ciascun valore dal file di testo mappa.txt, usando la fscanf e
 * successivamente memorizzando all'interno dell'array bidimensionale, tutti gli interi presi volta per volta dal file ciclando per le
 * righe e per le colonne.
 */
#include <stdio.h>
#include <stdlib.h>
#include "../utility/utility.h"
#include "../inventario/gestione_inventario.h"
#include "../gestione_avventura/gestione_avventura.h"
#include "../gestione_avventura/gestione_mappa.h"
#include "../personaggio/gestione_personaggio.h"

// FILE BINARI

bool leggere_file_salvataggio(stringa nome_file)
{
	int i;
	bool esito;

	FILE * fp;

	esito = true;

	if((fp = fopen(nome_file,"rb")) != NULL)  		// apre il file binario in modalità "append", se non esiste viene creato
	{
		fread(&giocatore, sizeof(personaggio), 1, fp);
		fread(&inv, sizeof(inventario), 1, fp);

		i = 0;
		while(i < RIGHE)
		{
			fread(mappa[i], sizeof(mappa[i][0]), COLONNE, fp);
			i++;
		}

		fread(&pos, sizeof(posizione), 1, fp);
	}
	else
	{
		esito = false;
	}

	fclose(fp);

	return esito;
}

bool accodare_file_salvataggio(stringa nome_file)
{
	int i;
	bool esito;

	FILE * fp;

	esito = true;

	if((fp = fopen(nome_file,"wb")) != NULL)  		// apre il file binario in modalità "append", se non esiste viene creato
	{
		fwrite(&giocatore, sizeof(personaggio), 1, fp);
		fwrite(&inv, sizeof(inventario), 1, fp);

		i = 0;
		while(i < RIGHE)
		{
			fwrite(mappa[i], sizeof(mappa[i][0]), COLONNE, fp);
			i++;
		}

		fwrite(&pos, sizeof(posizione), 1, fp);
	}
	else
	{
		esito = false;
	}

	fclose(fp);

	return esito;
}

// FILE DI TESTO

stringa leggere_file_testo(stringa nome_file, stringa stringa_file)
{

	int i;

	FILE * fp;

	if((fp = fopen(nome_file, "r")) != NULL)
	{
		i = 0;

		while(!feof(fp))
		{
			stringa_file = scrivere_carattere(stringa_file, i, fgetc(fp));

			i++;
		}

		stringa_file = scrivere_carattere(stringa_file, i-1, '\0'); //serve per gestire il carattere di fine stringa cioè \0
	}
	else
	{
		printf("Errore nell'apertura del file.");
	}

	fclose(fp);

	return stringa_file;
}

stringa leggere_file_storia(stringa nome_file, stringa stringa_file)
{
	int i;

	FILE * fp;

	if((fp = fopen(nome_file, "r")) != NULL)
	{
		i = 0;

		while(!feof(fp))
		{
			stringa_file = scrivere_carattere(stringa_file, i, fgetc(fp));

			i++;
		}

		stringa_file = scrivere_carattere(stringa_file, i-1, '\0'); //serve per gestire il carattere di fine stringa cioè \0
	}
	else
	{
		stringa_file = scrivere_stringa(stringa_file, "Non c'e' nulla di interessante qui!\n\n");
	}

	fclose(fp);

	return stringa_file;
}

void leggere_mappa_file(stringa nome_file)
{
	int i;
	int j;
	int intero;

	i = 0;
	j = 0;

	FILE * fp;

	if((fp = fopen(nome_file, "r")) != NULL)
	{
		while(i < RIGHE)
		{
			j = 0;
			while(j < COLONNE)
			{
				fscanf(fp, "%d", &intero);
				scrivere_valore_matrice(mappa, i, j, intero);
				j++;
			}
			i++;
		}
	}
	else
	{
		printf("Errore nell'apertura del file.");
	}

	fclose(fp);
}

