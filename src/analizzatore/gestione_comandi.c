/**
 * All'interno del seguente modulo vengono riportate tutte le funzioni per gestire i comandi della partita.
 * La funzione iniziare_partita si occupa di inizializzare gli attributi del personaggio richiamando la funzione impostare inizio e fornisce
 * all'utente la scelta di iniziare con la storia o resettare i valori inseriti a forza e intelligenza per poterli reinserire, ciclando fin
 * quando c'è una risposta negativa da parte dell'utente nel voler iniziare la storia.
 * La funzione salvare_partita ha il compito di scrivere su file binario, grazie alla funzione accodare_file_salvataggio, le strutture di:
 * personaggio, inventario, matrice (mappa), posizione. Dunque ha il compito di salvare i progressi dell'utente fino a quel punto.
 * La funzione caricare_partita ha il compito di leggere da file binario ciò che è stato scritto precedentemente dal comando salvare_partita.
 * La funzione stampare_aiuto consente di stampare un file di testo che riepiloga tutti i comandi possibili che l'utente può effettuare con
 * le corrispettive funzionalità.
 * La funzione visualizzare_attributi , stampa a video quelli che sono gli attributi del giocatore cioè il nome, la vita, la forza e
 * l'intelligenza. Comando simile è visualizzare_inventario che ha il compito di stampare gli oggetti presenti nell'inventario in base se
 * questi ultimi sono avvalorati a true.
 * Visualizzare_mappa invece permette di stampare a video la concatenazione dei file di testo che rappresentano i frammenti di mappa posseduti
 * dall'utente, es: se l'utente possiede 2 frammenti mappa est e ovest(impostati a true nell'inventario) verranno concatenati i file di testo
 * riguardanti il frammento mappa_est e ovest con due file contenenti spazi pari al numero di caratteri dei file di testo "mancanti"
 * (nord e sud).
 * La funzione esaminare_stanza ha il compito , qualora ci fossero dei file di testo sulla cella della matrice, di stamparne il contenuto.
 * La funzione aprire_porta serve per poter aprire una porta_semplice se abbiamo nell'inventario la chiave_semplice e se ci troviamo nella
 * cella della matrice appropriata (PORTA_SEMPLICE).
 * La funzione aprire_botola serve per poter giungere al finale del gioco solo nel caso in cui l'utente possieda tutti e 4 i frammenti di mappa
 * e si trovi nella cella della matrice appropriata(BOTOLE), inoltre è presente un'ulteriore condizione in base all'intelligenza posseduta
 * dal personaggio che se sarà maggiore di 2 non dovrà risolvere alcun indovinello, altrimenti dovrà risolverlo prima di poter visualizzare
 * il finale completo, tutto questo controllo è gestito dalla funzione gestire_finale che esegue dei controlli in base all'intelligenza.
 * La funzione sfondare_porta serve, sempre se ci troviamo in una cella della matrice appropriata (PORTA_CHIUSA_SFONDABILE), di poter
 * "oltrepassare" tale porta se il personaggio ha una forza maggiore di 2, altrimenti non può proseguire oltre e può solo tornare indietro.
 * Le funzioni prendere_frammento e prendere_chiave hanno lo stesso scopo, cioè se il giocatore si trova nella cella appropriata può prendere
 * il frammento di mappa o la chiave corrispondente, avvalorando a true (all'interno della struttura inventario)il campo corrispondente
 * all'oggetto raccolto.
 * La funzione muovere_personaggio ha il compito di effettuare una serie di controlli (muro, porte ecc), per far effettuare lo spostamento
 * del personaggio (nord, sud, est o ovest).
 * Infine la funzione gestire_errore_semantico stampa un messaggio di errore qualora ogni comando non presenti i vincoli contestuali richiesti.
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../utility/stringa/stringa.h"
#include "comandi.h"
#include "strutture_analizzatore.h"
#include "../inventario/gestione_inventario.h"
#include "../gestione_avventura/gestione_mappa.h"
#include "../gestione_file/gestione_file.h"
#include "../personaggio/gestione_personaggio.h"

// Funzioni per i comandi globali
void iniziare_partita();
bool salvare_partita(stringa nome_file);
void caricare_partita();
bool stampare_aiuto();

// Funzioni per i comandi in partita
void visualizzare_attributi();
void visualizzare_mappa();
void esaminare_stanza();
void aprire_porta();
void aprire_botola();
void sfondare_porta();
void prendere_frammento();
void prendere_chiave();
void gestire_finale(bool cifrato);

// Funzione per lo spostamento del personaggio
void muovere_personaggio(stringa direzione);

// Funzione che stampa "Non puoi usare questo comando qui!"
void gestire_errore_semantico();

void gestire_movimenti()
{
	if(leggere_lunghezza(leggere_nome(giocatore)) != 0)
	{
		muovere_personaggio(leggere_token_tabella_simboli(0));
	}
	else
	{
		gestire_errore_semantico();
	}
}

bool gestire_comandi_globali()
{
	bool esito;

	parola_chiave token;

	token = leggere_token_tabella_simboli(0);

	esito = false;

	if(confrontare_stringhe(token, NUOVA))
	{
		iniziare_partita();
		esito = true;
	}
	else if(confrontare_stringhe(token, AIUTO) == true)
	{
		esito = stampare_aiuto();
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

	return esito;
}


bool gestire_azioni_partita()
{
	bool esito;

	parola_chiave token = leggere_token_tabella_simboli(0);

	esito = false;

	// Se ci si trova in partita in corso (quindi il nome del giocatore esiste)
	if(leggere_lunghezza(leggere_nome(giocatore)) != 0)
	{
		if(confrontare_stringhe(token, VISUALIZZA))
		{
			if(leggere_dimensione_tabella_simboli() == 2)
			{
				token = leggere_token_tabella_simboli(1);

				if(confrontare_stringhe(token, ATTRIBUTI))
				{
					visualizzare_attributi();
					esito = true;
				}
				else if(confrontare_stringhe(token, INVENTARIO))
				{
					stampare_inventario();
					esito = true;
				}
				else if(confrontare_stringhe(token, MAPPA))
				{
					visualizzare_mappa();
					esito = true;
				}
				else
				{
					gestire_errore_semantico();
				}
			}
			else
			{
				rallentare_output("\nSintassi non riconosciuta! ", MILLISECONDI);
			}
		}
		else if(confrontare_stringhe(token, ESAMINA))
		{
			if(leggere_dimensione_tabella_simboli() == 2)
			{
				token = leggere_token_tabella_simboli(1);

				if(confrontare_stringhe(token, STANZA))
				{
					esaminare_stanza();
					esito = true;
				}
			}
			else
			{
				rallentare_output("\nSintassi non riconosciuta! ", MILLISECONDI);
			}
		}
		else if(confrontare_stringhe(token, APRI))
		{
			if(leggere_dimensione_tabella_simboli() == 2)
			{
				token = leggere_token_tabella_simboli(1);

				if(confrontare_stringhe(token, PORTA))
				{
					aprire_porta();
					esito = true;
				}
				else if(confrontare_stringhe(token, BOTOLA))
				{
					aprire_botola();
					esito = true;
				}
			}
			else
			{
				rallentare_output("\nSintassi non riconosciuta! ", MILLISECONDI);
			}
		}
		else if(confrontare_stringhe(token, SFONDA))
		{
			if(leggere_dimensione_tabella_simboli() == 2)
			{
				token = leggere_token_tabella_simboli(1);

				if(confrontare_stringhe(token, PORTA))
				{
					sfondare_porta();
					esito = true;
				}
			}
			else
			{
				rallentare_output("\nSintassi non riconosciuta! ", MILLISECONDI);
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
						prendere_frammento();
					}
				}
				else if(confrontare_stringhe(token, CHIAVE) && leggere_dimensione_tabella_simboli() == 2)
				{
					prendere_chiave();
					esito = true;
				}
				else
				{
					rallentare_output("\nSintassi non riconosciuta! ", MILLISECONDI);
				}
			}
		}
	}
	else
	{
		gestire_errore_semantico();
	}

	return esito;
}

void iniziare_partita()
{
	stringa risposta = "";
	risposta = allocare_stringa(risposta, 0); 										// Alloca la stringa


	// Ripete il ciclo fin quando non si inserisce "si" o "no"
	do
	{
		rallentare_output("\nSei sicuro di voler iniziare una nuova partita? Tutti i tuoi dati non salvati verranno persi! (si/no): ", MILLISECONDI);
		risposta = leggere_stringa_tastiera(risposta);								// Legge si/no da tastiera

		// Se la risposta è "si" convertita in minuscolo
		if(confrontare_stringhe(convertire_stringa_minuscolo(risposta), "si") == true)
		{
			impostare_inizio();														// Richiama la funzione di impostare_inizio e fa partire l'avventura
		}
		else if(confrontare_stringhe(convertire_stringa_minuscolo(risposta), "no") == false)
		{
			rallentare_output("\nComando non riconosciuto!", MILLISECONDI);			// Se la risposta è diversa anche da "no" convertita in minuscolo, stampa "Comando non riconosciuto!"
		}

	}
	while(confrontare_stringhe(convertire_stringa_minuscolo(risposta), "si") == false && confrontare_stringhe(convertire_stringa_minuscolo(risposta), "no") == false);
}

bool salvare_partita(stringa nome_file)
{
	bool esito;

	// Se ci si trova in partita in corso (quindi il nome del giocatore esiste)
	if(leggere_lunghezza(leggere_nome(giocatore)) != 0)
	{
		// Richiama la funzione di salvataggio passandogli il nome del file in cui salvare la partita
		esito = accodare_file_salvataggio(nome_file);

		// Se il file è stato salvato con successo stampa successo, altrimenti errore
		if(esito == true)
		{
			rallentare_output("\nHai salvato correttamente i dati di gioco! \n\n", MILLISECONDI);
		}
		else
		{
			rallentare_output("\nErrore nel salvataggio della partita in corso! \n", MILLISECONDI);
		}
	}
	else
	{
		gestire_errore_semantico();					// Stampa "Non puoi usare questo comando qui" se la partita non è incominciata
	}

	esito = true;

	return esito;
}

void caricare_partita()
{
	bool esito;

	esito = leggere_file_salvataggio(FILE_SALVATAGGIO);						// Leggi il file di salvataggio

	if(esito == true)														// Se è stato letto con successo
	{
		pulire_schermo();													// Ripulisci lo schermo e incomincia la partita
		rallentare_output("Hai caricato correttamente i dati di gioco! \n\n", MILLISECONDI);

		/*
		 * Se il personaggio si trovava in indice di colonna minore di 4, significa che si trovava nella sala del trono.
		 * Se il personaggio si trovava in indice di colonna minore di 8, significa che si trovava nelle celle.
		 * Se il personaggio si trovava in indice di colonna maggiore di 7, significa che si trovava nelle segrete.
		 */

		if(leggere_x(pos) < 4)
		{
			printf(COLORE_VERDE);
			rallentare_output("Ti trovavi nella sala del trono! \n\n", MILLISECONDI);
			printf(COLORE_BIANCO);
		}
		else if(leggere_x(pos) < 8)
		{
			printf(COLORE_VERDE);
			rallentare_output("Ti trovavi all'interno delle celle! \n\n", MILLISECONDI);
			printf(COLORE_BIANCO);
		}
		else
		{
			printf(COLORE_VERDE);
			rallentare_output("Ti trovavi nelle segrete! \n\n", MILLISECONDI);
			printf(COLORE_BIANCO);
		}

		rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);		// Stampa le direzioni disponibili al caricamento
		rallentare_output("\n", MILLISECONDI);
	}
	else
	{
		printf(COLORE_ROSSO);
		rallentare_output("\nErrore nel caricamento dei dati di gioco! \n", MILLISECONDI);	// Se il file non è stato letto con successo stampa errore
		printf(COLORE_BIANCO);
	}
}

