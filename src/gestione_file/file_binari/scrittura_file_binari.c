#include <stdio.h>
#include <stdlib.h>
#include "../../utility/utility.h"
#include "../../personaggio/personaggio.h"
#include "../../inventario/gestione_inventario.h"
#include "../../gestione_avventura/gestione_avventura.h"
#include "../../gestione_avventura/gestione_mappa.h"
#include "../../gestione_avventura/gestione_movimenti.h"

bool accodare_file_salvataggio(stringa nome_file, personaggio giocatore, inventario inv, matrice mappa, posizione pos)
{
	int i;
	bool esito;

	FILE * fp;

	esito = true;

	if((fp = fopen(nome_file,"ab+")) != NULL)  		// apre il file binario in modalità "append", se non esiste viene creato
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
