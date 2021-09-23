/////////////////////////////////////////////////////////////////////
//
// Laboratorio 4: calcolo di semplici espressioni numeriche 
//                mediante pile e code
//
// vengono accettati dall'esterno solo numeri positivi.
// Per trattare anche numeri negativi occorre modificare
// l'analizzatore lessicale.
//
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdexcept>

#include "token.h"
	
using namespace std;

// Implementa QUEUE con strutture indicizzate (array dinamici)
 
namespace queue{

const int BLOCKDIM = 1000;

// Gli elementi della QUEUE sono token
typedef token Elem;       

struct queue{
    Elem* queue = new Elem[BLOCKDIM];
    int size = 0;
    int maxsize = BLOCKDIM;
};

typedef queue Queue;

bool isEmpty(const Queue&);
void enqueue(Elem, Queue&);  /* inserisce l'elemento alla fine della lista */
Elem dequeue(Queue&);        /* cancella l'elemento in prima posizione (se esiste) e lo restituisce */
}