bool stampare_aiuto()
{
	bool esito;

	stringa risposta = "";
	risposta = allocare_stringa(risposta, 0);							// Alloca la stringa

	esito = false;														// Imposta esito a false

	if(leggere_dimensione_tabella_simboli() < 2)						// Se c'è solamente un unico simbolo identificato dal token "aiuto"
	{
		risposta = leggere_file_testo("aiuto.txt", risposta);			// Leggi il file di aiuto
		rallentare_output(risposta, MILLISECONDI);						// Stampa il file di aiuto
		esito = true;													// Imposta esito a true
	}

	return esito;
}

void visualizzare_attributi()
{
	stringa risposta = "";
	risposta = allocare_stringa(risposta, 0);							// Alloca la stringa

	// Stampa la stringa leggendo i valori dal giocatore
	sprintf(risposta, "\nATTRIBUTI:\nTi chiami: %s \nLa vita e': %d \nLa forza e': %d\nL'intelligenza e': %d\n\n", leggere_nome(giocatore), leggere_vita(giocatore), leggere_forza(giocatore), leggere_intelligenza(giocatore));
	rallentare_output(risposta, MILLISECONDI);
}

void visualizzare_mappa()
{
	stringa risposta = "";
	risposta = allocare_stringa(risposta, 0);							// Alloca la stringa

	// Stampa la mappa richiamando visualizzare_frammenti_mappa nel modulo gestione_inventario
	risposta = visualizzare_frammenti_mappa(risposta);
	rallentare_output(risposta, MILLISEC_MAPPA);
}

