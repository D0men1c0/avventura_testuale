/**
 * Il seguente modulo ha il compito di racchiudere le vare funzioni per la gestione del tipo di dato stringa. La funzione leggere_stringa
 * serve per rendere pi� comodo il ritorno del tipo di dato stringa. La funzione scrivere_stringa, che ha in input una stringa e un vettore
 * di caratteri, restituisce , usando la funzione di libreria strcpy, il vettore di caratteri all'interno della stringa, senza dover copiare
 * carattere per carattere, inoltre dato l'uso di una allocazione dinamica mediante la funzione malloc , non si devono effettuare controlli
 * per la lunghezza della prima stringa con il vettore di caratteri che si vuole copiare copiare. La funzione scrivere_carattere, oltre a
 * scrivere il carattere all'interno della stringa nella posizione indicata dall'indice, presenta un SE che permette di allocare dinamicamente
 * spazio alla stringa se quest'ultima presenta l'indice % 100 = 0. La funzione leggere_carattere invece ha il compito di restituire appunto
 * il carattere cercato all'interno della stringa in una determinata posizione. La funzione allocare_stringa ha il compito di allocare spazio
 * alla stringa mediante la malloc, se gli elementi da inserire all'interno della stringa dovessero essere molti, � presente la funzione
 * realloc, la quale se si dovesse sforare la lunghezza viene richiamata affich� si allochi nuovo spazio alla stringa.
 * Infine la funzione concatenare_stringhe, grazie alla funzione di libreria strcat, restituisce i caratteri della prima stringa alla quale
 * sono stati concatenati i caratteri presenti nel vettore di caratteri.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringa.h"

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


/** Se la dimensione � uguale a 0, esegue la malloc,
 * altrimenti se c'� bisogno di assegnare nuovo spazio
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
	strcat(str, str_2);

	return str;
}


int leggere_lunghezza(stringa str)
{
	int lunghezza;

	lunghezza = strlen(str);

	return lunghezza;
}


