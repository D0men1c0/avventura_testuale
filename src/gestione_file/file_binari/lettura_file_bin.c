#include <stdio.h>
#include <stdlib.h>
#include "../../utility/bin/bin.h"

bin leggere_file_bin(bin nome_file, bin stringa_file)
{

	int i;

	FILE * fp;

	if((fp = fopen(&nome_file, "rb")) != NULL)
	{
		i = 0;

		while(!feof(fp))
		{
			stringa_file = scrivere_bin(stringa_file, i, fgetc(fp));

			i++;
		}
	}
	else
	{
		printf("Errore nell'apertura del file.");
	}

	fclose(fp);


	return stringa_file;
}
