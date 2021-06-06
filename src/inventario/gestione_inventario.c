/**
 * Questo modulo contiene tutte le informazioni necessarie alla gestione dell'inventario. Presenta la funzione inizializza_inventario che viene richiamata
 * alla creazione di una nuova partita, impostando quindi tutte le chiavi e i frammenti a false(tranne per il frammento ovest che di default è impostato a true).
 * La funzione stampare_inventario, legge ogni frammento e ogni chiave presente nell'inventario e ne stampa un messaggio se presente.
 * La funzione visualizzare_mappa invece permette di stampare a video la concatenazione dei file di testo che rappresentano i frammenti di mappa posseduti
 * dall'utente, esempio: se l'utente possiede 2 frammenti mappa est e ovest(impostati a true nell'inventario) verranno concatenati i file di testo riguardanti
 * il frammento mappa est e ovest con due file contenenti spazi pari al numero di caratteri dei file di testo "mancanti" (nord e sud).
 * L'idea di base è quella di leggere la prima riga del primo file e la prima riga  del secondo file, per poi continuare con la 2° riga del primo file e la 2° riga
 * del secondo file. Quando questi due file sono finiti si procede con la prima riga del 3° file e la prima riga del 4° file eccetera fino a quando non si conclude
 * la lettura di tutti e 4 i file.
*/

#include <stdio.h>
#include <stdlib.h>
#include "gestione_inventario.h"
#include "../gestione_file/gestione_file.h"

bool leggere_frammento_est(inventario inv)
{
	return inv.frammento_mappa_est;				 			//Restituzione del valore che dice se è presente il frammento est della mappa nell'inventario.
}

bool leggere_frammento_ovest(inventario inv)
{
	return inv.frammento_mappa_ovest;						//Restituzione del valore che dice se è presente il frammento ovest della mappa nell'inventario.
}

bool leggere_frammento_nord(inventario inv)
{
	return inv.frammento_mappa_nord;						//Restituzione del valore che dice se è presente il frammento nord della mappa nell'inventario.
}

bool leggere_frammento_sud(inventario inv)
{
	return inv.frammento_mappa_sud;							//Restituzione del valore che dice se è presente il frammento sud della mappa nell'inventario.
}

bool leggere_chiave_semplice(inventario inv)
{
	return inv.chiave_semplice;								//Restituzione del valore che dice se è presente la chiave semplice nell'inventario.
}

bool leggere_chiave_re(inventario inv)
{
	return inv.chiave_re;									//Restituzione del valore che dice se è presente la chiave del Re nell'inventario.
}

void scrivere_frammento_est(inventario *inv, bool valore)
{
	inv->frammento_mappa_est = valore;						//Modifica del valore booleano che indica se è presente il frammento est della mappa nell'inventario.
}

void scrivere_frammento_ovest(inventario *inv, bool valore)
{
	inv->frammento_mappa_ovest = valore;					//Modifica del valore booleano che indica se è presente il frammento ovest della mappa nell'inventario.
}

void scrivere_frammento_nord(inventario *inv, bool valore)
{
	inv->frammento_mappa_nord = valore;						//Modifica del valore booleano che indica se è presente il frammento nord della mappa nell'inventario.
}

void scrivere_frammento_sud(inventario *inv, bool valore)
{
	inv->frammento_mappa_sud = valore;						//Modifica del valore booleano che indica se è presente il frammento sud della mappa nell'inventario.
}

void scrivere_chiave_semplice(inventario *inv, bool valore)
{
	inv->chiave_semplice = valore;							//Modifica del valore booleano che indica se è presente la chiave semplice nell'inventario.
}

void scrivere_chiave_re(inventario *inv, bool valore)
{
	inv->chiave_re = valore;								//Modifica del valore booleano che indica se è presente la chiave del Re nell'inventario.
}


void inizializza_inventario(inventario *inv)
{
	scrivere_frammento_nord(inv, false);					//Inizializzazione dell'inventario senza frammento nord della mappa.
	scrivere_frammento_sud(inv, false);						//Inizializzazione dell'inventario senza frammento sud della mappa.
	scrivere_frammento_est(inv, false);						//Inizializzazione dell'inventario senza frammento est della mappa.
	scrivere_frammento_ovest(inv, true);					//Inizializzazione dell'inventario con il frammento ovest della mappa presente.
	scrivere_chiave_re(inv, false);							//Inizializzazione dell'inventario senza chiave del Re.
	scrivere_chiave_semplice(inv, false);					//Inizializzazione dell'inventario senza chiave semplice.
}


