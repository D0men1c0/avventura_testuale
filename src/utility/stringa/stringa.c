/**
 * Il seguente modulo ha il compito di racchiudere le vare funzioni per la gestione del tipo di dato stringa. La funzione leggere_stringa
 * serve per rendere più comodo il ritorno del tipo di dato stringa. La funzione scrivere_stringa, che ha in input due stringhe restituisce,
 * usando la funzione di libreria strcpy, la seconda stringa all'interno della prima stringa, senza dover copiare carattere per carattere,
 * La funzione scrivere_carattere, oltre a scrivere il carattere all'interno della stringa nella posizione indicata dall'indice, presenta
 * un SE che permette di allocare dinamicamente spazio alla stringa se quest'ultima presenta l'indice % 100 = 0.
 * La funzione leggere_carattere invece ha il compito di restituire appunto il carattere cercato all'interno della stringa in una determinata
 * posizione.
 * La funzione allocare_stringa ha il compito di allocare spazio alla stringa mediante la malloc, se gli elementi da inserire all'interno
 * della stringa dovessero essere molti, è presente la funzione realloc, la quale se si dovesse sforare la lunghezza viene richiamata
 * affichè si allochi nuovo spazio alla stringa.
 * La funzione concatenare_stringhe, grazie alla funzione di libreria strcat, restituisce i caratteri della prima stringa alla quale
 * sono stati concatenati i caratteri presenti nel vettore di caratteri.
 * La funzione leggere_lunghezza serve a restituire la lunghezza della stringa passata in input grazie alla funzione di libreria strlen.
 * La funzione confrontare_stringhe ha il compito di restituire un esito (true o false) se le due stringhe passate in input sono uguali.
 * La funzione shiftare_sinistra ha il compito di shiftare tutta la stringa verso destra di n_ripetizioni cioè dell'intero passato in input.
 * La funzione convertire stringa minuscolo ha il compito di sostituire i caratteri maiuscoli con quelli minuscoli della stringa
 * qualora dovessero essere presenti.
 * Infine la funzione convertire_minuscolo fa la stessa cosa di convertire_stringa_minuscolo ma non restituisce una stringa bensì un singolo
 * carattere convertito.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringa.h"
#include "../utility.h"

stringa leggere_stringa(stringa str)
{
  return str;
}

stringa scrivere_stringa(stringa str, stringa str_2)
{
	int lunghezza;

	free(str);												//serve a liberare spazio all'interno della stringa
	lunghezza = leggere_lunghezza(str_2);
	str = allocare_stringa(str, 0);							//inizializzo la dimensione della stringa partendo da 0
	str = allocare_stringa(str, lunghezza);
	strcpy(str, str_2);										//copiamo il contenuto di str_2 in str

	return str;
}

stringa scrivere_carattere(stringa str, int indice, char c)
{
  if (indice % DIM_STRINGA == 0)
  {
    str = allocare_stringa(str, indice);
  }

  str[indice] = c;

  return str;
}

char leggere_carattere(stringa str, int indice)
{
  return str[indice];
}


/** Se la dimensione è uguale a 0, esegue la malloc,
 * altrimenti se c'è bisogno di assegnare nuovo spazio
 * esegue la realloc.
 */
stringa allocare_stringa(stringa str, int dimensione)
{
  if(dimensione == 0)
  {
    str =  malloc(sizeof(char) * DIM_STRINGA);
  }
  else
  {
    str = realloc(str, (dimensione + DIM_STRINGA) * sizeof(char));
  }

  return str;
}

stringa concatenare_stringhe(stringa str, stringa str_2)
{
	return strcat(str, str_2);
}

int leggere_lunghezza(stringa str)
{
	int lunghezza;

	lunghezza = strlen(str);

	return lunghezza;
}


bool confrontare_stringhe(stringa str1, stringa str2)
{
	bool esito;

	esito = false;

	if(strcmp(str1, str2) == 0)
	{
		esito = true;
	}

	return esito;
}

stringa shiftare_sinistra(stringa str, int ripetizioni)
{
	int i;
	int j;

	i = 0;

	while(i < ripetizioni)
	{
		j = 0;

		while(j < leggere_lunghezza(str))
		{
			str[j] = leggere_carattere(str, j+1);
			j++;
		}

		str = scrivere_carattere(str, j, '\0');                                    //serve per inserire il carattere di fine stringa

		i++;
	}


	return str;
}

stringa convertire_stringa_minuscolo(stringa str)
{
	int i;

	i = 0;

	while(i < leggere_lunghezza(str))
	{
		if(leggere_carattere(str, i) >= 'A' && leggere_carattere(str, i) <= 'Z')
		{
			str[i] = leggere_carattere(str, i) + 'a' - 'A';
		}

		i++;
	}

	return str;
}

char convertire_minuscolo(char c)
{
	if(c >= 'A' && c <= 'Z')
	{
		  c += 'a' - 'A';
	}

	return c;
}
