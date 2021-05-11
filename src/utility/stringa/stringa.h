#ifndef STRINGA_H
#define STRINGA_H

/**
 * Questo modulo contiene il tipo di dato stringa con le relative funzioni legate ad esso. Il tipo di dato stringa è composto da un vettore
 * di caratteri. Si è deciso di utilizzare il tipo di dato stringa in quanto riteniamo sia più comodo poter gestire il tipo di dato stringa
 * anzichè usare di volta in volta char * e poter sfruttare funzioni legate al tipo di dato. Perciò data la scelta dell'uso del tipo di dato,
 * sono state implementate le relative funzioni di leggere_stringa la quale ha in input la stringa e restituisce un vettore di caratteri,
 * scrivere_carattere che ha in input la stringa sulla quale bisogna operare, l'indice cioè la posizione in cui andare ad inserire il
 * carattere, e il carattere e restituisce la stringa di input in cui è stata aggiornata aggiungendo il carattere di input.
 * Funzione simile è leggere_carattere la quale riceve in input la stringa e l'indice e restituisce il carattere che si vuole leggere.
 * La funzione scrivere_stringa che riceve in input una stringa e un char *, ha il compito di copiare tutti i caratteri all'interno della
 * stringa senza dover inserire volta per volta ciascun carattere, infatti restituisce come output i caratteri copiati.
 * Inoltre è presente la funzione allocare_stringa in quanto si è scelto di operare su un vettore dinamico e dunque la funzione allocare
 * stringa, che riceve in input la stringa e la dimensione, ha il compito di allocare spazio dinamicamente all'interno della stringa.
 * E' anche presente la funzione concatenare_stringhe che riceve come input 1 stringa e una serie di caratteri, come output resituisce
 * la prima stringa concatenata con i caratteri.
 * Per concludere è stata definita la costante DIM_STRINGA per poter reallocare spazio con l'oppurtuna funzione realloc definita in
 * allocare_stringa.
 */

#include "../bool.h"

#define DIM_STRINGA 100

typedef char * stringa;

stringa leggere_stringa(stringa str);
stringa scrivere_stringa(stringa str, stringa str_2);
char leggere_carattere(stringa str, int indice);
stringa scrivere_carattere(stringa str, int indice, char c);
stringa allocare_stringa(stringa str, int dimensione);
stringa concatenare_stringhe(stringa str, stringa str_2);
stringa shiftare_sinistra(stringa str, int ripetizioni);
stringa leggere_stringa_tastiera(stringa str);
int leggere_lunghezza(stringa str);
int convertire_intero(stringa str);
char convertire_minuscolo(char c);
bool confrontare_stringhe(stringa str1, stringa str2);
stringa convertire_stringa_minuscolo(stringa str);

#endif


