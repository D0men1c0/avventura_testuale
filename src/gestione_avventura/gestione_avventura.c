#include <stdio.h>
#include <stdlib.h>
#include "../utility/utility.h"
#include "../gestione_file/file_di_testo/lettura_file_testo.h"
#include "../gestione_file/file_binari/scrittura_file_binari.h"
#include "../gestione_file/file_binari/lettura_file_binari.h"
#include "../analizzatore/analizzatore_sintattico.h"
#include "../personaggio/personaggio.h"

void inizializzare_strutture();

void gestire_avventura()
{
	stringa stringa_file = "";
	stringa stringa_nome_file = "";

	inizializzare_strutture();

	/*stringa_nome_file = scrivere_stringa(stringa_nome_file, "prova.txt");

	stringa_file = leggere_file_testo(stringa_nome_file, stringa_file);

	settare_valori_personaggio();


	rallentare_output(stringa_file, 50);
	ritardare_programma(3000);
	pulire_schermo();

	stringa_file = leggere_file_testo("start.txt",stringa_file);
	rallentare_output(stringa_file, MILLISEC_CASTELLO);
	settare_valori_personaggio();
*/

	//stampare_simboli_tabella();
	//stampare_parole_chiave_tabella();

}


void inizializzare_strutture()
{
	leggere_simboli_parole();
	leggere_sorgente();

	int i;
	i = 0;

	while(leggere_lunghezza(sorgente) != 0)
	{
		scansionare_token(estrarre_token(), i);
		i++;
	}
}