void stampare_inventario()
{	
	/**
	 * Attraverso questa serie di strutture di controllo, il giocatore può sapere cosa è presente nel suo inventario tramite apposito
	 * comando. Quindi tutti i valori che saranno impostati a true, saranno visualizzati nel messaggio.
	*/
	rallentare_output("\nINVENTARIO:\n", MILLISECONDI);

	if(leggere_frammento_nord(inv) == true)
	{
		rallentare_output("\nPossiedi il frammento di mappa nord!\n", MILLISECONDI);
	}

	if(leggere_frammento_est(inv) == true)
	{
		rallentare_output("\nPossiedi il frammento di mappa est!\n", MILLISECONDI);
	}

	if(leggere_frammento_sud(inv) == true)
	{
		rallentare_output("\nPossiedi il frammento di mappa sud!\n", MILLISECONDI);
	}

	if(leggere_frammento_ovest(inv) == true)
	{
		rallentare_output("\nPossiedi il frammento di mappa ovest!\n", MILLISECONDI);
	}

	if(leggere_chiave_semplice(inv) == true)
	{
		rallentare_output("\nPossiedi la chiave semplice!\n", MILLISECONDI);
	}

	if(leggere_chiave_re(inv) == true)
	{
		rallentare_output("\nPossiedi la chiave del re!\n", MILLISECONDI);
	}

	rallentare_output("\n", MILLISECONDI);
}

