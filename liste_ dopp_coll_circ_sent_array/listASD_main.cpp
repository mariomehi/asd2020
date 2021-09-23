// Cambiando l'header che includiamo nel main e compilando solo il file ausiliario corretto usiamo implementazioni diverse dello stesso TDD lista
// Si noti che il main non cambia anche se cambiamo l'implementazione del TDD, perché il main "non sa" come è stato implementato il TDD, ma solo quali operazioni mette a disposizione (information hiding)
// Compilare con g++ -ansi -Wall -std=c++11 listASD-dll_aux.cpp listASD_main.cpp -o  listASD-dll  per l'implementazione con puntatori
// Compilare con g++ -ansi -Wall -std=c++11 listASD-array_aux.cpp listASD_main.cpp -o  listASD-array  per l'implementazione con array
// Ricordarsi di commentare/decommentare l'include dell'header giusto

//#include "listASD-dll.h" 
#include "listASD-array.h" 

const int maxreg = 10;

const string menu = "\n\nSi hanno a disposizione 10 registri numerati da 0 a 9. I registri contengono delle liste (inizialmente vuote).\nSi selezioni l'operazione scelta e si inseriscano di seguito gli operandi richiesti.\na: lettura di una lista da file terminato da -1000000 (2 operandi: nome_file indice);\nb: lettura di una lista da standard input (1 operando: indice);\nc: inserimento di un elemento in una posizione data;\nd: inserimento di un elemento all'inizio di una lista; \ne: inserimento di un elemento alla fine di una lista; \nf: cancellazione di un elemento in posizione data; \ng: recupero dell'elemento in posizione data senza cancellarlo né modificarlo (2 operandi: posizione indice);  \nh: modifica dell'elemento in posizione data; \ni: verifica se la lista e' vuota (1 operando: indice);\nl: dimensione della lista (1 operando: indice); \nn: stampa (1 operando: indice);\no: stampa di tutti i registri (0 operandi);\np: mostra questo menu;\nq: terminazione.\n\n";


