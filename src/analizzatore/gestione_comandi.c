#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../utility/stringa/stringa.h"
#include "comandi.h"
#include "strutture_analizzatore.h"
#include "../inventario/gestione_inventario.h"
#include "../gestione_avventura/gestione_avventura.h"
#include "../gestione_avventura/gestione_mappa.h"
#include "../gestione_file/gestione_file.h"
#include "../personaggio/gestione_personaggio.h"

//funzioni per i comandi
stringa iniziare_partita(stringa risposta);
bool salvare_partita(stringa nome_file);
void caricare_partita();
stringa stampare_aiuto(stringa risposta, bool * esito);
stringa visualizzare_attributi();
stringa visualizzare_attributi(stringa risposta);
stringa visualizzare_inventario(stringa risposta);
stringa visualizzare_mappa(stringa risposta);
stringa esaminare_stanza(stringa risposta);
stringa aprire_porta(stringa risposta);
stringa aprire_botola(stringa risposta);
stringa sfondare_porta(stringa risposta);
stringa prendere_frammento(stringa risposta);
stringa prendere_chiave(stringa risposta);
void gestire_errore_semantico();
void gestire_finale(bool cifrato);
void muovere_personaggio(stringa direzione);					//Funzione per lo spostamento del personaggio.

bool gestire_movimenti()
{
	bool esito;

	esito = false;

	if(leggere_dimensione_tabella_simboli() == 1)
	{
		esito = true;

		if(leggere_lunghezza(leggere_nome(giocatore)) != 0)
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

bool gestire_comandi_globali()
{
	bool esito;

	stringa risposta = "";

	parola_chiave token = leggere_token_tabella_simboli(0);

	esito = false;

	if(confrontare_stringhe(token, NUOVA))
	{
		risposta = iniziare_partita(risposta);
		esito = true;
	}
	else if(confrontare_stringhe(token, AIUTO) == true)
	{
		risposta = stampare_aiuto(risposta, &esito);
	}
	else if(confrontare_stringhe(token, SALVA) == true)
	{
		esito = salvare_partita(FILE_SALVATAGGIO);
	}
	else if(confrontare_stringhe(token, CARICA) == true)
	{
		caricare_partita();
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
				risposta = visualizzare_attributi(risposta);
				esito = true;
			}
			else if(confrontare_stringhe(token, INVENTARIO))
			{
				risposta = visualizzare_inventario(risposta);
				esito = true;
			}
			else if(confrontare_stringhe(token, MAPPA))
			{
				risposta = visualizzare_mappa(risposta);
				esito = true;
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
				risposta = esaminare_stanza(risposta);
				esito = true;
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
				risposta = aprire_porta(risposta);
				esito = true;
			}
			else if(confrontare_stringhe(token, BOTOLA))
			{
				risposta = aprire_botola(risposta);
				esito = true;
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
				risposta = sfondare_porta(risposta);
				esito = true;
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
					risposta = prendere_frammento(risposta);
				}
			}
			else if(confrontare_stringhe(token, CHIAVE) && leggere_dimensione_tabella_simboli() == 2)
			{
				risposta = prendere_chiave(risposta);
				esito = true;
			}
		}
	}

	free(risposta);
	return esito;
}

stringa iniziare_partita(stringa risposta)
{
	do
	{
		rallentare_output("\nSei sicuro di voler iniziare una nuova partita? Tutti i tuoi dati non salvati verranno persi! (si/no): ", MILLISECONDI);
		risposta = leggere_stringa_tastiera(risposta);

		if(confrontare_stringhe(convertire_stringa_minuscolo(risposta), "si") == true)
		{
			impostare_inizio();
		}
		else if(confrontare_stringhe(convertire_stringa_minuscolo(risposta), "si") == false && confrontare_stringhe(convertire_stringa_minuscolo(risposta), "no") == false)
		{
			rallentare_output("\nComando non riconosciuto!", MILLISECONDI);
		}

	}
	while(confrontare_stringhe(convertire_stringa_minuscolo(risposta), "si") == false && confrontare_stringhe(convertire_stringa_minuscolo(risposta), "no") == false);

	return risposta;
}