stringa visualizzare_frammenti_mappa(stringa risposta)
{
	stringa frammenti[4];									//Array di stringhe che conterrà  i frammenti di mappa presenti nell'inventario.
	stringa frammento_nord = "";							//Stringa che conterrà  il frammento nord della mappa.
	stringa frammento_est = "";								//Stringa che conterrà  il frammento est della mappa.
	stringa frammento_sud = "";								//Stringa che conterrà  il frammento sud della mappa.
	stringa frammento_ovest = "";							//Stringa che conterrà  il frammento ovest della mappa.

	int i;													//Indice dei caratteri della stringa "risposta" in cui verranno inseriti i caratteri.
	int pos_1;												//Indice dei caratteri dedicato alle colonne dei frammenti nord ed est.
	int pos_2;												//Indice dei caratteri dedicato alle colonne dei frammenti ovest e sud.
	int j;													//Indice della prima struttura di ripetizione per l'inserimento dei frammenti. 
	int k;													//Indice dei caratteri dedicato alle righe dei frammenti.

	/**
	 * Se il frammento nord della mappa è presente nell'inventario, allora nella stringa "frammento_nord"
	 * andrà  il frammento corrispondente preso da un file ad esso dedicato. Se il frammento in questione non è invece
	 * presente nell'inventario, allora nella stringa verranno concatenate delle spaziature, anch'esse prese da un file di testo dedicato.
	*/

	if(leggere_frammento_nord(inv) == true)
	{
		frammento_nord = leggere_file_testo("mappa/pezzo_mappa1.txt", frammento_nord);				//Assegnazione di frammento_nord con il pezzo della mappa corrispondente.
	}
	else
	{
		frammento_nord = leggere_file_testo("mappa/pezzo_mappa_vuoto_2.txt", frammento_nord);		//Assegnazione di frammento_nord con degli spazi vuoti.
	}

	/**
	 * Se il frammento est della mappa è presente nell'inventario, allora nella stringa "frammento_est"
	 * andrà il frammento corrispondente preso da un file ad esso dedicato. Se il frammento in questione non è invece
	 * presente nell'inventario, allora nella stringa verranno concatenate delle spaziature, anch'esse prese da un file di testo dedicato.
	*/

	if(leggere_frammento_est(inv) == true)
	{
		frammento_est = leggere_file_testo("mappa/pezzo_mappa2.txt", frammento_est);				//Assegnazione di frammento_est con il pezzo della mappa corrispondente.
	}
	else
	{
		frammento_est = leggere_file_testo("mappa/pezzo_mappa_vuoto.txt", frammento_est);			//Assegnazione di frammento_est con degli spazi vuoti.
	}

	/**
	 * Se il frammento ovest della mappa è presente nell'inventario, allora nella stringa "frammento_ovest"
	 * andrà il frammento corrispondente preso da un file ad esso dedicato. Se il frammento in questione non è invece
	 * presente nell'inventario, allora nella stringa verranno concatenate delle spaziature, anch'esse prese da un file di testo dedicato.
	*/

	if(leggere_frammento_ovest(inv) == true)
	{
		frammento_ovest = leggere_file_testo("mappa/pezzo_mappa3.txt", frammento_ovest);			//Assegnazione di frammento_ovest con il pezzo della mappa corrispondente.
	}
	else
	{
		frammento_ovest = leggere_file_testo("mappa/pezzo_mappa_vuoto_3.txt", frammento_ovest);		//Assegnazione di frammento_ovest con degli spazi vuoti.
	}
	
	/**
	 * Se il frammento sud della mappa è presente nell'inventario, allora nella stringa "frammento_sud"
	 * andrà  il frammento corrispondente preso da un file ad esso dedicato. Se il frammento in questione non è invece
	 * presente nell'inventario, allora nella stringa verranno concatenate delle spaziature, anch'esse prese da un file di testo dedicato.
	*/
	
	if(leggere_frammento_sud(inv) == true)
	{
		frammento_sud = leggere_file_testo("mappa/pezzo_mappa4.txt", frammento_sud);				//Assegnazione di frammento_sud con il pezzo della mappa corrispondente.
	}
	else
	{
		frammento_sud = leggere_file_testo("mappa/pezzo_mappa_vuoto.txt", frammento_sud);			//Assegnazione di frammento_sud con degli spazi vuoti.
	}

	frammenti[0] = frammento_nord;							//Assegnazione della prima posizione di "frammenti" con la stringa "frammento_nord"
	frammenti[1] = frammento_est;							//Assegnazione della seconda posizione di "frammenti" con la stringa "frammento_est"
	frammenti[2] = frammento_ovest;							//Assegnazione della terza posizione di "frammenti" con la stringa "frammento_ovest"
	frammenti[3] = frammento_sud;							//Assegnazione della quarta posizione di "frammenti" con la stringa "frammento_sud"

	i = 0;
	j = 0;
	k = 0;

	/**
	 * Questa ciclo esterno serve ad assegnare alla stringa "risposta" un messaggio contentente i pezzi di mappa posseduti.
	 * Con la prima ripetizione vengono assegnati i frammenti nord ed ovest e con la seconda i frammenti est e sud.
	*/

	while(j < 2)
	{
		pos_1 = 0;											//Inizializzazione a zero dell'indice per le colonne dei frammenti nord e est.
		pos_2 = 0;											//Inizializzazione a zero dell'indice per le colonne dei frammenti ovest e sud.

		do{
			while(frammenti[k][pos_1] != '\n')				//Ciclo che inserisce in "risposta" il carattere corrispondente alla posizione k e pos_1.
			{
				risposta = scrivere_carattere(risposta, i, frammenti[k][pos_1]);		//Scrittura nella risposta del carattere corrispondente all'indice i nei frammenti nord o ovest.
				pos_1++;									//Incremento dell'indice per le colonne dei frammenti nord e est.
				i++;										//Incremento dell'indice per lo scorrimento dei caratteri della risposta.
			}
			pos_1++;										//Incremento dell'indice per le colonne dei frammenti nord e est.
			k++;											//Incremento dell'indice per le righe dei frammenti.

			while(frammenti[k][pos_2] != '\n')				//Ciclo che inserisce in "risposta" il carattere corrispondente alla posizione k e pos_2.
			{
				risposta = scrivere_carattere(risposta, i, frammenti[k][pos_2]);		//Scrittura nella risposta del carattere corrispondente all'indice i nei frammenti est o sud.
				pos_2++;									//Incremento dell'indice per le colonne dei frammenti ovest e sud.
				i++;										//Incremento dell'indice per lo scorrimento dei caratteri della risposta.
			}
			pos_2++;										//Incremento dell'indice per le colonne dei frammenti ovest e sud.
			risposta = scrivere_carattere(risposta, i, '\n');		//Scrittura nella risposta del carattere di new line.
			i++;											//Incremento dell'indice per lo scorrimento dei caratteri della risposta.
			k--;											//Decremento dell'indice per le righe dei frammenti.

		}while(pos_2 < leggere_lunghezza(frammenti[k+1]));

		k = 2;												//Assegnazione di k con il valore di due, per poter proseguire con i successivi frammenti di mappa.
		j++;
	}

	risposta = scrivere_carattere(risposta, i, '\0');

	return risposta;										//Restituzione del messaggio contenente i frammenti di mappa posseduti.
}
