#include <stdio.h>
#include <string.h>
#include "../utility/array/matrice.h"
#include "../utility/stringa/stringa.h"
#include "../utility/bool.h"
#include "gestione_movimenti.h"
#include "../gestione_file/file_di_testo/lettura_file_testo.h"
#include "../inventario/gestione_inventario.h"
#include "../personaggio/personaggio.h"
#include "gestione_mappa.h"

void scrivere_x(posizione * posizione_personaggio, int x)
{
	posizione_personaggio->x = x;
}

void scrivere_y(posizione * posizione_personaggio, int y)
{
	posizione_personaggio->y = y;
}

int leggere_x(posizione posizione_personaggio)
{
	return posizione_personaggio.x;
}

int leggere_y(posizione posizione_personaggio)
{
	return posizione_personaggio.y;
}

stringa trovare_direzioni_disponibili()
{
	int cella_attuale;
	posizione posizione_nord;
	posizione posizione_sud;
	posizione posizione_est;
	posizione posizione_ovest;
	bool nord;
	bool sud;
	bool est;
	bool ovest;

	cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));

	stringa direzioni = "";
	direzioni = allocare_stringa(direzioni, 0);
	direzioni = scrivere_stringa(direzioni, "");
	direzioni = strcat(direzioni, "Direzioni disponibili: ");

	posizione_nord = posizione_sud = posizione_est = posizione_ovest = pos;

	scrivere_y(&posizione_nord, leggere_y(pos) - 1);
	scrivere_y(&posizione_sud, leggere_y(pos) + 1);
	scrivere_x(&posizione_est, leggere_x(pos) + 1);
	scrivere_x(&posizione_ovest, leggere_x(pos) - 1);

	if(cella_attuale % PORTA_CHIUSA_SFONDABILE == 0 || cella_attuale % PORTA_SEMPLICE == 0 || cella_attuale % PORTA_RE == 0)
	{
		nord = leggere_valore_matrice(mappa, leggere_y(pos) - 1, leggere_x(pos)) != MURO && (leggere_y(posizione_precedente) == leggere_y(posizione_nord) && leggere_x(posizione_precedente) == leggere_x(posizione_nord));
		sud = leggere_valore_matrice(mappa, leggere_y(pos) + 1, leggere_x(pos)) != MURO && (leggere_y(posizione_precedente) == leggere_y(posizione_sud) && leggere_x(posizione_precedente) == leggere_x(posizione_sud));
		est = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos) + 1) != MURO && (leggere_y(posizione_precedente) == leggere_y(posizione_est) && leggere_x(posizione_precedente) == leggere_x(posizione_est));
		ovest = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos) - 1) != MURO && (leggere_y(posizione_precedente) == leggere_y(posizione_ovest) && leggere_x(posizione_precedente) == leggere_x(posizione_ovest));
	}
	else
	{
		nord = leggere_valore_matrice(mappa, leggere_y(pos) - 1, leggere_x(pos)) != MURO;
		sud = leggere_valore_matrice(mappa, leggere_y(pos) + 1, leggere_x(pos)) != MURO;
		est = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos) + 1) != MURO;
		ovest = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos) - 1) != MURO;
	}


	if(nord)
		direzioni = strcat(direzioni, "NORD - ");
	if(sud)
		direzioni = strcat(direzioni, "SUD - ");
	if(est)
		direzioni = strcat(direzioni, "EST - ");
	if(ovest)
		direzioni = strcat(direzioni, "OVEST - ");

	direzioni[leggere_lunghezza(direzioni) - 3] = '\n';
	direzioni[leggere_lunghezza(direzioni) - 2] = '\0';

	return direzioni;
}

