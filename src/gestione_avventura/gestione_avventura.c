/**
 * Questo è uno dei moduli principali ai fini della gestione generale dell'avventura.
 * Esso contiene infatti tutte la variabili globali che servono a gestire interamente il personaggio e l'ambiente di gioco.
 * Sono inoltre presenti due funzioni molto importanti per il funzionamento del gioco.
 * La funzione per la gestione dell'avventura è quella che di fatto la imposta, richiamando la funzione apposita e occupandosi
 * della continua richiesta di input da parte del giocatore.
 * La funzione per l'impostazione dell'avventura visualizza la schermata principale del gioco tramite la funzione che permette
 * la visualizzazione lenta dei messaggi e successivamente imposta le strutture dell'analizzatore lessicale tramite funzione dedicata. 
*/

#include <stdio.h>
#include <stdlib.h>
#include "../utility/utility.h"
#include "../analizzatore/strutture_analizzatore.h"
#include "../gestione_file/gestione_file.h"
#include "../inventario/gestione_inventario.h"
#include "../personaggio/gestione_personaggio.h"

void impostare_avventura();									//Funzione che imposta l'avventura e che visualizza la schermata iniziale del gioco.

void gestire_avventura()
{
	impostare_avventura();									//Chiamata della funzione che serve a impostare l'avventura.
	
	/**
	 * La lettura del comando da tastiera viene inserita in un ciclo infinito, cos� da richiedere per ogni azione un nuovo comando
	 * da eseguire.
	*/

	while(chiusura_gioco == false)
	{
		leggere_comando();									//Chiamata della funzione per la lettura del comando da tastiera.
	}
}

void impostare_avventura()
{
	chiusura_gioco = false;

	rallentare_output(COLORE_ROSSO, 0);						//Stampa che serve a colorare i successivi messaggi di rosso.
	rallentare_output(COLORE_BIANCO, 0);					//Stampa che serve a colorare i successivi messaggi di bianco.

	pulire_schermo();										//Chiamata della funzione per la pulizia dello schermo.

	stringa stringa_file = "";								//Inizializzazione della stringa che conterrà il file contentente la schermata iniziale del gioco.
	
	stringa_file = leggere_file_testo("start.txt", stringa_file);		//Assegnazione della schermata iniziale del gioco nella stringa "stringa_file".
	rallentare_output(stringa_file, MILLISEC_CASTELLO);		//Visualizzazione della schermata iniziale del gioco.
	inizializzare_strutture_analizzatore();					//Chiamata della funzione per l'inizializzazione dell'analizzatore.
}


