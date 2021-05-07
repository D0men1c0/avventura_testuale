#include <stdio.h>
#include <stdlib.h>
#include "../utility/utility.h"
#include "../gestione_file/file_di_testo/lettura_file_testo.h"
#include "../gestione_file/file_binari/scrittura_file_binari.h"
#include "../gestione_file/file_binari/lettura_file_binari.h"
#include "../analizzatore/analizzatore_sintattico.h"
#include "../personaggio/personaggio.h"


void gestire_avventura()
{
	//stringa stringa_file = "";
	/*stringa stringa_nome_file = "";

	stringa_nome_file = scrivere_stringa(stringa_nome_file, "prova.txt");

	stringa_file = leggere_file_testo(stringa_nome_file, stringa_file);

	settare_valori_personaggio();


	rallentare_output(stringa_file, 50);
	ritardare_programma(3000);
	pulire_schermo();

	stringa_file = leggere_file_testo("start.txt",stringa_file);
	rallentare_output(stringa_file,MILLISEC_CASTELLO);
	settare_valori_personaggio();*/

	leggere_simboli_parole();
	stampare_simboli_tabella();
	stampare_parole_chiave_tabella();


}
