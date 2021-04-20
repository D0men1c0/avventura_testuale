#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * leggere_file_testo(char * nome_file, char * stringa_file)
{

	int i;

	FILE * fp;

	if((fp = fopen("nome_file", "r")) != NULL)
	{
		i = 0;

		while(!feof(fp))
		{
			*(stringa_file + i) = fgetc(fp);
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