void esaminare_stanza()
{
	stringa nome_file = "";
	stringa risposta = "";

	risposta = allocare_stringa(risposta, 0);							// Alloca la stringa
	nome_file = allocare_stringa(nome_file, 0);							// Alloca la stringa

	// Legge il file di testo da leggere prelevando la riga e la colonna dalla posizione attuale
	sprintf(nome_file, "storia/[%d][%d].txt", leggere_y(pos), leggere_x(pos));
	risposta = leggere_file_storia(nome_file, risposta);
	printf("\n--------------------------------------------------------------------------\n\n");
	rallentare_output(risposta, MILLISECONDI);
	printf("--------------------------------------------------------------------------\n\n");
}

void aprire_porta()
{
	int cella_attuale;

	// Legge la cella attuale prelevando i dati dalla posizione attuale
	cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));

	// Se la cella contiene una porta semplice
	if(cella_attuale % PORTA_SEMPLICE == 0 && cella_attuale != 0)
	{
		// Se nell'inventario c'è la chiave semplice, allora apri la porta semplice
		if(leggere_chiave_semplice(inv) == true)
		{
			printf(COLORE_CIANO);
			rallentare_output("\nHai aperto con successo la porta, utilizzando la chiave semplice!\n\n",MILLISECONDI);
			printf(COLORE_BIANCO);
			cella_attuale /= PORTA_SEMPLICE;
			// Togli dalla mappa la porta semplice, perchè ora è aperta
			scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),	cella_attuale);
			// Stampa nuovamente le direzioni disponibili ora che è aperta la porta
			rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
			printf("\n");
		}
		else
		{
			// Stampa non possiedi la chiave semplice se non si ha la chiave nell'inventario
			rallentare_output("\nNon possiedi la chiave semplice, dunque non puoi entrare qui!\n\n",MILLISECONDI);
		}
	}
	else if(cella_attuale % PORTA_RE == 0 && cella_attuale != 0)		// Se la cella contiene una porta del re
	{
		// Se nell'inventario c'è la chiave del re, allora apri la porta del re
		if(leggere_chiave_re(inv) == true)
		{
			printf(COLORE_CIANO);
			rallentare_output("\nHai aperto con successo la porta del re, utilizzando la chiave del re!\n\n",MILLISECONDI);
			printf(COLORE_BIANCO);
			cella_attuale /= PORTA_RE;
			// Togli dalla mappa la porta del re, perchè ora è aperta
			scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
			// Stampa nuovamente le direzioni disponibili ora che è aperta la porta
			rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
			printf("\n");
		}
		else
		{
			// Stampa non possiedi la chiave del re se non si ha la chiave nell'inventario
			rallentare_output("\nNon possiedi la chiave del Re, dunque non puoi entrare qui!\n\n",MILLISECONDI);
		}
	}
	else
	{
		// Stampa "Non puoi usare questo comando qui!" se non c'è una porta in quella cella
		gestire_errore_semantico();
	}
}

