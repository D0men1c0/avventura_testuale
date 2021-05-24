/**
 * Il seguente modulo ha il compito di racchiudere le vare funzioni per la gestione del tipo di dato stringa. La funzione leggere_stringa
 * serve per rendere più comodo il ritorno del tipo di dato stringa. La funzione scrivere_stringa, che ha in input una stringa e un vettore
 * di caratteri, restituisce , usando la funzione di libreria strcpy, il vettore di caratteri all'interno della stringa, senza dover copiare
 * carattere per carattere, inoltre dato l'uso di una allocazione dinamica mediante la funzione malloc , non si devono effettuare controlli
 * per la lunghezza della prima stringa con il vettore di caratteri che si vuole copiare copiare. La funzione scrivere_carattere, oltre a
 * scrivere il carattere all'interno della stringa nella posizione indicata dall'indice, presenta un SE che permette di allocare dinamicamente
 * spazio alla stringa se quest'ultima presenta l'indice % 100 = 0. La funzione leggere_carattere invece ha il compito di restituire appunto
 * il carattere cercato all'interno della stringa in una determinata posizione. La funzione allocare_stringa ha il compito di allocare spazio
 * alla stringa mediante la malloc, se gli elementi da inserire all'interno della stringa dovessero essere molti, è presente la funzione
 * realloc, la quale se si dovesse sforare la lunghezza viene richiamata affichè si allochi nuovo spazio alla stringa.
 * Infine la funzione concatenare_stringhe, grazie alla funzione di libreria strcat, restituisce i caratteri della prima stringa alla quale
 * sono stati concatenati i caratteri presenti nel vettore di caratteri.
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
	int i = 0;

	while(i < leggere_lunghezza(str_2))
	{
		str = scrivere_carattere(str, i + leggere_lunghezza(str),  str_2[i]);
		i++;
	}

	str = scrivere_carattere(str, i + leggere_lunghezza(str),  '\0');

	return str;
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

		str = scrivere_carattere(str, j, '\0');

		i++;
	}


	return str;
}


int convertire_intero(stringa str)
{
	int intero;
	int i;
	char c;

	intero = 0;

	c = leggere_carattere(str, 0);

	i = 1;

	while(c != '\0' && c >= '0' && c <= '9')
	{
		intero = (c - '0') + intero * 10;
		c = leggere_carattere(str, i);

		i++;
	}

	return intero;
}

char convertire_minuscolo(char c)
{
	if(c >= 'A' && c <= 'Z')
	{
		  c += 'a' - 'A';
	}

	return c;
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
