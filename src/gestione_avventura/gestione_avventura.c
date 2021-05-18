#include <stdio.h>
#include <stdlib.h>
#include "../utility/utility.h"
#include "../gestione_file/file_di_testo/lettura_file_testo.h"
#include "../gestione_file/file_binari/scrittura_file_binari.h"
#include "../gestione_file/file_binari/lettura_file_binari.h"
#include "../analizzatore/strutture_analizzatore.h"
#include "../personaggio/personaggio.h"
#include "../inventario/gestione_inventario.h"

void impostare_avventura();


void gestire_avventura()
{
	impostare_avventura();
	
	while(true)
	{
		leggere_comando();
	}

}

void impostare_avventura()
{
	stringa stringa_file = "";
	
	stringa_file = leggere_file_testo("start.txt",stringa_file);
	rallentare_output(stringa_file, MILLISEC_CASTELLO);
	inizializzare_strutture_analizzatore();
}