void aprire_botola()
{
	int cella_attuale;

	// Legge la cella attuale prelevando i dati dalla posizione attuale
	cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));

	// Se la cella attuale contiene una BOTOLE
	if(cella_attuale % BOTOLE == 0 && cella_attuale != 0)
	{
		// Se il giocatore possiede tutti e 4 i frammenti (ovest è gia impostato a true)
		if(leggere_frammento_sud(inv) && leggere_frammento_est(inv) && leggere_frammento_nord(inv))
		{
			// Se il giocatore possiede un'intelligenza maggiore di 2 apre direttamente il finale, altrimenti deve risolvere un indovinello
			if(leggere_intelligenza(giocatore) > 2)
			{
				gestire_finale(false);
			}
			else
			{
				gestire_finale(true);
			}
		}
		// Se non posside tutti i frammenti di mappa non può accedere al finale
		else
		{
			rallentare_output("\nNon hai ancora raccolto tutti i frammenti di mappa!\n\n", MILLISECONDI);
		}
	}
	else
	{
		gestire_errore_semantico();
	}

}

void sfondare_porta()
{
	int cella_attuale;
	// Legge la cella attuale prelevando i dati dalla posizione attuale
	cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));

	// Se la cella contiene una porta_chiusa_sfondabile
	if(cella_attuale % PORTA_CHIUSA_SFONDABILE == 0 && cella_attuale != 0)
	{
		// Se la forza è maggiore di 2 può sfondare la porta
		if(leggere_forza(giocatore) > 2)
		{
			rallentare_output("\nHai sfondato con successo la porta.\n\n",MILLISECONDI);
			printf(COLORE_CIANO);
			rallentare_output("Visto il grande sforzo dovuto allo sfondamento della porta, ti sei indebolito. Hai perso 2 punti forza.\n\n",MILLISECONDI);
			printf(COLORE_BIANCO);
			cella_attuale /= PORTA_CHIUSA_SFONDABILE;
			// Perde 2 punti forza se ha sfondato con successo la porta
			scrivere_forza(&giocatore, leggere_forza(giocatore) - 2);
			scrivere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos), cella_attuale);
			rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
			printf("\n");
		}
		// Se l'utente ha una forza minore di 3 non può sfondare la porta e non può proseguire
		else
		{
			rallentare_output("\nNon puoi sfondare la porta perche' non hai forza sufficiente.\n\n",MILLISECONDI);
		}
	}
	// Se la cella invece non è una porta chiusa sfondabile non possiamo sfondare le altre porte
	else if((cella_attuale % PORTA_RE == 0 || cella_attuale % PORTA_SEMPLICE == 0) && cella_attuale != 0)
	{
		rallentare_output("\nQuesta porta e' piu' dura rispetto alle altre, non riesci a sfondarla!\n\n",MILLISECONDI);
	}
	else
	{
		gestire_errore_semantico();
	}
}

