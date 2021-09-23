#include "dictionary.h"

#include <math.h> // sqrt()

using namespace dict;

struct dict::cell {
        Elem	elem;
	cell	*next;
};


/****************************************************************/
int h1(Key s) // funzione di hash che considera unicamente il valore ascii del primo carattere della chiave (se esiste) e restituisce il resto della divisione di tale somma per tableDim 
{
 int asciiCode = 0;
 if (s.length()>0) asciiCode = s[0];
 return asciiCode % dict::tableDim;
}


/****************************************************************/
int h2(Key s) // funzione di hash che somma il codice ascii di ogni carattere nella chiave e restituisce il resto della divisione di tale somma per tableDim 
{
 int asciiCodeSum = 0;
 for (string::size_type i=0; i<s.length(); ++i)
      asciiCodeSum += s[i];

 return asciiCodeSum % dict::tableDim;
}


/****************************************************************/
int h(Key s)
{
   return h2(s); // modificare questa chiamata per sperimentare l'utilizzo di funzioni di hash diverse, definite prima
}


/****************************************************************/
Error dict::insertElem(const Key k, const Value v,  Dictionary& s)
{
   if (search(k, s) != emptyValue) return FAIL;
   Bucket temp = new cell;
   (temp->elem).key = k;
   (temp->elem).value = v;
   Bucket buck = s[h(k)];
   temp->next = buck;
   s[h(k)] = temp;
   // cout << "L'elemento con chiave *" << k << "* e' stato inserito nel bucket " << h(k) << endl; /* stampa di debug, da decommentare durante il testing */
   return OK;
}


/****************************************************************/
Error dict::deleteElem(const Key k, Dictionary& s)
{
  Bucket current = s[h(k)], prev = emptyBucket;
  while (current!=emptyBucket) {
        if ((current->elem).key == k)
           { 
           if (prev != emptyBucket) 
              prev->next = current->next;
           else 
              s[h(k)] = current->next;
           delete current;
           return OK;
           }
         else 
           {
              prev = current;
              current = current->next;
           }	
  }	
  return FAIL;  	
}


/****************************************************************/
Value dict::search(const Key k, const Dictionary& s)
{
  Bucket current = s[h(k)];
  while (current!=emptyBucket) {
        if ((current->elem).key == k)
           { 
             // cout << "L'elemento con chiave *" << k << "* e' stato trovato nel bucket " << h(k) << endl; /* stampa di debug, da decommentare durante il testing */
             return (current->elem).value;
           }   
         else 
           current = current->next;
         }		
  return emptyValue;  	
}


/****************************************************************/
Dictionary dict::createEmptyDict()
{
   Bucket* d = new Bucket[tableDim];
   for (int i=0; i < tableDim; ++i)
      d[i]=emptyBucket;
   return d;
}


/****************************************************************/
Dictionary readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    if (!ifs) {cout << "\nErrore apertura file, verificare di avere inserito un nome corretto\n"; return createEmptyDict();}  
    return readFromStream(ifs);
}


/****************************************************************/
Dictionary readFromStdin()
{
    cout << "\nInserire una sequenza di linee che rispettano la sintassi key: value.<enter>\nDigitare CTRL^ D per terminare l'inserimento\n";
    Dictionary d = readFromStream((std::cin));
// Questa serve per aggirare un bug di alcune versioni attuali di glibc.
    clearerr(stdin);
    return d;
}


/****************************************************************/
Dictionary readFromStream(istream& str)
{
    Dictionary d = createEmptyDict();     
    string key, kcopy;
    string value;
    getline (str, key, ':'); 
    getline (str, value); 
    while (!str.eof())  
        {     
        kcopy = key;
        removeBlanksAndLower(kcopy);   
        insertElem(kcopy, value, d);
        getline (str, key, ':'); 
        getline (str, value); 
        }
    str.clear();
    return d;
}


/****************************************************************/
int printBucket(Bucket b) // stampa il contenuto di un bucket e restituisce il numero di elementi in  quel bucket
{  
   int counter = 0;
   while(b!=emptyBucket) {
        counter++;
        cout << (b->elem).key << ": " << (b->elem).value << "\n"; 
	b=b->next;
	}
   return counter;	
}


/****************************************************************/
void print(const Dictionary& s)
// stampa il contenuto del dizionario ed anche informazioni su come sono stati organizzati gli elementi
{
int bucketDim[tableDim];
int totalElem = 0;
for (unsigned int i=0; i<tableDim; ++i)
   {
    cout << "\nBucket " << i << "\n\n";
    bucketDim[i] = printBucket(s[i]);
    totalElem += bucketDim[i]; 
   }
float means = totalElem/(float)tableDim;
float standardDevSum = 0;
for (unsigned int i=0; i<tableDim; ++i)
     standardDevSum += (bucketDim[i]-means)*(bucketDim[i]-means);
   
/* Lo scarto tipo, deviazione standard, o scarto quadratico medio e' un indice di dispersione statistico, vale a dire una stima della variabilita' di una popolazione di dati o di una variabile casuale.
Lo scarto tipo e' uno dei modi per esprimere la dispersione dei dati intorno ad un indice di posizione, quale puo' essere, ad esempio, la media aritmetica. */

cout << "\n===STATISTICHE SULL'ORGANIZZAZIONE DEL DIZIONARIO===\n";

for (unsigned int i=0; i<tableDim; ++i)
   cout << "\nBucket " << i << ": " << bucketDim[i] << " elementi";

cout << "\nIl numero totale di elementi memorizzati e' " << totalElem;
cout << "\nIl numero di bucket nel dizionario e' " << tableDim;
if (tableDim != 0) cout << "\nIl numero atteso di elementi per bucket e' " << means << "\nLa deviazione standard e' " << sqrt(standardDevSum/tableDim);
}
