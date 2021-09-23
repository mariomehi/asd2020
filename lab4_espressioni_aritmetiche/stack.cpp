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

#include "stack.h"

using namespace stack;

struct stack::cell {
    Elem	elem;
    cell	*next;
};

/****************************************************************/
bool stack::isEmpty(const Stack& s)
{
    return (s==EMPTYSTACK);
}
/****************************************************************/
void stack::push(const Elem x, Stack& s) 
{
    cell *aux = new cell; 
    aux->elem=x;
    aux->next=s;
    s = aux;
}
/****************************************************************/
Elem stack::pop(Stack& s)
{
    if (isEmpty(s)) return EMPTYELEM;
   
    cell* cur=s;
    s=s->next;
    Elem e = cur->elem;
    delete cur;
    return e;
}
/****************************************************************/

