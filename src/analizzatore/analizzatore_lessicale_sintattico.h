bool controllare_simboli_tabella();

#ifndef ANALIZZATORE_LESSICALE_SINTATTICO_H
#define ANALIZZATORE_LESSICALE_SINTATTICO_H

#include "../utility/utility.h"

#define SUCCESSO 1
#define ERRORE 0

void leggere_sorgente();
void individuare_errori(int codice);
stringa estrarre_token();
bool scansionare_token(stringa token, int indice);
bool gestire_errore_sintattico();

#endif
