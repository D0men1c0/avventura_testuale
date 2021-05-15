#include <stdio.h>
#include <stdlib.h>
#include "../../utility/utility.h"
#include "../../personaggio/personaggio.h"
#include "../../inventario/gestione_inventario.h"

bool accodare_file_salvataggio(stringa nome_file, personaggio giocatore, inventario inv)
{
	bool esito;

	FILE * fp;

	esito = true;

	if((fp = fopen(nome_file,"ab+")) != NULL)  		// apre il file binario in modalità "append", se non esiste viene creato
	{
		fwrite(&giocatore, sizeof(personaggio), 1, fp);
		//fwrite(&inv, sizeof(inventario), 1, fp);
	}
	else
	{
		esito = false;
	}

	fclose(fp);

	return esito;
}