void muovere_personaggio(stringa direzione)
{
	stringa stringa_file = "";
	int cella_successiva;
	int cella_attuale;
	posizione posizione_nord;
	posizione posizione_sud;
	posizione posizione_est;
	posizione posizione_ovest;

	posizione_nord = posizione_sud = posizione_est = posizione_ovest = pos;

	scrivere_y(&posizione_nord, leggere_y(pos) - 1);
	scrivere_y(&posizione_sud, leggere_y(pos) + 1);
	scrivere_x(&posizione_est, leggere_x(pos) + 1);
	scrivere_x(&posizione_ovest, leggere_x(pos) - 1);

	cella_attuale = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos));

	if(confrontare_stringhe(direzione, "nord"))
	{
		cella_successiva = leggere_valore_matrice(mappa, leggere_y(pos) - 1, leggere_x(pos));
		if(cella_successiva != MURO)
		{
			if(cella_attuale % PORTA_CHIUSA_SFONDABILE == 0 || cella_attuale % PORTA_SEMPLICE == 0 || cella_attuale % PORTA_RE == 0)
			{
				if(leggere_y(posizione_precedente) != leggere_y(posizione_nord) || leggere_x(posizione_precedente) != leggere_x(posizione_nord))
				{
					rallentare_output("C'e' una porta chiusa davanti a te! Cerca un modo per superarla...\n", MILLISECONDI);
					rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
				}
				else
				{
					posizione_precedente = pos;
					scrivere_y(&pos, leggere_y(pos) - 1);
					rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
					printf("\n");
					gestire_cella();
				}
			}
			else
			{
				posizione_precedente = pos;
				scrivere_y(&pos, leggere_y(pos) - 1);
				rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
				printf("\n");
				gestire_cella();
			}
		}
		else
		{
			stringa_file = leggere_file_testo("storia/muri/muro1.txt", stringa_file);
			rallentare_output(stringa_file, MILLISECONDI);
		}
	}

	if(confrontare_stringhe(direzione, "sud"))
	{
		cella_successiva = leggere_valore_matrice(mappa, leggere_y(pos) + 1, leggere_x(pos));
		if(cella_successiva != MURO)
		{
			if(cella_attuale % PORTA_CHIUSA_SFONDABILE == 0 || cella_attuale % PORTA_SEMPLICE == 0 || cella_attuale % PORTA_RE == 0)
			{
				if(leggere_y(posizione_precedente) != leggere_y(posizione_sud) || leggere_x(posizione_precedente) != leggere_x(posizione_sud))
				{
					rallentare_output("C'e' una porta chiusa davanti a te! Cerca un modo per superarla...\n", MILLISECONDI);
					rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
				}
				else
				{
					posizione_precedente = pos;
					scrivere_y(&pos, leggere_y(pos) + 1);
					rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
					printf("\n");
					gestire_cella();
				}
			}
			else
			{
				posizione_precedente = pos;
				scrivere_y(&pos, leggere_y(pos) + 1);
				rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
				printf("\n");
				gestire_cella();
			}
		}
		else
		{
			stringa_file = leggere_file_testo("storia/muri/muro2.txt", stringa_file);
			rallentare_output(stringa_file, MILLISECONDI);
		}
	}

	if(confrontare_stringhe(direzione, "ovest"))
	{
		cella_successiva = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos) - 1);
		if(cella_successiva != MURO)
		{
			if(cella_attuale % PORTA_CHIUSA_SFONDABILE == 0 || cella_attuale % PORTA_SEMPLICE == 0 || cella_attuale % PORTA_RE == 0)
			{
				if(leggere_y(posizione_precedente) != leggere_y(posizione_ovest) || leggere_x(posizione_precedente) != leggere_x(posizione_ovest))
				{
					rallentare_output("C'e' una porta chiusa davanti a te! Cerca un modo per superarla...\n", MILLISECONDI);
					rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
				}
				else
				{
					posizione_precedente = pos;
					scrivere_x(&pos, leggere_x(pos) - 1);
					rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
					printf("\n");
					gestire_cella();
				}
			}
			else
			{
				posizione_precedente = pos;
				scrivere_x(&pos, leggere_x(pos) - 1);
				rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
				printf("\n");
				gestire_cella();
			}
		}
		else
		{
			stringa_file = leggere_file_testo("storia/muri/muro3.txt", stringa_file);
			rallentare_output(stringa_file, MILLISECONDI);
		}
	}

	if(confrontare_stringhe(direzione, "est"))
	{
		cella_successiva = leggere_valore_matrice(mappa, leggere_y(pos), leggere_x(pos) + 1);
		if(cella_successiva != MURO)
		{
			if(cella_attuale % PORTA_CHIUSA_SFONDABILE == 0 || cella_attuale % PORTA_SEMPLICE == 0 || cella_attuale % PORTA_RE == 0)
			{
				if(leggere_y(posizione_precedente) != leggere_y(posizione_est) || leggere_x(posizione_precedente) != leggere_x(posizione_est))
				{
					rallentare_output("C'e' una porta chiusa davanti a te! Cerca un modo per superarla...\n", MILLISECONDI);
					rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
				}
				else
				{
					posizione_precedente = pos;
					scrivere_x(&pos, leggere_x(pos) - 1);
					rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
					printf("\n");
					gestire_cella();
				}
			}
			else
			{
				posizione_precedente = pos;
				scrivere_x(&pos, leggere_x(pos) + 1);
				rallentare_output(trovare_direzioni_disponibili(), MILLISECONDI);
				printf("\n");
				gestire_cella();
			}
		}
		else
		{
			stringa_file = leggere_file_testo("storia/muri/muro4.txt", stringa_file);
			rallentare_output(stringa_file, MILLISECONDI);
		}
	}
}
