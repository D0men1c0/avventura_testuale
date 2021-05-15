#include <stdlib.h>
#include <stdio.h>
#include "../utility/stringa/stringa.h"
#include "comandi.h"
#include "strutture_analizzatore.h"
#include "../personaggio/personaggio.h"
#include "../inventario/gestione_inventario.h"
#include "../gestione_file/file_di_testo/lettura_file_testo.h"
#include "../gestione_file/file_binari/scrittura_file_binari.h"
#include "../gestione_file/file_binari/lettura_file_binari.h"

void gestire_errore_semantico();


bool gestire_comandi_globali()
{
	bool esito;

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
	else if(confrontare_stringhe(token, AIUTO) == true)
	{
		if (leggere_dimensione_tabella_simboli() < 2)
		{
			risposta = leggere_file_testo("aiuto.txt", risposta);
			rallentare_output(risposta, MILLISECONDI);
			esito = true;
		}
	}
	else if(confrontare_stringhe(token, SALVA) == true)
	{
		if(leggere_nome(giocatore) != NULL)
		{
			esito = accodare_file_salvataggio("salvataggi.dat", giocatore, inv);

			if(esito == true)
			{
				rallentare_output("\nHai salvato correttamente i dati di gioco! \n", MILLISECONDI);
			}
			else
			{
				rallentare_output("\nErrore nel salvataggio della partita in corso! \n", MILLISECONDI);
			}
		}
		else
		{
			gestire_errore_semantico();
		}

		esito = true;
	}
	else if(confrontare_stringhe(token, CARICA) == true)
	{

		esito = leggere_file_salvataggio("salvataggi.dat");

		if(esito == true)
		{
			pulire_schermo();
			rallentare_output("Hai caricato correttamente i dati di gioco! \n", MILLISECONDI);
		}
		else
		{
			rallentare_output("\nErrore nel caricamento dei dati di gioco! \n", MILLISECONDI);
		}


		esito = true;
	}


	free(risposta);

	return esito;
}


bool gestire_azioni_partita()
{
	bool esito;
	stringa risposta = "";
	parola_chiave token = leggere_token_tabella_simboli(0);

	risposta = allocare_stringa(risposta, 0);
	esito = false;

	if(confrontare_stringhe(token, VISUALIZZA))
	{
		if(leggere_dimensione_tabella_simboli() == 2)
		{
			token = leggere_token_tabella_simboli(1);

			if(confrontare_stringhe(token, ATTRIBUTI))
			{
				esito = true;

				if(leggere_nome(giocatore) != NULL)
				{
					sprintf(risposta, "\nATTRIBUTI:\nTi chiami: %s \nLa vita e': %d \nLa forza e': %d\nL'intelligenza e': %d\n\n", leggere_nome(giocatore), leggere_vita(giocatore), leggere_forza(giocatore), leggere_intelligenza(giocatore));
					rallentare_output(risposta, MILLISECONDI);
				}
				else
				{
					gestire_errore_semantico();
				}
			}
			else if(confrontare_stringhe(token, INVENTARIO))
			{
				esito = true;

				if(leggere_nome(giocatore) != NULL)
				{
					risposta = visualizzare_inventario(risposta);
					rallentare_output("\nINVENTARIO:\n", MILLISECONDI);
					rallentare_output(risposta, MILLISECONDI);
				}
				else
				{
					gestire_errore_semantico();
				}
			}
			else if(confrontare_stringhe(token, MAPPA))
			{
				esito = true;

				if(leggere_nome(giocatore) != NULL)
				{
					risposta = visualizzare_frammenti_mappa(risposta);
					rallentare_output(risposta, MILLISECONDI);
				}
				else
				{
					gestire_errore_semantico();
				}
			}
			else
			{
				gestire_errore_semantico();
			}
		}
	}

	free(risposta);
	return esito;
}

void gestire_errore_semantico()
{
	rallentare_output("\nNon puoi usare questo comando qui!\n\n", MILLISECONDI);
}

