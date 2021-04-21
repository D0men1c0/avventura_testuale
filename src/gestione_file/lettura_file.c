/**
 * La seguente funzione leggere_file_testo serve a gestire l'apertura del file di testo in modalità di lettura, la quale è gestita mediante
 * fopen che a sua volta richiama un altra funzione leggere_stringa, che serve per riferirsi al nome del file di testo, in quanto è stato
 * utilizzato un tipo di dato denominato stringa per poter gestire più comodamente sia la lunghezza della stringa e anche gli stessi caratteri
 * all'interno di essa. Infatti proprio perchè utilizziamo il tipo di dato, è presente anche la funzione scrivere_carattere, la quale avrà il
 * compito di memorizzare all'interno della stringa tutti i caratteri presi volta per volta dal file di testo mediante fgetc(fp), fino a quando
 * i caratteri del file non sono terminati(!feof).
 * Inoltre alla fine del ciclo , viene richiamata ulteriormente la funzione scrivere carattere in modo tale da gestire il carattere di
 * fine stringa cioè \0. Infine se l'apertura del file dovesse andare a buon fine, quindi non dandoci alcun errore (!NULL), chiuderemo il file.
 * Perciò l'utilità di questo modulo risiede nella gestione dei file di testo per poter visualizzare le varie parti della storia, viene
 * usata un tipo di dato stringa e non una printf per stampare tutti i caratteri, in quanto negli altri moduli non ci servirà solo
 * la stampa a video del file di testo , ma ad esempio per gestire i movimenti del personaggio no avremo bisogno di una semplice stampa.
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

