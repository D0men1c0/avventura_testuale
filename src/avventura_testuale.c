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
	char * stringa_file;
	leggere_file_testo("prova.txt",stringa_file);

	printf("%s",stringa_file);
	system ("pause");
}
