#include <cstddef> // serve per il NULL
#include <iostream>
#include <stdexcept>
#include <vector> 
#include <fstream> 
#include <chrono>

using namespace std::chrono;
using namespace std;

// Implementa LIST con liste doppiamente collegate, circolari, con sentinella, senza ordinamento
 
namespace list{
 
typedef int Elem;

struct node;

typedef node* List;

const int FINEINPUT = -1000000;
const int EMPTYELEM = -1000000;

/************************* operazioni stateful (con side effect) ******************************************/

void createEmpty(List&);    /* crea la lista vuota */
void clear(List&);          /* "smantella" la lista */
void set(int, Elem, List&); /* modifica l'elemento in posizione pos */
void add(int, Elem, List&); /* inserisce l'elemento in posizione pos, shiftando a destra gli altri elementi */
void addBack(Elem, List&);  /* inserisce l'elemento alla fine della lista */
void addFront(Elem, List&); /* inserisce l'elemento all'inizio della lista */
void removePos(int, List&); /* cancella l'elemento in posizione pos dalla lista  */

/************************* operazioni stateless (funzionali) ******************************************/

Elem get(int, const List&);	         /* restituisce l'elemento in posizione pos */
List setF(int pos, Elem e, const List&); /* modifica l'elemento in posizione pos */
List addF(int, Elem, const List&);       /* inserisce l'elemento in posizione pos, shiftando a destra gli altri elementi */
List addBackF(Elem, const List&);        /* inserisce l'elemento alla fine della lista */
List addFrontF(Elem, const List&);       /* inserisce l'elemento all'inizio della lista */
List removePosF(int, const List&);       /* cancella l'elemento in posizione pos dalla lista e restituisce la lista modificata */
List createEmpty();                      /* crea la lista vuota e la restituisce */
bool isEmpty(const List&);
int size(const List&);
}

list::List readFromFile(string);         /* legge il contenuto di una lista da file */
list::List readFromStdin();              /* legge il contenuto di una lista da standard input */
void print(const list::List&);           /* stampa la lista */
