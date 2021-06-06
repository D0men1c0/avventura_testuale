/**
 * Questo è uno dei moduli principali ai fini della gestione generale dell'avventura.
 * La funzione gestire_avventura non fa altro che richiamare la funzione impostare_avventura all'apertura del gioco e,
 * in un ciclo legge continuamente il comando inserito dall'utente. L'unico modo per terminare la lettura del comando e quindi
 * chiudere il gioco è impostare la variabile globale chiusura_gioco a false e questo è possibile solo se l'utente, dopo aver
 * finito il gioco decide di uscire inserendo "si".
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
	 * La lettura del comando da tastiera viene inserita in un ciclo che non termina fino a quando l'utente finisce il gioco
	 * ed inserisce "si".
	*/

	while(chiusura_gioco == false)
	{
		leggere_comando();									//Chiamata della funzione per la lettura del comando da tastiera.
	}
}

void impostare_avventura()
{
	chiusura_gioco = false;									//La variabile chiusura_gioco viene di default impostata a false

	rallentare_output(COLORE_ROSSO, 0);						//Stampa che serve a colorare i successivi messaggi di rosso.
	rallentare_output(COLORE_BIANCO, 0);					//Stampa che serve a colorare i successivi messaggi di bianco.

	pulire_schermo();										//Chiamata della funzione per la pulizia dello schermo.

	stringa stringa_file = "";								//Inizializzazione della stringa che conterrà  il file contentente la schermata iniziale del gioco.
	
	stringa_file = leggere_file_testo("start.txt", stringa_file);		//Assegnazione della schermata iniziale del gioco nella stringa "stringa_file".
	rallentare_output(stringa_file, MILLISEC_CASTELLO);		//Visualizzazione della schermata iniziale del gioco.
	inizializzare_strutture_analizzatore();					//Chiamata della funzione per l'inizializzazione dell'analizzatore.
}


