#include "labo2_aux.h"


void scambia(vector<int>& v, int i, int j)
{ 
  int tmp = v[j];
  v[j] = v[i];
  v[i] = tmp;
}

/**************************************************************************************
				SELECTION SORT
***************************************************************************************/
void selectionSort(vector<int>& v)
{
   int current_min_index;
   unsigned int size = v.size();
   for (unsigned int i=0; i<size; ++i)
   { 
     current_min_index = i;
     for (unsigned int j=i+1;j<size; ++j)
        if (v[current_min_index] > v[j])
            current_min_index = j;
     scambia(v, i, current_min_index);
   }
}



/**************************************************************************************
				INSERTION SORT
***************************************************************************************/
void insertionSort(vector<int>& v)
{
   int current, prev;
   unsigned int size = v.size();
   for (unsigned int i=1; i<size; ++i)
   { current=i; 
     prev=i-1;
     while(prev>=0 && v[current]<v[prev])
        {
         scambia(v, current, prev);
         --current;
         --prev;
        }
   }
}


/**************************************************************************************
				BUBBLESORT
***************************************************************************************/
void bubbleSort(vector<int>& v)
{
   unsigned int size = v.size();
   bool scambiati;
   for (unsigned int i=1; i<size; ++i)
      {
      scambiati = false;
      for (unsigned int j=0; j<size-i; ++j)
          if(v[j]>v[j+1])
            { 
              scambia(v, j, j+1);
              scambiati = true;
            }
      if (!scambiati) return;
      }
}


/**************************************************************************************
				   MERGESORT
***************************************************************************************/
void fondi(vector<int>& v, unsigned int inizio, unsigned int centro, unsigned int fine)
{
   vector<int> vsinistra, vdestra;

   for (unsigned int i=inizio; i<=centro; ++i)
      vsinistra.push_back(v[i]);

   for (unsigned int i=centro+1; i<=fine; ++i)
      vdestra.push_back(v[i]);

   unsigned int indicesinistra = 0;
   unsigned int maxsin = vsinistra.size();
   unsigned int indicedestra = 0;
   unsigned int maxdes = vdestra.size();
   
   for (unsigned int i=inizio; i<=fine; ++i)
   {
      if (indicesinistra < maxsin && indicedestra < maxdes)
         {
         if (vsinistra[indicesinistra]<vdestra[indicedestra])
            {
             v[i] = vsinistra[indicesinistra];
             indicesinistra++; continue;
             }
         else
            { 
            v[i] = vdestra[indicedestra];
            indicedestra++; continue;
            }
         } 
      
      if (indicesinistra == maxsin && indicedestra < maxdes)
         { 
            v[i] = vdestra[indicedestra];
            indicedestra++; continue;
         }

       if (indicedestra == maxdes && indicesinistra < maxsin)
         { 
            v[i] = vsinistra[indicesinistra];
            indicesinistra++; continue;
         }         
   } 
}

void ms(vector<int>& v, unsigned int inizio, unsigned int fine)
{
    if (inizio < fine)
      {
          unsigned int centro = (inizio+fine)/2;
          ms(v, inizio, centro);
          ms(v, centro+1, fine);
          fondi(v, inizio, centro, fine);
      }
}


void mergeSort(vector<int>& v)
{  
   if (v.size() != 0) // necessario perche' ms prende come terzo parametro un unsigned int; se v.size() e' 0, v.size()-1 non e' correttamente rappresentabile come unsigned
      ms(v, 0, v.size()-1);
}


/**************************************************************************************
				QUICKSORT CON SCELTA "BANALE" DEL PIVOT
***************************************************************************************/

int partizionaInPlaceTrivial(vector<int>& v, int inizio, int fine)
{
   int pivotIndex = inizio; // scelgo il primo indice dell'array: sara' il mio pivot
   scambia(v, pivotIndex, inizio); // metto il pivot all'inizio della sequenza da riordinare - anche se sarebbe inutile vista la scelta fatta
   int i = inizio+1;
   for (int j=inizio+1; j<=fine; ++j)
       {
       if (v[j] < v[inizio]) // confronto con il pivot che e' all'inizio
          {
          scambia(v, i, j);
          ++i;
          }
       }
 scambia(v, inizio, i-1);
 return i-1;
}


void qsTrivial(vector<int>& v, int inizio, int fine)
{
    if (inizio < fine)
      {   
          int pivot_index=partizionaInPlaceTrivial(v, inizio, fine);
          qsTrivial(v, inizio, pivot_index-1);
          qsTrivial(v, pivot_index+1, fine);
      }
}

void quickSortTrivial(vector<int>& v)
{
   qsTrivial(v, 0, v.size()-1);
}




/**************************************************************************************
				QUICKSORT RANDOMIZZATO
***************************************************************************************/


int partizionaInPlace(vector<int>& v, int inizio, int fine)
{
   int pivotIndex = inizio+rand()%(fine-inizio+1); // scelgo un indice a caso tra inizio e fine: sara' il mio pivot
   scambia(v, pivotIndex, inizio); // metto il pivot all'inizio della sequenza da riordinare
   int i = inizio+1;
   for (int j=inizio+1; j<=fine; ++j)
       {
       if (v[j] < v[inizio]) // confronto con il pivot che e' all'inizio
          {
          scambia(v, i, j);
          ++i;
          }
       }
 scambia(v, inizio, i-1);
 return i-1;
}


void qs(vector<int>& v, int inizio, int fine)
{
    if (inizio < fine)
      {   
          int pivot_index=partizionaInPlace(v, inizio, fine);
          qs(v, inizio, pivot_index-1);
          qs(v, pivot_index+1, fine);
      }
}

void quickSortRandom(vector<int>& v)
{
   srand(time(NULL)); // srand ha un costo non trascurabile: poiché basta chiamarla una sola volta all'interno del programma per fissare il seme della 
                      // generazione pseudo-casuale, possiamo chiamarla in quickSortRandom prima di  qs(v, 0, v.size()-1) e non chiamarla più!
   qs(v, 0, v.size()-1);
}
