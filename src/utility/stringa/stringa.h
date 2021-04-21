/**
 * Questo modulo contiene il tipo di dato stringa con le relative funzioni legate ad esso. Il tipo di dato stringa � composto da un vettore
 * di caratteri. Si � deciso di utilizzare il tipo di dato stringa in quanto riteniamo sia pi� comodo poter gestire il tipo di dato stringa
 * anzich� usare di volta in volta char * e poter sfruttare funzioni legate al tipo di dato. Perci� data la scelta dell'uso del tipo di dato,
 * sono state implementate le relative funzioni di leggere_stringa la quale ha in input la stringa e restituisce un vettore di caratteri,
 * scrivere_carattere che ha in input la stringa sulla quale bisogna operare, l'indice cio� la posizione in cui andare ad inserire il
 * carattere, e il carattere e restituisce la stringa di input in cui � stata aggiornata aggiungendo il carattere di input.
 * Funzione simile � leggere_carattere la quale riceve in input la stringa e l'indice e restituisce il carattere che si vuole leggere.
 * La funzione scrivere_stringa che riceve in input una stringa e un char *, ha il compito di copiare tutti i caratteri all'interno della
 * stringa senza dover inserire volta per volta ciascun carattere, infatti restituisce come output i caratteri copiati.
 * Inoltre � presente la funzione allocare_stringa in quanto si � scelto di operare su un vettore dinamico e dunque la funzione allocare
 * stringa, che riceve in input la stringa e la dimensione, ha il compito di allocare spazio dinamicamente all'interno della stringa.
 * E' anche presente la funzione concatenare_stringhe che riceve come input 1 stringa e una serie di caratteri, come output resituisce
 * la prima stringa concatenata con i caratteri.
 * Per concludere � stata definita la costante DIM_STRINGA per poter reallocare spazio con l'oppurtuna funzione realloc definita in
 * allocare_stringa.
 */
#define DIM_STRINGA 100

typedef struct {
  char * stringa;
} stringa;

char * leggere_stringa(stringa str);
void scrivere_stringa(stringa * str, char * str_2);
char leggere_carattere(stringa str, int indice);
void scrivere_carattere(stringa * str, int indice, char c);
void allocare_stringa(stringa * str, int dimensione);
void concatenare_stringhe(stringa * str, char * str_2);

