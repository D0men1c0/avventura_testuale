#include "../utility/stringa/stringa.h"
#include "../utility/costanti.h"
#include "../gestione_file/file_di_testo/lettura_file_testo.h"
#include "../gestione_file/file_binari/scrittura_file_binari.h"

typedef struct
{
	stringa nome;
	int vita;
	int forza;
	int intelligenza;
}personaggio;

stringa leggere_nome(personaggio personaggio_nome);
void scrivere_nome(personaggio *personaggio_nome,stringa nome);
int leggere_vita(personaggio personaggio_vita);
void scrivere_vita(personaggio *personaggio_vita,int valore);
int leggere_forza(personaggio personaggio_forza);
void scrivere_forza(personaggio *personaggio_forza,int valore);
int leggere_intelligenza(personaggio personaggio_intelligenza);
void scrivere_intelligenza(personaggio *personaggio_intelligenza,int valore);
int controllare_valori_inseriti(int min,int max,stringa attributo);
void settare_valori_personaggio();
