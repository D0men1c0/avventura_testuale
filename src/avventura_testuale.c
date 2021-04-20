#include <stdio.h>
#include <stdlib.h>
#include "utility/utility.h"
#include "gestione_file/lettura_file.h"


int main(void)
{
	stringa stringa_file;
	stringa stringa_nome_file;

	scrivere_stringa(&stringa_nome_file, "prova.txt");

	stringa_file = leggere_file_testo(stringa_nome_file, stringa_file);

	printf("%s", leggere_stringa(stringa_file));
	system ("pause");

	return 0;
}