void prendere_frammento()
{
	int cella_attuale;
	// Legge la cella attuale prelevando i dati dalla posizione attuale
	cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));
	// Se la cella contiene un pezzo_mappa_est avvaloriamo a true il campo frammento_est all'interno dell'inventario
	if(cella_attuale % PEZZO_MAPPA_EST == 0 && cella_attuale != 0)
	{
		scrivere_frammento_est(&inv, true);
		printf(COLORE_VERDE);
		rallentare_output("\nHai preso il frammento di mappa EST!\n\n", MILLISECONDI);
		printf(COLORE_BIANCO);
		cella_attuale /= PEZZO_MAPPA_EST;
		scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
		rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
		printf("\n");

	}
	// Se la cella contiene un pezzo_mappa_nord avvaloriamo a true il campo frammento_nord all'interno dell'inventario
	else if(cella_attuale % PEZZO_MAPPA_NORD == 0 && cella_attuale != 0)
	{
		scrivere_frammento_nord(&inv, true);
		printf(COLORE_VERDE);
		rallentare_output("\nHai preso il frammento di mappa NORD!\n\n", MILLISECONDI);
		printf(COLORE_BIANCO);
		cella_attuale /= PEZZO_MAPPA_NORD;
		scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
		rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
		printf("\n");

	}
	// Se la cella contiene un pezzo_mappa_sud avvaloriamo a true il campo frammento_sud all'interno dell'inventario
	else if(cella_attuale % PEZZO_MAPPA_SUD == 0 && cella_attuale != 0)
	{
		scrivere_frammento_sud(&inv, true);
		printf(COLORE_VERDE);
		rallentare_output("\nHai preso il frammento di mappa SUD!\n\n", MILLISECONDI);
		printf(COLORE_BIANCO);
		cella_attuale /= PEZZO_MAPPA_SUD;
		scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
		rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
		printf("\n");

	}
	else
	{
		gestire_errore_semantico();
	}
}

