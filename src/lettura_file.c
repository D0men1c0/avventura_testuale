#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lettura_file.h"

stringa leggere_file_testo(stringa nome_file, stringa stringa_file)
{

	int i;

	FILE * fp;

	if((fp = fopen("prova.txt", "r")) != NULL)
	{
		i = 0;

    stringa_file.stringa = (char *) malloc(sizeof(char) * 100);

		while(!feof(fp))
		{
      stringa_file = assegnare_carattere(stringa_file, fgetc(fp), i);
			i++;
		}

    stringa_file = assegnare_carattere(stringa_file, '\0', i-1);
	}
	else
	{
		printf("Errore nell'apertura del file.");
	}

	fclose(fp);

	return stringa_file;
}


stringa assegnare_carattere(stringa stringa, char c, int numero)
{
  *(stringa.stringa + numero) = c;

  return stringa;
}

