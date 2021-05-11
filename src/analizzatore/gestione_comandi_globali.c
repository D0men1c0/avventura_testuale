#include <stdlib.h>
#include <stdio.h>
#include "../utility/stringa/stringa.h"
#include "comandi.h"
#include "strutture_analizzatore.h"
#include "../personaggio/personaggio.h"

#define NUOVA "nuova"
#define AIUTO "aiuto"
#define CARICA "carica"
#define SALVA "salva"

int gestire_comandi_globali()
{
	int esito;

	stringa risposta = "";

	parola_chiave token = leggere_token_tabella_simboli(0);

	esito = false;

	if(confrontare_stringhe(token, NUOVA))
	{
		esito = true;

		do
		{
			rallentare_output("\nSei sicuro di voler iniziare una nuova partita? Tutti i tuoi dati non salvati verranno persi! (si/no): ", MILLISECONDI);
			risposta = leggere_stringa_tastiera(risposta);

			if(confrontare_stringhe(convertire_stringa_minuscolo(risposta), "si") == true)
			{
				impostare_valori_personaggio();
			}
			else if(confrontare_stringhe(convertire_stringa_minuscolo(risposta), "si") == false && confrontare_stringhe(convertire_stringa_minuscolo(risposta), "no") == false)
			{
				rallentare_output("\nComando non riconosciuto!", MILLISECONDI);
			}

		}
		while(confrontare_stringhe(convertire_stringa_minuscolo(risposta), "si") == false && confrontare_stringhe(convertire_stringa_minuscolo(risposta), "no") == false);
	}

	return esito;
}
