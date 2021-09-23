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
#include <string>
#include <sstream>
#include <cstdlib>

#include "token.h"
#include "queue.h"
#include "stack.h"

using std::cout;
using std::cin;
using std::string;
using std::istringstream;
using std::ostringstream;

/////////////////////////////////////////////////////////////////////
// Funzioni principali: leggi() e calcola()
/////////////////////////////////////////////////////////////////////

bool leggi(const string &str, queue::Queue &codaToken) {

  token tok;

  // la funzione prossimoToken() usata dopo modifica la stringa. 
  // Pertanto serve una copia locale, onde evitare effetti collaterali al chiamante 
  // (che passa la stringa per riferimento).
  string localString = str;

  while (prossimoToken(localString,tok))
    queue::enqueue(tok, codaToken);

  // stringa consumata fino in fondo e ultimo token ok --> tutto a posto
  return ((localString.size() == 0) && (tok.k != SCONOSCIUTO));
}


bool calcola(queue::Queue codaToken, int &risultato) {

  token lastFive[5];
  token tok;
  stack::Stack tokStack = stack::EMPTYSTACK;
  int i, a, b, c;

  // finchè ci sono token nella coda spostali nella pila e calcola
  while (!queue::isEmpty(codaToken)) {
    tok = queue::dequeue(codaToken);
    
    stack::push(tok, tokStack);
    if (tok.k != PARENTESI_CHIUSA) continue;

    // fine sottoespressione, proviamo a calcolare seguendo l'algoritmo

    // estrazione ultimi 5 token
    for (i=4; i >= 0; i--) {
      lastFive[i].k = SCONOSCIUTO;
      lastFive[i] = stack::pop(tokStack); 
    }

    // controllo di sintassi
    if (lastFive[0].k != PARENTESI_APERTA) break;
    if (lastFive[1].k != NUMERO) break;
    if (lastFive[2].k != OP_SOMMA
      && lastFive[2].k != OP_SOTTRAZIONE
      && lastFive[2].k != OP_MOLTIPLICAZIONE) break;
    if (lastFive[3].k != NUMERO) break;
    if (lastFive[4].k != PARENTESI_CHIUSA) break;

    // sintassi ok, calcola risultato parziale
    a = str2int(lastFive[1].val);
    b = str2int(lastFive[3].val);
    switch (lastFive[2].k) {
      case OP_SOMMA:           c = a + b; break;
      case OP_SOTTRAZIONE:     c = a - b; break;
      case OP_MOLTIPLICAZIONE: c = a * b; break;
      default:                 exit (1); // ma non arrivera' mai qui!
    }

    // risultato parziale --> in cima allo stack
    tok.val = int2str(c);
    tok.k = NUMERO;
    stack::push(tok, tokStack);

  } // end while

  // uscito dal ciclo di analisi e calcolo.

  // se non ha consumato tutti i token dalla fifo --> errore di sintassi
  if (!queue::isEmpty(codaToken))
    return false;

  // dovrebbe essere rimasto un unico token sullo stack, di tipo NUMERO.
  // se non e' cosi' --> errore di sintassi
  tok = stack::pop(tokStack); 
  if (!stack::isEmpty(tokStack) || tok.k != NUMERO)
    return false;

  // nessun errore: trasformiamo la stringa in numero e modifichiamo risultato
  risultato = str2int(tok.val);
  return true;
}

/////////////////////////////////////////////////////////////////////
//                               MAIN
/////////////////////////////////////////////////////////////////////

int main() {

  string s;
  queue::Queue q;
  int r;

  cout << "Inserisci l'espressione che vuoi valutare:" << endl;
  getline(cin,s);

  if (!leggi(s,q)) {
    cout << "errore lessicale\n";
    exit(1);
  }
  
  if (!calcola(q,r)) {
    cout << "errore sintattico\n";
    exit(1);
  }
  
  cout << "risultato: " << r << "\n";
  exit(0);
}