int main()
{
try {
vector<list::List> v(maxreg);
for (int j=0; j<maxreg; ++j)  // inizializzo i registri in modo che tutti contengano all'inizio la lista vuota
   list::createEmpty(v[j]);


list::Elem e;
int i, j, pos;
string nome_file;
high_resolution_clock::time_point t1, t2;
double duration;

cout << menu;
cout << "\nDigitare p per stampare il menu, q per terminare\n> ";
char ch;
cin >> ch;
while (ch!='q')
{
   switch(ch)
   {
   case 'a':
   cin >> nome_file;
   if (!cin) throw runtime_error("Errore inserimento nome file\n");
   cin >> i;
   if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
   t1 = high_resolution_clock::now();
   v[i] = readFromFile(nome_file);
   t2 = high_resolution_clock::now();
   duration = duration_cast<microseconds>( t2 - t1 ).count();
   cout << "\nLa lettura da file ha richiesto " << duration << " microsecondi\n";
   // print(v[i]);
   break;


   case 'b':
   cin >> i;
   if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
   v[i] = readFromStdin();
   print(v[i]);
   break;


   case 'c':
   cout << "\nPer operazione stateful (con side effect) digitare s seguito da posizione, elemento e indice; per operazione stateless (funzionale) digitare f seguito da posizione, elemento, indiceFrom e indiceTo > ";
   cin >> ch; 
   if (ch == 's') 
      {
       cin >> pos >> e >> i;
       if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
       list::add(pos, e, v[i]);
       print(v[i]);
      }
       else if (ch == 'f')
      {
       cin >> pos >> e >> i >> j;
       if (i<0 || i>=maxreg || j<0 || j>=maxreg) {cout << "\nIndice fuori range\n"; break;}
       v[j] = list::addF(pos, e, v[i]);
       cout << "\nLista in posizione " << i; print(v[i]);
       cout << "\nLista in posizione " << j; print(v[j]);
      }
   break;


  case 'd':
   cout << "\nPer operazione stateful (con side effect) digitare s seguito elemento e indice; per operazione stateless (funzionale) digitare f seguito da elemento, indiceFrom e indiceTo > ";
   cin >> ch; 
   if (ch == 's') 
      {
       cin >> e >> i;
       if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
       list::addFront(e, v[i]);
       print(v[i]);
      }
       else if (ch == 'f')
      {
       cin >> e >> i >> j;
       if (i<0 || i>=maxreg || j<0 || j>=maxreg) {cout << "\nIndice fuori range\n"; break;}
       v[j] = list::addFrontF(e, v[i]);
       cout << "\nLista in posizione " << i; print(v[i]);
       cout << "\nLista in posizione " << j; print(v[j]);
      }
   break;


   case 'e':
   cout << "\nPer operazione stateful (con side effect) digitare s seguito elemento e indice; per operazione stateless (funzionale) digitare f seguito da elemento, indiceFrom e indiceTo > ";
   cin >> ch; 
   if (ch == 's') 
      {
       cin >> e >> i;
       if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
       list::addBack(e, v[i]);
       print(v[i]);
      }
       else if (ch == 'f')
      {
       cin >> e >> i >> j;
       if (i<0 || i>=maxreg || j<0 || j>=maxreg) {cout << "\nIndice fuori range\n"; break;}
       v[j] = list::addBackF(e, v[i]);
       cout << "\nLista in posizione " << i; print(v[i]);
       cout << "\nLista in posizione " << j; print(v[j]);
      }
   break;

   case 'f':
   cout << "\nPer operazione stateful (con side effect) digitare s seguito da posizione e indice; per operazione stateless (funzionale) digitare f seguito da posizione, indiceFrom e indiceTo > ";
   cin >> ch; 
   if (ch == 's') 
      {
       cin >> pos >> i;
       if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
       list::removePos(pos, v[i]);
       print(v[i]);
      }
       else if (ch == 'f')
      {
       cin >> pos >> i >> j;
       if (i<0 || i>=maxreg || j<0 || j>=maxreg) {cout << "\nIndice fuori range\n"; break;}
       v[j] = list::removePosF(pos, v[i]);
       cout << "\nLista in posizione " << i; print(v[i]);
       cout << "\nLista in posizione " << j; print(v[j]);
      }
   break;

   case 'g':
   cin >> pos >> i;
   if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
   e = list::get(pos, v[i]);
   if (e != list::EMPTYELEM)
      {cout << "\nL'elemento in posizione " << pos << " della lista in posizione " << i << " e' " << e << endl; print(v[i]);}
   break;

   case 'h':
   cout << "\nPer operazione stateful (con side effect) digitare s seguito da posizione, elemento e indice; per operazione stateless (funzionale) digitare f seguito da posizione, elemento, indiceFrom e indiceTo > ";
   cin >> ch; 
   if (ch == 's') 
      {
       cin >> pos >> e >> i;
       if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
       list::set(pos, e, v[i]);
       print(v[i]);
      }
       else if (ch == 'f')
      {
       cin >> pos >> e >> i >> j;
       if (i<0 || i>=maxreg || j<0 || j>=maxreg) {cout << "\nIndice fuori range\n"; break;}
       v[j] = list::setF(pos, e, v[i]);
       cout << "\nLista in posizione " << i; print(v[i]);
       cout << "\nLista in posizione " << j; print(v[j]);
      }
   break;

   case 'i':
   cin >> i;
   if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
   if (list::isEmpty(v[i])) 
      cout << "\nLa lista in posizione " << i << " e' vuota\n";
   else 
      {cout << "\nLa lista in posizione " << i << " non e' vuota\n"; print(v[i]);}
   break;

   case 'l':
   cin >> i;
   if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
   cout << "\nLa dimensione della lista in posizione " << i << " e' " << list::size(v[i]) << endl;
   print(v[i]);
   break;

   case 'n':
   cin >> i;
   if (i<0 || i>=maxreg) {cout << "\nIndice fuori range\n"; break;}
   print(v[i]);
   break;

   case 'o':
   for (int i=0; i<maxreg; ++i)
       {
        cout << "\nLista in posizione " << i;
        print(v[i]);
       }
   break;

   case 'p': 
   cout << menu;
   break;

   default: 
   cout << "\nOpzione non valida\n";
   }

cout << "\nDigitare p per stampare il menu, q per terminare\n> ";
cin >> ch;
}
return 0;
} 
catch (runtime_error &msg) 
   {cerr << "Errore a runtime: " << msg.what() << endl;} 
catch (...) 
   {cerr << "Eccezione non riconosciuta\n";}
}
