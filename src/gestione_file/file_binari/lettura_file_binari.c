#include <stdio.h>
#include <stdlib.h>
#include "../../utility/utility.h"

void * leggere_file_binario(stringa nome_file, int tipologia_struttura)
{
	void * puntatore;

	FILE * fp;

	if((fp = fopen(nome_file,"rb")) != NULL)  		// apre il file binario in modalità "append", se non esiste viene creato
	{
		if(tipologia_struttura == TIPO_INT)
		{
			int intero;

			fread(&intero, sizeof(int), 1, fp);

			puntatore = &intero;
		}
		//AGGIUNGERE MANO A MANO CHE SI VOGLIONO SALVARE ALTRE TIPOLOGIE
	}

	fclose(fp);

	return puntatore;
}
