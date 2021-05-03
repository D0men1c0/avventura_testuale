#include <stdio.h>
#include <stdlib.h>
#include "gestione_avventura.h"

void gestire_avventura()
{
	stringa stringa_file = "";
	stringa stringa_nome_file = "";

	stringa_nome_file = scrivere_stringa(stringa_nome_file, "prova.txt");

	stringa_file = leggere_file_testo(stringa_nome_file, stringa_file);

	settare_valori_personaggio();


	rallentare_output(stringa_file, 50);
	ritardare_programma(3000);
	pulire_schermo();

}



