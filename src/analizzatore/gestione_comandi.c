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
void gestire_finale(bool cifrato);


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
				//aggiungere in pseudo
				impostare_inizio();
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

			rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
			rallentare_output("\n", MILLISECONDI);
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
	}
	else if(confrontare_stringhe(token, ESAMINA))
	{
		if(leggere_dimensione_tabella_simboli() == 2)
		{
			token = leggere_token_tabella_simboli(1);

			if(confrontare_stringhe(token, STANZA))
			{
				esito = true;

				if(strlen(leggere_nome(giocatore)) != 0)
				{
					stringa nome_file = "";

					nome_file = allocare_stringa(nome_file, 0);

					sprintf(nome_file, "storia/[%d][%d].txt", leggere_y(pos), leggere_x(pos));
					risposta = leggere_file_storia(nome_file, risposta);
					rallentare_output(risposta, MILLISECONDI);
				}
				else
				{
					gestire_errore_semantico();
				}
			}
		}
	}
	else if(confrontare_stringhe(token, APRI))
	{
		if(leggere_dimensione_tabella_simboli() == 2)
		{
			token = leggere_token_tabella_simboli(1);

			if(confrontare_stringhe(token, PORTA))
			{
				esito = true;

				if(strlen(leggere_nome(giocatore)) != 0)
				{
					int cella_attuale;

					cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));

					if(cella_attuale % PORTA_SEMPLICE == 0 && cella_attuale != 0)
					{
						if(leggere_chiave_semplice(inv) == true)
						{
							rallentare_output("\nHai aperto con successo la porta, utilizzando la chiave semplice!\n",MILLISECONDI);
							cella_attuale /= PORTA_SEMPLICE;
							scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
							rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
							rallentare_output("\n", MILLISECONDI);
						}
						else
						{
							rallentare_output("\nNon possiedi la chiave semplice, dunque non puoi entrare qui!\n",MILLISECONDI);
						}
					}
					else if(cella_attuale % PORTA_RE == 0 && cella_attuale != 0)
					{
						if(leggere_chiave_re(inv) == true)
						{
							rallentare_output("\nHai aperto con successo la porta del re, utilizzando la chiave del re!\n",MILLISECONDI);
							cella_attuale /= PORTA_RE;
							scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
							rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
							rallentare_output("\n", MILLISECONDI);
						}
						else
						{
							rallentare_output("\nNon possiedi la chiave semplice, dunque non puoi entrare qui!\n",MILLISECONDI);
						}
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
			else if(confrontare_stringhe(token, BOTOLA))
			{
				esito = true;

				int cella_attuale;

				cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));

				if(cella_attuale % BOTOLE == 0 && cella_attuale != 0)
				{
					if(leggere_frammento_sud(inv) && leggere_frammento_est(inv) && leggere_frammento_nord(inv))
					{
						if(leggere_intelligenza(giocatore) > 2)
						{
							gestire_finale(false);
						}
						else
						{
							gestire_finale(true);
						}
					}
					else
					{
						rallentare_output("\nNon hai ancora raccolto tutti i frammenti di mappa!\n", MILLISECONDI);
					}
				}
				else
				{
					gestire_errore_semantico();
				}
			}
		}
	}
	else if(confrontare_stringhe(token, SFONDA))
	{
		if(leggere_dimensione_tabella_simboli() == 2)
		{
			token = leggere_token_tabella_simboli(1);

			if(confrontare_stringhe(token, PORTA))
			{
				esito = true;

				if(strlen(leggere_nome(giocatore)) != 0)
				{
					int cella_attuale;

					cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));

					if(cella_attuale % PORTA_CHIUSA_SFONDABILE == 0 && cella_attuale != 0)
					{
						if(leggere_forza(giocatore) > 2)
						{
							rallentare_output("\nHai sfondato con successo la porta.\n",MILLISECONDI);
							cella_attuale /= PORTA_CHIUSA_SFONDABILE;
							scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
							rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
							rallentare_output("\n", MILLISECONDI);
						}
						else
						{
							rallentare_output("\nNon puoi sfondare la porta perche' non hai forza sufficiente.\n",MILLISECONDI);
						}
					}
					else if((cella_attuale % PORTA_RE == 0 || cella_attuale % PORTA_SEMPLICE == 0) && cella_attuale != 0)
					{
						rallentare_output("\nQuesta porta e' piu' dura rispetto alle altre, non riesci a sfondarla!\n",MILLISECONDI);
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
	}
	else if(confrontare_stringhe(token, PRENDI))
	{
		if(leggere_dimensione_tabella_simboli() > 1)
		{
			token = leggere_token_tabella_simboli(1);

			if(confrontare_stringhe(token, FRAMMENTO))
			{
				if(leggere_dimensione_tabella_simboli() == 3)
				{
					token = leggere_token_tabella_simboli(2);

					if(confrontare_stringhe(token, MAPPA))
					{
						esito = true;
					}
				}
				else
				{
					esito = true;
				}

				if(esito == true)
				{
					int cella_attuale;

					cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));

					if(cella_attuale % PEZZO_MAPPA_EST == 0 && cella_attuale != 0)
					{
						scrivere_frammento_est(&inv, true);
						rallentare_output("\nHai preso il frammento di mappa EST!\n", MILLISECONDI);
						cella_attuale /= PEZZO_MAPPA_EST;
						scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
						rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);

					}
					else if(cella_attuale % PEZZO_MAPPA_NORD == 0 && cella_attuale != 0)
					{
						scrivere_frammento_nord(&inv, true);
						rallentare_output("\nHai preso il frammento di mappa NORD!\n", MILLISECONDI);
						cella_attuale /= PEZZO_MAPPA_NORD;
						scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
						rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);

					}
					else if(cella_attuale % PEZZO_MAPPA_SUD == 0 && cella_attuale != 0)
					{
						scrivere_frammento_sud(&inv, true);
						rallentare_output("\nHai preso il frammento di mappa SUD!\n", MILLISECONDI);
						cella_attuale /= PEZZO_MAPPA_SUD;
						scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
						rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);

					}
					else
					{
						gestire_errore_semantico();
					}
				}
			}
			else if(confrontare_stringhe(token, CHIAVE) && leggere_dimensione_tabella_simboli() == 2)
			{
				esito = true;

				int cella_attuale;

				cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));

				if(cella_attuale % CHIAVE_SEMPLICE == 0 && cella_attuale != 0)
				{
					scrivere_chiave_semplice(&inv, true);
					rallentare_output("\nHai raccolto la chiave semplice!\n", MILLISECONDI);
					cella_attuale /= CHIAVE_SEMPLICE;
					scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
					rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
				}
				else
				{
					gestire_errore_semantico();
				}
			}
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

