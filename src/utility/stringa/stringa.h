#define DIM_STRINGA 100

typedef struct {
  char * stringa;
  int lunghezza;
} stringa;

char * leggere_stringa(stringa str);
void scrivere_carattere(stringa * str, int indice, char carattere);
void allocare_stringa(stringa * str, int dimensione);
char leggere_carattere(stringa str, int indice);
void scrivere_stringa(stringa * str, char * caratteri);
int dimensione_stringa(stringa str);