void prendere_chiave()
{
	int cella_attuale;
	// Legge la cella attuale prelevando i dati dalla posizione attuale
	cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));
	// Se la cella contiene una CHIAVE_SEMPLICE avvaloriamo a true il campo chiave_semplice nell'inventario
	if(cella_attuale % CHIAVE_SEMPLICE == 0 && cella_attuale != 0)
	{
		if(cella_attuale % PORTA_CHIUSA_SFONDABILE == 0)
		{
			rallentare_output("\nNon riesci ad afferrare la chiave, bisogna necessariamente superare questa porta!\n\n", MILLISECONDI);
		}
		else
		{
			scrivere_chiave_semplice(&inv, true);
			printf(COLORE_GIALLO);
			rallentare_output("\nHai raccolto la chiave semplice!\n\n", MILLISECONDI);
			printf(COLORE_BIANCO);
			cella_attuale /= CHIAVE_SEMPLICE;
			scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
			rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
			printf("\n");
		}
	}
	// Se la cella contiene un CHIAVE_PORTA_RE avvaloriamo a true il campo chiave_re nell'inventario
	else if(cella_attuale % CHIAVE_PORTA_RE == 0 && cella_attuale != 0)
	{
		scrivere_chiave_re(&inv, true);
		printf(COLORE_GIALLO);
		rallentare_output("\nHai raccolto la chiave del re!\n\n", MILLISECONDI);
		printf(COLORE_BIANCO);
		cella_attuale /= CHIAVE_PORTA_RE;
		scrivere_valore_matrice(mappa,leggere_y(pos), leggere_x(pos),cella_attuale);
		rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
		printf("\n");
	}
	else
	{
		gestire_errore_semantico();
	}
}

void gestire_errore_semantico()
{
	rallentare_output("\nNon puoi usare questo comando qui!\n\n", MILLISECONDI);
}

