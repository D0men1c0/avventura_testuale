/*
 ============================================================================
 Name        : avventura_testuale.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "lettura_file.h"


int main(void)
{
	stringa stringa_file;
  stringa nome_file;

  nome_file.stringa = "prova.txt";

	stringa_file = leggere_file_testo(nome_file, stringa_file);

	printf("%s", stringa_file.stringa);
	system ("pause");
}
