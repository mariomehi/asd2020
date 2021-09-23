/////////////////////////////////////////////////////////////////////
//
// Laboratorio 4: calcolo di semplici espressioni numeriche 
//                mediante pile e code
//
// vengono accettati dall'esterno solo numeri positivi.
// Per trattare anche numeri negativi occorre modificare
// l'analizzatore lessicale.
//
///////////////////////////////////////////////////////////////////


#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "token.h"

using std::cout;
using std::cin;
using std::string;
using std::istringstream;
using std::ostringstream;

/////////////////////////////////////////////////////////////////////
// Funzioni ausiliarie su tipi di dato semplici
/////////////////////////////////////////////////////////////////////

// da stringa a numero
int str2int(const string &s) {
  int n;
  istringstream itmp(s);
  itmp >> n;
  return n;
}

// da numero a stringa
string int2str(int n) {
  ostringstream otmp;
  otmp << n;
  string s = otmp.str();
  return s;
}

// ritorna false se e solo se token di tipo sconosciuto o se stringa vuota.
// se stringa non vuota, la stringa perde il pezzo iniziale,
// che diventa token.

bool prossimoToken(string &s, token &t) {
  unsigned int proxSpazio, i;

  // eliminare eventuali spazi iniziali
  for (i=0; i<s.size(); i++)
    if (s[i] != ' ')
      break;
  s.erase(0,i);
  // stringa vuota
  if (s.empty()) return false;
  // isola il token
  proxSpazio = s.find(" ",0);
  if (proxSpazio == string::npos) // non c'e' nessun " "
    proxSpazio = s.size();
  t.val = s.substr(0,proxSpazio);
  // la stringa perde il pezzo che diventa token
  s.erase(0,proxSpazio);

  // classificare il token, se sconosciuto restituire false.

  // togliamoci subito il caso frequente: token formato da 1 solo carattere
  if (t.val.size() == 1) {
    if (t.val[0] >= '0' && t.val[0] <= '9')
      t.k = NUMERO;
    else {
      switch (t.val[0]) {
        case '+':  t.k = OP_SOMMA; break;
        case '-':  t.k = OP_SOTTRAZIONE; break;
        case '*':  t.k = OP_MOLTIPLICAZIONE; break;
        case '(':  t.k = PARENTESI_APERTA; break;
        case ')':  t.k = PARENTESI_CHIUSA; break;
        default:   t.k = SCONOSCIUTO;
      }
    }
    return (t.k != SCONOSCIUTO);  // carattere diverso da NUMERO, +, -, *, (, )
  }
  
  // resta il caso di un token formato da 2 o piu' caratteri.
  // puo' solo essere NUMERO, oppure SCONOSCIUTO
  for (i=0; i<t.val.size(); i++)
    if (t.val[i] < '0' || t.val[i] > '9')
      break;
  if (i >= t.val.size()) {
    // ciclo for andato fino in fondo, solo caratteri numerici --> NUMERO
    t.k = NUMERO;
    return true;
  }
  // trovato almeno 1 carattere non numerico --> token SCONOSCIUTO
  t.k = SCONOSCIUTO;
  return false;
}

