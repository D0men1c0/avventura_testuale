#include <stdio.h>
#include <stdlib.h>
#include "../utility/utility.h"
#include "../personaggio/personaggio.h"
#include "../inventario/gestione_inventario.h"
#include "../gestione_avventura/gestione_avventura.h"
#include "../gestione_avventura/gestione_mappa.h"
#include "../gestione_avventura/gestione_movimenti.h"

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

bool accodare_file_salvataggio(stringa nome_file, personaggio giocatore, inventario inv, matrice mappa, posizione pos)
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

/**
 * La seguente funzione leggere_file_testo serve a gestire l'apertura del file di testo in modalità di lettura, la quale è gestita mediante
 * fopen che a sua volta richiama un altra funzione leggere_stringa, che serve per riferirsi al nome del file di testo.Inoltre è presente
 * anche la funzione scrivere_carattere, la quale avrà il compito di memorizzare all'interno della stringa tutti i caratteri presi volta
 * per volta dal file di testo mediante fgetc(fp), fino a quando i caratteri del file non sono terminati(!feof).
 * Inoltre alla fine del ciclo , viene richiamata ulteriormente la funzione scrivere carattere in modo tale da gestire il carattere di
 * fine stringa cioè \0. Infine se l'apertura del file dovesse andare a buon fine, quindi non dando alcun messaggio di errore (!NULL),
 * si chiuderà il file.
 */

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
		printf("\nNon c'e' nulla di interessante qui!\n");
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

