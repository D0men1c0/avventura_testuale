#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringa.h"

char * leggere_stringa(stringa str)
{
  return str.stringa;
}

void scrivere_carattere(stringa * str, int indice, char carattere)
{
  if (indice % DIM_STRINGA == 0)
  {
    allocare_stringa(str, indice);
  }

  *(str->stringa + indice) = carattere;
}

void scrivere_stringa(stringa * str, char * caratteri)
{
  int i;

  i = 0;
  while(i < strlen(caratteri))
  {
    scrivere_carattere(str, i, caratteri[i]);

    i++;
  }

  scrivere_carattere(str, i, '\0');
}

char leggere_carattere(stringa str, int indice)
{
  return *(str.stringa + indice);
}

int dimensione_stringa(stringa str)
{
  return (sizeof((str.stringa)) / sizeof((str.stringa)[0]));
}

/** Se la dimensione è uguale a 0, esegue la malloc,
* altrimenti se c'è bisogno di assegnare nuovo spazio
* esegue la realloc.
*/
void allocare_stringa(stringa * str, int dimensione)
{
  if(dimensione == 0)
  {
    str->stringa =  malloc(sizeof(char) * DIM_STRINGA);
  }
  else
  {
    str->stringa = realloc(str->stringa, (dimensione + DIM_STRINGA) * sizeof(char));
  }
}