void gestire_finale(bool cifrato)
{
	stringa risposta = "";
	stringa risposta_indovinello = "";
	risposta = allocare_stringa(risposta, 0);
	risposta_indovinello = allocare_stringa(risposta_indovinello, 0);

	pulire_schermo();

	if(cifrato == true)
	{
		risposta = leggere_file_storia("storia/finale cifrato.txt", risposta);
		rallentare_output(risposta, MILLISEC_FINALE);

		do
		{
			rallentare_output("\n\nInserisci il nome di tale animale: ", MILLISECONDI);
			risposta_indovinello = leggere_stringa_tastiera(risposta_indovinello);

			if(confrontare_stringhe(convertire_stringa_minuscolo(risposta_indovinello), "serpente") == false)
			{
				rallentare_output("\nRisposta sbagliata!\n", MILLISECONDI);
			}
		}
		while(confrontare_stringhe(convertire_stringa_minuscolo(risposta_indovinello), "serpente") == false);

		pulire_schermo();

		risposta = leggere_file_storia("storia/finale cifrato2.txt", risposta);
		rallentare_output(risposta, MILLISEC_FINALE);

	}
	else
	{
		risposta = leggere_file_storia("storia/finale.txt", risposta);
		rallentare_output(risposta, MILLISEC_FINALE);
		ritardare_programma(5000);

		pulire_schermo();

		risposta = leggere_file_storia("storia/finale2.txt", risposta);
		rallentare_output(risposta, MILLISEC_FINALE);
	}


	ritardare_programma(5000);
	pulire_schermo();

	risposta = leggere_file_storia("storia/end.txt", risposta);
	rallentare_output(risposta, END);

	ritardare_programma(10000);
	pulire_schermo();

	impostare_avventura();
	free(risposta);
	free(risposta_indovinello);
}


