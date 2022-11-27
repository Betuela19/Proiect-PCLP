#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED
#include "data.h"


typedef struct masina *MASINA;
typedef struct lista *LISTA;

LISTA newl();
LISTA ins_la_urma(LISTA l, int idu, char *numec, char *combustibil, char *culoarem,int nr_locuri,int km, int pretm);
int nrMasini(LISTA l);
bool isEmptyl(LISTA l);
bool isFull(LISTA l);
char *toStringl(LISTA l,char *s);
void destroyl(LISTA l);
LISTA adauga_masina ( LISTA l);
LISTA citirefisier();
void administrator();



LISTA remove_ultimul(LISTA l);
LISTA remove_primul(LISTA l);
LISTA sterge_masina(LISTA l);

void client();
void preluare_date_client();
void numar_tel();
void parola();
void confirmare();

void adaugafisier(LISTA l);
#endif // CAR_H_INCLUDED
