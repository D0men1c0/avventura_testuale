#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../stringa/stringa.h"

void leggi_linea();

int leggere_intero_tastiera()
{
	int intero;

	scanf("%d", &intero);

	leggi_linea();

	return intero;
}

stringa leggere_stringa_tastiera(stringa str)
{
	str = allocare_stringa(str, 0);

	fgets (str, sizeof(char) * DIM_STRINGA, stdin);

	if ((leggere_lunghezza(str) > 0) && (str[leggere_lunghezza (str) - 1] == '\n'))
		str[leggere_lunghezza(str) - 1] = '\0';

	return str;
}

void leggi_linea()
{
	int c;

	do
	{
	    c = getchar();
	}
	while(c != EOF && c != '\n');
}
