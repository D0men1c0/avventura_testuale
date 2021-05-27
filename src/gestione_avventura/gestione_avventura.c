#include <stdio.h>
#include <stdlib.h>
#include "../utility/utility.h"
#include "../analizzatore/strutture_analizzatore.h"
#include "../gestione_file/gestione_file.h"
#include "../inventario/gestione_inventario.h"
#include "../personaggio/gestione_personaggio.h"

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
	rallentare_output(COLORE_ROSSO, 0);
	rallentare_output(COLORE_BIANCO, 0);

	pulire_schermo();

	stringa stringa_file = "";
	
	stringa_file = leggere_file_testo("start.txt",stringa_file);
	rallentare_output(stringa_file, MILLISEC_CASTELLO);
	inizializzare_strutture_analizzatore();

}


