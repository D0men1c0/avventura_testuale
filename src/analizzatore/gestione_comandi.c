#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../utility/stringa/stringa.h"
#include "comandi.h"
#include "strutture_analizzatore.h"
#include "../personaggio/personaggio.h"
#include "../inventario/gestione_inventario.h"
#include "../gestione_file/file_di_testo/lettura_file_testo.h"
#include "../gestione_file/file_binari/scrittura_file_binari.h"
#include "../gestione_file/file_binari/lettura_file_binari.h"
#include "../gestione_avventura/gestione_avventura.h"
#include "../gestione_avventura/gestione_mappa.h"
#include "../gestione_avventura/gestione_movimenti.h"

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

				//aggiungere nello pseudo
				leggere_mappa(mappa);

				scrivere_y(&pos, 8);
				scrivere_x(&pos, 4);

				pulire_schermo();
				ritardare_programma(2000);

				gestire_cella(mappa, pos, &giocatore, &inv);
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

		if(strlen(leggere_nome(giocatore)) != 0)
		{
			esito = accodare_file_salvataggio("salvataggi.dat", giocatore, inv, mappa, pos);

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
			rallentare_output("Hai caricato correttamente i dati di gioco! \n\n", MILLISECONDI);

			if(leggere_x(pos) < 4)
			{
				rallentare_output("Ti trovavi nella sala del trono! \n\n", MILLISECONDI);
			}
			else if(leggere_x(pos) <= 7)
			{
				rallentare_output("Ti trovavi all'interno delle celle! \n\n", MILLISECONDI);
			}
			else
			{
				rallentare_output("Ti trovavi nelle segrete! \n\n", MILLISECONDI);
			}
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
	int cella_attuale;
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

				if(strlen(leggere_nome(giocatore)) != 0)
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

				if(strlen(leggere_nome(giocatore)) != 0)
				{
					rallentare_output("\nINVENTARIO:\n", MILLISECONDI);
					visualizzare_inventario(risposta);
				}
				else
				{
					gestire_errore_semantico();
				}
			}
			else if(confrontare_stringhe(token, MAPPA))
			{
				esito = true;

				if(strlen(leggere_nome(giocatore)) != 0)
				{
					risposta = visualizzare_frammenti_mappa(risposta);
					rallentare_output(risposta, MILLISEC_MAPPA);
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
	}else if(confrontare_stringhe(token, ESAMINA))
	{
		if(leggere_dimensione_tabella_simboli() == 2)
		{
			token = leggere_token_tabella_simboli(1);

			if(confrontare_stringhe(token, STANZA))
			{
				esito = true;

				stringa nome_file = "";

				nome_file = allocare_stringa(nome_file, 0);

				cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));

				sprintf(nome_file, "storia/[%d][%d].txt", leggere_y(pos), leggere_x(pos));
				risposta = leggere_file_storia(nome_file, risposta);
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

	free(risposta);
	return esito;
}

bool gestire_movimenti()
{
	bool esito;

	esito = false;

	if(leggere_dimensione_tabella_simboli() == 1)
	{
		esito = true;

		if(strlen(leggere_nome(giocatore)) != 0)
		{
			muovere_personaggio(leggere_token_tabella_simboli(0));
		}
		else
		{
			gestire_errore_semantico();
		}
	}

	return esito;
}

void gestire_errore_semantico()
{
	rallentare_output("\nNon puoi usare questo comando qui!\n\n", MILLISECONDI);
}

