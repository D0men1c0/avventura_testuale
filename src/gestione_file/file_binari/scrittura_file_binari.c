#include <stdio.h>
#include <stdlib.h>
#include "scrittura_file_binari.h"

void accodare_file_binario(stringa nome_file, void * dato, int tipologia_struttura)
{
	FILE * fp;

	if((fp = fopen(nome_file,"ab+")) != NULL)  		// apre il file binario in modalità "append", se non esiste viene creato
	{
		if(tipologia_struttura == TIPO_STRINGA)
		{
			stringa str;

			str = (stringa)dato;

			fwrite(str, sizeof(char) * leggere_lunghezza(str), 1, fp);
		}
		else if(tipologia_struttura == TIPO_INT)
		{
			int * intero;

			intero = (int *)dato;

			fwrite(intero, sizeof(int), 1, fp);
		}
		else if(tipologia_struttura == TIPO_FLOAT)
		{
			float * reale;

			reale = (float *)dato;

			fwrite(reale, sizeof(float), 1, fp);
		}
		//AGGIUNGERE MANO A MANO CHE SI VOGLIONO SALVARE ALTRE TIPOLOGIE
	}

	fclose(fp);

}