bool salvare_partita(stringa nome_file)
{
	bool esito;

	if(leggere_lunghezza(leggere_nome(giocatore)) != 0)
	{
		esito = accodare_file_salvataggio(nome_file, giocatore, inv, mappa, pos);

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

	return esito;
}

void caricare_partita()
{
	bool esito;

	esito = leggere_file_salvataggio(FILE_SALVATAGGIO);

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
}

stringa stampare_aiuto(stringa risposta, bool * esito)
{
	if (leggere_dimensione_tabella_simboli() < 2)
	{
		risposta = leggere_file_testo("aiuto.txt", risposta);
		rallentare_output(risposta, MILLISECONDI);
		*esito = true;
	}

	return risposta;
}

stringa visualizzare_attributi(stringa risposta)
{
	if(leggere_lunghezza(leggere_nome(giocatore)) != 0)
	{
		sprintf(risposta, "\nATTRIBUTI:\nTi chiami: %s \nLa vita e': %d \nLa forza e': %d\nL'intelligenza e': %d\n\n", leggere_nome(giocatore), leggere_vita(giocatore), leggere_forza(giocatore), leggere_intelligenza(giocatore));
		rallentare_output(risposta, MILLISECONDI);
	}
	else
	{
		gestire_errore_semantico();
	}

	return risposta;
}

stringa visualizzare_inventario(stringa risposta)
{
	if(leggere_lunghezza(leggere_nome(giocatore)) != 0)
	{
		rallentare_output("\nINVENTARIO:\n", MILLISECONDI);
		stampare_inventario();
	}
	else
	{
		gestire_errore_semantico();
	}

	return risposta;
}

stringa visualizzare_mappa(stringa risposta)
{
	if(leggere_lunghezza(leggere_nome(giocatore)) != 0)
	{
		risposta = visualizzare_frammenti_mappa(risposta);
		rallentare_output(risposta, MILLISEC_MAPPA);
	}
	else
	{
		gestire_errore_semantico();
	}

	return risposta;
}

stringa esaminare_stanza(stringa risposta)
{
	stringa nome_file = "";

	if(leggere_lunghezza(leggere_nome(giocatore)) != 0)
	{
		nome_file = allocare_stringa(nome_file, 0);

		sprintf(nome_file, "storia/[%d][%d].txt", leggere_y(pos), leggere_x(pos));
		risposta = leggere_file_storia(nome_file, risposta);
		printf("\n--------------------------------------------------------------------------\n\n");
		rallentare_output(risposta, MILLISECONDI);
		printf("--------------------------------------------------------------------------\n\n");
	}
	else
	{
		gestire_errore_semantico();
	}

	return risposta;
}

stringa aprire_porta(stringa risposta)
{
	int cella_attuale;

	if(leggere_lunghezza(leggere_nome(giocatore)) != 0)
	{
		cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));

		if(cella_attuale % PORTA_SEMPLICE == 0 && cella_attuale != 0)
		{
			if(leggere_chiave_semplice(inv) == true)
			{
				rallentare_output("\nHai aperto con successo la porta, utilizzando la chiave semplice!\n\n",MILLISECONDI);
				cella_attuale /= PORTA_SEMPLICE;
				scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
				rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
				printf("\n");
			}
			else
			{
				rallentare_output("\nNon possiedi la chiave semplice, dunque non puoi entrare qui!\n\n",MILLISECONDI);
			}
		}
		else if(cella_attuale % PORTA_RE == 0 && cella_attuale != 0)
		{
			if(leggere_chiave_re(inv) == true)
			{
				rallentare_output("\nHai aperto con successo la porta del re, utilizzando la chiave del re!\n\n",MILLISECONDI);
				cella_attuale /= PORTA_RE;
				scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
				rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
				printf("\n");
			}
			else
			{
				rallentare_output("\nNon possiedi la chiave semplice, dunque non puoi entrare qui!\n\n",MILLISECONDI);
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

	return risposta;
}

stringa aprire_botola(stringa risposta)
{
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
			rallentare_output("\nNon hai ancora raccolto tutti i frammenti di mappa!\n\n", MILLISECONDI);
		}
	}
	else
	{
		gestire_errore_semantico();
	}

	return risposta;
}

