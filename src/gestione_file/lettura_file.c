/**
 * La seguente funzione leggere_file_testo serve a gestire l'apertura del file di testo in modalità di lettura, la quale è gestita mediante
 * fopen che a sua volta richiama un altra funzione leggere_stringa, che serve per riferirsi al nome del file di testo.Inoltre è presente
 * anche la funzione scrivere_carattere, la quale avrà il compito di memorizzare all'interno della stringa tutti i caratteri presi volta
 * per volta dal file di testo mediante fgetc(fp), fino a quando i caratteri del file non sono terminati(!feof).
 * Inoltre alla fine del ciclo , viene richiamata ulteriormente la funzione scrivere carattere in modo tale da gestire il carattere di
 * fine stringa cioè \0. Infine se l'apertura del file dovesse andare a buon fine, quindi non dando alcun messaggio di errore (!NULL),
 * si chiuderà il file.
 */
#include <stdio.h>
#include <stdlib.h>
#include "../utility/utility.h"

stringa leggere_file_testo(stringa nome_file, stringa stringa_file)
{

	int i;

	FILE * fp;

	if((fp = fopen(leggere_stringa(nome_file), "r")) != NULL)
	{
		i = 0;

		while(!feof(fp))
		{
			scrivere_carattere(&stringa_file, i, fgetc(fp));

			i++;
		}

		scrivere_carattere(&stringa_file, i-1, '\0');//serve per gestire il carattere di fine stringa cioè \0
	}
	else
	{
		printf("Errore nell'apertura del file.");
	}

	fclose(fp);

	return stringa_file;
}