void gestire_finale(bool cifrato)
{
	// Se abbiamo un'intelligenza minore di 3
	stringa risposta = "";
	stringa risposta_indovinello = "";
	risposta = allocare_stringa(risposta, 0);
	risposta_indovinello = allocare_stringa(risposta_indovinello, 0);

	pulire_schermo();

	if(cifrato == true)
	{
		risposta = leggere_file_storia("storia/finale cifrato.txt", risposta);
		rallentare_output(risposta, MILLISEC_FINALE);
		// Cicla fin quando l'utente non inserisce il nome "serpente"
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
	// Altrimenti l'utente non risolve nessun indovinello
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

	do
	{
		rallentare_output("Vuoi ritornare alla home? (si/no)", MILLISECONDI);
		risposta = leggere_stringa_tastiera(risposta);

		if(confrontare_stringhe(convertire_stringa_minuscolo(risposta), "si") == true)
		{

			impostare_avventura();
			scrivere_nome(&giocatore, "\0");
		}
		else if( confrontare_stringhe(convertire_stringa_minuscolo(risposta), "no") == true)
		{
			chiusura_gioco = true;
		}
		else
		{
			rallentare_output("\nComando non riconosciuto!", MILLISECONDI);
		}

	}
	while(confrontare_stringhe(convertire_stringa_minuscolo(risposta), "si") == false && confrontare_stringhe(convertire_stringa_minuscolo(risposta), "no") == false);


	free(risposta);
	free(risposta_indovinello);
}

void muovere_personaggio(stringa direzione)
{
	stringa stringa_file = "";										//Stringa in cui verrÃ  inserito il contenuto dei file di testo.
	int cella_successiva;											//Cella il cui il personaggio si troverÃ  dopo lo spostamento
	int cella_attuale;												//Cella in cui il personaggio si trova attualmente.
	posizione posizione_nord;										//Posizione a nord del personaggio.
	posizione posizione_sud;										//Posizione a sud del personaggio.
	posizione posizione_est;										//Posizione a est del personaggio.
	posizione posizione_ovest;										//Posizione a ovest del personaggio.
	posizione pos_successiva;
	time_t tempo;
	stringa percorso_file = "";
	srand((unsigned) time(&tempo));                                 //Serve per generare in modo randomico il file di testo dei muri

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
	 * altrimenti si procede con i controlli. Quindi Ã¨ presente un altro controllo che verifica che la cella attuale contenga una porta:
	 * in questo caso l'unica direzione consentita sarÃ  quella da cui siamo venuti. Quindi, dopo aver controllato che la posizione
	 * corrispondente al punto cardinale in questione Ã¨ uguale alla posizione precedente, viene effettuato lo spostamento aggiornando
	 * prima la posizione precedente e poi aggiornando le coordinate interessate della posizione corrente, stampando le nuove direzioni
	 * disponibili e richiamando la funzione che ci permette di gestire la cella. Altrimenti verrÃ  visualizzato un messaggio che ci
	 * avverte della presenza della porta e lo spostamento non avverrÃ .
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
				printf("\n");									//Stampa carattere di new line.
				gestire_cella();								//Chiamata della funzione per la gestione delle celle.
			}
		}
		else
		{
			posizione_precedente = pos;							//Aggiornamento posizione precedente.
			pos = pos_successiva;								//Modifica della posizione attuale.
			printf("\n");										//Stampa carattere di new line.
			gestire_cella();									//Chiamata della funzione per la gestione delle celle.
		}
	}
	else
	{
		percorso_file = allocare_stringa(percorso_file, 0);
		sprintf(percorso_file, "storia/muri/muro%d.txt", rand() % 4 + 1);	//Stampa del file di testo muro randomica
		stringa_file = leggere_file_testo(percorso_file, stringa_file);		//Assegnazione a stringa_file del contenuto del file di testo.
		printf("\n");
		rallentare_output(stringa_file, MILLISECONDI);			//Visualizzazione lenta del contenuto del file di testo.
	}
}