stringa sfondare_porta(stringa risposta)
{
	int cella_attuale;

	if(leggere_lunghezza(leggere_nome(giocatore)) != 0)
	{
		cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));

		if(cella_attuale % PORTA_CHIUSA_SFONDABILE == 0 && cella_attuale != 0)
		{
			if(leggere_forza(giocatore) > 2)
			{
				rallentare_output("\nHai sfondato con successo la porta.\n\n",MILLISECONDI);
				cella_attuale /= PORTA_CHIUSA_SFONDABILE;
				scrivere_forza(&giocatore,leggere_forza(giocatore)-2);
				scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
				rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
				printf("\n");
			}
			else
			{
				rallentare_output("\nNon puoi sfondare la porta perche' non hai forza sufficiente.\n\n",MILLISECONDI);
			}
		}
		else if((cella_attuale % PORTA_RE == 0 || cella_attuale % PORTA_SEMPLICE == 0) && cella_attuale != 0)
		{
			rallentare_output("\nQuesta porta e' piu' dura rispetto alle altre, non riesci a sfondarla!\n\n",MILLISECONDI);
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

	return risposta;
}

stringa prendere_frammento(stringa risposta)
{
	int cella_attuale;

	cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));

	if(cella_attuale % PEZZO_MAPPA_EST == 0 && cella_attuale != 0)
	{
		scrivere_frammento_est(&inv, true);
		rallentare_output("\nHai preso il frammento di mappa EST!\n\n", MILLISECONDI);
		cella_attuale /= PEZZO_MAPPA_EST;
		scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
		rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);

	}
	else if(cella_attuale % PEZZO_MAPPA_NORD == 0 && cella_attuale != 0)
	{
		scrivere_frammento_nord(&inv, true);
		rallentare_output("\nHai preso il frammento di mappa NORD!\n\n", MILLISECONDI);
		cella_attuale /= PEZZO_MAPPA_NORD;
		scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
		rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);

	}
	else if(cella_attuale % PEZZO_MAPPA_SUD == 0 && cella_attuale != 0)
	{
		scrivere_frammento_sud(&inv, true);
		rallentare_output("\nHai preso il frammento di mappa SUD!\n\n", MILLISECONDI);
		cella_attuale /= PEZZO_MAPPA_SUD;
		scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
		rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);

	}
	else
	{
		gestire_errore_semantico();
	}

	return risposta;
}

stringa prendere_chiave(stringa risposta)
{
	int cella_attuale;

	cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));

	if(cella_attuale % CHIAVE_SEMPLICE == 0 && cella_attuale != 0)
	{
		scrivere_chiave_semplice(&inv, true);
		rallentare_output("\nHai raccolto la chiave semplice!\n\n", MILLISECONDI);
		cella_attuale /= CHIAVE_SEMPLICE;
		scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
		rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
	}
	else if(cella_attuale % CHIAVE_PORTA_RE == 0 && cella_attuale != 0)
	{
		scrivere_chiave_re(&inv, true);
		rallentare_output("\nHai raccolto la chiave del re!\n\n", MILLISECONDI);
		cella_attuale /= CHIAVE_PORTA_RE;
		scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
		rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
	}
	else
	{
		gestire_errore_semantico();
	}

	return risposta;
}

void gestire_errore_semantico()
{
	rallentare_output("\n\nNon puoi usare questo comando qui!\n\n", MILLISECONDI);
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
	scrivere_nome(&giocatore, "\0");
	free(risposta);
	free(risposta_indovinello);
}

void muovere_personaggio(stringa direzione)
{
	stringa stringa_file = "";										//Stringa in cui verrà inserito il contenuto dei file di testo.
	int cella_successiva;											//Cella il cui il personaggio si troverà dopo lo spostamento
	int cella_attuale;												//Cella in cui il personaggio si trova attualmente.
	posizione posizione_nord;										//Posizione a nord del personaggio.
	posizione posizione_sud;										//Posizione a sud del personaggio.
	posizione posizione_est;										//Posizione a est del personaggio.
	posizione posizione_ovest;										//Posizione a ovest del personaggio.
	posizione pos_successiva;
	time_t tempo;
	stringa percorso_file = "";
	srand((unsigned) time(&tempo));

	posizione_nord = posizione_sud = posizione_est = posizione_ovest = pos;		//Assegnazione alle varie variabili di posizione lo stesso valore della posizione del personaggio.

	scrivere_y(&posizione_nord, leggere_y(pos) - 1);				//Modifica di "posizione_nord" per impostarla a nord della posizione del personaggio.
	scrivere_y(&posizione_sud, leggere_y(pos) + 1);					//Modifica di "posizione_sud" per impostarla a sud della posizione del personaggio.
	scrivere_x(&posizione_est, leggere_x(pos) + 1);					//Modifica di "posizione_est" per impostarla a est della posizione del personaggio.
	scrivere_x(&posizione_ovest, leggere_x(pos) - 1);				//Modifica di "posizione_ovest" per impostarla a ovest della posizione del personaggio.

	cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));		//Assegnazione del valore corrispondente alla cella attuale della mappa.

	/**
	 * Questa sequenza di selezioni ci permette di confrontare la stringa "direzione" passata in input dalla funzione
	 * con i vari punti cardinali. Dentro ogni selezione viene prima impostata la cella successiva in base al punto cardinale
	 * con cui si sta confrontando attualmente la direzione, poi si controlla che questa non contenga un muro.
	 * Se contiene un muro, lo spostamento non avviene e viene stampato un file di testo che avverte della presenza di esso,
	 * altrimenti si procede con i controlli. Quindi è presente un altro controllo che verifica che la cella attuale contenga una porta:
	 * in questo caso l'unica direzione consentita sarà quella da cui siamo venuti. Quindi, dopo aver controllato che la posizione
	 * corrispondente al punto cardinale in questione è uguale alla posizione precedente, viene effettuato lo spostamento aggiornando
	 * prima la posizione precedente e poi aggiornando le coordinate interessate della posizione corrente, stampando le nuove direzioni
	 * disponibili e richiamando la funzione che ci permette di gestire la cella. Altrimenti verrà visualizzato un messaggio che ci
	 * avverte della presenza della porta e lo spostamento non avverrà.
	 * Se la cella attuale non contiene nessuna porta, vengono effettuate direttamente le operazioni di spostamento sopra descritte.
	*/

	if(confrontare_stringhe(direzione, NORD))
	{
		cella_successiva = leggere_valore_matrice(mappa, leggere_y(pos) - 1, leggere_x(pos));		//Assegnazione del valore corrispondente alla cella a nord della mappa.
		pos_successiva = posizione_nord;
	}

	if(confrontare_stringhe(direzione, SUD))
	{
		cella_successiva = leggere_valore_matrice(mappa, leggere_y(pos) + 1, leggere_x(pos));		//Assegnazione del valore corrispondente alla cella a nord della mappa.
		pos_successiva = posizione_sud;
	}

	if(confrontare_stringhe(direzione, EST))
	{
		cella_successiva = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos) + 1);		//Assegnazione del valore corrispondente alla cella a nord della mappa.
		pos_successiva = posizione_est;
	}

	if(confrontare_stringhe(direzione, OVEST))
	{
		cella_successiva = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos) - 1);		//Assegnazione del valore corrispondente alla cella a nord della mappa.
		pos_successiva = posizione_ovest;
	}


	if(cella_successiva != MURO)
	{
		if(cella_attuale % PORTA_CHIUSA_SFONDABILE == 0 || cella_attuale % PORTA_SEMPLICE == 0 || cella_attuale % PORTA_RE == 0)
		{
			if(leggere_y(posizione_precedente) != leggere_y(pos_successiva) || leggere_x(posizione_precedente) != leggere_x(pos_successiva))
			{
				rallentare_output("\nC'e' una porta chiusa davanti a te! Cerca un modo per superarla...\n\n", MILLISECONDI);		//Visualizzazione messaggio porta.
				rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);		//Visualizzazione lenta delle direzioni disponibili.
				printf("\n");
			}
			else
			{
				posizione_precedente = pos;						//Aggiornamento posizione precedente.
				pos = pos_successiva;							//Modifica della posizione attuale.
				//rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);		//Visualizzazione lenta delle direzioni disponibili.
				printf("\n");									//Stampa carattere di new line.
				gestire_cella();								//Chiamata della funzione per la gestione delle celle.
			}
		}
		else
		{
			posizione_precedente = pos;							//Aggiornamento posizione precedente.
			pos = pos_successiva;								//Modifica della posizione attuale.
			//rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);		//Visualizzazione lenta delle direzioni disponibili.
			printf("\n");										//Stampa carattere di new line.
			gestire_cella();									//Chiamata della funzione per la gestione delle celle.
		}
	}
	else
	{
		percorso_file = allocare_stringa(percorso_file, 0);
		sprintf(percorso_file, "storia/muri/muro%d.txt", rand() % 4 + 1);
		stringa_file = leggere_file_testo(percorso_file, stringa_file);		//Assegnazione a stringa_file del contenuto del file di testo.
		printf("\n");
		rallentare_output(stringa_file, MILLISECONDI);			//Visualizzazione lenta del contenuto del file di testo.
	}
}
